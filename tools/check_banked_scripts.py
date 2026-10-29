"""Check banked-event reads against original Thumb code, with explicit stubs.

The native reader 0804D83C and command handlers execute. Calls outside the
command-handler block/D8CC are stubbed with zero; 080532D4 supplies a chosen
packed-state selector. Graphics, sound, waits and scene behavior are not checked.
Checks cover directory arithmetic/cursor wrap, operand read locations, recursive
80/81 dispatch and every stored 2F table entry, including its shared command bytes.
"""
import argparse
import bisect
import hashlib
import json
from pathlib import Path
import struct

from banked_scripts import decode, script_address
from common import find_rom, load_segments
from cpu import RoutineCpu, arm_const, unicorn

BASE = 0x08000000
WORK = 0x030057E0
ROOT = 0x08765EC0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--all-commands", action="store_true")
    parser.add_argument("--output", type=Path, default=Path("build/analysis/banked-cpu.json"))
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    offsets = struct.unpack_from("<2288H", rom, 0x769EC0)
    banks = rom[0x76B0A0:0x76B990]
    roots = [script_address(offset, bank) for offset, bank in zip(offsets, banks)]
    index_at = {address: i for i, address in enumerate(roots)}
    unique = sorted(index_at)
    commands = {}
    for start, end in zip(unique, unique[1:] + [0x08785EC0]):
        for command in decode(rom, start - BASE, end - BASE):
            commands[command.offset + BASE] = command
    handlers = struct.unpack_from("<256I", rom, 0x3D222C)
    cpu = RoutineCpu(rom)
    cpu.engine.mem_map(0x04000000, 0x1000)
    functions = {entry["start"] + BASE for entry in load_segments()
                 if entry.get("category") != "data" and entry["start"] < 0x7E868}
    allowed = {address for address in functions if 0x0804B73C <= address < 0x0804D83C}
    allowed.update((0x0804D83C, 0x0804D8CC, 0x0807CCF0))
    state = {"choice": 0, "reads": [], "pending": None, "stubs": {}}

    def hook(engine, address, size, user_data):
        if state["pending"] and address == state["pending"][0]:
            _, expected = state["pending"]
            actual = engine.reg_read(arm_const.UC_ARM_REG_R0)
            if actual != expected:
                raise ValueError(f"Native reader returned {actual:X}, expected {expected:X}")
            state["pending"] = None
        if address == 0x0804D83C:
            selected = struct.unpack("<H", cpu.read(WORK + 0xC8E, 2))[0]
            position = struct.unpack("<H", cpu.read(WORK + 0xC8A, 2))[0]
            target = script_address(offsets[selected], banks[selected], position)
            state["reads"].append(target)
            state["pending"] = (engine.reg_read(arm_const.UC_ARM_REG_LR) & ~1,
                                rom[target - BASE])
        elif address in functions and address not in allowed:
            state["stubs"][hex(address)] = state["stubs"].get(hex(address), 0) + 1
            engine.reg_write(arm_const.UC_ARM_REG_R0,
                             state["choice"] if address == 0x080532D4 else 0)
            engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)

    def prepare(index, position, choice=0):
        cpu.write(0x03000000, bytes(0x7000))
        cpu.write(0x03005590, struct.pack("<I", ROOT))
        cpu.write(WORK + 0xC8A, struct.pack("<H", position))
        cpu.write(WORK + 0xC8E, struct.pack("<H", index))
        state.update(choice=choice, reads=[], pending=None)

    reader_cases = 0
    for index in range(len(roots)):
        for position in (0, 1, 255, 65535):
            prepare(index, position)
            result = cpu.call(0x0804D83C, instruction_limit=1000, timeout_us=0)
            target = script_address(offsets[index], banks[index], position)
            if result[0] != rom[target - BASE]:
                raise ValueError(f"Directory read differs: index {index}, position {position}")
            actual_position = struct.unpack("<H", cpu.read(WORK + 0xC8A, 2))[0]
            if actual_position != ((position + 1) & 0xFFFF):
                raise ValueError("Reader cursor narrowing differs")
            reader_cases += 1

    def expected_reads(address, choice, depth=0):
        if depth > 32:
            raise ValueError("Excessive nested command dispatch")
        command = commands[address]
        if command.opcode == 0x2F:
            return [address + 1 + choice]
        reads = list(range(address + 1, command.end + BASE))
        if command.opcode in (0x80, 0x81):
            next_address = command.end + BASE
            reads.append(next_address)
            reads.extend(expected_reads(next_address, choice, depth + 1))
        return reads

    # Zero bank tails are reserved storage, rather than thousands of extra cases.
    active = [address for address, command in commands.items()
              if any(command.encode()) and address >= 0x0876DEC0]
    selected = active if args.all_commands else active[::max(1, len(active) // 512)]
    command_cases = 0
    for address in selected:
        index = index_at[unique[bisect.bisect_right(unique, address) - 1]]
        prepare(index, address - roots[index] + 1)
        cpu.call(handlers[commands[address].opcode] & ~1, instruction_limit=100000, timeout_us=0)
        if state["reads"] != expected_reads(address, 0):
            raise ValueError(f"Operand reads differ at {address:X}: {state['reads']}")
        command_cases += 1

    switch_cases = 0
    for address, command in commands.items():
        if command.opcode != 0x2F:
            continue
        index = index_at[unique[bisect.bisect_right(unique, address) - 1]]
        position = address - roots[index]
        for choice, displacement in enumerate(command.operands):
            prepare(index, position + 1, choice)
            cpu.call(handlers[0x2F] & ~1, instruction_limit=10000, timeout_us=0)
            actual = struct.unpack("<H", cpu.read(WORK + 0xC8A, 2))[0]
            if state["reads"] != [address + 1 + choice] or actual != ((position + 1 + displacement) & 0xFFFF):
                raise ValueError(f"Dispatch target differs at {address:X}, selector {choice}")
            switch_cases += 1
    # The overlapping entry is an ordinary two-byte facing command in native code.
    address = 0x0877A026
    index = index_at[unique[bisect.bisect_right(unique, address) - 1]]
    prepare(index, address - roots[index] + 1)
    cpu.call(handlers[0x0D] & ~1, instruction_limit=10000, timeout_us=0)
    if (state["reads"] != [address + 1] or cpu.read(WORK + 0xC94, 1) != b"\x02"
            or cpu.read(0x03002C30 + 47 * 64 + 0x21, 1) != b"\x02"
            or cpu.read(0x03002C30 + 47 * 64 + 0x20, 1) != b"\x02"):
        raise ValueError("Overlapping facing command 0D 02 differs")
    report = {"rom_sha256": hashlib.sha256(rom).hexdigest(), "reader_cases": reader_cases,
              "command_cases": command_cases, "switch_cases": switch_cases,
              "overlapping_facing_cases": 1, "stub_calls": state["stubs"], "scope": __doc__}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"Native checks pass: {reader_cases} directory reads, {command_cases} commands, "
          f"{switch_cases} dispatch entries and the overlapping facing command.")


if __name__ == "__main__":
    main()
