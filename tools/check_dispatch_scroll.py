"""Native table dispatch and scroll copying; callbacks and frame helpers stubbed."""
import sys, json, struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
state = {}
calls = []
reads = set()

def code(engine, address, size, user):
    if address == 0x0807CCF0:
        return
    if state['start'] <= address < state['end']:
        return
    if state['copy']:
        assert 0x0803F63C <= address < 0x0803F65C, hex(address)
        return
    calls.append(address)
    engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))

def read(engine, access, address, size, value, user):
    reads.update(range(address, address + size))

cpu.engine.hook_add(unicorn.UC_HOOK_CODE, code)
for a,b in ((0x083C3C84,0x083C3D34),(0x083D2104,0x083D2200)):
    cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, read, begin=a, end=b-1)

def call(start, end, copy):
    state.update(start=start, end=end, copy=copy)
    calls.clear()
    registers = cpu.call(start, timeout_us=0)
    assert registers[4:12] == tuple(0xAB000000 | i for i in range(4,12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

copies = dispatches = 0
for start,end in ((0x080121A8,0x080121CC),(0x0803E870,0x0803E894)):
    for index in range(22):
        ram = bytearray([0xA5] * 0x7000)
        ram[0x1838] = index
        expected = bytearray(ram)
        expected[0x1839:0x1841] = rom[0x3C3C84+index*8:0x3C3C8C+index*8]
        cpu.write(0x03000000, bytes(ram))
        call(start,end,True)
        assert cpu.read(0x03000000,len(expected)) == expected
        copies += 1

for start,end,table,count,index_address in (
    (0x0804763C,0x0804765C,0x3D2104,10,0x2B8C),
    (0x0804A220,0x0804A2F0,0x3D212C,53,0x137C),
):
    for index in range(count):
        ram = bytearray(0x7000)
        struct.pack_into('<I',ram,index_address,index)
        cpu.write(0x03000000,bytes(ram))
        call(start,end,False)
        target = struct.unpack_from('<I',rom,table+index*4)[0] & ~1
        assert calls[0] == target, (hex(start),index,calls)
        if count == 10:
            assert calls == [target]
            assert cpu.read(0x03000000,len(ram)) == ram
        else:
            assert calls[1:] == [0x08052784,0x08052204,0x08048174]+[0x08049374]*32+[0x0804B1B0]
            assert struct.unpack('<I',cpu.read(0x03005314,4))[0] == 1
        dispatches += 1

expected_reads = set(range(0x083C3C84,0x083C3D34)) | set(range(0x083D2104,0x083D2200))
assert reads == expected_reads
result = dict(copy_cases=copies,dispatch_cases=dispatches,covered_bytes=len(reads),scope='Two native scroll consumers and byte-copy helper; exact guarded IWRAM and ABI. Native main/frame dispatchers cover all nonzero entries; callbacks and subsequent frame helpers stubbed, dispatch trace and ABI checked. Frame fixture has zero flags/context; other branches and callback effects are outside scope. Trailing 44 zero bytes at083D2200 remain unclassified.')
Path('build/more/dispatch_scroll_cpu.json').write_text(json.dumps(result,indent=2)+'\n')
print(result)
