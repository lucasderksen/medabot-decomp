"""Native palette-transfer consumers with BIOS copy/DMA modeled and other calls stubbed."""
import sys,json,struct
from pathlib import Path
from common import find_rom,load_segments
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();rows=[{'start': 7935473, 'palette': 7935476, 'end': 7935988, 'owners': {'sub_0805F19C': [134607260, 134607704, 'src/continued_main2_name_frame_setup.c']}}, {'start': 7970590, 'palette': 7970592, 'end': 7971104, 'owners': {'sub_08061CE0': [134618336, 134618776, 'src/m2c_lean_a_44.c']}}, {'start': 8121857, 'palette': 8121860, 'end': 8122372, 'owners': {'sub_0806ED08': [134671624, 134672040, 'src/m2c_harvest_266.c']}}, {'start': 8133555, 'palette': 8133556, 'end': 8134068, 'owners': {'sub_0806EEA8': [134672040, 134672608, 'src/m2c_harvest_183.c']}}];ss=load_segments();cpu=RoutineCpu(r)
cpu.engine.mem_map(0x4000000,0x1000);cpu.engine.mem_map(0x5000000,0x1000)
state={};transfers=[];passed=[]
def transfer(src,dst,size,fill):
 if not size:return
 assert size<=0x18000,(hex(src),hex(dst),size)
 payload=cpu.read(src,4)*(size//4) if fill else cpu.read(src,size)
 cpu.write(dst,payload)
 if any(x['palette']+0x8000000==src for x in rows):
  assert size==512 and not fill and (0x5000000<=dst<=0x5000200 or 0x202f800<=dst<=0x202fc00),(hex(src),hex(dst),size)
  assert cpu.read(dst,size)==r[src-0x8000000:src-0x8000000+size]
  transfers.append(dict(function=state['start'],source=src,destination=dst,bytes=size))
def code(m,a,n,u):
 if state['start']<=a<state['end']:return
 if a==0x807ccc0:
  src,dst,ctl=(m.reg_read(x) for x in (arm_const.UC_ARM_REG_R0,arm_const.UC_ARM_REG_R1,arm_const.UC_ARM_REG_R2))
  transfer(src,dst,((ctl&0x1fffff)+7)//8*32,bool(ctl&0x1000000))
 m.reg_write(arm_const.UC_ARM_REG_R0,0);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def dma(m,access,a,n,v,u):
 src,dst=struct.unpack('<II',cpu.read(0x40000d4,8));transfer(src,dst,(v&65535)*(4 if v&0x4000000 else 2),bool(v&0x1000000))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE,dma,begin=0x40000dc,end=0x40000dc)
targets={n:(a,b) for x in rows for n,(a,b,f) in x['owners'].items()}
for name,(a,b) in targets.items():
 state.update(start=a,end=b);ram=bytearray(0x8000);struct.pack_into('<I',ram,0x6f74,0x2020000)
 cpu.write(0x3000000,bytes(ram));cpu.write(0x2020000,bytes(0x10000));cpu.write(0x5000000,bytes([0xa5])*0x1000)
 try:
  regs=cpu.call(a,timeout_us=0)
  assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
  passed.append(a);print(name,'PASS',flush=True)
 except Exception as e:raise AssertionError((name,str(e))) from e
covered={t['source']-0x8000000 for t in transfers if t['function'] in passed}
accepted=[x for x in rows if x['palette'] in covered]
assert len(accepted)==4 and len(passed)==4
Path('build/more/scene_palette_high_bits_cpu.json').write_text(json.dumps(dict(passed=passed,transfers=transfers,accepted=accepted,scope='Original integrated consumer bodies; CpuFastSet and DMA modeled, other helper calls return zero. Zero-initialized scene/context fixtures; ABI checked. Palette sources,512-byte size,destinations and transfer output checked. Does not validate full scene effects or all branches.'),indent=2)+'\n')
print(len(accepted),'banks covered;',len(transfers),'transfers')
