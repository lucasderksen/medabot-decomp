"""Check the original main-two setup's object palette transfer."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
cpu.engine.mem_map(0x04000000, 0x1000)
cpu.engine.mem_map(0x05000000, 0x1000)
transfers = []


def helpers(engine, address, _size, _user_data):
    if 0x0806030C <= address < 0x08060400:
        return
    if address == 0x0807CCC0:
        src, dst, ctl = (engine.reg_read(reg) for reg in (
            arm_const.UC_ARM_REG_R0, arm_const.UC_ARM_REG_R1, arm_const.UC_ARM_REG_R2))
        size = ((ctl & 0x1FFFFF) + 7) // 8 * 32
        assert not ctl & 0x01000000
        data = cpu.read(src, size)
        cpu.write(dst, data)
        transfers.append((src, dst, size))
    engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
for value in (0, 1, 127, 255):
    cpu.write(0x03000000, bytes(0x7E00))
    cpu.write(0x02000000, bytes(0x40000))
    cpu.write(0x04000000, bytes(0x1000))
    cpu.write(0x05000000, bytes([0xA5]) * 0x1000)
    cpu.write(0x03006F74, struct.pack('<I', 0x02020000))
    cpu.write(0x0300137C, struct.pack('<I', value))
    transfers.clear()
    regs = cpu.call(0x0806030C, timeout_us=0)
    assert (0x080AFB00, 0x05000200, 32) in transfers
    expected = bytearray([0xA5] * 0x1000)
    expected[0:224] = rom[0x792E9C:0x792F7C]
    expected[0x200:0x220] = rom[0xAFB00:0xAFB20]
    assert cpu.read(0x05000000, 0x1000) == expected
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

print('4 native setup fixtures cover the OBJ palette transfer; other helpers stubbed')
