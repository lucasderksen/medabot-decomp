"""Exercise original loaders for two interface palette banks."""

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
cpu.engine.mem_map(0x04000000, 0x1000)
cpu.engine.mem_map(0x05000000, 0x1000)
state, seen = {}, set()


def helper(engine, address, _size, _user_data):
    if state['start'] <= address < state['end']:
        return
    if address == 0x0807CCC0:
        src, dst, control = (engine.reg_read(reg) for reg in (
            arm_const.UC_ARM_REG_R0, arm_const.UC_ARM_REG_R1, arm_const.UC_ARM_REG_R2))
        size = ((control & 0x1FFFFF) + 7) // 8 * 32
        assert 0 < size <= 0x18000
        data = cpu.read(src, 4) * (size // 4) if control & 0x01000000 else cpu.read(src, size)
        cpu.write(dst, data)
        if 0x05000000 <= dst < 0x05001000:
            assert dst + size <= 0x05001000
            state['palette'][dst - 0x05000000:dst - 0x05000000 + size] = data
        if src in (0x08488520, 0x084885E0):
            assert size == 32 and not control & 0x01000000
            assert data == rom[src - 0x08000000:src - 0x08000000 + 32]
            seen.add((state['start'], src, dst))
    engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helper)
for start, end in ((0x0803F3A8, 0x0803F3E0), (0x080075AC, 0x08007834)):
    cpu.write(0x03000000, bytes(0x7E00))
    cpu.write(0x04000000, bytes(0x1000))
    state.update(start=start, end=end, palette=bytearray([0xA5] * 0x1000))
    cpu.write(0x05000000, bytes(state['palette']))
    regs = cpu.call(start, timeout_us=0, instruction_limit=200000)
    assert cpu.read(0x05000000, 0x1000) == state['palette']
    assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

assert seen == {(0x0803F3A8, 0x08488520, 0x050001E0),
                (0x080075AC, 0x084885E0, 0x05000160)}
print('Two native loader fixtures cover both palette banks; CpuFastSet modeled, other helpers stubbed')
