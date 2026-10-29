"""Compare original spawn-list selection with a ROM-backed descriptor model.

Executes 080513C8 and its real clear/copy helpers. Graphics/actor setup and
event flags are explicit stubs; no scene rendering is claimed. The event flag
stub blocks IDs divisible by seven on even-numbered maps. Actor setup leaves
cleared frame buffers unchanged, while the routine's own frame stores execute.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

BASE = 0x08000000
WORK = 0x030057E0
FRAMES = 0x03002C30
ATTRIBUTES = 0x030055A0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--limit", type=int, default=192)
    parser.add_argument("--unreferenced-lists", action="store_true",
                        help="Redirect map 0 to each of three unreferenced ROM lists")
    parser.add_argument("--output", type=Path, default=Path("build/analysis/map-object-spawns-cpu.json"))
    args = parser.parse_args()
    if not 1 <= args.limit <= 192:
        parser.error("limit must be 1..192")
    rom = find_rom().read_bytes()
    roots = struct.unpack_from("<192I", rom, 0x483234)
    cpu = RoutineCpu(rom)
    if args.unreferenced_lists:
        # Fixture-only redirection; the source ROM and all record bytes stay unchanged.
        cpu.engine.mem_protect(0x08483000, 0x1000, unicorn.UC_PROT_ALL)
    state = {"map": 0, "selections": []}
    stub_calls = {}
    stubs = {0x080531E0, 0x08048864, 0x08048684, 0x080487C8, 0x0805218C, 0x08049420}

    def blocked(identifier):
        return state["map"] % 2 == 0 and identifier % 7 == 0

    def hook(machine, address, size, user_data):
        if address not in stubs:
            return
        stub_calls[address] = stub_calls.get(address, 0) + 1
        if address in (0x0805218C, 0x08049420):
            arguments = tuple(machine.reg_read(getattr(arm_const, f"UC_ARM_REG_R{i}"))
                              for i in range(3 if address == 0x0805218C else 2))
            state["selections"].append((address, *arguments))
        value = int(blocked(machine.reg_read(arm_const.UC_ARM_REG_R0))) if address == 0x080531E0 else 0
        machine.reg_write(arm_const.UC_ARM_REG_R0, value)
        machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
    cases = selected = holes = 0
    fixtures = ([(0, 0x3D62F4, 0x3D6374), (0, 0x3D6374, 0x3D63D4),
                 (0, 0x3D63D4, 0x3D63DC)] if args.unreferenced_lists else
                [(i, roots[i] - BASE, roots[i + 1] - BASE if i < 191 else 0x483234)
                 for i in range(args.limit)])
    for map_index, start, end in fixtures:
        state["map"] = map_index
        if args.unreferenced_lists:
            cpu.write(0x08483234 + map_index * 4, struct.pack('<I', BASE + start))
        entries = [struct.unpack_from("<2BH2BH", rom, p) for p in range(start, end - 8, 8)]
        terminal = rom[end - 8:end]
        if terminal[0] != 255 or (not args.unreferenced_lists and terminal != bytes([255]) + bytes(7)):
            raise ValueError("Spawn terminal changed")
        visibility_bits = 0
        for entry in entries:
            visibility_bits |= entry[5]
        visibility_states = sorted({0, 15, 31} | {bit for bit in range(16) if visibility_bits & (1 << bit)})
        for visibility in visibility_states:
            for mode in (0, 1, 2):
                work = bytearray(0xD00)
                work[0x7FE], work[0x7FF] = map_index, visibility
                width = rom[0x3F8900 + map_index * 2]
                struct.pack_into("<H", work, 0x800, width)
                target = next((r[2] & 4095 for r in entries if r[2] & 4095), 0)
                struct.pack_into("<H", work, 0xC8E, target)
                work[0xCB4] = 254
                saved = bytearray(512)
                for i, record in enumerate(entries[::2][:8]):
                    struct.pack_into("<H", saved, i * 8 + 2, record[2] & 4095)
                    saved[i * 8 + 4] = 128 if i % 2 == 0 else 0
                    saved[i * 8 + 5] = i % 4
                work[0x5DC:0x7DC] = saved
                expected = bytearray(work)
                expected[0x5DC:0x7DC] = bytes(512)
                frames, attributes = bytearray(8192), bytearray(512)
                selection_calls = []
                slot = actor = 0
                for order in range(32):
                    for x, y, attr, appearance, record_order, mask in entries:
                        identifier = attr & 4095
                        if not ((mask >> visibility) & 1) or record_order != order or blocked(identifier):
                            continue
                        found = next((i for i in range(64) if struct.unpack_from("<H", saved, i * 8 + 2)[0] & 4095 == identifier), None)
                        output_slot = slot
                        slot += 1
                        if mode == 2 and (found is None or saved[found * 8 + 4] & 128 == 0):
                            holes += 1
                            continue
                        offset = 0x5DC + output_slot * 8
                        struct.pack_into("<2BH", expected, offset, x, y, attr)
                        kind = attr >> 12
                        if kind in (0, 4, 6):
                            expected[0x810 + y * (width // 2) + x] = 7
                        flags = 128
                        if appearance != 255:
                            if actor <= 29:
                                object_index, shadow_index = actor + 49, actor + 91
                                if kind in (0, 2, 4, 6):
                                    flags |= 64
                                flags |= actor
                                high = appearance >> 4
                                struct.pack_into("<H", attributes, object_index * 4, identifier)
                                frames[object_index * 64 + 0x2B] = high
                                position_x, position_y = x * 16 * 256, y * 16 * 256
                                struct.pack_into("<II", frames, object_index * 64 + 0xC, position_x, position_y)
                                struct.pack_into("<II", frames, shadow_index * 64 + 0xC, position_x, (position_y - 5 * 256) & 0xFFFFFFFF)
                                struct.pack_into("<h", frames, shadow_index * 64 + 4, -5)
                                selection_calls.append((0x0805218C, object_index, appearance & 15, WORK + offset))
                                selection_calls.append((0x08049420, object_index, high * 4 + (appearance & 15)))
                                if mode and found is not None:
                                    frame = saved[found * 8 + 5]
                                    selection_calls.append((0x0805218C, object_index, frame, WORK + offset))
                                    selection_calls.append((0x08049420, object_index, high * 4 + frame))
                            actor += 1
                        expected[offset + 4] = flags
                        selected += 1
                if slot > 64:
                    raise ValueError("Model encountered more than 64 eligible slots")
                if target:
                    for i in range(64):
                        if struct.unpack_from("<H", expected, 0x5DC + i * 8 + 2)[0] & 4095 == target:
                            expected[0xCB4] = i
                            break
                expected[0xCBA] = 2
                cpu.write(WORK, bytes(work))
                cpu.write(FRAMES, bytes(8192))
                cpu.write(ATTRIBUTES, bytes(512))
                state["selections"] = []
                registers = cpu.call(0x080513C8, (mode,), instruction_limit=1000000, timeout_us=0)
                if state["selections"] != selection_calls:
                    raise ValueError(f"Map {map_index}, visibility {visibility}, mode {mode}: frame-selection arguments differ")
                for address, wanted in ((WORK, expected), (FRAMES, frames), (ATTRIBUTES, attributes)):
                    actual = cpu.read(address, len(wanted))
                    if actual != wanted:
                        offset = next(i for i, (a, b) in enumerate(zip(actual, wanted)) if a != b)
                        raise ValueError(f"Map {map_index}, visibility {visibility}, mode {mode}: {address+offset:08X} got {actual[offset]:02X}, expected {wanted[offset]:02X}")
                if any(registers[i] != (0xAB000000 | i) for i in range(4, 12)):
                    raise ValueError("Saved register changed")
                if cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) != 0x03007F00:
                    raise ValueError("Stack pointer changed")
                cases += 1
    direction_cases = selector_cases = 0
    for y in range(0 if args.unreferenced_lists else 27):
        for x in range(21):
            for keys in (*range(16), 255):
                work = bytearray(0xD00)
                struct.pack_into("<H", work, 0x800, 42)
                work[0xC56], work[0xC57] = x, y
                cpu.write(WORK, bytes(work))
                cell = rom[0x47E40C + y * 21 + x]
                result = rom[0x3D2A43 + keys + (cell - 1) * 16] if 1 <= cell <= 4 else keys
                registers = cpu.call(0x08051C64, (keys,), timeout_us=0)
                if registers[0] != result or cpu.read(WORK, len(work)) != work:
                    raise ValueError("Special-map direction remapping differs")
                direction_cases += 1
    for flag in (() if args.unreferenced_lists else (0, 1, 254, 255)):
        for index in range(256):
            work = bytearray(0xD00)
            work[0xC30], work[0xC31], work[0x7FE] = flag, index, index
            cpu.write(WORK, bytes(work))
            result = cpu.call(0x080483F8, timeout_us=0)[0]
            expected = index if flag == 255 else rom[0x47E644 + index]
            if result != expected or cpu.read(WORK, len(work)) != work:
                raise ValueError("Map selector primary/fallback read differs")
            selector_cases += 1
    report = {"rom_sha256": hashlib.sha256(rom).hexdigest(), "maps": len(fixtures),
              "unreferenced_lists": args.unreferenced_lists,
              "cases": cases, "selected_records": selected, "mode2_empty_slots": holes,
              "visibility_states": "Every set visibility bit per map plus 0/15/31 controls",
              "direction_cases": direction_cases, "selector_cases": selector_cases,
              "stub_calls": {hex(k): v for k, v in sorted(stub_calls.items())}, "scope": __doc__}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
