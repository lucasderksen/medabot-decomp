"""Check early palette transfers through original loaders with external helpers stubbed."""
import json, struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn
rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
cpu.engine.mem_map(0x04000000, 4096)
cpu.engine.mem_map(0x05000000, 4096)
state = {}
coverage = set()
transfers = set()
cases = 0
LOW = 0x0850F298
HIGH = 0x0850FA58

def hook(machine, address, size, user):
    if state['start'] <= address < state['end']:
        return
    assert 0x08000000 <= address < 0x08800000, hex(address)
    if address == 0x0807CCC0:
        src, dst, ctl = [machine.reg_read(r) for r in (arm_const.UC_ARM_REG_R0, arm_const.UC_ARM_REG_R1, arm_const.UC_ARM_REG_R2)]
        n = ((ctl & 2097151) + 7) // 8 * 32
        for base in (0x05000000, 0x0202F800):
            if base <= dst < base + 4096:
                assert dst + n <= base + 4096
                data = cpu.read(src, 4) * (n // 4) if ctl & 0x01000000 else cpu.read(src, n)
                cpu.write(dst, data)
                state['expected'][base][dst - base:dst - base + n] = data
                if LOW <= src < HIGH:
                    assert src + n <= HIGH and (not ctl & 0x01000000)
                    coverage.update(range(src, src + n))
                    transfers.add((state['start'], src, dst, n))
    machine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
TARGETS = [
    (0x08013B8C, 0x08013DE4),
    (0x0801A788, 0x0801ABF8),
    (0x0801C6C4, 0x0801C774),
    (0x0801E474, 0x0801E54C),
    (0x0801E5DC, 0x0801E830),
    (0x0801E918, 0x0801E9B0),
    (0x0801F018, 0x0801F0F0),
    (0x0801F0F0, 0x0801F1C8),
    (0x0801F214, 0x0801F290),
    (0x0801F5BC, 0x0801F780),
    (0x0801F800, 0x0801F9B0),
    (0x080200A8, 0x080201DC),
    (0x08020288, 0x080202E0),
    (0x0802036C, 0x08020428),
    (0x08020474, 0x08020530),
    (0x08020FB8, 0x08021000),
    (0x08022480, 0x08022648),
    (0x0802480C, 0x08024870),
    (0x08024890, 0x0802494C),
    (0x08026D98, 0x08026EC0),
    (0x0805CDAC, 0x0805CED0),
]
for start, end in TARGETS:
    for choice in range(4):
        for flags in (0, 2):
            cpu.write(0x03000000, bytes(32256))
            cpu.write(0x02000000, bytes(262144))
            cpu.write(0x03006F74, struct.pack('<I', 0x030057E0))
            cpu.write(0x030057F0, bytes([1]))
            cpu.write(0x0300057A, bytes([8]))
            cpu.write(0x030005D9, bytes([48 if flags else 0]))
            cpu.write(0x03001851, bytes([choice]))
            cpu.write(0x0300188B, bytes([choice]))
            cpu.write(0x030018F8, bytes([flags]))
            expected = {a: bytearray([165] * 4096) for a in (0x05000000, 0x0202F800)}
            for a, data in expected.items():
                cpu.write(a, bytes(data))
            state.update(start=start, end=end, expected=expected)
            regs = cpu.call(start, (flags // 2,), timeout_us=0, instruction_limit=200000)
            for a, data in expected.items():
                assert cpu.read(a, 4096) == data, (hex(start), hex(a))
            assert regs[4:12] == tuple((0xAB000000 | i for i in range(4, 12)))
            assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
            cases += 1
assert coverage == set(range(LOW, 0x0850F5D8)) | set(range(0x0850F5F8, HIGH))
report = dict(cases=cases, loaders=len(TARGETS), scope='Native loader branches and copy arguments; CpuFastSet modeled for palette RAM and shadow buffer, all other callees return zero. Guarded palette/shadow memory and preserved registers/SP checked. Rendering, other helper effects, audio and timing excluded.', covered_bytes=len(coverage), missing=[hex(a) for a in range(LOW, HIGH, 32) if a not in coverage], transfers=[dict(loader=hex(a), source=hex(b), destination=hex(c), bytes=d) for a, b, c, d in sorted(transfers)])
Path('build/more/early_palette_cpu.json').write_text(json.dumps(report, indent=2) + '\n')
print(cases, len(coverage), report['missing'])
