"""Check native phase limits and the phase-zero preceding-ROM read."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
calls, reads = [], set()


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def sound(engine, address, _size, _user_data):
    if address == 0x08074DE0:
        calls.append(engine.reg_read(arm_const.UC_ARM_REG_R0))
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083AE94F, end=0x083AE952)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, sound)
cases = 0
for phase in (0, 1, 2, 3):
    for timer in (0, 1, 7, 59, 60, 79, 80, 65535):
        ram = bytearray(0x7100)
        ram[0x4C4] = phase
        struct.pack_into('<H', ram, 0x4C6, timer)
        struct.pack_into('<H', ram, 0x2C30 + 0x858, 100)
        expected = bytearray(ram)
        expected_calls = []
        if phase <= 2:
            if timer == 0:
                phase_after = phase + 1
                expected[0x4C4] = phase_after
                expected_calls = [0x4C]
            else:
                phase_after = phase
            next_timer = (timer + 1) & 0xFFFF
            limit = rom[0x3AE950 + phase_after - 1]
            struct.pack_into('<H', expected, 0x4C6, 0 if next_timer == limit else next_timer)
        cpu.write(0x03000000, bytes(ram))
        calls.clear()
        regs = cpu.call(0x0802BE44, timeout_us=0)
        assert cpu.read(0x03000000, len(ram)) == expected, (phase, timer)
        assert calls == expected_calls
        assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
        cases += 1

assert reads == set(range(0x083AE94F, 0x083AE953))
print(f'{cases} native phase fixtures cover all limits and the preceding-ROM read; sound stubbed')
