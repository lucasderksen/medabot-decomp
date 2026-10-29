"""Native setup/restore transfer paths with clear/DMA modeled and graphics helpers stubbed."""
import sys,json,struct,itertools
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r)
for a in (0x4000000,0x5000000,0x7000000):cpu.engine.mem_map(a,0x1000)
state={};transfers=[];cases=0
def code(m,a,n,u):
 if state['start']<=a<state['end']:return
 args=tuple(m.reg_read(getattr(arm_const,'UC_ARM_REG_R'+str(i))) for i in range(4));ret=0
 if a==0x8049714:
  assert args[1]<=0x2000;cpu.write(args[0],bytes(args[1]))
 elif a==0x8057d80:ret=state['choices'][args[0]]
 m.reg_write(arm_const.UC_ARM_REG_R0,ret);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def dma(m,access,a,n,v,u):
 src,dst=struct.unpack('<II',cpu.read(0x40000d4,8));unit=4 if v&0x4000000 else 2;size=(v&65535)*unit
 assert size<=0x2000
 payload=cpu.read(src,unit)*(size//unit) if v&0x1000000 else cpu.read(src,size);cpu.write(dst,payload)
 if src in (0x85fba78,0x85fbbc0,0x85fbbe0,0x85fbdfc):transfers.append((src,dst,v))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE,dma,begin=0x40000dc,end=0x40000dc)
for start,end in ((0x805718c,0x8057440),(0x80576e0,0x8057ad0)):
 for choices in itertools.product(range(3),repeat=4):
  ram=bytearray(0x8000);struct.pack_into('<I',ram,0x6d14,0x2020000);cpu.write(0x3000000,bytes(ram));cpu.write(0x2020000,bytes([0xa5])*0x2000);cpu.write(0x5000000,bytes([0xa5])*0x1000)
  state.update(start=start,end=end,choices=choices);transfers.clear();regs=cpu.call(start,timeout_us=0)
  palette=0x5000380 if start==0x805718c else 0x202f980
  assert transfers==[(0x85fba78,0x2020000,0x80000070),(0x85fbbc0,0x2020400,0x80000010),(0x85fbbe0,palette,0x84000008),(0x85fbdfc,palette+32,0x84000008)],(hex(start),choices,transfers)
  expected=bytearray(0x2000);expected[:224]=r[0x5fba78:0x5fbb58];expected[0x400:0x420]=r[0x5fbbc0:0x5fbbe0]
  assert cpu.read(0x2020000,0x2000)==expected and cpu.read(palette,32)==r[0x5fbbe0:0x5fbc00] and cpu.read(palette+32,32)==r[0x5fbdfc:0x5fbe1c]
  assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
  cases+=1
Path('build/more/command_setup_tables_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=320,scope='Original0805718C/080576E0, all81 selector combinations per routine. Memory clear/DMA modeled, remaining helpers stubbed; exact transfer traces, full setup buffer, two palette output spans and ABI checked. Other scene state not modeled.'),indent=2)+'\n');print(cases,'native setup/restore fixtures;320 bytes transferred')
