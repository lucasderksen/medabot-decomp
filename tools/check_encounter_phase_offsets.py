"""Exercise native phase-offset timing with the animation-reset path excluded."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();table=r[0x48576d:0x485783];slots=r[0x485764:0x48576d]
sines=struct.unpack_from('<256h',r,0x3d6a2c);cpu=RoutineCpu(r);coverage=set();cases=0
def read(m,a,p,n,v,u):coverage.update(range(p,p+n))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x848576d,end=0x8485782)
for variant in range(11):
 for phase in range(256):
  for state in (0,1,2,3):
   for timer in (0,20):
    ram=bytearray([0xa5]*0x7100);ram[0x6f84]=variant;ram[0x6f8c:0x6f8f]=bytes([3,state,state])
    struct.pack_into('<I',ram,0x1780,1);ram[0x6fec:0x6fef]=bytes([16]*3);ram[0x6ff0:0x6ff3]=bytes(3)
    for i in range(2):
     struct.pack_into('<i',ram,0x7000+i*4,phase);struct.pack_into('<i',ram,0x6ff8+i*4,timer)
    expected=bytearray(ram)
    if state<=2:
     for i in range(2):
      threshold=((sines[(table[i*11+variant]+phase)&255]>>5)&7)+6;t=timer+1
      if t>=threshold:
       t=0;expected[0x6fed+i]=12;struct.pack_into('<i',expected,0x7000+i*4,phase+1)
       b=0x2c30+slots[(i+1)*3+state]*64+0x1a
       struct.pack_into('<H',expected,b,(struct.unpack_from('<H',expected,b)[0]+3)&65535)
      struct.pack_into('<i',expected,0x6ff8+i*4,t);expected[0x6ff1+i]=1
    cpu.write(0x3000000,bytes(ram));regs=cpu.call(0x806a860,timeout_us=0)
    assert cpu.read(0x3000000,len(expected))==expected,(variant,phase,state,timer)
    assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
    cases+=1
assert coverage==set(range(0x848576d,0x8485783))
Path('build/more/encounter_phase_offsets_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=len(coverage),scope='Native0806A860 with no stubs; two participants,11variants,256phases,3active/1inactive states, firing/nonfiring timers; reset and global recovery branches excluded by fixture setup; full guarded IWRAM and ABI.'),indent=2)+'\n')
print(cases,'native fixtures;',len(coverage),'table bytes read')
