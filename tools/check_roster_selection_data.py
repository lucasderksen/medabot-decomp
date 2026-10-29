"""Verify bounded roster positions and random starts in native routines."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


POSITIONS = ((10, 6), (13, 8), (16, 10))
STARTS = (0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0)
cpu = RoutineCpu(find_rom().read_bytes())
cpu.engine.mem_map(0x04000000, 0x1000)
reads, calls, rng = set(), [], []


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helpers(engine, address, _size, _user_data):
    if address == 0x080435B0:
        values = tuple(engine.reg_read(reg) for reg in (
            arm_const.UC_ARM_REG_R0, arm_const.UC_ARM_REG_R1,
            arm_const.UC_ARM_REG_R2, arm_const.UC_ARM_REG_R3))
        extra = struct.unpack('<I', cpu.read(engine.reg_read(arm_const.UC_ARM_REG_SP), 4))[0]
        calls.append((address, values, extra))
    elif address == 0x080424B8:
        assert rng
        engine.reg_write(arm_const.UC_ARM_REG_R0, rng.pop(0))
    elif address == 0x08042114:
        calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R0),
                      engine.reg_read(arm_const.UC_ARM_REG_R1)))
        engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    else:
        return
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def check_abi(regs):
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083AD06A, end=0x083AD07F)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
for bg_control in (0, 0xFFFF):
    ram = bytes(0x7100)
    cpu.write(0x03000000, ram)
    cpu.write(0x04000008, struct.pack('<H', bg_control))
    calls.clear()
    regs = cpu.call(0x0803E83C, timeout_us=0)
    assert calls == [(0x080435B0, (0xFF, x, y, bg_control), 0x8300) for x, y in POSITIONS]
    assert cpu.read(0x03000000, len(ram)) == ram
    check_abi(regs)

for i, record in enumerate(STARTS):
    for slot in range(4):
        ram = bytearray(0x7100)
        setup = 0x590 + (record + 3) * 0x100
        ram[setup + 0xBA] = 1
        ram[setup + 0x5F + slot * 0x18] = i + 10
        expected = bytearray(ram)
        expected[0x1968] = slot
        expected[0x1969] = i + 10
        cpu.write(0x03000000, bytes(ram))
        rng[:] = [i, slot]
        calls.clear()
        regs = cpu.call(0x08012234, timeout_us=0)
        assert regs[0] == 1 and not rng
        assert calls == [(0x08042114, i + 10, slot)]
        assert cpu.read(0x03000000, len(ram)) == expected
        check_abi(regs)

assert reads == set(range(0x083AD06A, 0x083AD080))
print('66 native roster fixtures cover every position and random-start entry; helpers stubbed')
