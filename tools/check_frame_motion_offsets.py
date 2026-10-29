"""Check the original frame motion routine across the full signed-offset table."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


OFFSETS = (
    4, 3, -2, -1, 2, 1, -2, -1, -2, 0, 0, -1, 4, 3, 2, 1,
    4, 3, -4, -3, -4, -3, 2, 1, 4, 3, -2, -1, 4, 3, -4, -3,
    0, 0, -4, -3, -2, -1, -4, -3, -2, -1, -4, -3, 2, 1, 4, 3,
    2, 1, 0, 0, 4, 3, -4, -3, 2, 1, 4, 3, -4, -3, 0, 0,
)

cpu = RoutineCpu(find_rom().read_bytes())
reads = set()


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x080B00C8, end=0x080B0107)
cases = 0
for phase in range(64):
    for high in (0, 64, 128, 192):
        for index in (0, 1, 126, 127):
            for increment in (0, 1, 255):
                for base in (0, 255):
                    ram = bytearray([0xA5] * 0x7100)
                    obj = 0x2C30 + index * 64
                    ram[obj + 0x21] = phase | high
                    ram[obj + 0x22] = increment
                    ram[obj + 0x23] = base
                    expected = bytearray(ram)
                    y = base + (-OFFSETS[phase] if index & 1 else OFFSETS[phase])
                    struct.pack_into('<H', expected, obj + 4, y & 0xFFFF)
                    expected[obj + 0x21] = (phase + high + 1 + increment) & 0xFF
                    cpu.write(0x03000000, bytes(ram))
                    regs = cpu.call(0x080706A4, (index,), timeout_us=0)
                    assert cpu.read(0x03000000, len(ram)) == expected
                    assert regs[0] == 1
                    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
                    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
                    cases += 1

assert reads == set(range(0x080B00C8, 0x080B0108))
print(f'{cases} native motion fixtures cover all 64 signed offsets and both directions')
