"""Verify bounded command positions of the original scene script."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


cpu = RoutineCpu(find_rom().read_bytes())
cpu.engine.mem_map(0x04000000, 0x1000)
reads, calls, transfers = set(), [], []


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helpers(engine, address, _size, _user_data):
    if (0x080722B0 <= address < 0x080723AC or address == 0x0807CCF0
            or 0x0807E7A4 <= address < 0x0807E804):
        return
    assert address in (0x080446B4, 0x08044A3C, 0x08074DE0), hex(address)
    calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R0)))
    engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def dma(_engine, _access, _address, _size, control, _user_data):
    if not control & 0x80000000:
        return
    src, dst = struct.unpack('<II', cpu.read(0x040000D4, 8))
    assert control == 0x85000100 and dst == 0x02010B84
    assert cpu.read(src, 4) == struct.pack('<I', 0x200)
    cpu.write(dst, cpu.read(src, 4) * 256)
    transfers.append((src, dst, control))


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x080B0120, end=0x080B0128)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, dma, begin=0x040000DC, end=0x040000DC)
cases = 0
for position in (0, 2, 4, 6, 8):
    for wait in (0, 44, 45, 65, 66, 255):
        ram = bytearray(0x7100)
        struct.pack_into('<I', ram, 0x2414, 0x02010000)
        ram[0x1811] = wait
        ram[0x1812] = position
        expected = bytearray(ram)
        for index in (2, 3, 4, 5):
            struct.pack_into('<H', expected, 0x2C30 + index * 64 + 4, 0xC8)
        expected_sound = []
        if position in (0, 4):
            threshold = 65 if position == 0 else 44
            expected[0x1811] = (wait + 1) & 0xFF
            if wait > threshold:
                expected[0x1811] = 0
                expected[0x1812] += 2
        elif position in (2, 6):
            expected_sound = [(0x08074DE0, 37 if position == 2 else 36)]
            expected[0x1811] = 0
            expected[0x1812] += 2
        cpu.write(0x03000000, bytes(ram))
        cpu.write(0x02010000, bytes([0xA5]) * 0x2000)
        cpu.write(0x04000000, bytes(0x1000))
        calls.clear()
        transfers.clear()
        regs = cpu.call(0x080722B0, timeout_us=0)
        assert cpu.read(0x03000000, len(ram)) == expected, (position, wait)
        image = bytearray([0xA5] * 0x2000)
        image[0xB84:0xF84] = struct.pack('<I', 0x200) * 256
        assert cpu.read(0x02010000, len(image)) == image
        assert calls == [(0x080446B4, 0), *expected_sound, (0x08044A3C, 0)]
        assert len(transfers) == 1 and regs[0] == 0
        assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
        cases += 1

assert reads == set(range(0x080B0120, 0x080B0129))
print(f'{cases} native script fixtures cover all copied bytes and bounded command positions')
