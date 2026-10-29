"""Check numeric tile DMA and affine sine consumers against the original ROM."""
import json
import struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


def main():
    rom = find_rom().read_bytes()
    cpu = RoutineCpu(rom)
    cpu.engine.mem_map(0x04000000, 0x1000)
    transfers = []

    def code(machine, address, size, user):
        if address == 0x08048864:
            machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    def dma(machine, access, address, size, value, user):
        if address != 0x040000DC:
            return
        source, destination = struct.unpack('<II', cpu.read(0x040000D4, 8))
        assert value == 0x84000008
        cpu.write(destination, cpu.read(source, 32))
        transfers.append((source, destination))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, code)
    cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, dma)
    for tile in range(224):
        cpu.write(0x030057B3, b'\0')
        cpu.write(0x02020000, bytes([tile]))
        cpu.write(0x060179E0, bytes([0xA5]) * 96)
        transfers.clear()
        result = cpu.call(0x080598C0, (0x02020000, 1, 16, 24))
        source = 0x080ACCF4 + tile * 32
        assert transfers == [(source, 0x06017A00)]
        assert cpu.read(0x060179E0, 96) == bytes([0xA5]) * 32 + rom[source-0x08000000:source-0x08000000+32] + bytes([0xA5]) * 32
        assert cpu.read(0x030057B3, 1) == b'\1'
        assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
    sine = struct.unpack_from('<320h', rom, 0xAE8F4)
    assert sine[256:] == sine[:64]
    affine_cases = 0
    for angle in range(256):
        for scale_x, scale_y in ((256, 256), (128, 512), (-256, 256)):
            work = bytearray(0x38)
            struct.pack_into('<hh', work, 0x2C, 3, -7)
            struct.pack_into('<hhH', work, 0x32, scale_x, scale_y, angle)
            cpu.write(0x03005310, bytes(work))
            result = cpu.call(0x08048A8C)
            rx, ry = int(65536 / scale_x), int(65536 / scale_y)
            # Native fixed-point multiplication truncates toward zero.
            pa, pb, pc, pd = (int(sine[angle+64]*rx / 256), int(sine[angle]*rx / 256),
                              int(-sine[angle]*ry / 256), int(sine[angle+64]*ry / 256))
            expected = struct.pack('<hhhhii', pa, pb, pc, pd,
                                   (120-3)*256-pa*120-pb*80,
                                   (120+7)*256-pc*120-pd*80)
            assert cpu.read(0x03005318, 16) == expected, (angle, scale_x, scale_y)
            assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
            assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
            affine_cases += 1
    tilemap_cases = 0
    tiles = struct.unpack_from('<160H', rom, 0x3D611C)
    for mode in (0, 1):
        for palette in (0, 15):
            for offset in (0, 124, 1023):
                stride = 32 << mode
                expected = bytearray([0xA5]) * 0x1000
                for i, tile in enumerate(tiles):
                    row, column = divmod(i, 16)
                    value = ((tile & 1023) + offset) | (tile & 0xC00) | (palette << 12)
                    struct.pack_into('<H', expected, ((row + 1) * stride + column + 2) * 2, value & 65535)
                cpu.write(0x02020000, bytes([0xA5]) * 0x1000)
                cpu.write(0x03007F00, struct.pack('<5I', 16, 10, offset, palette, mode))
                result = cpu.call(0x08049210, (0x083D611C, 0x02020000, 1, 2))
                assert cpu.read(0x02020000, 0x1000) == expected
                assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
                assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
                tilemap_cases += 1
    report = dict(tile_cases=224, affine_cases=affine_cases, tilemap_cases=tilemap_cases,
                  hooks=['Immediate DMA3 host copy', '08048864 sprite initialization no-op'],
                  scope='Physical tile slots and 256 phases; native fixed-point arithmetic, no full rendering.')
    Path('build/analysis/numeric-display-data-cpu.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()
