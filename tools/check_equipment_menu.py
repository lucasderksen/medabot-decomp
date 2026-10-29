"""Native checks for equipment label copies, lookup indexing and placement records."""
import json
import struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
state = {'orientation': 0, 'calls': []}

def hook(machine, address, size, user):
    if address not in (0x08040D0C, 0x08040DB8, 0x08019184, 0x08015924):
        return
    args = tuple(machine.reg_read(getattr(arm_const, f'UC_ARM_REG_R{i}')) for i in range(4))
    state['calls'].append((address, args))
    if address == 0x08015924:
        machine.reg_write(arm_const.UC_ARM_REG_R0, state['orientation'])
    machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)

def abi(result):
    assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

label_cases = 0
for directory, count, width in [(0x3C47EC, 6, 12), (0x3C4B90, 128, 14)]:
    for index, pointer in enumerate(struct.unpack_from('<' + 'I' * count, rom, directory)):
        offset = pointer - 0x08000000
        cpu.write(0x030004DA, bytes([0xA5]) * 24)
        state['calls'].clear()
        if directory == 0x3C47EC:
            cpu.write(0x03001881, bytes([index]))
            result = cpu.call(0x08015F24)
            assert [c[0] for c in state['calls']] == [0x08040D0C, 0x08040DB8]
            assert state['calls'][1][1][0] == 0x030004DE
        else:
            result = cpu.call(0x08041D04, (pointer, 0x030004DE, width))
        assert cpu.read(0x030004DA, 24) == bytes([0xA5]) * 4 + rom[offset:offset + width] + bytes([0xA5]) * (20 - width)
        abi(result)
        label_cases += 1

lookup_cases = 0
for row in range(7):
    for column in range(11):
        for bank in range(6):
            cpu.write(0x03000590 + bank * 256 + 0x91, bytes([100 + row]))
            cpu.write(0x03001838, bytes([column]))
            cpu.write(0x0300052A, bytes([0xA5]) * 9)
            value = rom[0x3C4D90 + row * 11 + column]
            state['calls'].clear()
            result = cpu.call(0x080191E4, (bank,))
            assert len(state['calls']) == 1 and state['calls'][0][0] == 0x08019184
            assert state['calls'][0][1][:2] == (bank, value)
            assert cpu.read(0x0300052A, 9) == bytes([0xA5]) * 4 + bytes([value]) + bytes([0xA5]) * 4
            abi(result)
            lookup_cases += 1

placement_cases = 0
for record in range(17):
    raw = rom[0x3C4DE0 + record * 4:0x3C4DE4 + record * 4]
    dx, dy, palette, mirror = struct.unpack('<bBBB', raw)
    for bank in range(6):
        for mode in range(3):
            for orientation in (0, 1):
                slot = mode
                target = 0x03002C30 + (bank * 3 + slot + 0x46) * 64
                anchor = 0x03002C30 + (bank * 4 + 0x5D) * 64
                expected = bytearray([0xA5] * 64)
                cpu.write(target - 4, bytes([0xA5]) * 72)
                cpu.write(anchor + 2, struct.pack('<HH', 500, 20))
                cpu.write(0x0300052E, raw)
                cpu.write(0x0300183C, bytes([2]))
                for offset, kind in [(0xC4, 31), (0xC9, 13), (0xDF, 27)]:
                    cpu.write(0x03000590 + bank * 256 + offset, bytes([kind]))
                flags = 0xC004 | (0x1000 if orientation and mirror else 0)
                struct.pack_into('<HHH', expected, 0, flags, (500 - dx if orientation else 500 + dx) & 65535, 20 - 4 + dy)
                expected[0xA], expected[0xB], expected[0x1C], expected[0x23] = 11 + palette, 255, 0, (31, 13, 27)[mode]
                state.update(orientation=orientation, calls=[])
                result = cpu.call(0x08019D9C, (bank, slot, mode, 511))
                assert cpu.read(target - 4, 72) == bytes([0xA5]) * 4 + expected + bytes([0xA5]) * 4, (record, bank, mode, orientation)
                assert len(state['calls']) == 1 and state['calls'][0][0] == 0x08015924
                abi(result)
                placement_cases += 1
report = dict(label_cases=label_cases, lookup_cases=lookup_cases, placement_cases=placement_cases,
              hooks=['08040D0C/08040DB8 text display', '08019184 lookup result consumer', '08015924 orientation fixture'],
              scope='All stored labels via native fixed-width copy; first directory also via native selector. All lookup cells at six bank offsets; all placement records, banks, modes and orientations. Guarded writes and ABI checked; rendering excluded.')
Path('build/more/equipment_menu_cpu.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps(report))
