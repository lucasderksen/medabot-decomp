"""Exercise scene coordinate consumers, including adjacent ROM reads."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
calls, reads = [], set()


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helpers(engine, address, _size, _user_data):
    if address not in (0x08017994, 0x08040D0C):
        return
    calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R0),
                  engine.reg_read(arm_const.UC_ARM_REG_R1),
                  engine.reg_read(arm_const.UC_ARM_REG_R2)))
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def check_abi(regs):
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083AD524, end=0x083AD524 + 2047)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
cases = 0
for bank in (0, 1, 2, 3, 31, 255):
    for choice in (0, 1, 2, 3, 31, 255):
        offset = (bank * 3 + choice) * 2
        x, y = rom[0x3AD524 + offset:0x3AD526 + offset]
        ram = bytearray(0x7100)
        ram[0x47C] = bank
        ram[0x47D] = choice
        expected = bytearray(ram)
        obj = 0x2C30 + 8 * 64
        struct.pack_into('<HHHH', expected, obj, 0xC404,
                         (x + (16 if bank == 0 else -16)) & 0xFFFF, y,
                         0x306 if bank == 0 else 0x307)
        expected[obj + 0x0A] = 14
        expected[obj + 0x0B] = 0xC0
        cpu.write(0x03000000, bytes(ram))
        regs = cpu.call(0x08017B24, timeout_us=0)
        assert cpu.read(0x03000000, len(ram)) == expected, (bank, choice)
        check_abi(regs)
        cpu.write(0x03000000, bytes(ram))
        calls.clear()
        regs = cpu.call(0x080183A4, timeout_us=0)
        assert not calls and cpu.read(0x03000000, len(ram)) == ram
        check_abi(regs)
        cases += 2

for first in (0, 3, 4, 6):
    for shift in (0, 1):
        ram = bytearray(0x7100)
        for index in range(first, first + 3):
            ram[0x590 + index * 0x100 + 0x40] = 1
        cpu.write(0x03000000, bytes(ram))
        calls.clear()
        regs = cpu.call(0x08017A14, (first, shift), timeout_us=0)
        expected_calls = []
        for index in range(first, first + 3):
            x, y = rom[0x3AD524 + 2 * index:0x3AD526 + 2 * index]
            if shift:
                x += -0x68 if index <= 2 else 0x68
            expected_calls.append((0x08017994, index, x & 0xFFFFFFFF, y))
        assert calls == expected_calls and cpu.read(0x03000000, len(ram)) == ram
        check_abi(regs)
        cases += 1

for bank in (0, 1, 2, 10):
    ram = bytearray(0x7100)
    ram[0x47C] = bank
    ram[0x480] = 3
    for index in range(bank * 3, bank * 3 + 3):
        ram[0x590 + index * 0x100 + 0x40] = 1
    expected = bytearray(ram)
    expected[0x480] = 4
    cpu.write(0x03000000, bytes(ram))
    calls.clear()
    regs = cpu.call(0x080187D4, timeout_us=0)
    expected_calls = [(0x08040D0C, i, 1) for i in range(4, 8)]
    assert [(a, b, c) for a, b, c, _ in calls[:4]] == expected_calls
    for i, index in enumerate(range(bank * 3, bank * 3 + 3)):
        x, y = rom[0x3AD524 + index * 2:0x3AD526 + index * 2]
        x += -80 if bank == 0 else 80
        assert calls[i + 4] == (0x08017994, index, x & 0xFFFFFFFF, y)
    assert len(calls) == 7 and regs[0] == 0
    assert cpu.read(0x03000000, len(ram)) == expected
    check_abi(regs)
    cases += 1

assert set(range(0x083AD524, 0x083AD530)) <= reads
assert any(address >= 0x083AD530 for address in reads)
print(f'{cases} native fixtures cover all six coordinate pairs and adjacent-ROM reads; helpers stubbed')
