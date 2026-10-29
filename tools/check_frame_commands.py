"""Compare a bounded frame-command inventory with original Thumb execution.

This executes 08040B90/08040BD8 on an isolated CPU. Sound dispatch 08074DE0
is stubbed, recording only its IDs; audio/device behavior is not simulated.
"""

import argparse
import hashlib
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn
from frame_commands import analyze, initialize, tick

OBJECTS = 0x03002C30
SELECTED = 7


def check(cpu, commands, address, ticks, sound_ids):
    analysis = analyze(commands)
    cpu.write(OBJECTS, bytes(128 * 64))
    cpu.write(OBJECTS, struct.pack("<H", 0xC123))
    state = initialize(commands)
    cpu.call(0x08040B90, (address, SELECTED), instruction_limit=20000, timeout_us=0)
    expected = bytearray(64)
    struct.pack_into("<H", expected, 6, state.frame)
    if cpu.read(OBJECTS + SELECTED * 64, 64) != expected:
        raise ValueError(f"Initializer differs at {address:#x}")
    flags = 0xC123
    sounds_seen = 0
    for number in range(ticks):
        flags, expected_sounds = tick(commands, state, flags)
        sound_ids.clear()
        cpu.call(0x08040BD8, (address, SELECTED), instruction_limit=20000, timeout_us=0)
        sounds_seen += len(expected_sounds)
        struct.pack_into("<H", expected, 6, state.frame)
        expected[0x20:0x23] = bytes((state.delay, state.offset, state.stopped))
        zero = bytearray(64)
        struct.pack_into("<H", zero, 0, flags)
        if cpu.read(OBJECTS + SELECTED * 64, 64) != expected or cpu.read(OBJECTS, 64) != zero:
            raise ValueError(f"Frame state differs at {address:#x}, tick {number}")
        if sound_ids != expected_sounds:
            raise ValueError(f"Sound request differs at {address:#x}, tick {number}")
        if cpu.read(OBJECTS + 64, 6 * 64) != bytes(6 * 64) or cpu.read(OBJECTS + 8 * 64, 120 * 64) != bytes(120 * 64):
            raise ValueError("Neighboring frame object changed")
    return {"address": hex(address), "bytes": len(commands), "ticks": ticks,
            "reachable_commands": len(analysis["nodes"]), "sound_requests": sounds_seen,
            "sha256": hashlib.sha256(commands).hexdigest()}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=lambda x: int(x, 0), default=0x083B6100)
    parser.add_argument("--count", type=int, default=118)
    parser.add_argument("--ticks", type=int, default=256)
    parser.add_argument("--output", default="build/analysis/frame-command-cpu.json")
    args = parser.parse_args()
    if args.count < 1 or args.ticks < 1:
        parser.error("count and ticks must be positive")
    rom = find_rom().read_bytes()
    root = args.root - 0x08000000
    if root < 0 or root + args.count * 4 > len(rom):
        parser.error("root table is outside ROM")
    values = struct.unpack_from(f"<{args.count}I", rom, root)
    starts = sorted(set(value - 0x08000000 for value in values))
    if not all(0 <= start < root for start in starts):
        parser.error("payload roots must precede the root table")
    cpu = RoutineCpu(rom)
    sound_ids = []

    def sound_stub(engine, address, size, user_data):
        sound_ids.append(engine.reg_read(arm_const.UC_ARM_REG_R0))
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, sound_stub, begin=0x08074DE0, end=0x08074DE0)
    results = []
    for index, start in enumerate(starts):
        end = starts[index + 1] if index + 1 < len(starts) else root
        results.append(check(cpu, rom[start:end], 0x08000000 + start, args.ticks, sound_ids))
        if (index + 1) % 20 == 0:
            print(f"{index + 1}/{len(starts)} frame streams agree.", flush=True)
    synthetic = bytes([0xFC, 0xA5, 0x5A, 1, 0x12, 0x34, 0xFB, 2, 0,
                       0xFD, 9, 0, 1, 0x12, 0x34, 0xFE, 4])
    cpu.write(0x02010000, synthetic)
    synthetic_result = check(cpu, synthetic, 0x02010000, args.ticks, sound_ids)
    report = {"rom_sha256": hashlib.sha256(rom).hexdigest(), "root": hex(args.root),
              "root_count": args.count, "unique_streams": len(starts), "results": results,
              "synthetic_flag_sound_loop_case": synthetic_result,
              "note": "Isolated original Thumb CPU check; sound dispatch stub records IDs only."}
    output = Path(args.output)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"{len(results)} original streams and one synthetic control case agree for {args.ticks} ticks each.")


if __name__ == "__main__":
    main()
