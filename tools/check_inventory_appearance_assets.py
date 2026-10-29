"""Native inventory appearance selection; asset decompression and empty-slot drawing stubbed."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();table=struct.unpack_from('<150I',r,0x3ac614);cpu=RoutineCpu(r);calls=[];coverage=set();cases=0
def code(m,a,n,u):
 if 0x8009750<=a<0x80097e0:return
 assert a in (0x80009bc,0x8040d0c),hex(a)
 calls.append((a,m.reg_read(arm_const.UC_ARM_REG_R0),m.reg_read(arm_const.UC_ARM_REG_R1)))
 m.reg_write(arm_const.UC_ARM_REG_R0,0);m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):coverage.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x83ac614,end=0x83ac86b)
for category in range(30):
 for variant in range(5):
  for index in range(30):
   for owned in (0,128):
    ram=bytearray([0xa5]*0x7000);ram[0x440+0x3f]=index//6;ram[0x440+0x40]=index%6;b=0xbe0+index*64;ram[b]=owned;ram[b+1]=category;ram[b+8]=variant
    expected=bytearray(ram);expected[0x440+0x3d]=index
    if owned:
     struct.pack_into('<HHHH',expected,0x2c30,0xc804,192,80,512);expected[0x2c30+10]=13;expected[0x2c30+11]=64;expected[0x2c30+0x1c]=0
    cpu.write(0x3000000,bytes(ram));calls.clear();regs=cpu.call(0x8009750,timeout_us=0)
    assert cpu.read(0x3000000,len(expected))==expected,(category,variant,index,owned)
    assert calls==([(0x80009bc,table[category*5+variant],0x6010000)] if owned else [(0x8040d0c,0,1)])
    assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
    cases+=1
assert coverage==set(range(0x83ac614,0x83ac86c))
Path('build/more/inventory_appearance_assets_cpu.json').write_text(json.dumps(dict(cases=cases,covered_bytes=len(coverage),scope='Original08009750;30 categories x5 variants x30 inventory positions xowned/empty. Asset decompression/empty-slot drawing stubbed; exact call arguments, full guarded IWRAM and ABI checked. All150 pointer entries read.'),indent=2)+'\n');print(cases,'native inventory fixtures;',len(coverage),'bytes read')
