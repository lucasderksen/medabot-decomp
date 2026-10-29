"""Verify original state-three dispatch tables with callbacks stubbed."""
import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();tables=[struct.unpack_from('<8I',r,0x4856e8),struct.unpack_from('<5I',r,0x485708),struct.unpack_from('<5I',r,0x48571c),struct.unpack_from('<13I',r,0x485730)];ranges=[(0x8068440,0x8068460),(0x8068888,0x80688e0),(0x80688e0,0x8068920),(0x8068dd0,0x8068e00)];cpu=RoutineCpu(r);cpu.engine.mem_map(0x04000000,0x1000);state={};calls=[];reads=set()
def hook(m,a,n,u):
 if state['lo']<=a<state['hi'] or a==0x807ccf0:return
 assert a==(state['target'] & ~1),(hex(a),hex(state['target']));calls.append(a);m.reg_write(arm_const.UC_ARM_REG_R0,state['result']);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):reads.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,hook);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x84856e8,end=0x8485763)
cases=0
for kind,table in enumerate(tables):
 for index,target in enumerate(table):
  for result in (0,1):
   ram=bytearray(0x7000);struct.pack_into('<I',ram,0,9);ram[4]=index;struct.pack_into('<I',ram,0x2b8c,index);struct.pack_into('<I',ram,0x137c,index);ram[0x6f90]=1;cpu.write(0x3000000,bytes(ram));cpu.write(0x4000000,bytes([0xff])*0x1000)
   state.update(lo=ranges[kind][0],hi=ranges[kind][1],target=target,result=result);calls.clear();regs=cpu.call(state['lo'],timeout_us=0)
   assert calls==[target&~1],(kind,index,calls,hex(target));assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
   if kind in (1,2):
    assert regs[0]==result and struct.unpack('<I',cpu.read(0x3000000,4))[0]==(0 if result else 10)
    if kind==1: assert struct.unpack('<H',cpu.read(0x4000000,2))[0] == (0xfeff if index==3 and result else 0xffff)
   cases+=1
assert reads==set(range(0x84856e8,0x8485764)),len(reads)
print(cases,'native dispatch fixtures across all 31 entries; callbacks stubbed, return/counter and ABI checked')
