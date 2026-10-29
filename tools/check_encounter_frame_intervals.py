"""Verify encounter interval indexing and signed timer behavior in native 0806AA10."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();table=r[0x485783:0x4857d0];slots=r[0x485764:0x48576d]
cpu=RoutineCpu(r);coverage=set();cases=0
def read(m,a,p,n,v,u):coverage.update(range(p,p+n))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x8485783,end=0x84857cf)
for variant in range(11):
 for speed in range(7):
  threshold=table[variant*7+speed]
  for state in (0,1,2,3,255):
   for timer in (-2147483648,-1,0,threshold-2,threshold-1,threshold,2147483647):
    for frame in (0,65535):
     ram=bytearray([0xa5]*0x7100);ram[0x6f84]=variant
     for i in range(3):
      ram[0x6f8c+i]=state;ram[0x6fd0+i*3:0x6fd3+i*3]=bytes([speed]*3)
      struct.pack_into('<i',ram,0x6fe0+i*4,timer)
      for s in range(3):struct.pack_into('<H',ram,0x2c30+slots[i*3+s]*64+0x1a,frame)
     expected=bytearray(ram)
     for i in range(3):
      if state>2:continue
      t=(timer+1)&0xffffffff;signed=t if t<0x80000000 else t-0x100000000
      if signed>=threshold:
       t=0;b=0x2c30+slots[i*3+state]*64+0x1a
       struct.pack_into('<H',expected,b,(struct.unpack_from('<H',expected,b)[0]+1)&65535)
      struct.pack_into('<I',expected,0x6fe0+i*4,t)
     cpu.write(0x3000000,bytes(ram));regs=cpu.call(0x806aa10,timeout_us=0)
     assert cpu.read(0x3000000,len(expected))==expected,(variant,speed,state,timer,frame)
     assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
     cases+=1
assert coverage==set(range(0x8485783,0x84857d0))
Path('build/more/encounter_frame_intervals_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=len(coverage),scope='Native 0806AA10, no stubs; all 11 variants and seven speed classes, three active and two inactive states, signed timer boundaries including hardware wrap, frame counter wrap; full guarded IWRAM and ABI.'),indent=2)+'\n')
print(cases,'native fixtures;',len(coverage),'table bytes read')
