"""Exercise frame lookups and all byte-sized map-row counts in native code."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
calls = []


def helper(engine, address, _size, _user_data):
    if address == 0x08042E58:
        registers = tuple(engine.reg_read(getattr(arm_const, f'UC_ARM_REG_R{i}')) for i in range(4))
        stack = engine.reg_read(arm_const.UC_ARM_REG_SP)
        calls.append((address, registers, struct.unpack('<7I', cpu.read(stack, 28))))
    elif address == 0x08043240:
        calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R0),
                      engine.reg_read(arm_const.UC_ARM_REG_R1)))
    else:
        return
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helper)
for count in range(256):
    ram = bytearray(0x7100)
    ram[0x1802] = count
    for i in range(255 * 12):
        ram[0x1804 + i] = (i * 13 + 7) & 0xFF
    cpu.write(0x03000000, bytes(ram))
    calls.clear()
    regs = cpu.call(0x08012024, timeout_us=0)
    assert cpu.read(0x03000000, len(ram)) == ram, count
    assert len(calls) == count * 2, count
    for i in range(count):
        record = tuple(ram[0x1804 + i * 12:0x1808 + i * 12])
        position = rom[0x3AD064 + 2 * i:0x3AD066 + 2 * i]
        assert calls[i * 2] == (0x08042E58, record,
                                (i, 40 + 4 * i, position[0], position[1], 1, 1, 0))
        assert calls[i * 2 + 1] == (0x08043240, 40 + 4 * i, 8)
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

for address, table, frame in ((0x0805D6E4, 0xAF958, 0), (0x0805E2D8, 0xAF980, 20)):
    for value in range(256):
        for upper in (0, 0xABCD0000):
            ram = bytearray(0x7100)
            expected = bytearray(ram)
            expected[0x2C30 + frame * 64 + 6:0x2C30 + frame * 64 + 8] = rom[table + (value & 3) * 2:table + (value & 3) * 2 + 2]
            cpu.write(0x03000000, bytes(ram))
            regs = cpu.call(address, (upper | value,), timeout_us=0)
            assert cpu.read(0x03000000, len(ram)) == expected, (address, value, upper)
            assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
            assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

print('256 native row-count and 1,024 frame fixtures cover both tables and adjacent-ROM row reads; row helpers stubbed')
