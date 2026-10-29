"""Native selectors for object/scene callbacks, vertical steps and random choices."""
import sys, json, struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn
rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
state = {}
counts = {}
coverage = set()
ranges = [(0x83afaec, 0x83afe88)]

def read_hook(machine, access, address, size, value, user):
    for lo, hi in ranges:
        if lo <= address and address + size <= hi:
            coverage.update(range(address, address + size))

def code_hook(machine, address, size, user):
    if state['start'] <= address < state['end'] or address == 0x807ccf0:
        return
    assert 0x8000000 <= address < 0x8800000, hex(address)
    if state['start'] == 0x803c0cc and address == 0x804422c:
        cpu.write(0x3002c32, struct.pack('<H', 136))
    if state.get('callback') == address:
        state['calls'].append((address, cpu.read(0x300056f, 1)[0]))
    machine.reg_write(arm_const.UC_ARM_REG_R0, state.get('random', 0) if address == 0x80424b8 else 0)
    machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE, code_hook)
cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, read_hook, begin=0x83afaec, end=0x83afe87)

def begin(start, end):
    cpu.write(0x3000000, bytes(28672))
    state.clear()
    state.update(start=start, end=end, calls=[])

def run(expected):
    regs = cpu.call(state['start'], timeout_us=0)
    assert cpu.read(0x3000000, 28672) == expected, hex(state['start'])
    assert regs[4:12] == tuple((0xab000000 | i for i in range(4, 12)))
    assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x3007f00
    key = hex(state['start'])
    counts[key] = counts.get(key, 0) + 1
for index in range(80):
    begin(0x803b8c8, 0x803b900)
    for slot in range(1, 40):
        cpu.write(0x3002c30 + slot * 64 + 41, bytes([index]))
    state['callback'] = struct.unpack_from('<I', rom, 3865324 + index * 4)[0] & ~1
    expected = bytearray(cpu.read(0x3000000, 28672))
    expected[1391] = 39
    run(expected)
    assert state['calls'] == [(state['callback'], slot) for slot in range(1, 40)]
for index in range(96):
    begin(0x803d538, 0x803d5a0)
    cpu.write(0x300137c, struct.pack('<I', index))
    state['callback'] = struct.unpack_from('<I', rom, 3865720 + index * 4)[0] & ~1
    run(cpu.read(0x3000000, 28672))
    assert len(state['calls']) == 1, (index, state['calls'])
for index in range(32):
    for y in (0, 32767, 65535):
        begin(0x803c680, 0x803c738)
        cpu.write(0x3002c34, struct.pack('<H', y))
        cpu.write(0x3002c53, bytes([index]))
        cpu.write(0x3002c5c, bytes([2]))
        expected = bytearray(cpu.read(0x3000000, 28672))
        step = struct.unpack_from('<h', rom, 3865656 + index * 2)[0]
        struct.pack_into('<H', expected, 11316, y + step & 65535)
        expected[11347] = index + 1 & 31
        expected[11356] = 1
        run(expected)
for index in range(32):
    for upper in (0, 0xffffffe0):
        begin(0x803d71c, 0x803d74c)
        state['random'] = upper | index
        cpu.write(0x300137c, struct.pack('<I', 7))
        expected = bytearray(cpu.read(0x3000000, 28672))
        expected[6200] = rom[3866104 + index]
        struct.pack_into('<I', expected, 4988, 8)
        run(expected)
for index in range(16):
    for upper in (0, 0xfffffff0):
        begin(0x803e8b8, 0x803e8ec)
        state['random'] = upper | index
        expected = bytearray(cpu.read(0x3000000, 28672))
        expected[6554:6560] = rom[3866136 + index * 6:3866136 + index * 6 + 6]
        run(expected)
for index in range(12):
    begin(0x803c0cc, 0x803c33c)
    cpu.write(0x3001838, bytes([index]))
    cpu.write(0x3002c55, bytes([1]))
    cpu.write(0x3002c32, struct.pack('<H', 128))
    cpu.write(0x3002c60, struct.pack('<H', 130))
    expected = bytearray(cpu.read(0x3000000, 28672))
    shift = rom[3865644 + index]
    for off, val in [(11314, 120), (11360, 138), (6484, 496), (6488, 496), (1404, 16), (7172, 16 >> shift)]:
        struct.pack_into('<H', expected, off, val)
    run(expected)
for index in range(16):
    for side in range(2):
        for part in range(3):
            for active in range(8):
                begin(0x803ee10, 0x803eed8)
                state['random'] = index | 0xfffffff0
                cpu.write(0x30004dc, bytes([side]))
                cpu.write(0x300199a, bytes([part]))
                cpu.write(0x30019a4, b'\xa5Z')
                for bank in range(6):
                    base = 0x3000590 + bank * 256
                    cpu.write(base + 71, bytes([20 + bank]))
                    cpu.write(base + 186, bytes([active >> bank % 3 & 1]))
                    for slot in range(3):
                        cpu.write(base + 95 + slot * 24, bytes([100 + bank * 3 + slot]))
                expected = bytearray(cpu.read(0x3000000, 28672))
                choice = rom[3866232 + index]
                for j in range(3):
                    k = (choice + j) % 3
                    if active & 1 << k:
                        bank = side * 3 + k
                        expected[6564:6566] = bytes([20 + bank, 100 + bank * 3 + part])
                        break
                run(expected)
assert coverage == set().union(*(set(range(a, b)) for a, b in ranges))
report = dict(cases=counts, total_cases=sum(counts.values()), covered_bytes=len(coverage), scope='Original dispatch/selection/motion bodies and call trampoline. Callback bodies and other external helpers stubbed; random helper returns fixture value and the movement helper supplies a fixed +8 X step. Guarded IWRAM and ABI checked; callback effects/rendering/timing excluded.')
Path('build/more/object_scene_tables_cpu.json').write_text(json.dumps(report, indent=2) + '\n')
print(report)
