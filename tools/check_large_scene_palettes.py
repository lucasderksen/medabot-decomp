"""Native palette-transfer consumers with BIOS copy/DMA modeled and other calls stubbed."""
import sys,json,struct
from pathlib import Path
from common import find_rom,load_segments
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();rows=[{'start': 7913605, 'palette': 7913608, 'end': 7914120, 'owners': {'sub_0805CDAC': [134598060, 134598352, 'src/continued_main2_selection_setup.c']}}, {'start': 7920754, 'palette': 7920756, 'end': 7921268, 'owners': {'sub_0805D860': [134600800, 134601236, 'src/m2c_lean_a_38.c']}}, {'start': 7927272, 'palette': 7927272, 'end': 7927784, 'owners': {'sub_0805C17C': [134594940, 134595292, 'src/continued_main2_setup.c']}}, {'start': 7947803, 'palette': 7947804, 'end': 7948316, 'owners': {'sub_0805E718': [134604568, 134605280, 'src/continued_main2_name_setup.c']}}, {'start': 7956367, 'palette': 7956368, 'end': 7956880, 'owners': {'sub_0805FD10': [134610192, 134610564, 'src/m2c_harvest_330.c']}}, {'start': 7960846, 'palette': 7960848, 'end': 7961360, 'owners': {'sub_0806113C': [134615356, 134615528, 'src/m2c_harvest_206.c'], 'sub_0806280C': [134621196, 134621552, 'src/m2c_harvest_207.c']}}, {'start': 7974282, 'palette': 7974284, 'end': 7974796, 'owners': {'sub_08065074': [134631540, 134631832, 'src/m2c_harvest_271.c']}}, {'start': 7978034, 'palette': 7978036, 'end': 7978548, 'owners': {'sub_08065D44': [134634820, 134635216, 'src/m2c_harvest_154.c']}}, {'start': 7985296, 'palette': 7985296, 'end': 7985808, 'owners': {'sub_08062FB4': [134623156, 134623752, 'src/m2c_harvest_162.c']}}, {'start': 8183006, 'palette': 8183008, 'end': 8183520, 'owners': {'sub_0807028C': [134677132, 134677368, 'src/m2c_harvest_113.c']}}, {'start': 8199795, 'palette': 8199796, 'end': 8200308, 'owners': {'sub_08070378': [134677368, 134677604, 'src/m2c_harvest_323.c']}}, {'start': 8214357, 'palette': 8214360, 'end': 8214872, 'owners': {'sub_08070464': [134677604, 134677840, 'src/m2c_harvest_113.c']}}];ss=load_segments();cpu=RoutineCpu(r)
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
assert len(accepted)==12 and len(passed)==13 and len(transfers)==14
Path('build/more/large_scene_palettes_cpu.json').write_text(json.dumps(dict(passed=passed,transfers=transfers,accepted=accepted,scope='Original integrated consumer bodies; CpuFastSet and DMA modeled, other helper calls return zero. Zero-initialized scene/context fixtures; ABI checked. Palette sources,512-byte size,destinations and transfer output checked. Does not validate full scene effects or all branches.'),indent=2)+'\n')
print(len(accepted),'banks covered;',len(transfers),'transfers')
