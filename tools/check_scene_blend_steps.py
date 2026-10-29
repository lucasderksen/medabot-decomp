"""Check the eight in-bounds blend steps of the original scene routine."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


LOW = (16, 16, 16, 16, 16, 16, 16, 8)
HIGH = (4, 8, 12, 16, 16, 16, 16, 8)
cpu = RoutineCpu(find_rom().read_bytes())
cpu.engine.mem_map(0x04000000, 0x1000)
reads = set()


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x080B00B8, end=0x080B00C7)
for step in range(8):
    ram = bytearray([0xA5] * 0x7100)
    obj = 0x2C30
    struct.pack_into('<H', ram, obj + 0x1A, 22 + step)
    ram[obj + 0x20] = 7
    cpu.write(0x03000000, bytes(ram))
    cpu.write(0x04000000, bytes([0xA5]) * 0x1000)
    regs = cpu.call(0x0806CB28, timeout_us=0)
    assert cpu.read(0x03000000, len(ram)) == ram
    expected = bytearray([0xA5] * 0x1000)
    struct.pack_into('<H', expected, 0x52, HIGH[step] * 256 + LOW[step])
    assert cpu.read(0x04000000, len(expected)) == expected
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

assert reads == set(range(0x080B00B8, 0x080B00C8))
print('8 native in-bounds blend fixtures cover both copied tables and ABI')
