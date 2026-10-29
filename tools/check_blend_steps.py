import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);cpu.engine.mem_map(0x04000000,0x1000);reads=set()
def read(m,access,a,n,v,u):reads.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x80af868,end=0x80af8bb)
for value in list(range(162))+[0xffff,0x10000,0x1ffff]:
 cpu.write(0x4000000,bytes([0xa5])*0x1000);reg=cpu.call(0x805bc5c,(value,),timeout_us=0)
 value16=value&0xffff;n=value16 if value16<=160 else 0;word=struct.unpack_from('<I',r,0xaf868+(n//8)*4)[0]
 assert struct.unpack('<HHH',cpu.read(0x4000050,6))==(0x844,(word|0x1000)&0xffff,8)
 assert reg[0]==n+1 and reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
assert reads==set(range(0x80af868,0x80af8bc))
print('165 native blend fixtures cover all 20 words and the adjacent mask word; no helpers stubbed')
