"""Check action selection tables and unchecked adjacent reads in native code."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
calls, reads = [], set()


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helpers(engine, address, _size, _user_data):
    if address == 0x08016138:
        calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R0)))
        engine.reg_write(arm_const.UC_ARM_REG_R0, 1)
    elif address == 0x08015F24:
        calls.append((address,))
    elif address == 0x08042CA0:
        dst = engine.reg_read(arm_const.UC_ARM_REG_R0)
        calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R1)))
        cpu.write(dst, struct.pack('<HH', 96, 120))
    else:
        return
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def check_abi(regs):
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083AD3F0, end=0x083AD5FF)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
cases = 0
for choice in (1, 2):
    base = 0x3AD4F6 if choice == 1 else 0x3AD4FC
    for key in range(256):
        ram = bytearray(0x7100)
        ram[0x1881] = key
        ram[0x1883] = choice
        expected = bytearray(ram)
        expected[0x1881] = rom[base + key]
        expected[0x1883] = 0
        cpu.write(0x03000000, bytes(ram))
        calls.clear()
        regs = cpu.call(0x08016288, timeout_us=0)
        assert calls == [(0x08016138, choice - 1), (0x08015F24,)]
        assert cpu.read(0x03000000, len(ram)) == expected
        check_abi(regs)
        cases += 1

for reverse in (0, 1):
    table = 0x3AD4F6 if reverse == 0 else 0x3AD4FC
    for key in range(256):
        for index in (0, 5, 11):
            initial = rom[table + key]
            step = (index - initial) & 0xFFFFFFFF
            if step > 5:
                step = (step + 6) & 0xFFFFFFFF
            addr = (0x083AD4F0 + step) & 0xFFFFFFFF
            angle = rom[addr - 0x08000000]
            ram = bytearray(0x7100)
            ram[0x1881] = key
            obj = 0x2C30 + index * 64
            ram[obj + 0x21] = 6
            expected = bytearray(ram)
            struct.pack_into('<HHHH', expected, obj, 0, 96, 120, 0x60C + index)
            expected[obj + 8] = expected[obj + 9] = 52
            expected[obj + 0x0A] = 10
            expected[obj + 0x0B] = 8
            expected[obj + 0x20] = angle
            expected[obj + 0x21] = 0
            cpu.write(0x03000000, bytes(ram))
            calls.clear()
            regs = cpu.call(0x08016154, (index, reverse), timeout_us=0)
            assert calls == [(0x08042CA0, angle)], (key, index, reverse, calls)
            assert regs[0] == 1
            assert cpu.read(0x03000000, len(ram)) == expected, (key, index, reverse)
            check_abi(regs)
            cases += 1

assert set(range(0x083AD4F0, 0x083AD502)) <= reads
assert any(address < 0x083AD4F0 or address >= 0x083AD502 for address in reads)
print(f'{cases} native action fixtures cover all three tables and adjacent-ROM reads; helpers stubbed')
