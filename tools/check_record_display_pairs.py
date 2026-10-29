"""Check original record-display pair reads, including adjacent ROM bytes."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
calls, reads = [], set()


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def render(engine, address, _size, _user_data):
    if address != 0x08046A60:
        return
    registers = tuple(engine.reg_read(reg) for reg in (
        arm_const.UC_ARM_REG_R0, arm_const.UC_ARM_REG_R1,
        arm_const.UC_ARM_REG_R2, arm_const.UC_ARM_REG_R3))
    stack = engine.reg_read(arm_const.UC_ARM_REG_SP)
    calls.append((registers, struct.unpack('<5I', cpu.read(stack, 20))))
    engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x080AFBB4, end=0x080AFEBF)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, render)
cases = 0
for mode in (0, 1, 2, 7):
    for category in (0, 1, 2, 3, 4, 7, 127, 255):
        for slot in (0, 255):
            offset = category * 2 + mode * 8
            x, y = rom[0xAFBB4 + offset:0xAFBB6 + offset]
            ram = bytearray(0x7100)
            struct.pack_into('<I', ram, 0x2414, 0x02010000)
            display = bytearray([0xA5] * 0x100)
            expected_display = bytearray(display)
            struct.pack_into('<I', expected_display, 8, 0x020260D0 + mode * 0x410)
            cpu.write(0x03000000, bytes(ram))
            cpu.write(0x02026000, bytes(display))
            calls.clear()
            regs = cpu.call(0x08062B48, (slot, category, mode), timeout_us=0)
            expected_call = ((0x02010B84, 0x02026000, slot, category),
                             (y, x, 0x12B, 4 if mode else 0, 6 if mode else 5))
            assert calls == [expected_call], (mode, category, slot, calls)
            assert cpu.read(0x03000000, len(ram)) == ram
            assert cpu.read(0x02026000, len(display)) == expected_display
            assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
            assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
            cases += 1

assert set(range(0x080AFBB4, 0x080AFBC4)) <= reads
assert any(address >= 0x080AFBC4 for address in reads)
print(f'{cases} native record-display fixtures cover all pairs and adjacent reads; renderer stubbed')
