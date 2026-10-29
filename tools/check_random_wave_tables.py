"""Native random-byte selection and wave-RAM loader checks."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();table=r[0x3f7d80:0x3f7e80];cpu=RoutineCpu(r);coverage=set();cases=0
def read(m,access,a,n,v,u):coverage.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x83f7d80,end=0x83f7e7f)
def division(m,interrupt,u):
 assert m.reg_read(arm_const.UC_ARM_REG_PC)==0x807ccd2
 numerator=m.reg_read(arm_const.UC_ARM_REG_R0);denominator=m.reg_read(arm_const.UC_ARM_REG_R1)
 assert numerator<256 and 0<denominator<256
 m.reg_write(arm_const.UC_ARM_REG_R0,numerator//denominator);m.reg_write(arm_const.UC_ARM_REG_R1,numerator%denominator);m.reg_write(arm_const.UC_ARM_REG_R3,numerator//denominator)
cpu.engine.hook_add(unicorn.UC_HOOK_INTR,division)
def abi(regs):assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
for step in (0,1,255,256,0xffffffff):
 for index in range(256):
  for limit in (1,2,3,7,11,16,255,257,0xfffffffe):
   ram=bytearray([0xa5]*0x7000);struct.pack_into('<I',ram,0x5314,step);ram[0x6417]=(index-step)&255
   expected=bytearray(ram);expected[0x6417]=table[index]
   cpu.write(0x3000000,bytes(ram));regs=cpu.call(0x8049780,(limit,),timeout_us=0)
   assert regs[0]==table[index]%(limit&255) and cpu.read(0x3000000,len(ram))==expected
   abi(regs);cases+=1
assert coverage==set(range(0x83f7d80,0x83f7e80))
cpu=RoutineCpu(r);cpu.engine.mem_map(0x4000000,0x1000);calls=[];wave_cases=0
def code(m,a,n,u):
 if 0x8073a48<=a<0x8073a88:return
 src,dst,ctl=(m.reg_read(x) for x in (arm_const.UC_ARM_REG_R0,arm_const.UC_ARM_REG_R1,arm_const.UC_ARM_REG_R2))
 assert (dst,ctl)==(0x4000090,0x4000004) and 0x80b0820<=src<0x80b0860
 calls.append((src,dst,ctl));cpu.write(dst,cpu.read(src,16))
 m.reg_write(arm_const.UC_ARM_REG_R0,0);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code)
for wave in range(4):
 for control in (0,1,0x40,0x80,0xc0,0x100,0xff80,0xffff):
  io=bytearray([0xa5]*0x1000);struct.pack_into('<H',io,0x70,control);expected=bytearray(io)
  expected[0x90:0xa0]=r[0xb0820+wave*16:0xb0830+wave*16];struct.pack_into('<H',expected,0x70,0xc0 if control==0x80 else 0x80)
  ram=bytes([0xa5])*0x7000;cpu.write(0x3000000,ram);cpu.write(0x4000000,bytes(io));calls.clear();regs=cpu.call(0x8073a48,(wave,),timeout_us=0)
  assert calls==[(0x80b0820+wave*16,0x4000090,0x4000004)] and cpu.read(0x4000000,len(io))==expected and cpu.read(0x3000000,len(ram))==ram
  abi(regs);wave_cases+=1
Path('build/more/random_wave_tables_cpu.json').write_text(json.dumps(dict(random_cases=cases,wave_cases=wave_cases,scope='Random08049780 and native Mod wrapper with BIOS division modeled: every index, five step/wrap cases, nine narrowed nonzero ranges; full guarded IWRAM and ABI. Wave08073A48 all four packed4-bit waves and eight sound-control values; BIOS CpuSet modeled, exact call/IO/guarded IWRAM/ABI checked.'),indent=2)+'\n')
print(cases,'native random fixtures;',wave_cases,'wave fixtures')
