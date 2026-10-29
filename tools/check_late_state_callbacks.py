import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
rom=find_rom().read_bytes();cpu=RoutineCpu(rom);state={}
def hook(machine,address,size,user):
 if address==state['target']:
  state['calls']+=1
 elif address in (0x08034E94,0x0803D424):machine.reg_write(arm_const.UC_ARM_REG_R0,state['index'])
 elif address in (0x0803EED8,0x0803E780,0x080195C0,0x08032F64):machine.reg_write(arm_const.UC_ARM_REG_R0,0)
 else:return
 machine.reg_write(arm_const.UC_ARM_REG_PC,machine.reg_read(arm_const.UC_ARM_REG_LR))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,hook)
tables=[(0x08030860,0x3aecd8,112,1),(0x08031a70,0x3aeea0,60,1),(0x08031abc,0x3aef90,60,1),(0x08033318,0x3af090,60,1),(0x08033840,0x3af180,128,1),(0x08037b9c,0x3af6b0,64,27),(0x080383e8,0x3af810,16,17),(0x080385f8,0x3af860,16,27),(0x0803884c,0x3af8a0,8,27),(0x080393ec,0x3af8c0,80,1)]
cases=0;dispatches=0
for entry,root,count,repeats in tables:
 for index,target in enumerate(struct.unpack_from('<'+'I'*count,rom,root)):
  cpu.write(0x03000000,bytes(0x7e00));cpu.write(0x0300137c,struct.pack('<I',index));cpu.write(0x030005d9,bytes([index]))
  for frame in range(128):cpu.write(0x03002c30+frame*64+0x29,bytes([index]))
  state.update(target=target&~1,index=index,calls=0)
  result=cpu.call(entry,(0,1) if entry==0x08033318 else (),timeout_us=0,instruction_limit=100000)
  assert state['calls']==repeats,(hex(entry),index,state)
  assert result[4:12]==tuple(0xab000000|i for i in range(4,12))
  assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007f00
  if repeats==27:assert result[0]==int(index==0)
  cases+=1;dispatches+=state['calls']
report=dict(cases=cases,callback_dispatches=dispatches,tables=10,hooks=['selected callback bodies','08034E94/0803D424 return fixture index','0803EED8/0803E780/080195C0/08032F64 no-ops'],scope='Render mode zero; original dispatcher indexing and loops; selected callback effects excluded.')
Path('build/more/late_state_callback_cpu.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report))
