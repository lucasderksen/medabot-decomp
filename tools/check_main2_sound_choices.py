import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);state={};sounds=[];reads=set()
def hook(m,a,n,u):
 if 0x805c574<=a<0x805c7f8:return
 assert 0x8000000<=a<0x8800000,hex(a)
 if a==0x8074b88:sounds.append(m.reg_read(arm_const.UC_ARM_REG_R0))
 m.reg_write(arm_const.UC_ARM_REG_R0,0);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):reads.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,hook);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x80af8ca,end=0x80af8cc)
for i in range(3):
 cpu.write(0x3000000,bytes(0x7000));cpu.write(0x3006f74,struct.pack('<I',0x3001000));cpu.write(0x300058c,bytes([0x40]));cpu.write(0x3000b94,bytes([i]));sounds.clear();reg=cpu.call(0x805c574,timeout_us=0)
 assert sounds==[1,r[0xaf8ca+i]],sounds;assert reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
assert reads==set(range(0x80af8ca,0x80af8cd))
print('3 native menu fixtures check all sound choices and preserved ABI; audio and other helpers stubbed')

