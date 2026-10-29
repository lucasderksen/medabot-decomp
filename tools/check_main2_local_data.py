"""Verify native menu text copy and local callback dispatch."""
import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
from check_dialogue import prepare_cpu,check
r=find_rom().read_bytes();msg=r[0xaf8cd:0xaf920];table=struct.unpack_from('<6I',r,0xaf920);dc,_=prepare_cpu(r);check(dc,msg,0x80af8cd);cpu=RoutineCpu(r);state={};calls=[];reads=set()
def code(m,a,n,u):
 if state['lo']<=a<state['hi'] or 0x807e7a4<=a<0x807e804 or a==0x807ccf0:return
 if a==0x803fb3c:
  ptr=m.reg_read(arm_const.UC_ARM_REG_R0);assert cpu.read(ptr,83)==msg;calls.append(a);m.reg_write(arm_const.UC_ARM_REG_R0,state['result'])
 elif a==0x80415e8:calls.append(a)
 else:assert a==(state['target']&~1),(hex(a),state);calls.append(a)
 m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):reads.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x80af920,end=0x80af937)
for result in (0,1):
 cpu.write(0x3000000,bytes(0x7000));state.update(lo=0x805ca3c,hi=0x805ca74,result=result,target=0);calls.clear();reg=cpu.call(state['lo'],timeout_us=0)
 assert calls==([0x803fb3c,0x80415e8] if result else [0x803fb3c]);assert struct.unpack('<I',cpu.read(0x300137c,4))[0]==result
 assert reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
for i,t in enumerate(table):
 cpu.write(0x300137c,struct.pack('<I',i));state.update(lo=0x805cb20,hi=0x805cb50,result=0,target=t);calls.clear();reg=cpu.call(state['lo'],timeout_us=0)
 assert calls==[t&~1] and reg[4:12]==tuple(0xab000000|j for j in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
assert reads==set(range(0x80af920,0x80af938))
print('2 native message-copy and 6 callback fixtures; original memcpy and call trampoline, dialogue/callbacks stubbed; interpreter boundary check passed')
