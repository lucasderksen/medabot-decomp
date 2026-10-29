"""Exercise original loaders for five new banks and one existing bank."""

import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
cpu.engine.mem_map(0x04000000, 0x1000)
cpu.engine.mem_map(0x05000000, 0x1000)
state, coverage, transfers = {}, set(), set()
RANGES = ((0x080AFBC4, 0x080AFBE4), (0x08488540, 0x084885E0))


def helpers(engine, address, _size, _user_data):
    if state['start'] <= address < state['end']:
        return
    if address == 0x0807CCC0:
        src, dst, control = (engine.reg_read(reg) for reg in (
            arm_const.UC_ARM_REG_R0, arm_const.UC_ARM_REG_R1, arm_const.UC_ARM_REG_R2))
        size = ((control & 0x1FFFFF) + 7) // 8 * 32
        assert 0 < size <= 0x18000
        data = cpu.read(src, 4) * (size // 4) if control & 0x01000000 else cpu.read(src, size)
        cpu.write(dst, data)
        for base, expected in state['expected'].items():
            if base <= dst < base + len(expected):
                assert dst + size <= base + len(expected)
                expected[dst - base:dst - base + size] = data
        for low, high in RANGES:
            if low <= src < high:
                assert size == 32 and src % 32 == low % 32 and not control & 0x01000000
                assert src + size <= high
                assert data == rom[src - 0x08000000:src - 0x08000000 + size]
                coverage.update(range(src, src + size))
                transfers.add((state['start'], src, dst))
    engine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))


cpu.engine.hook_add(unicorn.UC_HOOK_CODE, helpers)
cases = 0
for start, end in ((0x0801A788, 0x0801ABF8), (0x0801E300, 0x0801E3C0),
                   (0x0806113C, 0x080611E8), (0x080636FC, 0x0806379C)):
    for flag in (0, 1):
        cpu.write(0x03000000, bytes(0x7E00))
        cpu.write(0x02000000, bytes(0x40000))
        cpu.write(0x04000000, bytes(0x1000))
        cpu.write(0x03006F74, struct.pack('<I', 0x02020000))
        cpu.write(0x0300057A, bytes([8]))
        cpu.write(0x030004C4, bytes([65]))
        cpu.write(0x030018F8, bytes([flag * 2]))
        expected = {base: bytearray([0xA5] * 0x1000)
                    for base in (0x05000000, 0x0202F800)}
        for base, data in expected.items():
            cpu.write(base, bytes(data))
        state.update(start=start, end=end, expected=expected)
        regs = cpu.call(start, (flag,), timeout_us=0, instruction_limit=200000)
        for base, data in expected.items():
            assert cpu.read(base, len(data)) == data, (hex(start), flag, hex(base))
        assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
        cases += 1

assert coverage == set().union(*(set(range(low, high)) for low, high in RANGES))
assert {src for _, src, _ in transfers} == {0x080AFBC4, *(0x08488540 + 32 * i for i in range(5))}
print(f'{cases} native loader fixtures cover five new banks and one existing bank; other helpers stubbed')
