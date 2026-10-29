"""Check native fixed-count frame and coordinate table consumers."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


FRAMES = (0x19, 0x1C, 0x04, 0x07)
POSITIONS = ((150, 240), (170, 248), (198, 248), (218, 240))
rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
calls, reads = [], set()


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helpers(engine, address, _size, _user_data):
    if address not in (0x0803D450, 0x08040B90, 0x0803D4AC):
        return
    calls.append((address, engine.reg_read(arm_const.UC_ARM_REG_R0),
                  engine.reg_read(arm_const.UC_ARM_REG_R1)))
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def check_abi(regs):
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083AE060, end=0x083AE063)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083AFACC, end=0x083AFADB)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
for slot in (0, 1, 2):
    ram = bytearray(0x7100)
    ram[0x1888] = slot
    struct.pack_into('<hh', ram, 0x2C30 + (0x5A + slot * 4) * 64 + 2, 100, 200)
    expected = bytearray(ram)
    for i, frame in enumerate(FRAMES):
        obj = 0x2C30 + (0x26 + i) * 64
        struct.pack_into('<HhhH', expected, obj, 0xC404, 100, 204, 0x4D01)
        expected[obj + 0x0A] = 7
        expected[obj + 0x0B] = 0xF0
        expected[obj + 0x24] = 6
        expected[obj + 0x25] = frame
    expected[0x18AA] = 1
    cpu.write(0x03000000, bytes(ram))
    regs = cpu.call(0x08024488, timeout_us=0)
    assert cpu.read(0x03000000, len(ram)) == expected, slot
    check_abi(regs)

command = struct.unpack_from('<I', rom, 0x3B6100 + 4 * 4)[0]
for mirror in (0, 2):
    ram = bytearray(0x7100)
    ram[0x18F8] = mirror
    struct.pack_into('<4H', ram, 0x1902, 1, 2, 3, 4)
    expected = bytearray(ram)
    for i, (x, y) in enumerate(POSITIONS):
        obj = 0x2C30 + (10 + i) * 64
        struct.pack_into('<Hhh', expected, obj, 0xC004, (0xF6 - x) & 0x1FF if mirror else x, y)
        expected[obj + 0x0A] = 14
        expected[obj + 0x0B] = 0x80
        expected[obj + 0x24] = 3
        expected[obj + 0x25] = 2
        expected[obj + 0x29] = 11
        expected[obj + 0x2B] = 1
        expected[obj + 0x2C] = 1
        expected[obj + 0x2D] = 4
    cpu.write(0x03000000, bytes(ram))
    calls.clear()
    regs = cpu.call(0x0803B0C0, timeout_us=0)
    assert cpu.read(0x03000000, len(ram)) == expected, mirror
    assert [call[0] for call in calls] == [0x0803D450] + [0x08040B90] * 4 + [0x0803D4AC]
    assert [call[1:] for call in calls[1:5]] == [(command, i) for i in range(10, 14)]
    check_abi(regs)

assert set(range(0x083AE060, 0x083AE064)) <= reads
assert all(0x083AFACC + i * 4 + offset in reads for i in range(4) for offset in (0, 1, 2))
print('5 native fixtures cover four frame entries and four coordinate records; scene helpers stubbed')
