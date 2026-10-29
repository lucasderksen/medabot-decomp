"""Run a portable mGBA libretro core without a GUI and trace canonical GBA RAM.

This optional research frontend uses libretro API version 1. It captures frames
and state changes, but does not persist cartridge saves or load an external BIOS.
See docs/EMULATION.md for the core provenance and validation limits.
"""

import argparse
import ctypes as ct
import hashlib
import json
from pathlib import Path
import struct
import sys
import zlib

from common import ROOT, find_rom

CORE = ROOT / "tools/downloads/libretro/mgba_libretro.dll"
CORE_SHA256 = "6af3783821b69bba6cad654cf73f3e1fceb3b2549dbb933a47ff20ba88f49bfa"
BUTTONS = dict(B=0, SELECT=2, START=3, UP=4, DOWN=5, LEFT=6, RIGHT=7, A=8, L=10, R=11)


class SystemInfo(ct.Structure):
    _fields_ = [("name", ct.c_char_p), ("version", ct.c_char_p),
                ("extensions", ct.c_char_p), ("need_fullpath", ct.c_bool),
                ("block_extract", ct.c_bool)]


class GameInfo(ct.Structure):
    _fields_ = [("path", ct.c_char_p), ("data", ct.c_void_p),
                ("size", ct.c_size_t), ("meta", ct.c_char_p)]


class Variable(ct.Structure):
    _fields_ = [("key", ct.c_char_p), ("value", ct.c_char_p)]


class MemoryDescriptor(ct.Structure):
    _fields_ = [("flags", ct.c_uint64), ("ptr", ct.c_void_p),
                ("offset", ct.c_size_t), ("start", ct.c_size_t),
                ("select", ct.c_size_t), ("disconnect", ct.c_size_t),
                ("length", ct.c_size_t), ("addrspace", ct.c_char_p)]


class MemoryMap(ct.Structure):
    _fields_ = [("descriptors", ct.POINTER(MemoryDescriptor)), ("count", ct.c_uint)]


ENVIRONMENT = ct.CFUNCTYPE(ct.c_bool, ct.c_uint, ct.c_void_p)
VIDEO = ct.CFUNCTYPE(None, ct.c_void_p, ct.c_uint, ct.c_uint, ct.c_size_t)
AUDIO = ct.CFUNCTYPE(None, ct.c_int16, ct.c_int16)
AUDIO_BATCH = ct.CFUNCTYPE(ct.c_size_t, ct.POINTER(ct.c_int16), ct.c_size_t)
INPUT_POLL = ct.CFUNCTYPE(None)
INPUT_STATE = ct.CFUNCTYPE(ct.c_int16, ct.c_uint, ct.c_uint, ct.c_uint, ct.c_uint)


def png_rgb(path, width, height, rgb):
    """Write exact RGB pixels with only standard-library PNG encoding."""
    if len(rgb) != width * height * 3:
        raise ValueError("RGB buffer dimensions disagree")

    def chunk(kind, data):
        return struct.pack(">I", len(data)) + kind + data + struct.pack(">I", zlib.crc32(kind + data))

    rows = b"".join(b"\0" + rgb[y * width * 3:(y + 1) * width * 3] for y in range(height))
    path.write_bytes(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0))
                     + chunk(b"IDAT", zlib.compress(rows)) + chunk(b"IEND", b""))


def rgb_pixels(raw, width, height, pitch, pixel_format):
    output = bytearray(width * height * 3)
    bytes_per_pixel = 4 if pixel_format == 1 else 2
    if pixel_format not in (0, 1, 2) or pitch < width * bytes_per_pixel:
        raise ValueError("Unsupported or inconsistent libretro pixel format")
    if width < 1 or height < 1 or len(raw) < (height - 1) * pitch + width * bytes_per_pixel:
        raise ValueError("Truncated or invalid libretro frame")
    for y in range(height):
        for x in range(width):
            at = y * pitch + x * bytes_per_pixel
            value = int.from_bytes(raw[at:at + bytes_per_pixel], sys.byteorder)
            if pixel_format == 1:
                red, green, blue = (value >> 16) & 255, (value >> 8) & 255, value & 255
            else:
                green_bits = 6 if pixel_format == 2 else 5
                red = (value >> (5 + green_bits)) & 31
                green = (value >> 5) & ((1 << green_bits) - 1)
                blue = value & 31
                red = red * 255 // 31
                green = green * 255 // ((1 << green_bits) - 1)
                blue = blue * 255 // 31
            dst = (y * width + x) * 3
            output[dst:dst + 3] = bytes((red, green, blue))
    return bytes(output)


class Emulator:
    def __init__(self, core_path, output_dir):
        digest = hashlib.sha256(core_path.read_bytes()).hexdigest()
        if digest != CORE_SHA256:
            raise ValueError(f"Unrecognized mGBA core SHA-256: {digest}")
        self.core = ct.CDLL(str(core_path))
        self.output_dir = output_dir
        self.directory = str(output_dir).encode("utf-8")
        self.options = {b"mgba_use_bios": b"OFF", b"mgba_skip_bios": b"ON",
                        b"mgba_idle_optimization": b"Don't Remove"}
        self.maps = []
        self.pixel_format = 0
        self.framebuffer = None
        self.buttons = set()
        self.callback_errors = []
        self.loaded = False
        self.initialized = False
        self.callbacks = [ENVIRONMENT(self.environment), VIDEO(self.video),
                          AUDIO(lambda left, right: None), AUDIO_BATCH(lambda data, frames: frames),
                          INPUT_POLL(lambda: None), INPUT_STATE(self.input_state)]
        for name, callback in zip(("environment", "video_refresh", "audio_sample", "audio_sample_batch",
                                   "input_poll", "input_state"), self.callbacks):
            fn = getattr(self.core, "retro_set_" + name)
            fn.argtypes = [type(callback)]
            fn.restype = None
            fn(callback)
        self.core.retro_api_version.restype = ct.c_uint
        if self.core.retro_api_version() != 1:
            raise ValueError("Unsupported libretro API version")
        self.core.retro_get_system_info.argtypes = [ct.POINTER(SystemInfo)]
        self.core.retro_get_system_info.restype = None
        self.info = SystemInfo()
        self.core.retro_get_system_info(ct.byref(self.info))
        self.core.retro_load_game.argtypes = [ct.POINTER(GameInfo)]
        self.core.retro_load_game.restype = ct.c_bool
        for name in ("init", "run", "reset", "unload_game", "deinit"):
            getattr(self.core, "retro_" + name).argtypes = []
            getattr(self.core, "retro_" + name).restype = None
        self.core.retro_init()
        self.initialized = True

    def environment(self, command, data):
        try:
            command &= ~0x10000  # The API marks several commands experimental.
            if command in (9, 31):  # System/save directory: local empty research output.
                ct.cast(data, ct.POINTER(ct.c_char_p))[0] = self.directory
                return True
            if command == 10:
                self.pixel_format = ct.cast(data, ct.POINTER(ct.c_uint))[0]
                return self.pixel_format in (0, 1, 2)
            if command == 15:
                var = ct.cast(data, ct.POINTER(Variable)).contents
                if var.key not in self.options:
                    return False
                var.value = self.options[var.key]
                return True
            if command == 16:
                variables = ct.cast(data, ct.POINTER(Variable))
                for i in range(1024):
                    var = variables[i]
                    if not var.key:
                        return True
                    if var.value and b";" in var.value:
                        default = var.value.split(b";", 1)[1].strip().split(b"|", 1)[0]
                        self.options.setdefault(var.key, default)
                raise ValueError("Unterminated core option list")
            if command in (3, 17):
                ct.cast(data, ct.POINTER(ct.c_bool))[0] = command == 3
                return True
            if command == 36:
                mapping = ct.cast(data, ct.POINTER(MemoryMap)).contents
                if mapping.count > 128:
                    raise ValueError("Unexpected memory descriptor count")
                # mGBA supplies descriptors on its stack. Copy them immediately.
                self.maps = [MemoryDescriptor.from_buffer_copy(mapping.descriptors[i]) for i in range(mapping.count)]
                return True
            if command == 47:
                ct.cast(data, ct.POINTER(ct.c_int))[0] = 3
                return True
            if command == 52:
                ct.cast(data, ct.POINTER(ct.c_uint))[0] = 0
                return True
            if command in (1, 11, 18, 32, 35, 37):
                return True
            return False
        except Exception as error:
            self.callback_errors.append(str(error))
            return False

    def video(self, data, width, height, pitch):
        if data:
            if width > 1024 or height > 1024 or pitch > 8192:
                self.callback_errors.append("Unexpected video buffer dimensions")
                return
            self.framebuffer = (ct.string_at(data, pitch * height), width, height, pitch, self.pixel_format)

    def input_state(self, port, device, index, button):
        return int(port == 0 and device == 1 and index == 0 and button in self.buttons)

    def load(self, rom_path):
        self.rom_bytes = rom_path.read_bytes()
        self.rom_buffer = ct.create_string_buffer(self.rom_bytes)
        self.rom_path = str(rom_path).encode("utf-8")
        game = GameInfo(self.rom_path, ct.cast(self.rom_buffer, ct.c_void_p), len(self.rom_bytes), None)
        if not self.core.retro_load_game(ct.byref(game)):
            raise ValueError("mGBA refused the supplied ROM")
        self.loaded = True

    def read(self, address, size):
        # Only canonical, unmapped ranges are requested here; aliases are not used.
        for mapping in self.maps:
            if mapping.ptr and mapping.start <= address and address + size <= mapping.start + mapping.length:
                return ct.string_at(mapping.ptr + mapping.offset + address - mapping.start, size)
        raise ValueError(f"No canonical mapped range for {address:08X}+{size}")

    def state(self):
        return dict(main=struct.unpack("<I", self.read(0x0300178C, 4))[0],
                    substate=struct.unpack("<I", self.read(0x03002B8C, 4))[0],
                    callback=struct.unpack("<I", self.read(0x0300137C, 4))[0],
                    render=struct.unpack("<I", self.read(0x03000430, 4))[0])

    def capture(self, filename):
        if not self.framebuffer:
            return False
        raw, width, height, pitch, pixel_format = self.framebuffer
        png_rgb(self.output_dir / filename, width, height, rgb_pixels(raw, width, height, pitch, pixel_format))
        return True

    def close(self):
        if self.loaded:
            self.core.retro_unload_game()
            self.loaded = False
        if self.initialized:
            self.core.retro_deinit()
            self.initialized = False


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom")
    parser.add_argument("--core", type=Path, default=CORE)
    parser.add_argument("--frames", type=int, default=600)
    parser.add_argument("--inputs", type=Path, help="JSON list of {start,end,buttons}; frame bounds inclusive")
    parser.add_argument("--capture", default="1,60,120,240,600", help="Comma-separated frame numbers")
    parser.add_argument("--output-dir", type=Path, default=ROOT / "build/emulator/boot")
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if not output.is_relative_to(ROOT / "build") or not 1 <= args.frames <= 100000:
        raise ValueError("Use a build/ output directory and 1..100000 frames")
    output.mkdir(parents=True, exist_ok=True)
    schedule = json.loads(args.inputs.read_text()) if args.inputs else []
    for event in schedule:
        if not 1 <= event["start"] <= event["end"] <= args.frames:
            raise ValueError("Input events must have ordered bounds within the run")
        event["buttons"] = [name.upper() for name in event["buttons"]]
        if any(name not in BUTTONS for name in event["buttons"]):
            raise ValueError("Unknown input button")
    captures = {int(item) for item in args.capture.split(",") if item}
    emulator = Emulator(args.core, output)
    transitions = []
    try:
        rom = find_rom(args.rom)
        emulator.load(rom)
        previous = None
        for frame in range(1, args.frames + 1):
            emulator.buttons = {BUTTONS[name] for event in schedule if event["start"] <= frame <= event["end"] for name in event["buttons"]}
            emulator.core.retro_run()
            if emulator.callback_errors:
                raise RuntimeError("; ".join(emulator.callback_errors))
            state = emulator.state()
            if state != previous:
                filename = f"state-{frame:06d}.png"
                emulator.capture(filename)
                transitions.append(dict(frame=frame, **state, image=filename))
                print(f"Frame {frame}: {state}", flush=True)
                previous = state
            if frame in captures:
                emulator.capture(f"frame-{frame:06d}.png")
        emulator.capture("last.png")
        report = dict(core=emulator.info.name.decode(), version=emulator.info.version.decode(),
                      core_sha256=CORE_SHA256, rom_sha256=hashlib.sha256(emulator.rom_bytes).hexdigest(),
                      frames=args.frames, inputs=schedule, options={k.decode(): v.decode() for k, v in emulator.options.items()},
                      memory=[dict(start=f"0x{m.start:08X}", size=m.length, flags=m.flags) for m in emulator.maps],
                      transitions=transitions, final_state=emulator.state())
        (output / "trace.json").write_text(json.dumps(report, indent=2) + "\n")
        print(f"Saved {len(transitions)} state changes and final frame to {output}")
    finally:
        emulator.close()
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (ValueError, OSError, RuntimeError) as error:
        print(f"Emulator trace failed: {error}", file=sys.stderr)
        sys.exit(1)
