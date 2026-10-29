"""Check scene animation state and unconditional ROM prefetch against Thumb.

Executes original 08049440. Sound and BIOS decompression calls are recorded and
stubbed; this is not a graphics/audio playback check. The model reads all four
halfwords before dispatch, including adjacent ROM after abbreviated records.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct

from common import find_rom, load_segments
from cpu import RoutineCpu, arm_const, unicorn

BASE = 0x08000000
OBJECT = 0x03002C30


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=Path("build/analysis/scene-animation-cpu.json"))
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    roots = struct.unpack_from("<128I", rom, 0x3F7B80)
    cpu = RoutineCpu(rom)
    functions = {s["start"] + BASE for s in load_segments()
                 if s.get("category") != "data" and s["start"] < 0x7E868}
    functions.add(0x0807CCD8)  # BIOS LZ77 VRAM wrapper inside the shared runtime section.
    state = {"prefetch": [], "calls": []}

    def hook(engine, address, size, user_data):
        if address == 0x08049462:
            state["prefetch"].append(engine.reg_read(arm_const.UC_ARM_REG_R0))
        elif address in functions and address != 0x08049440:
            if address == 0x08047BA8:
                state["calls"].append(("sound", engine.reg_read(arm_const.UC_ARM_REG_R0)))
            else:
                state["calls"].append(("copy", engine.reg_read(arm_const.UC_ARM_REG_R0),
                                       engine.reg_read(arm_const.UC_ARM_REG_R1)))
            engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
            engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)

    def model(index, work, prefetch, calls, depth=0):
        if depth > 64:
            raise ValueError("Excessive animation recursion")
        target = roots[index] + work[0x22] * 8
        prefetch.append(target)
        op, argument, duration, frame = struct.unpack_from("<4H", rom, target - BASE)
        if op == 0xFFFD:
            work[0x22] = (work[0x22] + 1) & 255
            calls.append(("sound", argument))
            model(index, work, prefetch, calls, depth + 1)
        elif op == 0xFFFE:
            work[0x22] = argument & 255
            work[0x23] = 0
            model(index, work, prefetch, calls, depth + 1)
        elif op != 0xFFFF:
            if op == 0xFFFC and work[0x23] == 0:
                record = 0xAEB74 + argument * 16
                if rom[record] == 0:
                    source, destination = struct.unpack_from("<II", rom, record + 4)
                    calls.append(("copy", source, destination))
            if work[0x23] < duration:
                value = frame + work[0x2F] if op == 0xFFFA else frame
                struct.pack_into("<H", work, 6, value & 65535)
                work[0x23] = (work[0x23] + 1) & 255
                if work[0x23] >= duration:
                    work[0x23] = 0
                    work[0x22] = (work[0x22] + 1) & 255

    cases = prefetches = adjacent = 0
    for index in range(128):
        for timer, group, ticks in ((0, 0, 256), (255, 255, 32)):
            expected = bytearray(64)
            expected[0x24] = index
            expected[0x23] = timer
            expected[0x2F] = group
            cpu.write(OBJECT, bytes(expected))
            for tick in range(ticks):
                wanted_reads, wanted_calls = [], []
                model(index, expected, wanted_reads, wanted_calls)
                state.update(prefetch=[], calls=[])
                registers = cpu.call(0x08049440, (0,), instruction_limit=100000, timeout_us=0)
                if cpu.read(OBJECT, 64) != expected:
                    raise ValueError(f"Animation fields differ: root {index}, timer {timer}, tick {tick}")
                if state["prefetch"] != wanted_reads or state["calls"] != wanted_calls:
                    raise ValueError(f"Animation reads/calls differ: root {index}, tick {tick}")
                if any(registers[i] != (0xAB000000 | i) for i in range(4, 12)):
                    raise ValueError("Callee-saved register changed")
                if cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) != 0x03007F00:
                    raise ValueError("Animation stack pointer changed")
                cases += 1
                prefetches += len(wanted_reads)
                end = roots[index + 1] if index < 127 else 0x083F7B80
                adjacent += sum(target + 8 > end for target in wanted_reads)
    report = {"rom_sha256": hashlib.sha256(rom).hexdigest(), "root_count": len(roots),
              "cases": cases, "prefetches": prefetches, "adjacent_prefetches": adjacent,
              "scope": __doc__}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"All {cases} native animation steps agree across 128 roots; "
          f"{adjacent} adjacent-ROM prefetches preserved.")


if __name__ == "__main__":
    main()
