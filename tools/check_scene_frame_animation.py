"""Run original scene animation advance and initializer; no helper stubs."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();rows=[struct.unpack_from('<Hh4B',r,0x4857fc+i*8) for i in range(32)]
assert all(x[2]<32 and x[3:]==(0,0,0) for x in rows)
cpu=RoutineCpu(r);coverage=set();cases=0
def read(m,access,a,n,v,u):coverage.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x84857fc,end=0x84858fb)
def run(start,initial,expected,args=()):
 global cases
 cpu.write(0x3000000,bytes(initial));regs=cpu.call(start,args,timeout_us=0)
 assert cpu.read(0x3000000,len(expected))==expected,(hex(start),cases)
 assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
 cases+=1
for index in range(32):
 for tick in range(256):
  ram=bytearray([0xa5]*0x7000)
  for slot in range(20):
   b=0x2c30+slot*64;ram[b+0x21]=index;ram[b+0x27]=(tick+slot)&255
  expected=bytearray(ram)
  if index:
   frame,duration,nxt,*pad=rows[index]
   for slot in range(20):
    b=0x2c30+slot*64;old=ram[b+0x27]
    expected[b+0x27]=(old+1)&255
    if duration<=old:
     expected[b+0x27]=0;expected[b+0x21]=nxt;struct.pack_into('<H',expected,b+6,rows[nxt][0])
  run(0x806b4c8,ram,expected)
for slot in range(20):
 for state,record,saved in [(1,1,51),(2,3,51),(3,7,51),(4,11,256),(5,15,263)]:
  for first,second in [(0,0),(1,2),(128,255),(255,128)]:
   ram=bytearray([0xa5]*0x7000);b=0x2c30+slot*64;ram[b+0x20]=0;expected=bytearray(ram)
   expected[b+0x20]=state;expected[b+0x21]=record;expected[b+0x22]=first>>1 if state in(2,3) else first
   if state==1:expected[b+0x23]=second
   struct.pack_into('<H',expected,b+6,rows[record][0]);struct.pack_into('<H',expected,b+0x30,saved);struct.pack_into('<H',expected,b+0x1a,0)
   run(0x806b530,ram,expected,(slot,state,first,second))
expected_reads={0x84857fc+i*8+j for i in range(1,32) for j in range(5)}
assert coverage==expected_reads,(len(coverage),sorted(expected_reads-coverage))
Path('build/more/scene_animation_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=len(coverage),padding_bytes=96,inactive_record_payload_bytes=5,scope='Original animation advance and five table-backed initializer states. All 32 indices, all byte timers, all 20 frame slots, 400 initializer cases; full guarded IWRAM and ABI, no stubs. Index0 is inactive; its five payload bytes are not read.'),indent=2)+'\n')
print(cases,'native fixtures;',len(coverage),'payload bytes read; 96 padding + 5 inactive payload bytes verified structurally')
