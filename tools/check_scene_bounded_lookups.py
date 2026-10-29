"""Check two bounded native scene and record lookup consumers."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


CHOICES = (2, 3, 1)
SLOTS = (4, 5, 6, 7, 10, 11)
cpu = RoutineCpu(find_rom().read_bytes())
reads, calls = set(), []
ready = 1


def record_read(_engine, _access, address, size, _value, _user_data):
    reads.update(range(address, address + size))


def helpers(engine, address, _size, _user_data):
    if address == 0x08065710:
        assert engine.reg_read(arm_const.UC_ARM_REG_R0) == 0x02020050
        engine.reg_write(arm_const.UC_ARM_REG_R0, ready)
    elif address == 0x08044C38:
        calls.append(engine.reg_read(arm_const.UC_ARM_REG_R0))
    elif address == 0x08074F4C:
        value = engine.reg_read(arm_const.UC_ARM_REG_R0)
        calls.append(value)
        engine.reg_write(arm_const.UC_ARM_REG_R0, 100 + 7 * value)
    else:
        return
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


def check_abi(regs):
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x080AFCBD, end=0x080AFCBF)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, record_read,
                    begin=0x083ABDFC, end=0x083ABE13)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
cases = 0
for index in range(3):
    for ready in (0, 1):
        ram = bytearray(0x7100)
        struct.pack_into('<I', ram, 0x6F74, 0x02020000)
        context = bytearray(0x100)
        context[5] = index
        cpu.write(0x03000000, bytes(ram))
        cpu.write(0x02020000, bytes(context))
        calls.clear()
        regs = cpu.call(0x080665B0, timeout_us=0)
        assert calls == ([CHOICES[index]] if ready else [])
        assert cpu.read(0x03000000, len(ram)) == ram
        assert cpu.read(0x02020000, len(context)) == context
        check_abi(regs)
        cases += 1

for match in range(7):
    ram = bytes(0x7100)
    cpu.write(0x03000000, ram)
    calls.clear()
    target = 100 + 7 * SLOTS[match] if match < 6 else 0xFFFFFFFF
    regs = cpu.call(0x08074F74, (target,), timeout_us=0)
    assert regs[0] == (match < 6)
    assert calls == list(SLOTS[:match + 1] if match < 6 else SLOTS)
    assert cpu.read(0x03000000, len(ram)) == ram
    check_abi(regs)
    cases += 1

assert reads == set(range(0x080AFCBD, 0x080AFCC0)) | set(range(0x083ABDFC, 0x083ABE14))
print(f'{cases} native fixtures cover both bounded lookup tables; helpers stubbed')
