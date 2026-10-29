"""Native scene dispatch and bridge-label token consumers; callbacks/DMA modeled."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);cpu.engine.mem_map(0x4000000,0x1000)
ranges = [(0x84857d0, 0x84857fc), (0x84858fc, 0x8485924), (0x8485964, 0x8485994), (0x84859bc, 0x84859d8), (0x84859d8, 0x8485a08), (0x8485a08, 0x8485a58), (0x8485a80, 0x8485acc), (0x8485acc, 0x8485aec), (0x8485b68, 0x8485bb4), (0x8485bd8, 0x8485c00)]
state={};coverage=set();cases=0
def code(m,a,n,u):
 if state['start']<=a<state['end'] or 0x807ccf0<=a<0x807cd20:return
 assert 0x8000000<=a<0x8080000,hex(a)
 args=tuple(m.reg_read(getattr(arm_const,'UC_ARM_REG_R'+str(i))) for i in range(4))
 state['calls'].append((a,args))
 if a==state.get('callback') and state.get('clear'):
  cpu.write(0x3002c30+args[0]*64+0x20,b'\0')
 m.reg_write(arm_const.UC_ARM_REG_R0,state.get('result',0) if a==state.get('callback') else 0)
 m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):
 if any(lo<=a and a+n<=hi for lo,hi in ranges):coverage.update(range(a,a+n))
def dma(m,access,a,n,v,u):
 assert n==4 and v==0x8000000d
 src,dst=struct.unpack('<II',cpu.read(0x40000d4,8));assert(src,dst)==(0x30018d2,0x600fc44)
 cpu.write(dst,cpu.read(src,26));state['dma']+=1
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x8485700,end=0x8485bff)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE,dma,begin=0x40000dc,end=0x40000dc)
def begin(start,end):
 state.clear();state.update(start=start,end=end,calls=[],dma=0)
 return bytearray(0x7000)
def run(initial,expected,args=(),result=None,vram=None):
 global cases
 cpu.write(0x3000000,bytes(initial));cpu.write(0x6000000,bytes([0xa5])*0x18000)
 regs=cpu.call(state['start'],args,timeout_us=0)
 assert cpu.read(0x3000000,len(expected))==expected,(hex(state['start']),cases,'RAM')
 assert cpu.read(0x6000000,0x18000)==(vram if vram is not None else bytes([0xa5])*0x18000)
 assert result is None or regs[0]==result,(hex(state['start']),regs[0],result)
 assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
 cases+=1
for start,end,table,count,extra_before,extra_after in [(0x806b744,0x806b764,0x4858fc,10,[],[]),(0x806d588,0x806d5b4,0x485964,12,[0x806d4a4],[0x806de0c,0x806d41c]),(0x806e130,0x806e150,0x4859bc,7,[],[]),(0x806e460,0x806e484,0x4859d8,12,[],[0x806e404]),(0x806ea98,0x806eac0,0x485a08,20,[0x806e9e0],[0x806ea54]),(0x80708d8,0x8070914,0x485b68,19,[],[]),(0x8071ddc,0x8071dfc,0x485bd8,10,[],[])]:
 for index in range(count):
  for mask in (range(4) if start==0x80708d8 else [0]):
   ram=begin(start,end);ram[0x1810 if start==0x8071ddc else 0x137c]=index
   before=list(extra_before)
   if start==0x80708d8:
    ram[0x180c]=mask&1;ram[0x180d]=mask>>1
    if mask&1:before.append(0x8070804)
    if mask&2:before.append(0x8070824)
   cb=struct.unpack_from('<I',r,table+index*4)[0]&~1;state.update(callback=cb,result=0xfedcba98)
   run(ram,ram,result=0xfedcba98 if start==0x8071ddc else None)
   assert [a for a,args in state['calls']]==before+[cb]+extra_after
for index in range(11):
 for slot in range(20):
  for outcome in range(3):
   ram=begin(0x806b0d4,0x806b130);base=0x2c30+slot*64;ram[base+0x20]=index+1;struct.pack_into('<H',ram,base+0x1a,0xffff)
   expected=bytearray(ram);cb=struct.unpack_from('<I',r,0x4857d0+index*4)[0]&~1
   state.update(callback=cb,result=int(outcome==1),clear=outcome==2)
   if outcome==1:struct.pack_into('<H',expected,base+0x1a,0)
   if outcome==2:expected[base+0x20]=0
   run(ram,expected)
   assert [a for a,args in state['calls']]==[cb]+([0x806b530] if outcome==0 else [])
   assert state['calls'][0][1][0]==slot
   if outcome==0:assert state['calls'][1][1]==(slot,0,0,0)
for index,p in enumerate(struct.unpack_from('<8I',r,0x485acc)):
 tokens=r[p-0x8000000:r.index(bytes([20]),p-0x8000000)+1]
 for cursor,token in enumerate(tokens):
  for phase in (0,1,8,9,0x7fffffff,0xffffffff):
   ram=begin(0x806fccc,0x806fda4);struct.pack_into('<I',ram,0x1808,phase);ram[0x18d0]=cursor;ram[0x18d2:0x18ec]=bytes([0x5a])*26
   expected=bytearray(ram);vram=bytearray([0xa5]*0x18000)
   if not phase&1:
    tile=(0 if phase&8 else 0x9078) if token==20 else (0 if token==21 else token+0x9064)
    struct.pack_into('<H',expected,0x18d2+cursor*2,tile)
    if token!=20:expected[0x18d0]=cursor+1
    vram[0xfc44:0xfc5e]=expected[0x18d2:0x18ec]
   run(ram,expected,(index,),int(token==20),vram)
   assert state['dma']==int(not phase&1) and state['calls']==[]
expected_coverage=set().union(*(set(range(a,b)) for a,b in ranges));expected_coverage.remove(0x8485acb)
assert coverage==expected_coverage,(len(coverage),len(expected_coverage),sorted(expected_coverage-coverage))
Path('build/more/late_scene_tables_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=len(coverage),padding_bytes=1,scope='Native consumers; callback bodies stubbed with specified results, label DMA modeled. All table entries, frame slots, return/clear branches, label tokens and parity/blink phases checked; full guarded RAM/VRAM and ABI.'),indent=2)+'\n')
print(cases,'native fixtures;',len(coverage),'bytes read plus one alignment byte')
