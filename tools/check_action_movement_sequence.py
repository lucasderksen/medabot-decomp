"""Verify the native movement sequence, sentinel, and unchecked ROM reads."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
reads, calls = set(), []
helpers = {0x08040BD8, 0x0804422C, 0x08040CD0}


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helper(engine, address, _size, _user_data):
    if address in helpers:
        calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R0),
                      engine.reg_read(arm_const.UC_ARM_REG_R1)))
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083AEB08, end=0x083AED07)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helper)
pointer = struct.unpack_from('<I', rom, 0x3B62A4)[0]
cases = 0
for index in range(256):
    for mirror in (0, 1):
        ram = bytearray(0x7100)
        struct.pack_into('<H', ram, 0x4C6, 1)
        ram[0x3493] = index
        ram[0x18F8] = mirror
        expected = bytearray(ram)
        struct.pack_into('<H', expected, 0x4C6, 2)
        expected[0x3494] = 4
        value = rom[0x3AEB08 + index * 2]
        expected[0x3495] = value
        expected_calls = [(0x08040BD8, pointer, 0x21), (0x0804422C, 0x21, 0x21)]
        if value == 0xFF:
            expected[0x18AA] = 10
            expected_calls.append((0x08040CD0, 0x21, 1))
        else:
            if mirror:
                expected[0x3495] = (0x20 - value) & 0x1F
            expected[0x3498] = rom[0x3AEB09 + index * 2]
            expected[0x3493] = (index + 1) & 0xFF
        cpu.write(0x03000000, bytes(ram))
        calls.clear()
        regs = cpu.call(0x0802DE1C, timeout_us=0)
        assert cpu.read(0x03000000, len(ram)) == expected, (index, mirror)
        assert calls == expected_calls, (index, mirror, calls, expected_calls)
        assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
        cases += 1

assert all(0x083AEB08 + i * 2 in reads for i in range(256))
assert 0x083AEB18 in reads and 0x083AED07 in reads
print(f'{cases} native movement fixtures cover all indices, sentinel, mirror and adjacent-ROM reads; three helpers stubbed')
