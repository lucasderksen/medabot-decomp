import sys,struct
from pathlib import Path
sys.path.insert(0,'tools');from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();variants=r[0x3cad78:0x3cad78+124];data=struct.unpack_from('<329I',r,0x7e8ec);ptrs=struct.unpack_from('<59I',r,0x3d2018);counts=[]
for p in ptrs:
 if p==0:counts.append(0);continue
 o=p-0x8000000;j=0
 while j<=254 and r[o+j]!=0:j+=1
 counts.append(j)
cpu=RoutineCpu(r);state={};calls=[];reads=set()
def hook(m,a,n,u):
 if 0x8044a3c<=a<0x8044b28:return
 assert a==0x8047428,hex(a)
 sp=m.reg_read(arm_const.UC_ARM_REG_SP);stack=struct.unpack('<5I',cpu.read(sp,20));group=state['group'];
 assert stack[0]==group and stack[1]==1 and stack[2]==0 and stack[3]==64 and stack[4]==counts[group],(stack,group,counts[group]);calls.append(group)
 m.reg_write(arm_const.UC_ARM_REG_R0,0);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):reads.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,hook);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x807e8ec,end=0x807ee0f)
for row in range(47):
 for v in range(7):
  index=variants.index(v);g=data[row*7+v];assert counts[g]>0; state['group']=g;calls.clear();ram=bytearray([0x5a]*0x1100);ram[0xcc]=0;ram[0xce]=0;cpu.write(0x2026000,bytes(ram))
  regs=cpu.call(0x8044a3c,(0,row,index),timeout_us=0);assert calls==[g] and regs[0]==0 and regs[4:12]==tuple(0xab000000|i for i in range(4,12));assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
  struct.pack_into('<I',ram,8,0x020260d0);ram[0xcc]=1
  assert cpu.read(0x2026000,0x1100)==ram
assert reads==set(range(0x807e8ec,0x807ee10)),(len(reads),len(set(range(0x807e8ec,0x807ee10))))
print('329 pose selection fixtures passed; original selector/count loop, animation interpolation stubbed; guarded work RAM and ABI checked')


