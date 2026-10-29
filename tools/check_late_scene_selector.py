"""Check original late-scene dialogue pointer selection and completion transitions."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);state={}
def hook(m,a,s,u):
 if a!=0x0803fb3c:return
 assert m.reg_read(arm_const.UC_ARM_REG_R0)==state['pointer']
 state['calls']+=1;m.reg_write(arm_const.UC_ARM_REG_R0,state['result']);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,hook)
for i,pointer in enumerate(struct.unpack_from('<12I',r,0x48698c)):
 for result in (0,1,255):
  work=bytearray([0xa5]*18);struct.pack_into('<HH',work,6,3,0xa5a5);struct.pack_into('<H',work,14,i);cpu.write(0x030017fe,bytes(work));cpu.write(0x0300137c,struct.pack('<I',7));state.update(pointer=pointer,result=result,calls=0)
  regs=cpu.call(0x0806e3c4)
  if result:struct.pack_into('<H',work,6,5)
  assert cpu.read(0x030017fe,18)==work
  assert cpu.read(0x0300137c,4)==struct.pack('<I',2 if result else 7)
  assert state['calls']==1 and regs[4:12]==tuple(0xab000000|j for j in range(4,12))
  assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007f00
report=dict(cases=36,hook='0803FB3C returns fixture completion status; verifies original pointer selection and state transition')
Path('build/more/late_scene_selector_cpu.json').write_text(json.dumps(report,indent=2)+'\n');print(report)
