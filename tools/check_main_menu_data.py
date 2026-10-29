"""Check original menu table consumers with bounded Thumb CPU execution.

Callback bodies are explicitly intercepted: this verifies dispatch and the
dispatchers' scroll/frame updates, not the behavior of every menu state.
Cursor positioning, label lookup and boolean lookup run without stubs.
"""
import argparse
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

BASE = 0x08000000
FRAMES = 0x03002C30
CONTEXT = 0x02010000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=Path('build/analysis/main-menu-data-cpu.json'))
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    cpu = RoutineCpu(rom)
    state = {'target': None, 'calls': 0}

    def hook(machine, address, size, user_data):
        if address == state['target']:
            state['calls'] += 1
            machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
    # Entry, root, entries, BG2 increment, BG3 X/Y increments on odd frames,
    # optional frame-object update and its halfword choice root.
    dispatchers = [
        (0x0805BBE0, 0x483594, 30, 0, 0, 0, None),
        (0x0805C0D4, 0x48360C, 10, 1, 1, 1, None),
        (0x0805CB50, 0x483634, 15, 0, 1, 1, None),
        (0x0805D704, 0x483670, 15, 0, 1, 1, (0, 0xAF958)),
        (0x0805E404, 0x4836D8, 7, 0, 1, 1, (20, 0xAF980)),
        (0x0805F104, 0x483700, 14, 0, 1, 1, None),
        (0x0805FC58, 0x483738, 8, 0, 0, 1, None),
        (0x08060280, 0x483758, 7, 0, 0, -1, None),
        (0x08060688, 0x483834, 8, 0, 0, 0, None),
        (0x08060D6C, 0x4838A4, 16, 0, 1, 1, None),
        (0x08061958, 0x483920, 10, 0, 1, 1, None),
        (0x08064DB4, 0x483948, 11, 0, 1, 1, None),
    ]
    dispatch_cases = 0
    for entry, root, count, bg2, dx, dy, frame_choice in dispatchers:
        for index in range(count):
            target = struct.unpack_from('<I', rom, root + index * 4)[0] & ~1
            for frame in (0, 1, 24, 0xFFFFFFFF):
                cpu.write(0x03000000, bytes(0x8000))
                cpu.write(FRAMES, bytes([0xA5]) * 8192)
                cpu.write(0x03002B8C, struct.pack('<I', index))
                cpu.write(0x0300137C, struct.pack('<I', index))
                cpu.write(0x03001780, struct.pack('<I', frame))
                cpu.write(0x0300057C, struct.pack('<HH', 0xFFFF, 0x1234))
                cpu.write(0x03001C04, struct.pack('<HH', 0xFFFF, 0))
                state.update(target=target, calls=0)
                registers = cpu.call(entry, timeout_us=0, instruction_limit=5000)
                assert state['calls'] == 1, (hex(entry), index, frame, state)
                assert cpu.read(0x0300057C, 4) == struct.pack('<HH', (0xFFFF + bg2) & 0xFFFF, 0x1234 + bg2)
                odd = frame & 1
                assert cpu.read(0x03001C04, 4) == struct.pack('<HH', (0xFFFF + dx * odd) & 0xFFFF, (dy * odd) & 0xFFFF), (hex(entry), index, frame, cpu.read(0x03001C04, 4).hex())
                expected = bytearray([0xA5]) * 8192
                if frame_choice:
                    slot, choices = frame_choice
                    value = struct.unpack_from('<H', rom, choices + ((frame >> 3) & 3) * 2)[0]
                    struct.pack_into('<H', expected, slot * 64 + 6, value)
                assert cpu.read(FRAMES, 8192) == expected
                assert registers[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
                assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
                dispatch_cases += 1
    state['target'] = None
    cursor_cases = 0
    # Include choice 10: the reference reads its coordinate bytes from the
    # adjacent X-offset object. Physical table extents are not a clamp.
    for coordinate in range(11):
        for choice in range(2):
            for timer in (*range(97), 0xFFFF):
                work = bytearray(256)
                work[0x17], work[0x18] = coordinate, choice
                cpu.write(CONTEXT, bytes(work))
                cpu.write(0x03006F74, struct.pack('<I', CONTEXT))
                frame_data = bytearray([0x5A]) * 64
                struct.pack_into('<H', frame_data, 0x1A, timer)
                cpu.write(FRAMES, bytes(frame_data))
                next_timer = timer + 1
                if next_timer & 0xFFFF > 96:
                    next_timer = 0
                phase = (next_timer & 0xFFFF) >> 3 & 3
                offset = choice * 8 + phase * 2
                x = rom[0x483854 + coordinate * 2] * 8 + struct.unpack_from('<H', rom, 0x483868 + offset)[0]
                y = rom[0x483855 + coordinate * 2] * 8 + struct.unpack_from('<H', rom, 0x483878 + offset)[0]
                group = struct.unpack_from('<H', rom, 0x483888 + offset)[0]
                struct.pack_into('<HHH', frame_data, 2, x, y, group)
                struct.pack_into('<H', frame_data, 0x1A, next_timer & 0xFFFF)
                registers = cpu.call(0x080605A0, timeout_us=0, instruction_limit=1000)
                assert cpu.read(FRAMES, 64) == frame_data, (coordinate, choice, timer)
                assert cpu.read(CONTEXT, 256) == work
                assert registers[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
                cursor_cases += 1
    for index in range(64):
        assert cpu.call(0x080480D4, (index,), timeout_us=0, instruction_limit=100)[0] == struct.unpack_from('<I', rom, 0x483ED8 + index * 4)[0]
        assert cpu.call(0x0805B5FC, (index,), timeout_us=0, instruction_limit=100)[0] == int(rom[0x483554 + index] == 1)
    roots = struct.unpack_from('<3I', rom, 0xB0014)
    assert roots == (0x08483974, 0x084839F0, 0x08483A64)
    line_counts = tuple(rom[0x483C10:0x483C13])
    assert line_counts == (31, 29, 107)
    for root, count in zip(roots, line_counts):
        for address in struct.unpack_from('<'+str(count)+'I', rom, root-BASE):
            assert 0x080AFCF4 <= address < 0x080B000E
            end = rom.index(0, address-BASE)
            assert all(0x20 <= c < 0x7F for c in rom[address-BASE:end])
    report = {'dispatch_cases': dispatch_cases, 'cursor_cases': cursor_cases,
              'label_lookup_cases': 64, 'boolean_lookup_cases': 64,
              'credit_lines': sum(line_counts), 'credits_unique_strings': 53,
              'stubs': 'Only the selected callback body; no stubs in cursor/label/boolean checks.',
              'scope': 'Dispatchers, cursor, pointer lookups and credits layout; no full menu/graphics emulation.'}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()
