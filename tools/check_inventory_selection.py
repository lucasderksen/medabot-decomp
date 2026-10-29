"""Check inventory selection copies and cursor tables against native ROM consumers."""
import json
import struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
calls = []

def hook(machine, address, size, user):
    if address not in (0x08015564, 0x08040B90):
        return
    calls.append((address, machine.reg_read(arm_const.UC_ARM_REG_R0),
                  machine.reg_read(arm_const.UC_ARM_REG_R1)))
    machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)

def check_abi(result):
    assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

copy_cases = 0
for record in range(30):
    for slot in range(3):
        for setup in (0, 1, 7):
            cpu.write(0x03000400, bytes([0xA5]) * 0x1000)
            base = 0x03000590 + setup * 256
            cpu.write(base + 1, bytes([record]))
            before = bytearray(cpu.read(0x03000400, 0x1000))
            indices = rom[0x3B7F8C + record * 3:0x3B7F8C + record * 3 + 3]
            selected = indices[slot]
            assert selected < 52
            before[0x12E:0x131] = indices
            destination = base + 0xA8 - 0x03000400
            before[destination:destination + 6] = rom[0x3B7E54 + selected * 6:0x3B7E54 + selected * 6 + 6]
            calls.clear()
            result = cpu.call(0x08015668, (setup, slot))
            assert calls == [(0x08015564, setup, slot + 4)]
            assert cpu.read(0x03000400, 0x1000) == before
            check_abi(result)
            copy_cases += 1

cursor_cases = 0
roots = struct.unpack_from('<6I', rom, 0x3B803C)
for table, root in enumerate(roots):
    offset = root - 0x08000000
    count = rom[offset]
    assert offset + 2 + count * 2 == (roots[table + 1] - 0x08000000 if table < 5 else 0x3B803C)
    for selection in range(count):
        for entry in (0x0800FF50, 0x0800FFF4):
            work = bytearray([0xA5] * 0x100)
            work[0x43:0x45] = bytes([table, selection])
            frame = bytearray([0x5A] * 64)
            cpu.write(0x03000440, bytes(work))
            cpu.write(0x03002C30 + 6 * 64 - 4, bytes([0xA5]) * 72)
            cpu.write(0x03002C30 + 6 * 64, bytes(frame))
            x, y = rom[offset + 2 + selection * 2:offset + 4 + selection * 2]
            struct.pack_into('<HH', frame, 2, x * 8, y * 8)
            if entry == 0x0800FF50:
                work[0x45] = count
                struct.pack_into('<H', frame, 0, 0xC004)
                struct.pack_into('<H', frame, 6, 0x308)
                frame[0xA], frame[0xB], frame[0x1C] = 14, 193, 0
            calls.clear()
            result = cpu.call(entry)
            assert calls == ([(0x08040B90, struct.unpack_from('<I', rom, 0x3B6100 + 12)[0], 6)] if entry == 0x0800FF50 else [])
            assert cpu.read(0x03000440, 0x100) == work
            assert cpu.read(0x03002C30 + 6 * 64 - 4, 72) == bytes([0xA5]) * 4 + frame + bytes([0xA5]) * 4
            check_abi(result)
            cursor_cases += 1

report = dict(copy_cases=copy_cases, cursor_cases=cursor_cases,
              hooks=['08015564 follow-up display', '08040B90 animation setup'],
              scope='All 30 selection lists and 3 slots at 3 setup offsets; every cursor position in both native consumers. Copy helper executes natively; guarded RAM, preserved registers and SP checked.')
Path('build/more/inventory_selection_cpu.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps(report))
