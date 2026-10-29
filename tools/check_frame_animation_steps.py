"""Exercise the three animation and movement tables in the original ROM."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


FRAMES = (0, 1, 0, 2)
TIMES8 = (6, 11, 15, 18, 21, 23, 25, 26)
TIMES12 = (1, 3, 5, 7, 9, 12, 15, 18, 21, 25, 30, 36)
cpu = RoutineCpu(find_rom().read_bytes())
reads = set()
calls = []
result = 0


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def stub_timer(engine, address, _size, _user_data):
    if address == 0x0807CDF8:
        calls.append((engine.reg_read(arm_const.UC_ARM_REG_R0),
                      engine.reg_read(arm_const.UC_ARM_REG_R1)))
        engine.reg_write(arm_const.UC_ARM_REG_R0, result)
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def check_abi(regs):
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x080B0108, end=0x080B011F)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, stub_timer)
cases = 0
for mask in range(16):
    for phase in range(4):
        for result in (0, 1):
            ram = bytearray([0xA5] * 0x7100)
            ram[0x7010] = mask
            expected = bytearray(ram)
            expected_calls = []
            for i in range(4):
                obj = 0x2C30 + (0x16 + i) * 64
                ram[obj + 0x21] = expected[obj + 0x21] = phase
                ram[obj + 0x23] = expected[obj + 0x23] = 3 + i
                struct.pack_into('<hh', ram, obj + 0x30, 50 + i, 70 + i)
                struct.pack_into('<hh', expected, obj + 0x30, 50 + i, 70 + i)
                if mask & (1 << i):
                    expected_calls.append((70 + i, 3 + i))
                    if result == 0:
                        new_phase = (phase + 1) & 3
                        expected[obj + 0x21] = new_phase
                        struct.pack_into('<H', expected, obj + 6, 50 + i + FRAMES[new_phase])
                    struct.pack_into('<H', expected, obj + 0x32, 71 + i)
            cpu.write(0x03000000, bytes(ram))
            calls.clear()
            regs = cpu.call(0x08071804, timeout_us=0)
            assert calls == expected_calls
            assert cpu.read(0x03000000, len(ram)) == expected
            check_abi(regs)
            cases += 1

for routine, times, direction in ((0x0807190C, TIMES8, 1),
                                   (0x080719B8, TIMES8, -1),
                                   (0x08071A64, TIMES12, -1),
                                   (0x08071B64, TIMES12, 1)):
    for phase, time in enumerate(times):
        for match in (False, True):
            ram = bytearray([0xA5] * 0x7100)
            obj = 0x2C30 + 64
            struct.pack_into('<h', ram, obj + 2, 100)
            struct.pack_into('<H', ram, obj + 0x1A, time if match else time + 1)
            ram[obj + 0x21] = phase
            ram[obj + 0x22] = 255  # Suppress the transition helper.
            expected = bytearray(ram)
            if match:
                struct.pack_into('<h', expected, obj + 2, 100 + direction)
                expected[obj + 0x21] = phase + 1
            cpu.write(0x03000000, bytes(ram))
            regs = cpu.call(routine, (1,), timeout_us=0)
            assert cpu.read(0x03000000, len(ram)) == expected, (hex(routine), phase, match)
            assert regs[0] == 1
            check_abi(regs)
            cases += 1

assert reads == set(range(0x080B0108, 0x080B0120))
print(f'{cases} native fixtures cover the frame sequence and both movement timing tables')
