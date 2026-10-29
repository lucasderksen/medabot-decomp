"""Native initial motion/spawn branch of0806C694; sound stubbed."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();limits=struct.unpack_from('<3i',r,0xb00ac);random=r[0x3f7d80:0x3f7e80];cpu=RoutineCpu(r);calls=[];coverage=set();cases=0
def code(m,a,n,u):
 if 0x806c694<=a<0x806c88c:return
 assert a==0x8074de0,hex(a)
 calls.append(m.reg_read(arm_const.UC_ARM_REG_R0));m.reg_write(arm_const.UC_ARM_REG_R0,0);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):coverage.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x80b00ac,end=0x80b00b7)
for tick in range(80):
 for delay in (1,2,3):
  for free in range(9):
   for direction in (0,1):
    ram=bytearray([0xa5]*0x7100);b=0x2c30+30*64;frame=tick*11+delay
    struct.pack_into('<I',ram,0x1780,frame);struct.pack_into('<H',ram,b+0x1a,tick);ram[b+0x20]=delay;ram[b+0x22]=direction
    for i in range(8):ram[0x2c30+(40+i)*64+0x20]=int(i<free)
    expected=bytearray(ram);sound=[]
    if tick<=limits[delay-1] and tick%8==0 and free<8:
     obj=0x2c30+(40+free)*64;expected[obj+0x20]=3;struct.pack_into('<HH',expected,obj+2,(random[(frame+free)&255]&63)+88,144);struct.pack_into('<H',expected,obj+0x1a,0)
     if tick%16==0:sound=[59]
    x,y=struct.unpack_from('<HH',expected,b+2);struct.pack_into('<HH',expected,b+2,(x+(2 if direction else -2))&65535,(y-2)&65535);struct.pack_into('<H',expected,b+0x1a,tick+1)
    cpu.write(0x3000000,bytes(ram));calls.clear();regs=cpu.call(0x806c694,timeout_us=0)
    assert cpu.read(0x3000000,len(expected))==expected and calls==sound,(tick,delay,free,direction)
    assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
    cases+=1
assert coverage==set(range(0x80b00ac,0x80b00b8))
Path('build/more/scene_spawn_limits_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=12,scope='Original0806C694 initial tick0..79 branch only; all three limits, first-free slots0..7/all occupied, both directions. Sound stubbed; whole guarded IWRAM and ABI checked. Later reset/transition branches excluded.'),indent=2)+'\n');print(cases,'native initial-phase fixtures')
