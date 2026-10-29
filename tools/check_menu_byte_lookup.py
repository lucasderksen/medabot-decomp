from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);seen=set()
def read(m,access,a,n,v,u):seen.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x80afb88,end=0x80afb97)
for selector in list(range(16))+[16,255]:
 cpu.write(0x3000000,bytes(0x7000));cpu.write(0x3002420,bytes([selector]));cpu.write(0x2010000,b'\x11\x22\x33\xff\x04\xa5\xa5\xa5');cpu.write(0x2011000,bytes([0xa5])*32)
 reg=cpu.call(0x8060d28,(0x2011000,0x2010000,0,0),timeout_us=0);expected=bytes([0x11,0x22,r[0xafb88+selector],0xff,0x04])+bytes([0xa5])*27
 assert cpu.read(0x2011000,32)==expected and reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
assert seen==set(range(0x80afb88,0x80afb98))
print('18 native lookup/copy fixtures including adjacent ROM reads; no helpers stubbed')
