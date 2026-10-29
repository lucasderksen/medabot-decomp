"""Original timed and untimed object dispatch; native signed remainder helper."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);state={};coverage=set();cases=0
ranges=[(0x8485994,0x84859bc),(0x8485b4c,0x8485b65),(0x8485bb8,0x8485bd8)]
assert r[0x485b65:0x485b68]==bytes(3)
def read(m,access,a,n,v,u):
 if any(lo<=a and a+n<=hi for lo,hi in ranges):coverage.update(range(a,a+n))
def code(m,a,n,u):
 if state['start']<=a<state['end'] or 0x807ccf0<=a<0x807cd20 or 0x807cdf8<=a<0x807cec8:return
 assert a in (state['callback'],0x806b718),hex(a)
 state['calls'].append((a,m.reg_read(arm_const.UC_ARM_REG_R0)))
 m.reg_write(arm_const.UC_ARM_REG_R0,state['result'] if a==state['callback'] else 0)
 m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x8485994,end=0x8485bd7)
for start,end,table,count,limit,slots,clear in [(0x806de0c,0x806de9c,0x485994,8,0x4859b4,5,0x22),(0x8070550,0x80705e0,0x485b4c,5,0x485b60,11,0x21),(0x807178c,0x8071804,0x485bb8,8,None,26,0x21)]:
 for index in range(count):
  callback=struct.unpack_from('<I',r,table+index*4)[0]&~1
  ticks=list(range(32))+[65534,65535] if limit else [0,1,65534,65535]
  for slot in range(slots):
   for tick in ticks:
    for result in (0,1,255,2):
     ram=bytearray(0x7000);b=0x2c30+slot*64;ram[b+0x20]=index+1;ram[b+0x21]=0x5a;ram[b+0x22]=0xa5;struct.pack_into('<H',ram,b+0x1a,tick)
     expected=bytearray(ram);next_tick=(tick+1)&65535;struct.pack_into('<H',expected,b+0x1a,next_tick)
     fires=limit is None or next_tick%r[limit+index]==0
     calls=[]
     if fires:
      calls.append((callback,slot))
      if result==0:expected[b+0x20]=0;expected[b+clear]=0
      elif result==255:calls.append((0x806b718,slot))
     state.update(start=start,end=end,callback=callback,result=result,calls=[])
     cpu.write(0x3000000,bytes(ram));regs=cpu.call(start,timeout_us=0)
     assert cpu.read(0x3000000,len(expected))==expected,(hex(start),index,slot,tick,result)
     assert state['calls']==calls,(state['calls'],calls)
     assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
     cases+=1
expected_coverage=set().union(*(set(range(a,b)) for a,b in ranges));assert coverage==expected_coverage
Path('build/more/late_frame_dispatch_tables_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=len(coverage),padding_bytes=3,scope='Original dispatchers and signed remainder helper; callback bodies and reset helper stubbed. All entries/slots, timer wrap, firing and nonfiring intervals, four result values. Full guarded IWRAM, call sequence/arguments, ABI checked.'),indent=2)+'\n')
print(cases,'native fixtures;',len(coverage),'table bytes read + 3 zero alignment bytes')
