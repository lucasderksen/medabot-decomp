import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const
rom=find_rom().read_bytes();cpu=RoutineCpu(rom);cases=0
for phase in range(256):
 for frac,y,step,low,high in [(0,0,1,80,90),(3,254,255,0,2),(255,10,16,10,40),(1,511,0,300,400)]:
  data=bytearray(64);struct.pack_into('<h',data,4,y);data[0x24]=step;data[0x25]=frac;struct.pack_into('<H',data,0x30,phase);cpu.write(0x03002c30,bytes(data));result=cpu.call(0x0803526c,(0,low,high))
  fraction=(frac+rom[0x3af390+phase])&255;next_y=((fraction>>2)+y)&255;data[0x25]=fraction&3
  landed=low<=next_y<=high
  struct.pack_into('<h',data,4,low if landed else next_y)
  if not landed:struct.pack_into('<H',data,0x30,min(255,phase+step))
  assert cpu.read(0x03002c30,64)==data,(phase,frac,y)
  assert result[0]==landed;assert result[4:12]==tuple(0xab000000|i for i in range(4,12));assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007f00;cases+=1
path_cases=0
for path in range(4):
 for phase in range(17):
  for enabled in (0,1):
   data=bytearray(64);struct.pack_into('<3H',data,0,0x8000 if enabled else 0,510,254);data[0x23]=phase;cpu.write(0x03002c30,bytes(data));result=cpu.call(0x080366dc,(0,path))
   stopped=not enabled or phase==16
   if not stopped:
    dx,dy=struct.unpack_from('<hh',rom,0x3af500+path*64+phase*4);struct.pack_into('<HH',data,2,(510+dx)&511,(254+dy)&255);data[0x23]+=1
   assert result[0]==stopped;assert cpu.read(0x03002c30,64)==data
   assert result[4:12]==tuple(0xab000000|i for i in range(4,12));assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007f00;path_cases+=1
report=dict(acceleration_cases=cases,path_cases=path_cases,hooks=[],scope='All256 acceleration entries and all4x16 path vectors, boundary/truncation/early-stop cases.')
Path('build/more/action_motion_cpu.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report))
