"""Check the four-entry equipment byte scan and its repeated read order."""
import itertools,json
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
cpu=RoutineCpu(find_rom().read_bytes());state={};cases=0
pairs=[(0,0),(17,0),(17,17),(17,19)]
def read_hook(machine,access,address,size,value,user):
 if state['base']<=address<state['base']+0x100:state['reads'].append((address,size))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read_hook,begin=0x03000590,end=0x03000B8F)
for bank in range(6):
 base=0x03000590+bank*256
 for entries in itertools.product(pairs,repeat=4):
  data=bytearray([0xA5]*256);wanted=[];result=0
  for i,(first,second) in enumerate(entries):data[0x4C+24*i]=first;data[0x59+24*i]=second
  for i,(first,second) in enumerate(entries):
   wanted.append((base+0x59+24*i,1))
   if second:
    wanted.extend([(base+0x4C+24*i,1),(base+0x59+24*i,1)])
    if first!=second:result=i+1;break
  cpu.write(base,bytes(data));state.update(base=base,reads=[])
  registers=cpu.call(0x08018EE0,(bank,),timeout_us=0)
  assert registers[0]==result and state['reads']==wanted
  assert cpu.read(base,256)==data
  assert registers[4:12]==tuple(0xAB000000|i for i in range(4,12))
  assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007F00
  cases+=1
Path('build/more/equipment_scan_cpu.json').write_text(json.dumps(dict(cases=cases,scope='Native routine without stubs; return value, exact byte-read order, preserved input RAM and ABI checked.'),indent=2)+'\n')
print(cases,'cases; native read order and outputs verified')
