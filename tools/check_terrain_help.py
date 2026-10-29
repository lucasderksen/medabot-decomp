"""Native terrain-help selection and dialogue command-boundary checks."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
from dialogue import decode
from check_dialogue import prepare_cpu,check
r=find_rom().read_bytes();pointers=struct.unpack_from('<7I',r,0x3beaac)
dialogue_cpu,stub_counts=prepare_cpu(r)
messages=[]
for pointer in pointers:
    start=pointer-0x8000000;end=decode(r,start)[-1].end
    messages.append(check(dialogue_cpu,r[start:end],pointer))
cpu=RoutineCpu(r);state={};calls=[];reads=set();cases=0
def code(m,a,n,u):
    if 0x800e350<=a<0x800e3a0:return
    assert a in (0x800ebfc,0x800f440,0x800fd74,0x800f6cc,0x803fb3c),hex(a)
    calls.append(a)
    if a==0x803fb3c:assert m.reg_read(arm_const.UC_ARM_REG_R0)==pointers[state['index']]
    m.reg_write(arm_const.UC_ARM_REG_R0,state['index'] if a==0x800f6cc else state['done'] if a==0x803fb3c else 0)
    m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):reads.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code);cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=0x83beaac,end=0x83beac7)
for index in range(7):
    for kind in (3,255):
        for done in (0,1):
            state.update(index=index,done=done);calls.clear();ram=bytearray([0xa5]*0x7000);ram[0x47e]=kind;e=bytearray(ram)
            if done:struct.pack_into('<I',e,0x137c,0xa5a5a5a6)
            cpu.write(0x3000000,bytes(ram));regs=cpu.call(0x800e350,timeout_us=0)
            assert cpu.read(0x3000000,len(e))==e
            assert calls==[0x800ebfc,0x800f440,0x800fd74,0x800f6cc,0x803fb3c]
            assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
            cases+=1
assert reads==set(range(0x83beaac,0x83beac8))
report=dict(selector_cases=cases,native_messages=messages,scope='Original E350 selection with update helpers, index supplier and dialogue entry stubbed; all7 pointers,done0/1,kind3/255,full guarded IWRAM and ABI. Separately original3FD28 interpreter and handlers verify all7 message boundaries with BIOS copy,drawing,sound stubs per check_dialogue.py. No rendered text claim.')
Path('build/more/terrain_help_validation.json').write_text(json.dumps(report,indent=2)+'\n');print(cases,'selector fixtures and',len(messages),'native messages passed')
