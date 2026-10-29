"""Exercise every stored asset pair through the original ROM loader.

RAM fixtures select each physical pair independently; this does not establish
gameplay reachability. LZ77 and CpuSet are host models; sprite setup runs native.
"""
import json
import struct
from pathlib import Path

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn
from lz77_codec import decode


def main():
    rom = find_rom().read_bytes()
    cpu = RoutineCpu(rom)
    cpu.engine.mem_map(0x04000000, 0x1000)
    cpu.engine.mem_map(0x05000000, 0x1000)
    calls = []

    def hook(machine, address, size, userdata):
        if address not in (0x08044D0C, 0x0807CCC4):
            return
        a, b, c = (machine.reg_read(getattr(arm_const, f'UC_ARM_REG_R{i}')) for i in range(3))
        if address == 0x08044D0C:
            payload, _ = decode(rom, a - 0x08000000)
            cpu.write(b, payload)
            machine.reg_write(arm_const.UC_ARM_REG_R0, len(payload))
        else:
            width = 4 if c & (1 << 26) else 2
            count = c & 0x1FFFFF
            payload = cpu.read(a, width) * count if c & (1 << 24) else cpu.read(a, width * count)
            cpu.write(b, payload)
            calls.append((a, b, len(payload)))
        machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
    pairs = list(struct.iter_unpack('<II', rom[0x3CF5B0:0x3D1940]))
    descriptor = bytearray(rom[0x3D1940:0x3D1958])
    descriptor[15:22] = bytes([0, 0, 0, 8, 8, 0x11, 0])
    for index, (source, companion) in enumerate(pairs):
        struct.pack_into('<I', descriptor, 0, 0x083CF5B0 + 8 * index)
        cpu.write(0x02020000, struct.pack('<II', 0, 0x02020100))
        cpu.write(0x02020100, bytes(descriptor))
        cpu.write(0x02021000, struct.pack('<II', 1, 0))
        cpu.write(0x02022000, bytes(800))
        cpu.write(0x02023000, struct.pack('<H', 0x40))
        cpu.write(0x03007F00, struct.pack('<III', 0x02022000, 0x02023000, 0))
        cpu.write(0x05000240, bytes([0xA5]) * 96)
        cpu.write(0x02030440, bytes([0xA5]) * 96)
        cpu.write(0x060107E0, bytes([0xA5]) * 0x5000)
        calls.clear()
        result = cpu.call(0x08045E6C, (0x02020000, 0x02021000, 1, 3))
        expected = decode(rom, source - 0x08000000)[0] if source else b''
        assert result[0] == len(expected), (index, result[0], len(expected))
        assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12)), index
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
        assert cpu.read(0x02023000, 2) == struct.pack('<H', 0x40 + bool(source)), index
        assert cpu.read(0x06010800, len(expected)) == expected, index
        assert cpu.read(0x060107E0, 32) == bytes([0xA5]) * 32
        assert cpu.read(0x06010800 + len(expected), 32) == bytes([0xA5]) * 32
        palette = rom[companion - 0x08000000:companion - 0x08000000 + 32] if companion else bytes([0xA5]) * 32
        for address in (0x05000260, 0x02030460):
            assert cpu.read(address - 32, 96) == bytes([0xA5]) * 32 + palette + bytes([0xA5]) * 32, index
        assert len(calls) == (3 if source else 0), (index, calls)
        assert cpu.read(0x02022010, 8) == (struct.pack('<4H', 0, 0, 0x3840, 0) if source else bytes(8)), index
    shapes = {(8, 8): (0, 0), (16, 16): (0, 1), (32, 32): (0, 2), (64, 64): (0, 3),
              (16, 8): (1, 1), (32, 8): (1, 1), (32, 16): (1, 2), (64, 32): (1, 3),
              (8, 16): (2, 1), (8, 32): (2, 1), (16, 32): (2, 2), (32, 64): (2, 3)}
    descriptor_cases = 0
    for offset in range(0x3D1940, 0x3D1D78, 24):
        data = rom[offset:offset + 24]
        assert data[20:24] == bytes([0x11, 0, 0, 0])
        assert data[15] < 50 and data[16] < 50
        height, width = data[18:20]
        shape, size = shapes[width, height]
        for palette, tile in ((0, 0), (3, 1023), (15, 1024)):
            cpu.write(0x02024000, bytes(8))
            result = cpu.call(0x08045D34, (0x02024000, offset + 0x08000000, palette, tile))
            assert result[0] == height * width // 64
            assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
            assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
            expected = struct.pack('<4H', shape << 14, size << 14,
                                   (tile & 1023) | 0x800 | (((palette + data[17]) & 15) << 12), 0)
            assert cpu.read(0x02024000, 8) == expected, (hex(offset), width, height)
            descriptor_cases += 1
    directory = struct.unpack_from('<50I', rom, 0x3D1D78)
    assert directory.count(0) == 1
    assert {p for p in directory if p >= 0x08000000} == set(range(0x083D1940, 0x083D1D78, 24))
    assert {p for p in directory if p and p < 0x08000000} == {0x03005290, 0x030052B0, 0x030052D0, 0x030052F0}
    report = {'pair_cases': len(pairs), 'descriptor_cases': descriptor_cases,
              'null_pairs': sum(not a for a, b in pairs),
              'native_loader': '08045E6C', 'native_sprite_builder': '08045D34',
              'host_models': ['08044D0C LZ77', '0807CCC4 CpuSet'],
              'scope': 'Physical pairs selected through RAM fixtures; not gameplay reachability.'}
    path = Path('build/analysis/record-assets-cpu.json')
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()
