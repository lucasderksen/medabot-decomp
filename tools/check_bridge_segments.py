"""Execute bridge construction with modeled object initialization and DMA."""
import sys,struct,json
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);cpu.engine.mem_map(0x4000000,0x1000)
coverage=set();calls=[];dma=[]
def code(m,a,n,u):
 if 0x806ff2c<=a<0x80700c8:return
 assert a==0x8048864,hex(a)
 calls.append(tuple(m.reg_read(getattr(arm_const,'UC_ARM_REG_R'+str(i))) for i in range(4)))
 m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):coverage.update(range(a,a+n))
def write(m,access,a,n,v,u):
 assert n==4 and v==0x80000001
 src,dst=struct.unpack('<II',cpu.read(0x40000d4,8));data=cpu.read(src,2)
 dma.append((dst,data));cpu.write(dst,data)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x8485aec,end=0x8485b4b)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE,write,begin=0x40000dc,end=0x40000dc)
cases=0
for index in range(8):
 for step in range(4):
  for column in range(256):
   ram=bytearray(0x7000);ram[0x18ec:0x18ee]=bytes([column,step]);cpu.write(0x3000000,bytes(ram))
   vram=bytearray([0xa5]*0x18000);cpu.write(0x6000000,bytes(vram));calls.clear();dma.clear();ec=[];ed=[]
   if step<3:
    x,y,end,row=r[0x485aec+index*12+step*4:0x485aec+index*12+step*4+4]
    if end<=x+column:
     struct.pack_into('<H',ram,0x2c30+(step+11)*64+4,row*8)
     ram[0x18ec:0x18ee]=bytes([0,step+1])
    else:
     if column<=1 and (row+column<y or y+column<row):
      obj=step*2+column+14;down=row+column<y
      ec=[(obj,0xc400 if down else 0xe400,0x303,0)]
      struct.pack_into('<HH',ram,0x2c30+obj*64+2,(x+column)*8,(y-column)*8-4 if down else (y+column)*8+12)
     else:
      dst=0x600f800+(column+x+row*32)*2;ed=[(dst,b'\xd2\x00')];vram[dst-0x6000000:dst-0x6000000+2]=b'\xd2\x00'
     ram[0x18ec]=(column+1)&255
   regs=cpu.call(0x806ff2c,(index,),timeout_us=0)
   assert regs[0]==int(step>2) and calls==ec and dma==ed,(index,step,column,calls,ec,dma,ed)
   assert cpu.read(0x3000000,len(ram))==ram,(index,step,column,'RAM')
   assert cpu.read(0x6000000,len(vram))==vram
   assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
   cases+=1
assert coverage==set(range(0x8485aec,0x8485b4c))
Path('build/more/bridge_segments_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=len(coverage),scope='Original routine; object initialization stubbed and one-halfword DMA modeled. Full guarded RAM/VRAM, calls, returns and ABI checked.'),indent=2)+'\n')
print(cases,'native fixtures;',len(coverage),'table bytes covered')
