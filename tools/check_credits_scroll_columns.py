"""Check credits lookups through the original code up to their first reads."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
reads, state = set(), {}


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def hook(engine, address, _size, _user_data):
    if address == 0x08066D8C:
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))
    elif address == state['stop']:
        state['hit'] = True
        state['value'] = engine.reg_read(state['register'])
        engine.emu_stop()


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x080B000E, end=0x080B010D)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x08483C10, end=0x08483D0F)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
cases = 0
for start, stop, register, table in (
        (0x080673AC, 0x080673C4, arm_const.UC_ARM_REG_R7, 0x0B000E),
        (0x08067974, 0x08067986, arm_const.UC_ARM_REG_R6, 0x483C10)):
    for index in range(256):
        ram = bytearray(0x7100)
        struct.pack_into('<I', ram, 0x6F74, 0x02020000)
        context = bytearray(0x100)
        context[5] = index
        cpu.write(0x03000000, bytes(ram))
        cpu.write(0x02020000, bytes(context))
        for reg, value in ((arm_const.UC_ARM_REG_R0, 0),
                           (arm_const.UC_ARM_REG_R1, 0),
                           (arm_const.UC_ARM_REG_SP, 0x03007F00),
                           (arm_const.UC_ARM_REG_LR, 0x0203FFF1)):
            cpu.engine.reg_write(reg, value)
        state.update(stop=stop, register=register, hit=False)
        cpu.engine.emu_start(start | 1, 0x0203FFF0, count=20000)
        assert state['hit'] and state['value'] == rom[table + index], (hex(start), index)
        cases += 1

assert set(range(0x080B000E, 0x080B010E)) <= reads
assert set(range(0x08483C10, 0x08483D10)) <= reads
print(f'{cases} partial native credits fixtures cover both lookups and adjacent-ROM reads')
