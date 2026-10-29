"""Exercise original action palette loaders with graphics/audio helpers intercepted."""
import json
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
cpu.engine.mem_map(0x04000000, 0x1000)
cpu.engine.mem_map(0x05000000, 0x1000)
state = {}
RANGES = [(0x0850FBF8, 0x0850FEF8), (0x085100D8, 0x08510538), (0x0850FF18, 0x0850FF98)]
coverage = set()
transfers = set()
helper_calls = {}

def hook(machine, address, size, user):
    if state['start'] <= address < state['end']:
        return
    assert 0x08000000 <= address < 0x08800000, hex(address)
    helper_calls[address] = helper_calls.get(address, 0) + 1
    if address == 0x0807CCC0:
        source, destination, control = (machine.reg_read(reg) for reg in
            (arm_const.UC_ARM_REG_R0, arm_const.UC_ARM_REG_R1, arm_const.UC_ARM_REG_R2))
        size = ((control & 0x1FFFFF) + 7) // 8 * 32
        if 0x05000000 <= destination < 0x05001000 and 0x08000000 <= source < 0x08800000:
            assert not control & 0x01000000
            payload = rom[source - 0x08000000:source - 0x08000000 + size]
            assert len(payload) == size and destination + size <= 0x05001000
            cpu.write(destination, payload)
            offset = destination - 0x05000000
            state['expected'][offset:offset + size] = payload
            if any(a <= source < b for a, b in RANGES):
                assert (any(a <= source and source + size <= b for a, b in RANGES) or (source == 0x0850FED8 and size == 64)) and size in (32, 64), (hex(state["start"]), hex(source), hex(destination), size)
                # FED8 also copies the already reconstructed adjacent palette at FEF8.
                coverage.update(x for x in range(source, source + size) if any(a <= x < b for a, b in RANGES))
                transfers.add((state['start'], source, destination, size))
    machine.reg_write(arm_const.UC_ARM_REG_R0, 0)
    machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)

def dma_hook(machine, access, address, size, value, user):
    if address != 0x040000DC or size != 4:
        return
    import struct
    source, destination = struct.unpack('<II', cpu.read(0x040000D4, 8))
    if not any(a <= source < b for a, b in RANGES):
        return
    assert value == 0x84000008
    payload = rom[source - 0x08000000:source - 0x08000000 + 32]
    assert 0x05000000 <= destination <= 0x05000FE0
    cpu.write(destination, payload)
    offset = destination - 0x05000000
    state['expected'][offset:offset + 32] = payload
    coverage.update(range(source, source + 32))
    transfers.add((state['start'], source, destination, 32))

cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, dma_hook, begin=0x040000DC, end=0x040000DC)

# Exact integrated function bounds containing all literals into this palette bank.
TARGETS = [
    (0x08010DAC, 0x08010E50),
    (0x08026184, 0x08026284),
    (0x080264E4, 0x08026628),

    (0x08020DF8, 0x08020EDC),
    (0x08021038, 0x080211C8),
    (0x08021950, 0x080219C0),
    (0x08021EA0, 0x08021F90),
    (0x080221C8, 0x080222A8),
    (0x08022870, 0x08022938),
    (0x08022D4C, 0x08022E14),
    (0x0802306C, 0x080230A4),
    (0x080234A8, 0x08023564),
    (0x080237C8, 0x080238A0),
    (0x08023B44, 0x08023C18),
    (0x08023D44, 0x08023E18),
    (0x08023E94, 0x08023F48),
    (0x0802410C, 0x080241F0),
    (0x08024A30, 0x08024AF4),
    (0x08024E9C, 0x08024F90),
    (0x08025230, 0x08025308),
    (0x08025858, 0x08025974),
    (0x08025B9C, 0x08025C84),
    (0x08025FC8, 0x08026080),
    (0x080270BC, 0x080271C4),
    (0x080279E4, 0x08027BA0),
    (0x08028270, 0x080282E0),
    (0x08028504, 0x080287C0),
    (0x08028A38, 0x08028B58),
    (0x08028CC8, 0x08028E84),
    (0x080291E0, 0x080292D4),
    (0x080294DC, 0x08029600),
    (0x08029680, 0x0802976C),
    (0x08029868, 0x08029984),
    (0x08029A14, 0x08029B04),
    (0x08029E34, 0x08029F50),
    (0x0802A110, 0x0802A274),
    (0x0802A6D4, 0x0802A7E0),
    (0x0802AAF8, 0x0802AC7C),
    (0x0802ACF4, 0x0802AE88),
    (0x0802B028, 0x0802B184),
    (0x0802B258, 0x0802B388),
    (0x0802B3CC, 0x0802B460),
    (0x0802B8BC, 0x0802B980),
    (0x0802C2D4, 0x0802C440),
    (0x0802C66C, 0x0802C714),
    (0x0802C864, 0x0802C960),
    (0x0802CC74, 0x0802CD48),
    (0x0802D6B0, 0x0802D758),
    (0x0802D7EC, 0x0802D8D0),
    (0x0802DCDC, 0x0802DD98),
    (0x0802E4C8, 0x0802E5D4),
    (0x0802E948, 0x0802EAA4),
    (0x0802EC4C, 0x0802ED34),
    (0x0802F058, 0x0802F13C),
    (0x0802F4D0, 0x0802F594),
    (0x0802F6CC, 0x0802F7B8),
    (0x0802F9B8, 0x0802FB74),
    (0x0802FC3C, 0x0802FD08),
    (0x0802FE78, 0x08030180),
    (0x0803DCDC, 0x0803DE70),
]
cases = 0
for start, end in TARGETS:
    kinds = [4, 5, 6, 7, 8, 255] if start == 0x080279E4 else [12, 14, 16, 18, 40] if start == 0x08028504 else [0, 46] if start == 0x08025858 else [0]
    choices = range(4) if start == 0x08028CC8 else [0]
    for kind in kinds:
        for choice in choices:
            for bank, flags in [(0, 0), (2, 1)]:
                cpu.write(0x03000000, bytes(0x7E00))
                cpu.write(0x02000000, bytes(0x40000))
                cpu.write(0x03001887, bytes([bank]))
                cpu.write(0x030018F8, bytes([flags]))
                cpu.write(0x03001851, bytes([choice]))
                cpu.write(0x03000590 + bank * 256 + 0xA8, bytes([kind]))
                cpu.write(0x03000590 + bank * 256 + 0x49, bytes([kind]))
                expected = bytearray([0xA5] * 0x1000)
                cpu.write(0x05000000, bytes(expected))
                state.update(start=start, end=end, expected=expected)
                registers = cpu.call(start, timeout_us=0, instruction_limit=200000)
                assert cpu.read(0x05000000, 0x1000) == expected, hex(start)
                assert registers[4:12] == tuple(0xAB000000 | i for i in range(4, 12)), hex(start)
                assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
                cases += 1
expected_coverage = {x for a, b in RANGES for x in range(a, b)}
assert coverage == expected_coverage, [hex(x) for x in sorted(expected_coverage - coverage)[:32]]
report = dict(cases=cases, loaders=len(TARGETS), covered_bytes=len(coverage),
              transfers=[dict(loader=hex(a), source=hex(b), destination=hex(c), bytes=d) for a,b,c,d in sorted(transfers)],
              intercepted_helpers={hex(k):v for k,v in sorted(helper_calls.items())},
              scope='Original loader branches and transfer arguments; all external callees return zero, except ROM-to-palette CpuFastSet copies modeled. DMA3 word transfer at 08010DAC is modeled on its register write. Palette memory and ABI checked. Other helper effects, graphics rendering, audio and hardware timing excluded.')
Path('build/more/action_palette_cpu.json').write_text(json.dumps(report, indent=2) + '\n')
print(f'{cases} cases, {len(TARGETS)} native loaders, {len(coverage)} palette bytes covered, {len(transfers)} distinct transfers')

