"""Check native medal-icon and background-palette selection.

BIOS copy/LZ77 operations and immediate DMA3 transfers are explicit host
models. Background display setup helpers are no-ops; no rendering is claimed.
"""
import argparse
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn
from lz77_codec import decode


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=Path('build/analysis/ui-graphics-cpu.json'))
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    cpu = RoutineCpu(rom)
    cpu.engine.mem_map(0x04000000, 0x1000)
    cpu.engine.mem_map(0x05000000, 0x1000)
    calls, dma_calls = [], []

    def hook(machine, address, size, user_data):
        if address not in (0x0807CCC0, 0x0807CCD8, 0x08068460, 0x0803FAA0):
            return
        r0, r1, r2 = (machine.reg_read(getattr(arm_const, f'UC_ARM_REG_R{i}')) for i in range(3))
        calls.append((address, r0, r1, r2))
        if address == 0x0807CCC0:
            assert r2 == 0x20, hex(r2)
            machine.mem_write(r1, bytes(machine.mem_read(r0, 128)))
        elif address == 0x0807CCD8:
            payload, consumed = decode(rom, r0 - 0x08000000)
            machine.mem_write(r1, payload)
        machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    def dma_hook(machine, access, address, size, value, user_data):
        if address != 0x040000DC:
            return
        source, destination = struct.unpack('<II', machine.mem_read(0x040000D4, 8))
        assert value in (0x84000140, 0x800000E0), hex(value)
        byte_count = (value & 0xFFFF) * (4 if value & 0x04000000 else 2)
        machine.mem_write(destination, bytes(machine.mem_read(source, byte_count)))
        dma_calls.append((source, destination, value))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
    cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, dma_hook)
    icon_cases = 0
    for asset in range(32):
        for mode in range(2):
            for choice in range(3):
                setup = bytearray([0xA5]) * (6 * 256)
                for bank in range(6):
                    setup[bank * 256 + 1] = (asset + 3 * bank) % 32
                selected = setup[(mode * 3 + choice) * 256 + 1]
                cpu.write(0x03000590, bytes(setup))
                cpu.write(0x0300047C, bytes([mode, choice]))
                cpu.write(0x060077C0, bytes([0xC3]) * 256)
                calls.clear()
                registers = cpu.call(0x08017D50, timeout_us=0, instruction_limit=1000)
                source = 0x084C29D8 + selected * 128
                assert calls == [(0x0807CCC0, source, 0x06007800, 0x20)]
                expected = bytes([0xC3]) * 64 + rom[source-0x08000000:source-0x08000000+128] + bytes([0xC3]) * 64
                assert cpu.read(0x060077C0, 256) == expected
                assert registers[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
                assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
                icon_cases += 1
    palettes = struct.unpack_from('<12I', rom, 0x486E24)
    maps = struct.unpack_from('<12I', rom, 0x486DF4)
    tiles = struct.unpack_from('<12I', rom, 0x486DC4)
    for index in range(12):
        cpu.write(0x03001800, bytes(0x1B1))
        cpu.write(0x0300180C, struct.pack('<H', index))
        cpu.write(0x05000000, bytes([0xA5]) * 512)
        cpu.write(0x06007800, bytes([0xC3]) * 1280)
        cpu.write(0x04000000, bytes(0x1000))
        calls.clear()
        dma_calls.clear()
        registers = cpu.call(0x0806E2A0, timeout_us=0, instruction_limit=50000)
        packed, consumed = decode(rom, maps[index]-0x08000000)
        assert len(packed) == 1200
        expected = b''.join(packed[row*60:(row+1)*60] + bytes(4) for row in range(20))
        assert cpu.read(0x06007800, 1280) == expected
        assert cpu.read(0x05000000, 512) == rom[palettes[index]-0x08000000:palettes[index]-0x08000000+448] + bytes([0xA5]) * 64
        decoded_tiles, consumed = decode(rom, tiles[index]-0x08000000)
        assert cpu.read(0x06008000, len(decoded_tiles)) == decoded_tiles
        assert [call[0] for call in calls] == [0x0807CCD8, 0x0807CCD8, 0x08068460, 0x0803FAA0]
        assert [call[1:] for call in dma_calls] == [(0x06007800, 0x84000140), (0x05000000, 0x800000E0)]
        assert dma_calls[-1][0] == palettes[index]
        assert cpu.read(0x03001804, 2) == struct.pack('<H', 4)
        assert cpu.read(0x0300137C, 4) == struct.pack('<I', 1)
        assert registers[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
    report = {'icon_selection_cases': icon_cases, 'background_cases': 12,
              'background_palette_copy_bytes': 448, 'stored_icons': 32,
              'duplicate_fallback_icons': rom[0x4C38D8:0x4C3958] == rom[0x4C3958:0x4C39D8],
              'hooks': ['CpuFastSet: 128-byte copy', 'LZ77UnCompVram: host decoder',
                        'DMA3: immediate 1280-byte map and 448-byte palette copies',
                        '08068460 and 0803FAA0: no-op display helpers'],
              'scope': 'Original Thumb selection/map expansion; no hardware or rendering emulation.'}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()
