"""Verify the menu cancellation message with the original selector."""
import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
from check_dialogue import prepare_cpu,check
r=find_rom().read_bytes();msg=r[0xafca8:0xafcb7];d,_=prepare_cpu(r);check(d,msg,0x80afca8);cpu=RoutineCpu(r);calls=[]
def hook(m,a,n,u):
 if 0x8066280<=a<0x8066460:return
 if a==0x803fb3c:assert m.reg_read(arm_const.UC_ARM_REG_R0)==0x80afca8
 assert a in (0x8041c14,0x803fb3c),hex(a);calls.append(a);m.reg_write(arm_const.UC_ARM_REG_R0,0);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,hook)
cpu.write(0x3000000,bytes(0x7000));cpu.write(0x3006f74,struct.pack('<I',0x3001000));cpu.write(0x3001005,b'\x06');reg=cpu.call(0x8066280,timeout_us=0)
assert calls==[0x8041c14,0x803fb3c] and reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
print('native cursor-6 selection and original interpreter boundary pass; display/dialogue helpers stubbed')

