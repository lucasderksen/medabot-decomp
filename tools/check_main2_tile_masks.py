import struct,itertools
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();masks=struct.unpack_from('<9H',r,0xaf8b8);cpu=RoutineCpu(r);cpu.engine.mem_map(0x04000000,0x1000);reads=set()
def read(m,access,a,n,v,u):reads.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x80af8b8,end=0x80af8c9)
for selected in range(4):
 for choices in itertools.product(range(3),repeat=3):
  cpu.write(0x4000000,bytes(0x1000));cpu.write(0x3001788,bytes([choices[0]]));cpu.write(0x3001360,bytes([choices[1]]));cpu.write(0x3000b94,bytes([choices[2]]))
  initial=bytes([0xbc,0x0a])*0x2000;expected=bytearray(initial);cpu.write(0x6000000,initial)
  for row in range(3):
   for col in range(3):
    mask=masks[row*3+col]
    for k in range(16):
     if mask & (0x8000>>k):
      pal=(0xa000 if selected==row else 0x9000) if choices[row]==col else 0x8000
      struct.pack_into('<H',expected,(((row*3+11)*32)+7+k)*2,pal|0x0abc)
  reg=cpu.call(0x805be0c,(selected,),timeout_us=0);assert cpu.read(0x6000000,len(initial))==expected
  assert reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
assert reads==set(range(0x80af8b8,0x80af8ca))
print('108 native mask fixtures cover all nine halfwords and VRAM guard; no helpers stubbed')
