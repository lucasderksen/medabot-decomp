"""Check the original five-row inventory page tile selector."""
import sys,json
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
rom=find_rom().read_bytes();cpu=RoutineCpu(rom);state={};coverage=set()
def hook(machine,address,size,user):
 if address!=0x0807CCC0:return
 src,dst,count=[machine.reg_read(r) for r in (arm_const.UC_ARM_REG_R0,arm_const.UC_ARM_REG_R1,arm_const.UC_ARM_REG_R2)]
 row=len(state['copies']);assert count==8 and row<5
 assert src==0x084C4330+row*256+state['page']*32
 assert dst==0x06007A00+row*32
 payload=rom[src-0x08000000:src-0x08000000+32];cpu.write(dst,payload)
 state['expected'][dst-0x060079E0:dst-0x060079E0+32]=payload
 state['copies'].append((src,dst));coverage.update(range(src,src+32))
 machine.reg_write(arm_const.UC_ARM_REG_R0,0)
 machine.reg_write(arm_const.UC_ARM_REG_PC,machine.reg_read(arm_const.UC_ARM_REG_LR))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,hook)
for page in range(8):
 cpu.write(0x0300047F,bytes([page]));expected=bytearray([0xA5]*224);cpu.write(0x060079E0,bytes(expected));state.update(page=page,copies=[],expected=expected)
 regs=cpu.call(0x0800B0F8,timeout_us=0)
 assert len(state['copies'])==5 and cpu.read(0x060079E0,224)==expected
 assert regs[4:12]==tuple(0xAB000000|i for i in range(4,12))
 assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x03007F00
assert coverage==set(range(0x084C4330,0x084C4830))
Path('build/more/inventory_page_tiles_cpu.json').write_text(json.dumps(dict(cases=8,copies=40,covered_bytes=len(coverage),scope='Native selector, modeled BIOS CpuFastSet, guarded VRAM and ABI; rendering and timing excluded.'),indent=2)+'\n')
print('8 page cases, 40 copies, 1280 bytes covered')
