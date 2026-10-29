"""Check bounded table consumers in the original main-two scene routines."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


FRAMES = (0x10B,) * 9 + (0x10C, 0x10B, 0x10C)
VERTICAL = (-3, -5, -6, -6, -5, -3, 0, -2, -2, 0, -1, -1, 0)
SEQUENCE = (0x12, 0x13, 0x14, 0x15, 0x14, 0x13, 0x12, 0x12)
cpu = RoutineCpu(find_rom().read_bytes())
cpu.engine.mem_map(0x04000000, 0x1000)
reads = set()
calls = []


def read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def code(engine, address, _size, _user_data):
    if address == 0x0805FB4C:
        calls.append(engine.reg_read(arm_const.UC_ARM_REG_R0))
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def check_abi(regs):
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, read, begin=0x080AFABA, end=0x080AFAFF)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, code)
cases = 0
for step in range(13):
    for tick in range(72):
        ram = bytearray(0x7100)
        struct.pack_into('<I', ram, 0x6F74, 0x02020000)
        struct.pack_into('<H', ram, 0x2C30 + 64 + 0x1A, tick)
        context = bytearray(0x100)
        struct.pack_into('<h', context, 0x3A, 28 + step)
        expected = bytearray(ram)
        next_tick = (tick + 1) % 72
        struct.pack_into('<H', expected, 0x2C30 + 4, 32 + VERTICAL[step])
        if step == 0:
            expected[0x2C30 + 8] = expected[0x2C30 + 9] = 0x40
        struct.pack_into('<H', expected, 0x2C30 + 64 + 0x1A, next_tick)
        struct.pack_into('<H', expected, 0x2C30 + 64 + 6, FRAMES[next_tick // 6])
        struct.pack_into('<h', context, 0x3A, 28 + step)
        cpu.write(0x03000000, bytes(ram))
        cpu.write(0x02020000, bytes(context))
        regs = cpu.call(0x0805FFF8, timeout_us=0)
        assert cpu.read(0x03000000, len(ram)) == expected, (step, tick)
        struct.pack_into('<h', context, 0x3A, 29 + step)
        assert cpu.read(0x02020000, len(context)) == context
        check_abi(regs)
        cases += 1

for tick in range(72):
    ram = bytearray(0x7100)
    struct.pack_into('<I', ram, 0x6F74, 0x02020000)
    struct.pack_into('<H', ram, 0x2C30 + 64 + 0x1A, tick)
    expected = bytearray(ram)
    next_tick = (tick + 1) % 72
    struct.pack_into('<H', expected, 0x2C30 + 64 + 0x1A, next_tick)
    struct.pack_into('<H', expected, 0x2C30 + 64 + 6, FRAMES[next_tick // 6])
    cpu.write(0x03000000, bytes(ram))
    cpu.write(0x02020000, bytes(0x100))
    calls.clear()
    regs = cpu.call(0x080601D4, timeout_us=0)
    assert cpu.read(0x03000000, len(ram)) == expected
    assert calls == [9] and struct.unpack('<H', cpu.read(0x0202003A, 2))[0] == 1
    check_abi(regs)
    cases += 1

for tick in range(64):
    ram = bytearray(0x7100)
    struct.pack_into('<H', ram, 0x2C30 + 0x1A, tick)
    expected = bytearray(ram)
    next_tick = (tick + 1) % 64
    struct.pack_into('<H', expected, 0x2C30 + 0x1A, next_tick)
    struct.pack_into('<H', expected, 0x2C30 + 6, 0x100 + SEQUENCE[next_tick >> 3])
    cpu.write(0x03000000, bytes(ram))
    regs = cpu.call(0x08060248, timeout_us=0)
    assert cpu.read(0x03000000, len(ram)) == expected
    check_abi(regs)
    cases += 1

expected_reads = set(range(0x080AFABA, 0x080AFADF)) | set(range(0x080AFAE0, 0x080AFB00))
assert expected_reads <= reads, (len(expected_reads), len(reads))
print(f'{cases} native animation cases cover both frame tables, signed steps and frame sequence')
