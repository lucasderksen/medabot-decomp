"""Exercise object dispatch, scripted randomness and stored tilemap spans.

Callback bodies are intercepted. Tilemap fixtures cover physical spans, without
claiming that every span is one rectangle in gameplay. Other consumers run native.
"""
import json
import math
import struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


def main():
    rom = find_rom().read_bytes()
    cpu = RoutineCpu(rom)
    state = dict(target=None, calls=0, marker=0)

    def hook(machine, address, size, user):
        if address == state['target']:
            state['calls'] += 1
            cpu.write(0x03000444, bytes([state['marker']]))
            machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    def preserved(result):
        assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
    callback_cases = 0
    for entry, root, count, selector in ((0x08041674, 0x3B2994, 14, 0x29),
                                        (0x08041CA4, 0x3B29CC, 6, 0x1B),
                                        (0x08041CD4, 0x3B29E4, 2, 0x1B)):
        for index, target in enumerate(struct.unpack_from('<' + 'I' * count, rom, root)):
            for marker in (0, 7, 8, 255):
                cpu.write(0x03000440, bytes(256))
                cpu.write(0x03000440 + selector, bytes([index]))
                cpu.write(0x03000468, b'\xA5')
                state.update(target=target & ~1, calls=0, marker=marker)
                result = cpu.call(entry)
                assert state['calls'] == 1
                assert result[0] == (0xA5 if entry == 0x08041674 else int(marker > 7))
                preserved(result)
                callback_cases += 1
    state['target'] = None
    for index in range(256):
        cpu.write(0x03000440, bytes(256))
        cpu.write(0x030004C9, b'\1')
        cpu.write(0x030004CD, bytes([index]))
        result = cpu.call(0x080424B8)
        expected_index = (index + 1) & 255
        expected = rom[0x3B29EC + expected_index]
        assert result[0] == expected
        assert cpu.read(0x030004CC, 2) == bytes([expected, expected_index])
        preserved(result)
    selector_cases = 0
    for selector in range(16):
        cpu.write(0x0300643C, bytes([selector]))
        for argument in (0, 1, 255, 256, 257):
            result = cpu.call(0x08044B34, (argument,))
            assert result[0] == (argument & 255 or rom[0x3B2AF0 + selector])
            preserved(result)
            selector_cases += 1
    roots = struct.unpack_from('<106I', rom, 0x3B4C60)
    boundaries = sorted(set(roots) | {0x083B4C60})
    ends = dict(zip(boundaries, boundaries[1:]))
    tilemap_cases = 0
    for root in roots:
        count = (ends[root] - root) // 2
        width = math.gcd(count, 32)
        height = count // width
        values = struct.unpack_from('<' + 'H' * count, rom, root - 0x08000000)
        for offset in (0, 0x400, 0xFFFF):
            expected = bytearray([0xA5]) * 0x8000
            for i, value in enumerate(values):
                row, column = divmod(i, width)
                struct.pack_into('<H', expected, 0x800 + ((row + 1) * 32 + column) * 2, (value + offset) & 65535)
            cpu.write(0x06000000, bytes([0xA5]) * 0x8000)
            cpu.write(0x03007F00, struct.pack('<III', root, 0x100, offset))
            result = cpu.call(0x0803F15C, (width, height, 0, 1))
            assert cpu.read(0x06000000, 0x8000) == expected, (hex(root), offset)
            preserved(result)
            tilemap_cases += 1
    part_cases = 0
    for record in range(120):
        for slot in range(4):
            cpu.write(0x02020000, bytes([0xA5]) * 48)
            result = cpu.call(0x08042B58, (record, slot, 0x02020010))
            source = 0x3B83FC + record * 64 + slot * 16
            assert cpu.read(0x02020000, 48) == bytes([0xA5]) * 16 + rom[source:source+16] + bytes([0xA5]) * 16
            preserved(result)
            part_cases += 1
    report = dict(callback_cases=callback_cases, scripted_random_cases=256, part_cases=part_cases,
                  selector_cases=selector_cases, tilemap_cases=tilemap_cases,
                  tilemap_roots=106, unique_tilemap_roots=len(set(roots)),
                  hooks='Selected callback bodies only; no-op except controlled result flag.')
    Path('build/analysis/object-display-data-cpu.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()
