"""Validate original late-background DMA transfers and BG control setup."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
rom=find_rom().read_bytes();cpu=RoutineCpu(rom)
cpu.engine.mem_map(0x04000000,0x1000);cpu.engine.mem_map(0x05000000,0x1000)
coverage=set();copies=[]
expected={0x06000000:bytearray([0xA5]*0x18000),0x05000000:bytearray([0x5A]*0x400)}
for base,data in expected.items():cpu.write(base,bytes(data))
def call_hook(machine,address,size,user):
 if 0x0806D7A0<=address<0x0806D8AC:return
 assert 0x08000000<=address<0x08800000
 machine.reg_write(arm_const.UC_ARM_REG_R0,0);machine.reg_write(arm_const.UC_ARM_REG_PC,machine.reg_read(arm_const.UC_ARM_REG_LR))
def dma_hook(machine,access,address,size,control,user):
 assert size==4 and control in (0x84000090,0x84000030,0x840000A0,0x80000060,0x8000000E)
 src,dst=struct.unpack('<II',cpu.read(0x040000D4,8));n=(control&0xFFFF)*(4 if control&0x04000000 else 2)
 data=rom[src-0x08000000:src-0x08000000+n];assert len(data)==n
 cpu.write(dst,data)
 if dst>=0x05000000:
  base=0x06000000 if dst>=0x06000000 else 0x05000000
  expected[base][dst-base:dst-base+n]=data
 if src in (0x087BAD60,0x087BAFA0,0x087BB7E0):coverage.update(range(src,src+n))
 copies.append((src,dst,n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,call_hook);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE,dma_hook,begin=0x040000DC,end=0x040000DC)
regs=cpu.call(0x0806D7A0,timeout_us=0)
assert copies[:3]==[(0x087BAD60,0x06008000,576),(0x087BAFA0,0x05000000,192),(0x087BB7E0,0x06007800,640)]
assert len(copies)==5
assert coverage==set(range(0x087BAD60,0x087BB060))|set(range(0x087BB7E0,0x087BBA60))
for base,data in expected.items():assert cpu.read(base,len(data))==data
assert struct.unpack('<3H',cpu.read(0x04000008,6))==(0xD01,0xE03,0x6F8A)
assert regs[4:12]==tuple(0xAB000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007F00
Path('build/more/late_background_cpu.json').write_text(json.dumps(dict(cases=1,covered_bytes=len(coverage),copies=copies,scope='Native loader; DMA modeled, external decompression and setup calls stubbed. Guarded VRAM/palette RAM, BG controls and ABI checked; rendering and timing excluded.'),indent=2)+'\n');print(len(coverage),'bytes covered; five DMA transfers')
