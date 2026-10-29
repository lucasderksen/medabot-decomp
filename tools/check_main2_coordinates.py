import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);cpu.engine.mem_map(0x4000000,0x1000);seen=set()
def read(m,access,a,n,v,u):seen.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x80afb80,end=0x80afb87)
for selection in range(5):
 for frame in (0,8):
  for block in (0,31):
   cpu.write(0x3000000,bytes(0x7000));cpu.write(0x3006f74,struct.pack('<I',0x3001000));cpu.write(0x3001038,struct.pack('<H',12));cpu.write(0x4000000,bytes(0x1000));cpu.write(0x400000c,struct.pack('<H',block<<8))
   initial=bytes([0x12,0x03])*0x8000;expect=bytearray(initial);cpu.write(0x6000000,initial);base=block<<11;tile=(selection*4+12+5)|0xc000
   for n,offset in enumerate((0x152,0x154,0x192,0x194)):struct.pack_into('<H',expect,base+offset,(tile+n)&0xffff)
   for i in range(4):
    col,row=r[0xafb80+i*2:0xafb82+i*2];palette=0x6000 if frame&8 and i==selection else 0x5000
    for k in range(8):
     for y in (row,row+1):
      p=base+col*2+y*64+k*2;v=struct.unpack_from('<H',expect,p)[0];struct.pack_into('<H',expect,p,(v&0xfff)|palette)
   reg=cpu.call(0x8060be4,(selection,frame),timeout_us=0);assert cpu.read(0x6000000,len(initial))==expect
   assert reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
assert seen==set(range(0x80afb80,0x80afb88))
print('20 native menu tile fixtures cover all four coordinate pairs; no helpers stubbed')
