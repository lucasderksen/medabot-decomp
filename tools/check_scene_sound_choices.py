"""Check the sound-choice consumer, including its adjacent-ROM reads."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
calls, reads = [], set()


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def sound(engine, address, _size, _user_data):
    if address == 0x08074B88:
        calls.append(engine.reg_read(arm_const.UC_ARM_REG_R0))
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083AD530, end=0x083AD62F)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083AD520, end=0x083AD61F)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, sound)
for key in range(256):
    ram = bytearray(0x7100)
    ram[0x0B94] = key
    cpu.write(0x03000000, bytes(ram))
    calls.clear()
    regs = cpu.call(0x08018A54, timeout_us=0)
    assert calls == [rom[0x3AD530 + key]], key
    assert cpu.read(0x03000000, len(ram)) == ram
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

assert set(range(0x083AD530, 0x083AD630)) <= reads
for key in range(256):
    ram = bytearray(0x7100)
    ram[0x1882] = key
    expected = bytearray(ram)
    obj = 0x2C30
    struct.pack_into('<HhhH', expected, obj, 0xC404, 0x78, 0x78,
                     rom[0x3AD520 + key] + 0x600)
    expected[obj + 0x0A] = 10
    expected[obj + 0x0B] = 0xC0
    cpu.write(0x03000000, bytes(ram))
    regs = cpu.call(0x0801677C, timeout_us=0)
    assert cpu.read(0x03000000, len(ram)) == expected, key
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

assert set(range(0x083AD520, 0x083AD630)) <= reads
print('512 native sound/frame fixtures cover both tables and adjacent-ROM reads; sound stubbed')
