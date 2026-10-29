"""Verify main-two callback dispatches with callback bodies stubbed."""
import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();data=[(0x80629dc,0x8062a10,0xafb98,7),(0x8063948,0x80639c4,0xafbe4,13),(0x806463c,0x80646c4,0xafc18,12),(0x80649bc,0x8064a08,0xafc48,4),(0x8064b90,0x8064bbc,0xafc58,2),(0x8065d10,0x8065d44,0xafc88,8),(0x8066824,0x8066870,0xafcc0,13)];cpu=RoutineCpu(r);cpu.engine.mem_map(0x04000000,0x1000);state={};calls=[];seen=set()
def hook(m,a,n,u):
 if state['lo']<=a<state['hi'] or 0x807e7a4<=a<0x807e804 or a==0x807ccf0:return
 assert a==(state['target']&~1),(hex(a),state);calls.append(a);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):
 for j in range(a,a+n):
  if any(0x8000000+start<=j<0x8000000+start+cnt*4 for _,_,start,cnt in data):seen.add(j)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,hook);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x80afb98,end=0x80afcf3)
for lo,hi,start,count in data:
 table=struct.unpack_from('<%dI'%count,r,start)
 for i,target in enumerate(table):
  cpu.write(0x3000000,bytes(0x7000));cpu.write(0x300137c,struct.pack('<I',i));state.update(lo=lo,hi=hi,target=target);calls.clear();reg=cpu.call(lo,timeout_us=0)
  assert calls==[target&~1] and reg[4:12]==tuple(0xab000000|x for x in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
expected=set(j for _,_,start,cnt in data for j in range(0x8000000+start,0x8000000+start+cnt*4));assert seen==expected,(len(seen),len(expected))
print('59 native callback dispatch fixtures; all table bytes read; callback bodies stubbed, ABI checked')
