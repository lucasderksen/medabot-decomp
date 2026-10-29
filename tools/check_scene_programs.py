"""Check stored scene commands and geometry against original Thumb consumers.

Program cases execute exactly one dispatched command, routing a second dispatch
to the routine's native epilogue. Engine/render helpers are explicit no-ops;
the real integer/float conversions and 49714/497C0 memory helpers execute.
Geometry cases stub projection/drawing, retaining native vertex arithmetic.
"""
import argparse
import collections
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn
from scene_programs import decode_bank, validate_roots

BASE = 0x08000000
SCENE = 0x03005350
ACTORS = 0x02010000
PROGRAM_HELPERS = {
    0x0804387C, 0x08047BA8, 0x080480E4, 0x0804842C, 0x08048864,
    0x08048888, 0x08049318, 0x08049374, 0x08049420, 0x08049440,
    0x080497E0, 0x08049A6C, 0x08049CFC, 0x08049D0C, 0x08049D18,
    0x08049D90, 0x08049E08, 0x08049EC0, 0x08049ED4, 0x0804B1B0,
    0x080505FC, 0x080506BC, 0x080517F0, 0x0805196C, 0x08051E38,
    0x0805273C, 0x08052760, 0x080528F8, 0x08052AA4, 0x08052B70,
    0x08052E0C, 0x08052E34, 0x08053464, 0x08054014, 0x080568F4,
    0x080569E4, 0x08056F24, 0x0807CCD8,
}
GEOMETRY_HELPERS = {0x08053858, 0x0805390C, 0x08053FBC, 0x080539C0, 0x080534C4}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=Path('build/analysis/scene-programs-cpu.json'))
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    commands = decode_bank(rom, 0x3D2FB0, 0x3D5F70)
    roots = struct.unpack_from('<33I', rom, 0x3D5F70)
    targets = validate_roots(commands, roots)
    cpu = RoutineCpu(rom)
    cpu.engine.mem_map(0x04000000, 0x1000)
    state = {'mode': 'program', 'dispatches': 0, 'script': None, 'motion': [], 'geometry': 0}
    helper_counts = collections.Counter()

    def hook(machine, address, size, user_data):
        if state['mode'] == 'setup':
            if address == state.get('callback'):
                state['callback_calls'] += 1
                machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))
            return
        if state['mode'] == 'program':
            if address == 0x08054280:
                state['dispatches'] += 1
                if state['dispatches'] > 1:
                    machine.reg_write(arm_const.UC_ARM_REG_PC, 0x080568C5)
                return
            if address == 0x080568C4:
                state['script'] = machine.reg_read(arm_const.UC_ARM_REG_R9)
                return
            helpers = PROGRAM_HELPERS
        else:
            helpers = GEOMETRY_HELPERS
        if address not in helpers:
            return
        helper_counts[address] += 1
        if address == 0x080569E4:
            pointer = machine.reg_read(arm_const.UC_ARM_REG_R1)
            state['motion'].append(bytes(machine.mem_read(pointer, 64)))
        if address == 0x080534C4:
            state['geometry'] += 1
        machine.reg_write(arm_const.UC_ARM_REG_R0, 0)
        machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)

    def word(address):
        return struct.unpack('<i', cpu.read(address, 4))[0]

    def put(address, value):
        cpu.write(address, struct.pack('<i', value))

    def saved(registers):
        assert registers[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
        assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00

    program_cases = scalar_checks = 0
    for command in commands:
        op, *values = command.words
        assert op not in (0, 5, 37), 'These unused/stalled commands need separate fixtures'
        for actor in (0, 1, 7):
            cpu.write(0x03000000, bytes(0x8000))
            cpu.write(ACTORS, bytes(16 * 0x300))
            put(0x03006D30, ACTORS)
            cursor = (command.offset - (roots[0] - BASE)) // 4
            put(SCENE + 0xFC, cursor)
            put(SCENE + 0x184, actor)
            if op == 35:
                put(SCENE + 0x140, 1)
                put(SCENE + 0x100, 9)
                put(SCENE + 0x144, roots[0])
                put(SCENE + 0x188, 3)
            for i in range(16):
                for axis in range(3):
                    cpu.write(ACTORS + i * 0x300 + 0x10 + axis * 0x48, struct.pack('<f', 10.0 * (i + 1) + axis))
                    put(ACTORS + i * 0x300 + 0x34 + axis * 0x48, 300 + axis * 100)
            state.update(dispatches=0, script=None, motion=[])
            registers = cpu.call(0x0805424C, timeout_us=0, instruction_limit=100000)
            saved(registers)
            expected_pc = cursor + len(command.words)
            expected_script = roots[0]
            if op == 2:
                expected_pc = cursor
            elif op == 4:
                expected_pc = 0
                assert word(SCENE + 0xF0) == 0
            elif op == 34:
                expected_pc, expected_script = 0, values[1]
                assert word(SCENE + 0x184) == values[0]
                assert word(SCENE + 0x100) == cursor + 3
                assert word(SCENE + 0x144) == roots[0]
                assert word(SCENE + 0x140) == 1
            elif op == 35:
                expected_pc = 9
                assert word(SCENE + 0x184) == 3 and word(SCENE + 0x140) == 0
            assert word(SCENE + 0xFC) == expected_pc, (hex(command.offset), actor, op, word(SCENE + 0xFC), expected_pc, state)
            assert state['script'] == expected_script, (hex(command.offset), actor, op)
            assert registers[0] == op
            if op in (1, 2, 4):
                assert state['dispatches'] == 1
            else:
                assert state['dispatches'] == 2
            a = ACTORS + actor * 0x300
            if op in (6, 7, 8):
                result = float(values[2]) + (10.0 + op - 6 if values[1] else 0.0)
                assert cpu.read(a + 0x10 + (op - 6) * 0x48, 4) == struct.pack('<f', result)
                scalar_checks += 1
            if op in (9, 10, 13, 14, 15):
                offset = {9: 0xF8, 10: 0x110, 13: 0x164, 14: 0x17C, 15: 0x194}[op]
                assert cpu.read(a + offset, 4) == struct.pack('<f', float(values[1]))
                scalar_checks += 1
            if op in (16, 17, 18):
                assert state['motion'] == [struct.pack('<16i', *values[1:])]
            if op == 36:
                child, mode, when, target, *relative = values
                if relative:
                    assert relative == [1, 0]
                    when = 500 - when
                assert word(a + 0x29C + child * 4) == target
                assert word(a + 0x21C + child * 4) == when
                assert word(a + 0x25C + child * 4) == child
                assert word(ACTORS + child * 0x300 + 0x214) == actor
                scalar_checks += 1
            program_cases += 1

    state['mode'] = 'geometry'
    source_roots = struct.unpack_from('<32I', rom, 0x3D2F30)
    geometry_cases = 0
    # Every stored source-pointer slot is exercised in its own list context.
    for scene_index, (start, end) in enumerate(zip(source_roots, source_roots[1:] + (0x083D2F30,))):
        for actor in range((end - start) // 4):
            source = struct.unpack_from('<I', rom, start - BASE + actor * 4)[0]
            count, *rows = struct.unpack_from('<13i', rom, source - BASE)
            for scales in ((1.0, 1.0, 1.0), (-2.0, 3.0, 0.5), (0.0, -0.5, 4.0)):
                cpu.write(0x03000000, bytes(0x8000))
                cpu.write(ACTORS, bytes(16 * 0x300))
                put(0x03006D30, ACTORS)
                put(SCENE + 0xF8, scene_index)
                a = ACTORS + actor * 0x300
                for offset, value in ((0, 1), (4, 1), (8, 0), (0x1C0, 1), (0x1C4, 1), (0x1C8, 0)):
                    put(a + offset, value)
                for offset, value in zip((0x10, 0x58, 0xA0, 0x164, 0x17C, 0x194), (10.0, -20.0, 30.0, *scales)):
                    cpu.write(a + offset, struct.pack('<f', value))
                expected = bytearray(cpu.read(SCENE, 0x240))
                struct.pack_into('<ii', expected, 0, 240, 160)
                struct.pack_into('<12i', expected, 0xC0, *rows)
                struct.pack_into('<i', expected, 0x1D0, count)
                struct.pack_into('<i', expected, 0x1CC, actor)
                struct.pack_into('<f', expected, 0x98, float(rows[0]))
                for axis, offset in enumerate((10.0, -20.0, 30.0)):
                    struct.pack_into('<4f', expected, 0x60 + axis * 16,
                                     *(value * scales[axis] + offset for value in rows[axis*4:axis*4+4]))
                state['geometry'] = 0
                registers = cpu.call(0x08054014, timeout_us=0, instruction_limit=100000)
                saved(registers)
                assert state['geometry'] == 1
                assert cpu.read(SCENE, 0x240) == expected, (scene_index, actor, scales)
                geometry_cases += 1
    state['mode'] = 'setup'
    setup_cases = 0
    for row in range(16):
        for selector in range(16):
            cpu.write(0x03000000, bytes(0x8000))
            work = bytearray([0xA5]) * 0xD00
            work[0xC28], work[0xC5C] = row, selector
            frames = bytearray([0x5A]) * 8192
            cpu.write(0x030057E0, bytes(work))
            cpu.write(0x03002C30, bytes(frames))
            registers = cpu.call(0x0805330C, timeout_us=0, instruction_limit=3000)
            saved(registers)
            work[0xC10:0xC18] = rom[0x3D2A98+row*8:0x3D2AA0+row*8]
            frames[47*64+0x2A] = rom[0x3D2A88+selector]
            assert cpu.read(0x030057E0, 0xD00) == work
            assert cpu.read(0x03002C30, 8192) == frames
            setup_cases += 1
    for selector in range(16):
        cpu.write(0x030057E0 + 0xC5C, bytes([selector]))
        assert cpu.call(0x08048210, (0,), timeout_us=0, instruction_limit=1000)[0] == rom[0x3D2B26+selector]
    for scene_index in range(192):
        for flag in (0, 0x20):
            cpu.write(0x030057E0+0x7FE, bytes([scene_index]))
            cpu.write(0x030057E0+0xC5D, bytes([flag]))
            expected = 2 if rom[0x3D2B6B+scene_index] == 10 else (3 if flag else 1)
            assert cpu.call(0x08048960, (0,), timeout_us=0, instruction_limit=1000)[0] == expected
    callbacks = struct.unpack_from('<64I', rom, 0x3D5FF4)
    assert all(callbacks[:17]) and not any(callbacks[17:])
    for index, target in enumerate(callbacks[:17]):
        put(0x0300137C, index)
        state.update(callback=target & ~1, callback_calls=0)
        registers = cpu.call(0x0805716C, timeout_us=0, instruction_limit=1000)
        saved(registers)
        assert state['callback_calls'] == 1
    report = {'physical_commands': len(commands), 'program_cases': program_cases,
              'scalar_checks': scalar_checks, 'script_roots': len(roots),
              'distinct_roots': len(set(roots)), 'distinct_call_targets': len(targets),
              'geometry_cases': geometry_cases, 'source_pointer_slots': 48,
              'setup_row_cases': setup_cases, 'graphics_lookup_cases': 16,
              'map_selector_cases': 384, 'setup_callback_cases': 17,
              'program_helper_stubs': [hex(x) for x in sorted(PROGRAM_HELPERS)],
              'geometry_helper_stubs': [hex(x) for x in sorted(GEOMETRY_HELPERS)],
              'observed_helper_calls': {hex(k): v for k, v in sorted(helper_counts.items())},
              'scope': 'Single-command consumption/calls/payload checks and native geometry arithmetic; no complete scene flow or rendering.'}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps({k: v for k, v in report.items() if not k.endswith('stubs') and k != 'observed_helper_calls'}))


if __name__ == '__main__':
    main()
