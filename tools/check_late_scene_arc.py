"""Original eight-object arc motion, without external stubs."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();table=struct.unpack_from('<64b',r,0x485924);cpu=RoutineCpu(r);coverage=set();cases=0
def read(m,access,a,n,v,u):coverage.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x8485924,end=0x8485963)
for tick in list(range(65))+[255,256,65534,65535]:
 for command in range(5):
  for y in (0,32768,65535):
   ram=bytearray([0xa5]*0x7000)
   for slot in range(40,48):
    b=0x2c30+slot*64;phase=(tick+slot-40)&65535;ram[b+0x20]=command;struct.pack_into('<H',ram,b+0x1a,phase);struct.pack_into('<H',ram,b+4,y)
   expected=bytearray(ram)
   for slot in range(40,48):
    b=0x2c30+slot*64;phase=(tick+slot-40)&65535
    if command in (1,2):struct.pack_into('<HH',expected,b+4,(y-table[phase&63])&65535,16 if phase&8 else 17)
    if command==3:struct.pack_into('<H',expected,b+6,((phase-1 if phase else phase+2)>>2)+19)
   cpu.write(0x3000000,bytes(ram));regs=cpu.call(0x806cf7c,timeout_us=0)
   assert cpu.read(0x3000000,len(expected))==expected,(tick,command,y)
   assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
   cases+=1
assert coverage==set(range(0x8485924,0x8485964))
Path('build/more/late_scene_arc_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=len(coverage),scope='Original0806CF7C, all64arc phases, timer high bits and wrap, five command states, three Y boundaries, eight objects; full guarded IWRAM and ABI; no stubs.'),indent=2)+'\n');print(cases,'native arc fixtures;',len(coverage),'bytes read')
