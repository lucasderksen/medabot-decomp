"""Check original action, motion, piece-list and tile-animation consumers.

Script tests check linear stored positions through opcode 01, not execution of
the action handlers. Motion runs without stubs. Graphic decode, BIOS copies,
sound and the selection-update helper are explicitly stubbed/recorded; this is
not a rendering, audio or random-number-quality check.
"""
import argparse
import hashlib
import itertools
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

BASE = 0x08000000
WORK = 0x03001800
TYPED = 0x03000440
OBJECT = 0x03002C30


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=Path("build/analysis/action-scene-cpu.json"))
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    cpu = RoutineCpu(rom)
    state = {"calls": []}
    counts = {"byte_script_positions": 0, "halfword_script_positions": 0,
              "motion_cases": 0, "piece_loaders": 0, "piece_palettes": 0,
              "animation_ticks": 0, "selection_cases": 0}

    def hook(machine, address, size, user_data):
        names = {0x08044B28: "decode", 0x0807CCC0: "fast_copy", 0x0807CCC4: "copy",
                 0x08074DE0: "sound", 0x080424B8: "selection_update"}
        if address not in names:
            return
        values = tuple(machine.reg_read(getattr(arm_const, f"UC_ARM_REG_R{i}")) for i in range(3))
        if names[address] == "sound":
            state["calls"].append(("sound", values[0]))
        elif names[address] != "selection_update":
            state["calls"].append((names[address], *values[:2 if names[address] == "decode" else 3]))
        machine.reg_write(arm_const.UC_ARM_REG_R0, 0)
        machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)

    def call(address, arguments=()):
        state["calls"] = []
        registers = cpu.call(address, arguments, instruction_limit=100000, timeout_us=0)
        if any(registers[i] != (0xAB000000 | i) for i in range(4, 12)):
            raise ValueError(f"Saved register changed at {address:08X}")
        if cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) != 0x03007F00:
            raise ValueError("Stack pointer changed")
        return registers[0]

    for unit, directory, length_base, slot, cursor, phase, output, capture, advance, counter in (
        (1, 0x3C6CA8, 0x3C6EB8, 0xA8, 0xBC, 0xAA, 0xAC, 0x08034EB8, 0x08034F08, "byte_script_positions"),
        (2, 0x3CE164, 0x3CE374, 0xF9, 0x100, None, 0x102, 0x0803D450, 0x0803D4AC, "halfword_script_positions"),
    ):
        roots = struct.unpack_from("<132I", rom, directory)
        for index, root in enumerate(roots):
            position = 0
            for step in range(2000):
                address = root - BASE + position * unit
                opcode = int.from_bytes(rom[address:address + unit], "little")
                if opcode >= (144 if unit == 1 else 156):
                    raise ValueError("Opcode beyond stored parameter table")
                length = rom[length_base + opcode]
                expected = bytearray([0x5A] * 0x180)
                expected[slot] = index
                struct.pack_into("<H", expected, cursor, position)
                cpu.write(WORK, bytes(expected))
                if unit == 1 and call(0x08034E94) != opcode:
                    raise ValueError("Byte opcode read differs")
                expected[output:output + length * unit] = rom[address + unit:address + (length + 1) * unit]
                call(capture)
                if cpu.read(WORK, len(expected)) != expected:
                    raise ValueError(f"Parameter capture differs: slot {index}, cursor {position}")
                if phase is not None:
                    expected[phase] = 0
                position = (position + length + 1) & 65535
                struct.pack_into("<H", expected, cursor, position)
                call(advance)
                if cpu.read(WORK, len(expected)) != expected:
                    raise ValueError("Script advancement differs")
                counts[counter] += 1
                if opcode == 1:
                    break
            else:
                raise ValueError("Script control boundary was not reached")

    motion_cases = itertools.chain(
        itertools.product(range(1, 32), range(32), range(4), (0, 255)),
        ((g, direction, frame, 255) for g in (0, 32, 255) for direction in (0, 31, 255) for frame in (0, 255)),
    )
    for group, direction, frame, position in motion_cases:
        expected = bytearray([0xA5] * 64)
        struct.pack_into("<hh", expected, 2, position, position)
        expected[0x24], expected[0x25], expected[0x27] = group, direction, frame
        cpu.write(OBJECT, bytes(expected))
        if group:
            index = (group - 1) * 256 + direction * 8 + (frame & 3) * 2
            y, x = struct.unpack_from("<2h", rom, 0x3C6F78 + index * 2)
            struct.pack_into("<HH", expected, 2, (position + x) & 511, (position + y) & 255)
            expected[0x27] = (frame + 1) & 255
        call(0x0804422C, (0,))
        if cpu.read(OBJECT, 64) != expected:
            raise ValueError("Motion delta or position mask differs")
        counts["motion_cases"] += 1

    pieces = struct.unpack_from("<132I", rom, 0x3CE600)
    for root in pieces:
        expected_calls, offset, destination = [], root - BASE, 0x02000000
        entries = []
        while (units := struct.unpack_from("<H", rom, offset)[0]) != 0:
            asset = struct.unpack_from("<H", rom, offset + 2)[0]
            source = struct.unpack_from("<I", rom, 0x3B2704 + asset * 8)[0]
            expected_calls.append(("decode", source, destination))
            entries.append(asset)
            destination += units * 32
            offset += 4
        index = counts["piece_loaders"]
        call(0x0801BC5C, (index,))
        if state["calls"] != expected_calls:
            raise ValueError("Graphic-piece loader requests differ")
        counts["piece_loaders"] += 1
        # Include the zero halfword's following asset read, as done by 1BCE4.
        for entry in range(len(entries) + 1):
            asset = struct.unpack_from("<H", rom, root - BASE + entry * 4 + 2)[0]
            source = struct.unpack_from("<I", rom, 0x3B2708 + asset * 8)[0]
            call(0x0801BCE4, (index, entry, 3))
            if state["calls"] != [("fast_copy", source, 0x05000060, 8)]:
                raise ValueError("Graphic-piece palette request differs")
            counts["piece_palettes"] += 1

    animations = struct.unpack_from("<37I", rom, 0x3CEDF4)
    for root, routine, mode in itertools.product(animations, (0x0801BD58, 0x0801BFB4), (0, 1)):
        expected = bytearray([0x5A] * 0x140)
        base, width = struct.unpack_from("<2H", rom, root - BASE)
        cpu.write(TYPED, bytes(expected))
        call(0x0801BD1C, (root, mode, 0))
        expected[0x64:0x6C] = struct.pack("<4B2H", 0, 2, 0, mode, base, width)
        if cpu.read(TYPED, len(expected)) != expected:
            raise ValueError("Animation initialization differs")
        for tick in range(256):
            wanted = []
            if expected[0x66] != 255:
                for step in range(100):
                    if expected[0x64]:
                        expected[0x64] -= 1
                        break
                    position = expected[0x65]
                    opcode = struct.unpack_from("<H", rom, root - BASE + position * 2)[0]
                    if opcode & 255 == 255:
                        expected[0x66] = 255
                        break
                    argument = struct.unpack_from("<H", rom, root - BASE + (position + 1) * 2)[0]
                    if opcode & 255 == 253:
                        wanted.append(("sound", argument))
                        expected[0x65] = (position + 2) & 255
                    elif opcode & 255 == 254:
                        expected[0x65] = (argument * 2) & 255
                    else:
                        expected[0x64] = opcode & 255
                        source = 0x02000000 + base * 32 + width * argument * 32
                        destination = (0x06004000 + mode * 0x1200 if routine == 0x0801BD58 else
                                       0x06010000 + mode * 32)
                        wanted.append(("copy", source, destination, (width << 3) | 0x04000000))
                        expected[0x65] = (position + 2) & 255
                else:
                    raise ValueError("Animation failed to yield")
            call(routine, (root, 0))
            if cpu.read(TYPED, len(expected)) != expected or state["calls"] != wanted:
                raise ValueError(f"Tile animation differs: {root:08X}, routine {routine:08X}, tick {tick}")
            counts["animation_ticks"] += 1

    for kind, selection, index in itertools.product((0, 1, 2, 3, 4, 255), (0, 1, 2, 3, 255), range(256)):
        expected = bytearray([0x5A] * 0x140)
        expected[0x8C] = index
        cpu.write(TYPED, bytes(expected))
        group = min(kind, 4)
        table = 0x3CEE88 + selection * 128 if group == 0 else 0x3CF008 + ((group - 1) * 3 + selection) * 64
        value = rom[table + (index & (127 if group == 0 else 63))] if selection <= 2 else 0
        if call(0x08037578, (kind, selection)) != value or cpu.read(TYPED, len(expected)) != expected:
            raise ValueError("Selection table result differs")
        counts["selection_cases"] += 1
    report = {"rom_sha256": hashlib.sha256(rom).hexdigest(), "cases": counts,
              "stubs": ["08044B28 decode", "0807CCC0 CpuFastSet", "0807CCC4 CpuSet",
                        "08074DE0 sound", "080424B8 selection update"], "scope": __doc__}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
