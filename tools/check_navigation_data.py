"""Check stored navigation pointers through original Thumb input consumers."""
import json
import struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


def main():
    rom = find_rom().read_bytes()
    cpu = RoutineCpu(rom)
    hooks = []

    def hook(machine, address, size, user):
        if address in (0x080582B8, 0x08059960, 0x08074DE0):
            hooks.append(address)
            machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
    cases = 0
    for function, start, count, width in ((0x08058A10, 0x3D625C, 3, 2),
                                          (0x08058AB8, 0x3D6268, 3, 2),
                                          (0x08058B28, 0x3D6274, 21, 1)):
        for index, target in enumerate(struct.unpack_from('<' + 'I' * count, rom, start)):
            for initial in (0, 1, 15, 16, 31, 127, 254, 255, 65535):
                initial &= (1 << (width * 8)) - 1
                for keys in (0, 0x10, 0x20, 0x30):
                    for held in (0, 0x100):
                        cpu.write(0x03000000, bytes(0x7E00))
                        cpu.write(target, initial.to_bytes(width, 'little'))
                        cpu.write(0x03001798, struct.pack('<H', keys))
                        cpu.write(0x03002B64, struct.pack('<H', held))
                        hooks.clear()
                        result = cpu.call(function, (index, 32))
                        amount = 16 if held and width == 2 else 1
                        expected = initial
                        mask = (1 << (width * 8)) - 1
                        if keys & 0x20:
                            expected -= amount
                            if function == 0x08058AB8:
                                if expected == -1:
                                    expected = 31
                            else:
                                expected &= mask
                                if expected == mask:
                                    expected = 31
                        elif keys & 0x10:
                            expected += amount
                            if function != 0x08058AB8:
                                expected &= mask
                            if expected >= 32:
                                expected = 0
                        expected &= mask
                        actual = int.from_bytes(cpu.read(target, width), 'little')
                        assert actual == expected, (hex(function), index, initial, keys, held, actual, expected)
                        assert hooks == ([0x080582B8] if function == 0x08058A10 and keys else [])
                        assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
                        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
                        cases += 1
    nested_cases = 0
    for category, pointer in enumerate(struct.unpack_from('<7I', rom, 0x3D62C8)):
        if not pointer:
            continue
        # One target per non-null root; no inferred sub-list lengths.
        target = struct.unpack_from('<I', rom, pointer - 0x08000000)[0]
        for initial in (0, 1, 31, 255):
            for keys in (0, 0x10, 0x20, 0x30):
                cpu.write(0x03000000, bytes(0x7E00))
                cpu.write(target, bytes([initial]))
                cpu.write(0x03001798, struct.pack('<H', keys))
                hooks.clear()
                result = cpu.call(0x08058B90, (category, 0, 32))
                expected = initial
                if keys & 0x20:
                    expected = 31 if initial == 0 else initial - 1
                elif keys & 0x10:
                    expected = 0 if initial + 1 >= 32 else initial + 1
                assert cpu.read(target, 1) == bytes([expected])
                assert hooks == ([0x08059960] if category == 5 and keys else [])
                assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
                assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
                nested_cases += 1
    menu_cases = 0
    for alternate in (0, 1):
        for mode in range(3):
            for previous in range(10):
                for keys in (0, 0x20, 0x10, 0x40, 0x80, 0xF0):
                    cpu.write(0x03000000, bytes(0x7E00))
                    cpu.write(0x03006F74, struct.pack('<I', 0x02020000))
                    context = bytearray(32)
                    context[0x17:0x19] = bytes([previous, alternate])
                    cpu.write(0x02020000, bytes(context))
                    cpu.write(0x03006412, bytes([mode]))
                    cpu.write(0x0300058C, bytes([keys]))
                    hooks.clear()
                    result = cpu.call(0x0805B8EC)
                    expected = previous
                    if keys:
                        direction = next(i for i, bit in enumerate((0x20, 0x10, 0x40, 0x80)) if keys & bit)
                        expected = rom[0xAF774 + alternate * 120 + mode * 40 + previous * 4 + direction]
                    assert cpu.read(0x02020017, 1) == bytes([expected])
                    assert result[0] == bool(keys)
                    assert hooks == ([0x08074DE0] if keys else [])
                    assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
                    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
                    menu_cases += 1
    report = dict(direct_cases=cases, nested_cases=nested_cases, menu_cases=menu_cases,
                  hooks=['080582B8 refresh', '08059960 refresh', '08074DE0 sound'],
                  scope='All direct slots; first entry of each non-null nested root. Refresh helpers are no-ops.')
    Path('build/analysis/navigation-data-cpu.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()
