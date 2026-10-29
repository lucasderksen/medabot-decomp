"""Execute original encounter/equipment readers against a ROM-backed model.

The byte-copy helper executes normally. Only random routine 08043C94 is stubbed
with explicit draws, so this checks selection/copy behavior, not RNG quality.
A separately labelled synthetic ROM control enables the unused random-parts
branch; all 246 shipped encounter records instead have selectionMode == 1.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

WORK = 0x030057E0
TRANSFER = 0x03001800
SCRATCH = 0x0300052E


def engine(rom):
    cpu = RoutineCpu(rom)
    state = {"draws": [], "used": 0}

    def random_hook(machine, address, size, user_data):
        if address != 0x08043C94:
            return
        if state["used"] >= len(state["draws"]):
            raise ValueError("Unexpected random draw")
        machine.reg_write(arm_const.UC_ARM_REG_R0, state["draws"][state["used"]])
        state["used"] += 1
        machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, random_hook)
    return cpu, state


def bucket(value):
    return 0 if value <= 39 else 1 if value <= 69 else 2 if value <= 89 else 3


def reset(cpu, index, condition=0, selected=0):
    work = bytearray([0xA5] * 0x1000)
    transfer = bytearray([0x5A] * 0x80)
    scratch = bytearray([0xC3] * 16)
    work[0x7FE], work[0xC2D], work[0xC2A] = index, condition, selected
    cpu.write(WORK, bytes(work))
    cpu.write(TRANSFER, bytes(transfer))
    cpu.write(SCRATCH, bytes(scratch))
    return work, transfer, scratch


def check_memory(cpu, expected):
    for address, data in zip((WORK, TRANSFER, SCRATCH), expected):
        if cpu.read(address, len(data)) != bytes(data):
            raise ValueError(f"Memory differs at {address:08X}")
    for number in range(4, 12):
        if cpu.engine.reg_read(getattr(arm_const, f"UC_ARM_REG_R{number}")) != 0xAB000000 | number:
            raise ValueError(f"Saved register r{number} differs")
    if cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) != 0x03007F00:
        raise ValueError("Stack pointer differs")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=Path("build/analysis/encounter-records-cpu.json"))
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    pointers = struct.unpack_from("<246I", rom, 0x3C1B80)
    if pointers != tuple(0x083BF510 + i * 40 for i in range(246)):
        raise ValueError("Encounter directory is not the stored linear bank")
    if any(rom[p - 0x08000000 + 3] != 1 for p in pointers):
        raise ValueError("Stored encounter selection modes changed")
    cpu, state = engine(rom)
    counts = {"equipment_queries": 0, "equipment_copies": 0, "weighted_encounters": 0,
              "direct_encounters": 0, "synthetic_random_parts": 0}
    for index in range(256):
        for mode in (0, 1, 2, 255):
            expected = reset(cpu, index)
            result = cpu.call(0x08048088, (mode,), timeout_us=0)[0]
            value = rom[0x3BEC10 + index * 8 + mode + 2] if mode <= 1 else 0
            if result != value:
                raise ValueError(f"Equipment query differs: {index}, {mode}")
            check_memory(cpu, expected)
            counts["equipment_queries"] += 1
        for address, length in ((0x0804387C, 1), (0x08011DE4, 2)):
            expected = reset(cpu, index)
            work, transfer, scratch = expected
            source = rom[0x3BEC10 + index * 8:0x3BEC10 + index * 8 + length]
            scratch[:length] = source
            if length == 1:
                work[0xC29], work[0xC2B] = source[0], 0
            else:
                transfer[0x38] = source[1]
            cpu.call(address, timeout_us=0)
            check_memory(cpu, expected)
            counts["equipment_copies"] += 1
        for draw in (0, 39, 40, 69, 70, 89, 90, 99, 0xFFFFFFFF):
            expected = reset(cpu, index)
            work, transfer, scratch = expected
            choices = rom[0x3BF210 + index * 4:0x3BF214 + index * 4]
            selected = choices[bucket(draw)]
            if selected >= len(pointers):
                raise ValueError("Out-of-range selector in tested ROM read")
            scratch[:4] = choices
            work[0xC2A] = selected
            offset = pointers[selected] - 0x08000000
            transfer[:40] = rom[offset:offset + 40]
            state.update(draws=[draw], used=0)
            cpu.call(0x08011E20, timeout_us=0)
            if state["used"] != 1:
                raise ValueError("Weighted selection draw count differs")
            check_memory(cpu, expected)
            counts["weighted_encounters"] += 1
    for selected in range(246):
        expected = reset(cpu, 0, condition=1, selected=selected)
        offset = pointers[selected] - 0x08000000
        expected[1][:40] = rom[offset:offset + 40]
        state.update(draws=[], used=0)
        cpu.call(0x08011E20, timeout_us=0)
        check_memory(cpu, expected)
        counts["direct_encounters"] += 1

    control = bytearray(rom)
    control[0x3BF513] = 0
    for member in range(3):
        start = 0x3BF514 + member * 12
        control[start:start + 4] = bytes(range(10 + member * 4, 14 + member * 4))
    synthetic, random = engine(bytes(control))
    expected = reset(synthetic, 0, condition=1, selected=0)
    expected[1][:40] = control[0x3BF510:0x3BF538]
    for member in range(3):
        start = 4 + member * 12
        choices = bytes(expected[1][start:start + 4])
        for item, draw in enumerate((90, 70, 40, 0)):
            expected[1][start + item] = choices[bucket(draw)]
    random.update(draws=[90, 70, 40, 0] * 3, used=0)
    synthetic.call(0x08011E20, timeout_us=0)
    if random["used"] != 12:
        raise ValueError("Synthetic random-parts draw count differs")
    check_memory(synthetic, expected)
    counts["synthetic_random_parts"] = 1
    report = {"rom_sha256": hashlib.sha256(rom).hexdigest(), "cases": counts,
              "equipment_indices_beyond_stored_192": 64,
              "choice_indices_beyond_stored_192": 64,
              "stored_encounters": 246, "stored_selection_modes": [1],
              "stubs": ["08043C94 explicit random draws"],
              "synthetic_control": "record 0 mode zero; three distinct four-byte choice lists"}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
