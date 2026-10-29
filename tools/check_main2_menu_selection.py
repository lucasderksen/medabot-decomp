"""Exercise main-two menu tables and selected unchecked ROM reads."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
cpu.engine.mem_map(0x04000000, 0x1000)
calls, reads, stop = [], set(), {}


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helpers(engine, address, _size, _user_data):
    if stop and address == stop['address']:
        stop['hit'] = True
        engine.emu_stop()
        return
    if address in (0x08041C14, 0x08074B88, 0x08074DE0):
        calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R0)))
        engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def check_abi(regs):
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x080AF9C8, end=0x080BF9FF)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
cases = 0
effect_indices = list(range(121)) + [255, 256, 1023, 65535]
for mode, indices in ((0, range(256)), (1, effect_indices)):
    for index in indices:
        ram = bytearray(0x7100)
        struct.pack_into('<I', ram, 0x6F74, 0x02020000)
        ram[0x58C] = 1
        context = bytearray(0x100)
        context[5] = mode
        if mode == 0:
            context[0x2B] = index
        else:
            struct.pack_into('<H', context, 0x2C, index)
        expected_ram = bytearray(ram)
        struct.pack_into('<H', expected_ram, 0x2C30 + 4, 32 + 16 * mode)
        expected_context = bytearray(context)
        if mode == 0:
            expected_calls = [(0x08041C14, 0), (0x08074B88, rom[0xAF9CC + index])]
        else:
            expected_context[0x4B] = 2
            expected_context[0x4A] = rom[0xAFA00 + index]
            expected_calls = [(0x08041C14, 0), (0x08074B88, 0), (0x08074DE0, 0)]
        cpu.write(0x03000000, bytes(ram))
        cpu.write(0x02020000, bytes(context))
        calls.clear()
        regs = cpu.call(0x0805F488, timeout_us=0)
        assert calls == expected_calls, (mode, index, calls)
        assert cpu.read(0x03000000, len(ram)) == expected_ram, (mode, index)
        assert cpu.read(0x02020000, len(context)) == expected_context, (mode, index)
        check_abi(regs)
        cases += 1

# Stop immediately after each keyboard-column lookup: later rendering uses
# the resulting value as another index, which may be invalid in these probes.
for direction, stop_address, expected_row in ((0x40, 0x0805EB86, 2),
                                               (0x80, 0x0805EBB0, 0)):
    for index in range(256):
        ram = bytearray(0x7100)
        struct.pack_into('<I', ram, 0x6F74, 0x02020000)
        ram[0x1798] = direction
        context = bytearray(0x100)
        context[0x0D] = index
        context[0x0E] = 3
        cpu.write(0x03000000, bytes(ram))
        cpu.write(0x02020000, bytes(context))
        calls.clear()
        stop.update(address=stop_address, hit=False)
        cpu.engine.reg_write(arm_const.UC_ARM_REG_SP, 0x03007F00)
        cpu.engine.reg_write(arm_const.UC_ARM_REG_LR, 0x0203FFF1)
        cpu.engine.emu_start(0x0805EA45, 0x0203FFF0, count=20000)
        assert stop['hit'], (direction, index)
        assert cpu.read(0x0202000D, 2) == bytes((rom[0xAF9C8 + index], expected_row))
        assert calls == [(0x08074DE0, 2)]
        cases += 1
stop.clear()

assert set(range(0x080AF9C8, 0x080AF9CB)) <= reads
assert set(range(0x080AF9CC, 0x080AFA00)) <= reads
assert set(range(0x080AFA00, 0x080AFA76)) <= reads
assert 0x080BF9FF in reads
print(f'{cases} native menu fixtures cover all three tables and selected adjacent reads; helpers stubbed')
