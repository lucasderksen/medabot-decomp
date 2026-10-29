"""Native inventory initialization, copy, rank and division; level supplier stubbed."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();table=r[0x3b62d8:0x3b64b8];cpu=RoutineCpu(r);state={};coverage=set();cases=0
def code(m,a,n,u):
 if any(lo<=a<hi for lo,hi in ((0x8041d70,0x8041fe4),(0x8041d04,0x8041d28),(0x80420c4,0x8042114),(0x807cd20,0x807cfd0))):return
 assert a==0x804206c,hex(a);state['calls']+=1;m.reg_write(arm_const.UC_ARM_REG_R0,state['level']);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):coverage.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x83b62d8,end=0x83b64b7)
for kind in range(30):
 record=table[kind*16:kind*16+16]
 for free in range(31):
  for level in (0,9,10,19,20,29,30,59,60,99,100,255):
   ram=bytearray([0xa5]*0x7000)
   for i in range(30):ram[0xbe0+i*64]=i|(128 if i<free else 0)
   expected=bytearray(ram);expected[0x52e:0x53e]=record
   if free<30:
    b=0xbe0+free*64;expected[b]|=128;expected[b+1]=kind;struct.pack_into('<H',expected,b+2,(level+1)*100);expected[b+4]=record[1];expected[b+5]=level;expected[b+6]=record[2];expected[b+7]=record[7]
    expected[b+8]=max([i+1 for i,t in enumerate(record[3:7]) if t and level>=t] or [0])
    expected[b+32:b+40]=bytes(min(100,v*(level//10+1)) for v in record[8:16])
   cpu.write(0x3000000,bytes(ram));state.update(level=level,calls=0);regs=cpu.call(0x8041d70,(kind,),timeout_us=0)
   assert regs[0]==free and state['calls']==int(free<30) and cpu.read(0x3000000,len(expected))==expected,(kind,free,level)
   assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
   cases+=1
assert coverage==set(range(0x83b62d8,0x83b64b8))
Path('build/more/inventory_kind_metadata_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=len(coverage),scope='Original08041D70 with native byte copy,rank selection and integer division; only0804206C level supplier stubbed.30 kinds,all30 first-free slots/all occupied,12 injected level boundaries. Exact return,full guarded IWRAM and ABI checked; all480 metadata bytes read.'),indent=2)+'\n');print(cases,'native metadata fixtures;',len(coverage),'bytes read')
