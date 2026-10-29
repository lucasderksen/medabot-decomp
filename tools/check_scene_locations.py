import sys,struct
sys.path.insert(0,'tools');from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
from check_dialogue import prepare_cpu,check
from dialogue import decode
r=find_rom().read_bytes(); ptrs=struct.unpack_from('<10I',r,0x484f98); cpu,_=prepare_cpu(r)
for i,p in enumerate(ptrs):
 off=p-0x8000000; end=decode(r,off,end=0x484f98)[-1].end
 print('message',i,check(cpu,r[off:end],p)['calls'],flush=True)
cpu=RoutineCpu(r);state={};calls=[];reads=set()
def code(m,a,n,u):
 if 0x8060a1c<=a<0x8060a54:return
 assert a in (0x803fb3c,0x80605a0,0x8060620),hex(a)
 calls.append(a)
 if a==0x803fb3c:
  assert m.reg_read(arm_const.UC_ARM_REG_R0)==ptrs[state['index']]
  m.reg_write(arm_const.UC_ARM_REG_R0,state['done'])
 else:m.reg_write(arm_const.UC_ARM_REG_R0,0)
 m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):reads.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x8484f98,end=0x8484fbf)
for index in range(10):
 for done in range(2):
  state.update(index=index,done=done);calls.clear();ram=bytearray([0xa5]*0x7000);struct.pack_into('<I',ram,0x6f74,0x02010000);context=bytearray([0x5a]*0x40);context[0x17]=index;cpu.write(0x2000000,bytes([0x5a])*0x10000+context);cpu.write(0x3000000,bytes(ram));reg=cpu.call(0x8060a1c,timeout_us=0)
  if done:struct.pack_into('<I',ram,0x137c,0xa5a5a5a6)
  assert cpu.read(0x3000000,0x7000)==ram and cpu.read(0x2010000,0x40)==context
  assert calls==[0x803fb3c,0x80605a0,0x8060620] and reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
assert reads==set(range(0x8484f98,0x8484fc0))
print('20 selector fixtures and 10 interpreter boundary checks passed; dialogue/update helpers stubbed during selection; interpreter drawing, BIOS and sound stubbed.')
