"""Native palette-transfer consumers with BIOS copy/DMA modeled and other calls stubbed."""
import sys,json,struct
from pathlib import Path
from common import find_rom,load_segments
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();rows=[{'start': 8000832, 'palette': 8000832, 'end': 8001120, 'owners': {'sub_080646C4': [134629060, 134629504, 'src/m2c_harvest_162.c']}}, {'start': 8150605, 'palette': 8150608, 'end': 8151024, 'owners': {'sub_08070C0C': [134679564, 134679924, 'src/m2c_harvest_386.c']}}, {'start': 8152156, 'palette': 8152156, 'end': 8152188, 'owners': {'sub_08069530': [134649136, 134649512, 'src/m2c_harvest_153.c']}}, {'start': 8153060, 'palette': 8153060, 'end': 8153092, 'owners': {'sub_080696A8': [134649512, 134649780, 'src/m2c_harvest_214.c']}}, {'start': 8167176, 'palette': 8167176, 'end': 8167208, 'owners': {'sub_0806EEA8': [134672040, 134672608, 'src/m2c_harvest_183.c']}}, {'start': 8335659, 'palette': 8335660, 'end': 8335692, 'owners': {'sub_0806E5E0': [134669792, 134670052, 'src/m2c_harvest_387.c']}}, {'start': 8337866, 'palette': 8337868, 'end': 8337900, 'owners': {'sub_0806E6E4': [134670052, 134670316, 'src/m2c_harvest_387.c']}}];ss=load_segments();cpu=RoutineCpu(r)
cpu.engine.mem_map(0x4000000,0x1000);cpu.engine.mem_map(0x5000000,0x1000)
state={};transfers=[];passed=[]
def transfer(src,dst,size,fill):
 if not size:return
 assert size<=0x18000,(hex(src),hex(dst),size)
 payload=cpu.read(src,4)*(size//4) if fill else cpu.read(src,size)
 cpu.write(dst,payload)
 if any(x['palette']+0x8000000==src for x in rows):
  assert size==next(x["end"]-x["palette"] for x in rows if x["palette"]+0x8000000==src) and not fill and (0x5000000<=dst and dst+size<=0x5000400 or 0x202f800<=dst<=0x202fc00),(hex(src),hex(dst),size)
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
assert len(accepted)==7 and len(passed)==7 and len(transfers)==7

Path('build/more/scene_palette_tails_cpu.json').write_text(json.dumps(dict(passed=passed,transfers=transfers,accepted=accepted,scope='Original integrated consumer bodies; CpuFastSet and DMA modeled, other helper calls return zero. Zero-initialized scene/context fixtures; ABI checked. Palette sources,source-specific sizes,destinations and transfer output checked. Does not validate full scene effects or all branches.'),indent=2)+'\n')
print(len(accepted),'banks covered;',len(transfers),'transfers')
