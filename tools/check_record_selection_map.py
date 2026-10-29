"""Verify the native record selection lookup and adjacent-ROM reads."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
reads, calls = set(), []


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helper(engine, address, _size, _user_data):
    if address == 0x0805218C:
        calls.append(tuple(engine.reg_read(reg) for reg in (
            arm_const.UC_ARM_REG_R0, arm_const.UC_ARM_REG_R1, arm_const.UC_ARM_REG_R2)))
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083D262C, end=0x083D272B)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helper)
for index in range(256):
    ram = bytearray(0x7100)
    ram[0x2C30 + 47 * 64 + 0x21] = index
    struct.pack_into('<H', ram, 0x57E0 + 0x5DE, 0xABC)
    struct.pack_into('<H', ram, 0x57E0 + 0xC8E, 0xABC)
    ram[0x57E0 + 0x5E0] = 7
    cpu.write(0x03000000, bytes(ram))
    calls.clear()
    regs = cpu.call(0x0804BE50, timeout_us=0)
    assert calls == [(56, rom[0x3D262C + index], 0x03005DBC)], index
    assert cpu.read(0x03000000, len(ram)) == ram
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

assert reads == set(range(0x083D262C, 0x083D272C))
print('256 native record lookup fixtures cover all map entries and adjacent-ROM reads; helper stubbed')
