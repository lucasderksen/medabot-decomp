"""Check the native signed pointer lookup across neighboring ROM tables."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
calls, reads = [], set()
helpers = {0x0803D450, 0x08015838, 0x0803D4AC}


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.add((address, size))


def helper(engine, address, _size, _user_data):
    if address in helpers:
        calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R0)))
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083AF8C0, end=0x083AFACB)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helper)
cases = 0
for index in list(range(-82, -2)) + list(range(49)):
    slot = 0x3AFA08 + index * 4
    pointer = struct.unpack_from('<I', rom, slot)[0]
    assert 0x08000000 <= pointer + 3 < 0x08800000
    for flag in (0, 2):
        ram = bytearray(0x7100)
        ram[0x1867] = 0x78
        ram[0x1887] = 7
        ram[0x18F6] = flag
        ram[0x1961] = 9
        struct.pack_into('<hHhHH', ram, 0x1902, 0, 0xABCD, index, 0x1234, 0x5678)
        expected = bytearray(ram)
        frame = 0x2C30 + 5 * 64
        expected[frame + 0x29] = 0x18
        expected[frame + 0x2B] = rom[pointer + 3 - 0x08000000]
        expected[frame + 0x2C] = 0
        expected[frame + 0x2D] = 0x34
        expected[frame + 0x2E] = 0x78
        struct.pack_into('<H', expected, frame + 0x30, 0xABCD)
        cpu.write(0x03000000, bytes(ram))
        calls.clear()
        regs = cpu.call(0x08039AC8, timeout_us=0)
        assert cpu.read(0x03000000, len(ram)) == expected, (index, flag)
        assert [call[0] for call in calls] == [0x0803D450, 0x08015838, 0x0803D4AC]
        assert calls[1][1] == (9 if flag else 7)
        assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
        cases += 1

assert all((0x083AFA08 + index * 4, 4) in reads
           for index in list(range(-82, -2)) + list(range(49)))
print(f'{cases} native selection fixtures cover signed neighboring pointer slots; three helpers stubbed')
