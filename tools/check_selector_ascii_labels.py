import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);seen=set();calls=[]
lengths={}
p=0xac604
while p<0xac71c:
 end=r.index(b'\0',p,0xac71c);lengths[0x8000000+p]=end-p;p=(end+4)&~3
def hook(m,a,n,u):
 if 0x8058c0c<=a<0x8059434:return
 assert 0x08000000<=a<0x08800000,hex(a)
 if a==0x080598c0:
  ptr=m.reg_read(arm_const.UC_ARM_REG_R0);length=m.reg_read(arm_const.UC_ARM_REG_R1)
  if 0x80ac604<=ptr<0x80ac71c:
   assert ptr in lengths and length==lengths[ptr], (hex(ptr),length,lengths.get(ptr))
   assert cpu.read(ptr,length)==r[ptr-0x8000000:ptr-0x8000000+length];seen.add(ptr);calls.append((ptr,length))
 m.reg_write(arm_const.UC_ARM_REG_R0,0);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,hook)
for category in range(8):
 for selection in range(16):
  for t in range(4):
   ram=bytearray(0x7000)
   ram[0x57a0+0x32]=0;struct.pack_into('<H',ram,0x57a0+0x2e,16 if t&1 else 0);ram[0x57e0+0xc5c]=selection;ram[0x57e0+0xcb7]=t;ram[0x57e0+0xc4e]=t;ram[0x57e0+0xc4f]=t%3
   cpu.write(0x3000000,bytes(ram));calls.clear();reg=cpu.call(0x8058c0c,(category,),timeout_us=0)
   assert reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
p=0xac604;starts=[]
while p<0xac71c:
 starts.append(0x8000000+p);p=(r.index(b'\0',p,0xac71c)+4)&~3
missing=set(starts)-seen
assert not missing, [hex(x) for x in sorted(missing)]
print('512 native selector fixtures reached all 64 ASCII labels; renderer and other helpers stubbed')

