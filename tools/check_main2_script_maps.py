"""Verify bounded main-two script maps and their unchecked ROM reads."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
calls, reads = [], set()


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helpers(engine, address, _size, _user_data):
    if address not in (0x0803FB3C, 0x08041C14):
        return
    calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R0)))
    engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def script_pointer(index):
    return struct.unpack_from('<I', rom, 0x485678 + index * 4)[0]


def check_abi(regs):
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x080AFC80, end=0x080AFDB6)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
cases = 0
for flags, phases in ((0, range(256)), (2, range(5))):
    for phase in phases:
        ram = bytearray(0x7100)
        struct.pack_into('<I', ram, 0x6F74, 0x02020000)
        ram[0x1784] = flags
        context = bytearray(0x100)
        struct.pack_into('<I', context, 8, phase)
        expected_context = bytearray(context)
        struct.pack_into('<H', expected_context, 2, 1)
        base = 0xAFC80 if flags == 0 else 0xAFC83
        target = script_pointer(rom[base + phase])
        cpu.write(0x03000000, bytes(ram))
        cpu.write(0x02020000, bytes(context))
        calls.clear()
        regs = cpu.call(0x080657C4, timeout_us=0)
        assert calls == [(0x0803FB3C, target)], (flags, phase, calls)
        assert cpu.read(0x03000000, len(ram)) == ram
        assert cpu.read(0x02020000, len(context)) == expected_context
        check_abi(regs)
        cases += 1

for cursor in range(256):
    ram = bytearray(0x7100)
    struct.pack_into('<I', ram, 0x6F74, 0x02020000)
    context = bytearray(0x100)
    context[5] = cursor
    expected = bytearray(ram)
    if cursor <= 4:
        struct.pack_into('<H', expected, 0x2C30 + 4, cursor * 16 + 0x1C)
    target = 0x080AFCA8 if cursor == 6 else script_pointer(rom[0xAFCB7 + cursor])
    cpu.write(0x03000000, bytes(ram))
    cpu.write(0x02020000, bytes(context))
    calls.clear()
    regs = cpu.call(0x08066280, timeout_us=0)
    assert calls == [(0x08041C14, 0), (0x0803FB3C, target)], (cursor, calls)
    assert cpu.read(0x03000000, len(ram)) == expected, cursor
    assert cpu.read(0x02020000, len(context)) == context
    check_abi(regs)
    cases += 1

assert set(range(0x080AFC80, 0x080AFC88)) <= reads
assert set(range(0x080AFCB7, 0x080AFCBD)) <= reads
assert any(address >= 0x080AFCC0 for address in reads)
print(f'{cases} native script-map fixtures cover all entries and adjacent-ROM reads; helpers stubbed')
