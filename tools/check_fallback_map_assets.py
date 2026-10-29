"""Exercise fallback-map DMA branches with explicitly injected null table entries."""
import json
import struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

reference = find_rom().read_bytes()
coverage = set()
cases = 0
transfers = []
for map_index in (0, 191):
    for start, end, table in ((0x0804830C, 0x080483F8, 0x3F9980),
                              (0x0804B2B0, 0x0804B5FC, 0x3F9080)):
        fixture = bytearray(reference)
        stride = 4 if table == 0x3F9980 else 12
        struct.pack_into('<I', fixture, table + map_index * stride, 0)
        cpu = RoutineCpu(bytes(fixture))
        cpu.engine.mem_map(0x04000000, 0x1000)
        cpu.write(0x03005FDE, bytes([map_index]))
        cpu.write(0x03006D14, struct.pack('<I', 0x02010000))
        expected = {0x0202FA00: bytearray([0xA5] * 0x400),
                    0x06009000: bytearray([0x5A] * 0x1000)}
        for base, data in expected.items():
            cpu.write(base, bytes(data))
        seen = []

        def call_hook(machine, address, size, user):
            if start <= address < end:
                return
            assert 0x08000000 <= address < 0x08800000, hex(address)
            machine.reg_write(arm_const.UC_ARM_REG_R0, 0)
            machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

        def dma_hook(machine, access, address, size, control, user):
            assert size == 4 and control in (0x84000008, 0x80000040)
            source, destination = struct.unpack('<II', cpu.read(0x040000D4, 8))
            length = (control & 0xFFFF) * (4 if control & 0x04000000 else 2)
            assert 0x080AC72C <= source < source + length <= 0x080ACAEC
            base = 0x0202FA00 if control == 0x84000008 else 0x06009000
            assert base <= destination <= base + len(expected[base]) - length
            payload = reference[source - 0x08000000:source - 0x08000000 + length]
            cpu.write(destination, payload)
            expected[base][destination - base:destination - base + length] = payload
            coverage.update(range(source, source + length))
            seen.append((source, destination, length))

        cpu.engine.hook_add(unicorn.UC_HOOK_CODE, call_hook)
        cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, dma_hook, begin=0x040000DC, end=0x040000DC)
        registers = cpu.call(start, timeout_us=0, instruction_limit=200000)
        assert len(seen) == 9
        assert [((src - 0x080AC72C) // 160) for src, _, _ in seen] == [0, 1, 2, 3, 0, 0, 0, 4, 5]
        for base, data in expected.items():
            assert cpu.read(base, len(data)) == data
        assert registers[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
        transfers.append(dict(loader=hex(start), map_index=map_index, copies=seen))
        cases += 1
assert coverage == set(range(0x080AC72C, 0x080ACAEC))
report = dict(cases=cases, covered_bytes=len(coverage), transfers=transfers,
              scope='Original loader bodies with one ROM table entry explicitly replaced by null per fixture. DMA copies modeled; other external callees return zero. Guarded transfer buffers and ABI checked. Does not establish fallback reachability in the shipped game, rendering or hardware timing.')
Path('build/more/fallback_map_cpu.json').write_text(json.dumps(report, indent=2) + '\n')
print(cases, 'fixtures;', len(coverage), 'bytes covered')
