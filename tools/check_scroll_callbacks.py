import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);state={};calls=[];reads=set()
def hook(m,a,n,u):
 if state['lo']<=a<state['hi'] or a==0x807ccf0:return
 assert a==(state['target']&~1),(hex(a),state);calls.append(a);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):reads.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,hook);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x80b0020,end=0x80b0057)
for lo,hi,start,delta in [(0x8067b9c,0x8067bdc,0xb0020,-1),(0x8068400,0x8068440,0xb003c,1)]:
 table=struct.unpack_from('<7I',r,start)
 for i,target in enumerate(table):
  for y in (0,0xffff):
   cpu.write(0x3000000,bytes(0x7000));cpu.write(0x300137c,struct.pack('<I',i));cpu.write(0x300057e,struct.pack('<H',y));state.update(lo=lo,hi=hi,target=target);calls.clear();reg=cpu.call(lo,timeout_us=0)
   assert calls==[target&~1] and struct.unpack('<H',cpu.read(0x300057e,2))[0]==(y+delta)&0xffff
   assert reg[4:12]==tuple(0xab000000|x for x in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
assert reads==set(range(0x80b0020,0x80b0058))
print('28 native callback fixtures cover both seven-entry tables and scroll wrap; callbacks stubbed')
