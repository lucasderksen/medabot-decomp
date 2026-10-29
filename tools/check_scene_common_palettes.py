"""Verify eight common palettes through native loaders, with DMA/BIOS modeled."""
import json
import struct
from pathlib import Path

from common import find_rom, load_segments
from cpu import RoutineCpu, arm_const, unicorn

LOW, HIGH = 0x084C7F34, 0x084C8034
NAMES = ('sub_080103F4', 'sub_0801058C', 'sub_08011764', 'sub_0801A788', 'sub_0801E300', 'sub_0803B5DC', 'sub_0803FAA0', 'sub_0805718C', 'sub_08061CE0',)

rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
cpu.engine.mem_map(0x04000000, 4096)
cpu.engine.mem_map(0x05000000, 4096)
state, coverage, transfers = {}, set(), set()


def transfer(src, dst, size, fill, unit):
    if size == 0:
        return
    assert 0 < size <= 0x18000, (hex(src), hex(dst), size)
    data = cpu.read(src, unit) * (size // unit) if fill else cpu.read(src, size)
    try: cpu.write(dst, data)
    except Exception:
        print('unmapped transfer',hex(src),hex(dst),size,hex(state['start']),flush=True); raise
    for base, expected in state['expected'].items():
        if base <= dst < base + len(expected):
            assert dst + size <= base + len(expected)
            expected[dst - base:dst - base + size] = data
    if LOW <= src < HIGH:
        assert size == 32 and (src - LOW) % 32 == 0 and not fill
        assert src + size <= HIGH
        assert 0x05000000 <= dst < 0x05000400 or 0x0202F800 <= dst < 0x0202FC00
        assert data == rom[src - 0x08000000:src - 0x08000000 + size]
        coverage.update(range(src, src + size))
        transfers.add((state['start'], src, dst, size))


def hook(machine, address, size, user):
    if state['start'] <= address < state['end']:
        return
    assert 0x08000000 <= address < 0x08800000, hex(address)
    if address == 0x0807CCC0:
        src, dst, ctl = [machine.reg_read(r) for r in (
            arm_const.UC_ARM_REG_R0, arm_const.UC_ARM_REG_R1, arm_const.UC_ARM_REG_R2)]
        transfer(src, dst, ((ctl & 0x1FFFFF) + 7) // 8 * 32, bool(ctl & 0x01000000), 4)
    machine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))


def dma(machine, access, address, width, value, user):
    if value & 0x80000000:
        src, dst = struct.unpack('<II', cpu.read(0x040000D4, 8))
        unit = 4 if value & 0x04000000 else 2
        transfer(src, dst, (value & 65535) * unit, bool(value & 0x01000000), unit)


cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, dma, begin=0x040000DC, end=0x040000DC)
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
segments = {q['name']: q for q in load_segments()}
cases = 0
for name in NAMES:
    segment = segments[name]
    start, end = (segment[k] + 0x08000000 for k in ('start', 'end'))
    for phase in range(4):
        for flags in (0, 2):
            cpu.write(0x03000000, bytes(0x7E00))
            cpu.write(0x02000000, bytes(0x40000))
            cpu.write(0x04000000, bytes(4096))
            cpu.write(0x03006F74, struct.pack('<I', 0x030057E0))
            cpu.write(0x03006D14, struct.pack('<I', 0x02010000))
            cpu.write(0x030057F0, bytes([1]))
            cpu.write(0x03000579, bytes([phase]))
            cpu.write(0x0300057A, bytes([8]))
            cpu.write(0x030005D9, bytes([48 if flags else 0]))
            cpu.write(0x03001851, bytes([phase]))
            cpu.write(0x0300188B, bytes([phase]))
            cpu.write(0x030018F8, bytes([flags]))
            expected = {a: bytearray([0xA5] * 4096) for a in (0x05000000, 0x0202F800)}
            for base, data in expected.items():
                cpu.write(base, bytes(data))
            state.update(start=start, end=end, expected=expected)
            regs = cpu.call(start, (flags // 2,), timeout_us=0, instruction_limit=200000)
            for base, data in expected.items():
                assert cpu.read(base, len(data)) == data, (name, hex(base))
            assert regs[4:12] == tuple(0xAB000000 | i for i in range(4, 12)), name
            assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00, name
            cases += 1
assert coverage == set(range(LOW, HIGH))
report = dict(
    cases=cases, loaders=len(NAMES), covered_bytes=len(coverage),
    scope='Native loader bodies; CpuFastSet and DMA copy/fill modeled, all other '
          'callees return zero. Four phase values and two flag/slot values, '
          'guarded palette/shadow memory and preserved registers/SP checked. '
          'Rendering, other helper effects, audio and hardware timing excluded.',
    transfers=[dict(loader=hex(a), source=hex(b), destination=hex(c), bytes=d)
               for a, b, c, d in sorted(transfers)],
)
output = Path('build/more/scene_common_palette_cpu.json')
output.parent.mkdir(parents=True, exist_ok=True)
output.write_text(json.dumps(report, indent=2) + '\n')
print(f'{cases} native fixtures; {len(NAMES)} loaders; {len(coverage)} palette bytes')



