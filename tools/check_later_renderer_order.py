"""Probe the renderer's original lookup instructions, not the full routine."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
assert sorted(rom[0x81490:0x814C2]) == list(range(50))
selectors = [struct.unpack_from('<I', rom, offset)[0] & 0x3F
             for offset in range(0x7EE70, 0x81490, 4)]
assert max(selectors) == 49
for index in range(256):
    cpu.engine.reg_write(arm_const.UC_ARM_REG_R10, index)
    cpu.engine.emu_start(0x08046627, 0x0804662C, count=3)
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_R1) == rom[0x81490 + index], index

print('256 partial native lookup probes cover all byte indices, including neighboring ROM')
