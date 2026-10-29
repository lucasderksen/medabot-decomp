"""Native first-entry asset consumers and FF02 script; external bodies stubbed."""
import sys,json,struct
from pathlib import Path
from common import find_rom,load_segments
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();ss=load_segments();cpu=RoutineCpu(r)
cpu.engine.mem_map(0x4000000,0x1000);cpu.engine.mem_map(0x5000000,0x1000)
state={};coverage=set();cases=0
def code(m,a,n,u):
 if any(lo<=a<hi for lo,hi in state['ranges']):return
 args=tuple(m.reg_read(getattr(arm_const,'UC_ARM_REG_R'+str(i))) for i in range(4));state['calls'].append((a,args))
 m.reg_write(arm_const.UC_ARM_REG_R0,0);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):coverage.update(range(a,a+n))
def dma(m,access,a,n,v,u):
 src,dst=struct.unpack('<II',cpu.read(0x40000d4,8));size=(v&65535)*(4 if v&0x4000000 else 2)
 state['dma'].append((src,dst,v));cpu.write(dst,cpu.read(src,size))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x8485a58,end=0x8485a7f)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x8485bb4,end=0x8485bb7)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE,dma,begin=0x40000dc,end=0x40000dc)
def bounds(a):
 s=next(s for s in ss if s['start']==a-0x8000000);return(a,s['end']+0x8000000)
def run(a,ram,ranges=None):
 global cases
 state.clear();state.update(ranges=ranges or [bounds(a)],calls=[],dma=[])
 cpu.write(0x3000000,bytes(ram));cpu.write(0x5000000,bytes(0x1000));regs=cpu.call(a,timeout_us=0)
 assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
 cases+=1
run(0x806ed08,bytearray(0x7100))
assert [(x[0],x[1],x[2]) for x in state['dma']]==[(0x87bee04,0x5000000,0x84000080),(0x87c9a0c,0x5000000,0x84000008),(0x87c951c,0x5000020,0x84000008),(0x807c570,0x5000200,0x80000050)]
assert cpu.read(0x5000020,32)==r[0x7c951c:0x7c953c]
assert cpu.read(0x5000200,160)==r[0x7c570:0x7c610]
assert any(args[:2]==(0x87c68b8,0x6008c80) for a,args in state['calls'])
assert any(args[0]==0x87c901c and 0x3007000<=args[1]<0x3007f00 for a,args in state['calls'])
run(0x806f0e0,bytearray(0x7100));assert any(args[:2]==(0x87b0af0,0x6010000) for a,args in state['calls'])
for keys in range(16):
 for script_state in (4,7,8,255):
  ram=bytearray([0xa5]*0x7100);b=0x440;ram[b:b+40]=bytes(40);ram[b+4]=script_state;struct.pack_into('<I',ram,b+8,0x8485bb4);struct.pack_into('<H',ram,0x1798,keys)
  expected=bytearray(ram);expected[b+0x13]=1
  if keys&3:expected[b+4]=(script_state+1)&255
  run(0x803fd28,ram,[bounds(0x803fd28),bounds(0x8040820)])
  assert cpu.read(0x3000000,len(expected))==expected,(keys,script_state)
  assert [a for a,args in state['calls']]==([0x8074de0] if keys&3 else [])
  if keys&3:assert state['calls'][0][1][0]==13
expected=set().union(*(set(range(a,a+4)) for a in (0x8485a58,0x8485a60,0x8485a68,0x8485a70,0x8485a78)),{0x8485bb4,0x8485bb5})
assert coverage==expected,(coverage-expected,expected-coverage)
assert r[0x485bb6:0x485bb8]==bytes(2)
Path('build/more/late_scene_assets_cpu.json').write_text(json.dumps(dict(cases=cases,native_table_bytes=len(coverage),scope='Native0806ED08/0806F0E0 first-entry pointer loads; DMA modeled, other calls stubbed; verify asset arguments and palette output. Second pointer entries structurally verified against existing assets, not runtime exercised. Native0803FD28+08040820 FF02 script all low key bits and state wrap; sound stubbed, full IWRAM and ABI.'),indent=2)+'\n');print(cases,'native fixtures;',len(coverage),'table bytes read')
