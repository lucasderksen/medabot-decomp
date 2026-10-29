"""Exercise the native equipment scene's four palette DMA transfers."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
cpu.engine.mem_map(0x04000000, 0x1000)
cpu.engine.mem_map(0x05000000, 0x1000)
transfers = []


def stub_helpers(engine, address, _size, _user_data):
    if 0x08069530 <= address < 0x080696A8:
        return
    engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def dma(_engine, _access, _address, _size, control, _user_data):
    if not control & 0x80000000:
        return
    src, dst = struct.unpack('<II', cpu.read(0x040000D4, 8))
    assert control == 0x84000008
    assert 0x087C643C <= src < 0x087C64BC
    assert 0x05000100 <= dst < 0x05000180
    payload = cpu.read(src, 32)
    cpu.write(dst, payload)
    transfers.append((src, dst, payload))


cpu.engine.hook_add(unicorn.UC_HOOK_CODE, stub_helpers)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, dma, begin=0x040000DC, end=0x040000DC)
for selection in range(4):
    cpu.write(0x03000000, bytes(0x7E00))
    cpu.write(0x02000000, bytes(0x40000))
    cpu.write(0x04000000, bytes(0x1000))
    cpu.write(0x05000000, bytes([0xA5]) * 0x1000)
    cpu.write(0x03006F84, bytes([selection]))
    transfers.clear()
    regs = cpu.call(0x08069530, timeout_us=0)
    expected = bytearray([0xA5] * 0x1000)
    expected[0x100:0x180] = rom[0x7C643C:0x7C64BC]
    assert cpu.read(0x05000000, len(expected)) == expected
    assert [(s, d) for s, d, _ in transfers] == [
        (0x087C643C + i * 32, 0x05000100 + i * 32) for i in range(4)]
    assert b''.join(payload for _, _, payload in transfers) == rom[0x7C643C:0x7C64BC]
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

print('4 native equipment scene fixtures cover all four palette DMAs; helpers stubbed')
