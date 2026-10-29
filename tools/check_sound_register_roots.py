"""Verify sound register table targets through original routines."""
import struct
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);cpu.engine.mem_map(0x04000000,0x1000);state={};calls=[];writes=[]
def code(m,a,n,u):
 if a==0x8073b2c and state.get('stub'):calls.append(m.reg_read(arm_const.UC_ARM_REG_R0));m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def write(m,access,a,n,v,u):
 if state.get('trace'):writes.append((a,n,v))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE,write,begin=0x04000000,end=0x04000fff)
for channel in (1,2):
 cpu.write(0x4000000,bytes(4096));state.update(stub=False,trace=False);reg=cpu.call(0x8073ab8,(channel,0x02010000),timeout_us=0);base=0x40000b0+channel*12
 assert struct.unpack('<3I',cpu.read(base,12))==(0x02010000,0x40000a0+4*(channel-1),0xf6400004)
 assert reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007f00
 for old in (0,0xffff,0x1234):
  dest=0x40000c6+(channel-1)*12;cpu.write(dest,struct.pack('<H',old));writes.clear();state.update(stub=False,trace=True);reg=cpu.call(0x8073b2c,(channel,),timeout_us=0);state['trace']=False
  assert reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007f00
  first=(old&0x499f)|0x8440;second=(first&0x499f)|0x440
  assert writes==[(dest,2,first),(dest,2,second)],writes
 for enabled in (0,1):
  record=bytearray(0x40);record[0x3a]=channel;cpu.write(0x2010000,bytes(record));dest=0x4000100+(channel-1)*4;cpu.write(dest,struct.pack('<I',0x800000 if enabled else 0));cpu.write(0x4000082,struct.pack('<H',0xffff));calls.clear();state.update(stub=True,trace=False);reg=cpu.call(0x8073c84,(0x2010000,),timeout_us=0)
  assert calls==([channel] if enabled else []) and struct.unpack('<I',cpu.read(dest,4))[0]==0
  assert reg[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007f00
print('12 sound MMIO fixtures cover both FIFO, DMA control and timer pointers; helper stubbed in timer cases')
