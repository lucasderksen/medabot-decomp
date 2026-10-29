"""Verify the original object-affine wrapper copies its identity initializer."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


cpu = RoutineCpu(find_rom().read_bytes())
reads, calls = set(), []
angle = 0
RESULT = (-20, 30, -40, 50)


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helpers(engine, address, _size, _user_data):
    if address == 0x08045A40:
        engine.reg_write(arm_const.UC_ARM_REG_R0, 1)
    elif address == 0x0804538C:
        pass
    elif address == 0x08045794:
        engine.reg_write(arm_const.UC_ARM_REG_R0, 0x1234)
    elif address == 0x0807CCE0:
        src = engine.reg_read(arm_const.UC_ARM_REG_R0)
        dst = engine.reg_read(arm_const.UC_ARM_REG_R1)
        assert struct.unpack('<hhH', cpu.read(src, 6)) == (256, 256, (-angle) & 0xFFFF)
        assert struct.unpack('<hhhh', cpu.read(dst, 8)) == (256, 0, 0, 256)
        assert engine.reg_read(arm_const.UC_ARM_REG_R2) == 1
        assert engine.reg_read(arm_const.UC_ARM_REG_R3) == 2
        cpu.write(dst, struct.pack('<hhhh', *RESULT))
    else:
        return
    calls.append(address)
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x080ABD5C, end=0x080ABD63)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
cases = 0
for angle in (0, 1, 0x1234, 0xFFFF):
    for mode in range(4):
        cpu.write(0x03000000, bytes(0x8000))
        cpu.write(0x02003000, bytes([0xA5]) * 0x80)
        cpu.write(0x03007F00, struct.pack('<6I', 50, 3, 2, angle, 0x02003010, mode))
        calls.clear()
        regs = cpu.call(0x08045C30, (0x02001000, 0x02002000, 7, 20), timeout_us=0)
        assert calls == [0x08045A40, 0x0804538C, 0x08045794, 0x0807CCE0]
        expected = bytearray([0xA5] * 0x80)
        struct.pack_into('<hhhh', expected, 0x10 + mode * 8, *RESULT)
        assert cpu.read(0x02003000, len(expected)) == expected
        assert regs[0] == 0x1234
        assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
        cases += 1

assert reads == set(range(0x080ABD5C, 0x080ABD64))

# Stop the original unmatched recursive renderer immediately after its matrix
# copy. This checks the second initializer without claiming the rest of the
# function has been reconstructed or emulating its BIOS call.
second_reads = set()
stopped = []


def record_second(_engine, _access, address, size, _value, _user_data):
    second_reads.update(range(address, address + size))


def stop_after_copy(engine, address, _size, _user_data):
    if address == 0x0804660A:
        stack = engine.reg_read(arm_const.UC_ARM_REG_SP)
        assert struct.unpack('<hhhh', cpu.read(stack + 24, 8)) == (256, 0, 0, 256)
        stopped.append(True)
        engine.emu_stop()


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_second,
                    begin=0x080ABD64, end=0x080ABD6B)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, stop_after_copy)
for selector in (0, 1, 2):
    cpu.write(0x03000000, bytes(0x8000))
    cpu.write(0x02001000, struct.pack('<III', 0x02005000, 0x02002000, 0x02004000))
    cpu.write(0x02002000, struct.pack('<3I', 0x02003000, 0x02003000, 0x02003000))
    cpu.write(0x02003000, bytes(0x100))
    cpu.write(0x02004000, bytes(0x100))
    cpu.write(0x03007F00, struct.pack('<4I', 50, 2, 0x1234, 0))
    for reg, value in ((arm_const.UC_ARM_REG_R0, 0x02001000),
                       (arm_const.UC_ARM_REG_R1, 0),
                       (arm_const.UC_ARM_REG_R2, selector),
                       (arm_const.UC_ARM_REG_R3, 20),
                       (arm_const.UC_ARM_REG_SP, 0x03007F00),
                       (arm_const.UC_ARM_REG_LR, 0x0203FFF1)):
        cpu.engine.reg_write(reg, value)
    stopped.clear()
    cpu.engine.emu_start(0x080465B9, 0x0203FFF0, count=2000)
    assert stopped == [True]

assert second_reads == set(range(0x080ABD64, 0x080ABD6C))
print(f'{cases} native wrapper fixtures and 3 partial renderer fixtures cover both affine initializers')
