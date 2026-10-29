"""Check two original menu palette transfers with helper effects explicitly stubbed."""
import struct
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn
rom=find_rom().read_bytes();cpu=RoutineCpu(rom);cpu.engine.mem_map(0x04000000,0x1000);cpu.engine.mem_map(0x05000000,0x1000);calls=[]
def code(m,a,n,u):
    if 0x8060708<=a<0x806096c:return
    assert 0x08000000<=a<0x08800000,hex(a)
    args=tuple(m.reg_read(x) for x in (arm_const.UC_ARM_REG_R0,arm_const.UC_ARM_REG_R1,arm_const.UC_ARM_REG_R2))
    if a==0x0807ccc0:
        src,dst,ctl=args;size=((ctl&0x1fffff)+7)//8*32;cpu.write(dst,cpu.read(src,size));calls.append((src,dst,ctl))
    m.reg_write(arm_const.UC_ARM_REG_R0,0x80 if a==0x08044d0c else 0)
    m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code)
for mode in (0,1,2,255):
 for substate in (0,23):
    cpu.write(0x03000000,bytes(0x7000));cpu.write(0x03006f74,struct.pack('<I',0x030057e0));cpu.write(0x03006412,bytes([mode]));cpu.write(0x03002b8c,struct.pack('<I',substate));cpu.write(0x05000000,bytes([0xa5])*0x400);calls.clear()
    regs=cpu.call(0x8060708,timeout_us=0)
    expect=bytearray([0xa5]*0x400);expect[:448]=rom[0x7883f4:0x7883f4+448];expect[0x200:0x260]=rom[0xafb20:0xafb20+96]
    assert cpu.read(0x05000000,0x400)==bytes(expect)
    assert (0x087883f4,0x05000000,0x70) in calls and (0x080afb20,0x05000200,0x18) in calls
    assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007f00
print('8 native menu setup fixtures; both palette transfers and guarded palette RAM match; other helpers stubbed')
