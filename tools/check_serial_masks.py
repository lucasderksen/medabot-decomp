import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
cpu=RoutineCpu(find_rom().read_bytes());cpu.engine.mem_map(0x4000000,0x1000);reads=set()
def read(m,access,a,n,v,u):reads.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x80af864,end=0x80af867)
for bits in range(4):
 cpu.write(0x3000000,bytes(0x7000));cpu.write(0x4000000,bytes(0x1000));cpu.write(0x4000128,struct.pack('<I',bits<<4));reg=cpu.call(0x805bb0c,timeout_us=0)
 assert cpu.read(0x3000b90,1)==bytes([bits]) and reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
assert reads==set(range(0x80af864,0x80af868))
print('4 native serial fixtures cover all mask bytes; original memcpy runs without stubs')

