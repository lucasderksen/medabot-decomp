"""Run every stored action/map callback slot through its original dispatcher.

Selected callbacks are intercepted and 0803EED8 returns zero to enter the map
phase dispatcher. Rendering mode stays zero, so neither map dispatcher runs
its alternate object-buffer DMA/fill path.
"""
import argparse
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

# Native entry, table address, physical pointer count, clears transfer[B5].
TABLES = [
    (0x08010264, 0x83ACE24, 144, False),
    (0x08012970, 0x83AD080, 192, False),
    (0x0801C4FC, 0x83AD5CC, 48, True),
    (0x0801D2F0, 0x83AD68C, 9, True),
    (0x0801D380, 0x83AD6B0, 8, True),
    (0x0801D40C, 0x83AD6D0, 8, True),
    (0x0801D580, 0x83AD6F0, 16, True),
    (0x0801DE1C, 0x83AD730, 8, True),
    (0x0801DEE4, 0x83AD750, 16, True),
    (0x0801E2D8, 0x83AD790, 80, True),
    (0x0801F484, 0x83AD8D0, 17, True),
    (0x0801FA40, 0x83AD914, 16, True),
    (0x0801FDEC, 0x83AD954, 16, True),
    (0x08020050, 0x83AD994, 25, True),
    (0x0802057C, 0x83AD9F8, 8, True),
    (0x080207A4, 0x83ADA18, 8, True),
    (0x0802081C, 0x83ADA38, 8, True),
    (0x080208C0, 0x83ADA58, 25, True),
    (0x080209B0, 0x83ADABC, 8, True),
    (0x08020A68, 0x83ADADC, 25, True),
    (0x08020CFC, 0x83ADB40, 43, True),
    (0x080218BC, 0x83ADBEC, 32, True),
    (0x08021E04, 0x83ADC6C, 16, True),
    (0x08022154, 0x83ADCAC, 16, True),
    (0x080223BC, 0x83ADCEC, 16, True),
    (0x080227D8, 0x83ADD2C, 24, True),
    (0x08022CA8, 0x83ADD8C, 24, True),
    (0x08022FF0, 0x83ADDEC, 21, True),
    (0x0802342C, 0x83ADE40, 24, True),
    (0x08023730, 0x83ADEA0, 24, True),
    (0x08023AC8, 0x83ADF00, 24, True),
    (0x08023C90, 0x83ADF60, 32, True),
    (0x08024090, 0x83ADFE0, 32, True),
    (0x08024998, 0x83AE064, 24, True),
    (0x08024E04, 0x83AE0C4, 24, True),
    (0x0802518C, 0x83AE124, 24, True),
    (0x080257C0, 0x83AE184, 24, True),
    (0x08025AF8, 0x83AE1E4, 32, True),
    (0x08025F2C, 0x83AE264, 7, True),
    (0x08025FA0, 0x83AE280, 6, True),
    (0x08026108, 0x83AE298, 21, True),
    (0x0802645C, 0x83AE2EC, 21, True),
    (0x08026884, 0x83AE340, 32, True),
    (0x08026CF4, 0x83AE3C0, 48, True),
    (0x08026ED0, 0x83AE480, 32, True),
    (0x08026FD0, 0x83AE500, 32, True),
    (0x0802793C, 0x83AE580, 16, True),
    (0x08027F5C, 0x83AE5C0, 16, True),
    (0x08028248, 0x83AE600, 16, True),
    (0x08028404, 0x83AE640, 16, True),
    (0x08028C40, 0x83AE680, 16, True),
    (0x080294B4, 0x83AE6C0, 16, True),
    (0x08029840, 0x83AE700, 16, True),
    (0x08029E0C, 0x83AE740, 16, True),
    (0x0802A0E8, 0x83AE780, 16, True),
    (0x0802A6AC, 0x83AE7C0, 16, True),
    (0x0802AAD0, 0x83AE800, 16, True),
    (0x0802ACCC, 0x83AE840, 16, True),
    (0x0802B000, 0x83AE880, 20, True),
    (0x0802B7E8, 0x83AE8D0, 16, True),
    (0x0802BD6C, 0x83AE910, 16, True),
    (0x0802C2AC, 0x83AE954, 16, True),
    (0x0802C644, 0x83AE994, 16, True),
    (0x0802CBE8, 0x83AE9D4, 23, True),
    (0x0802D688, 0x83AEA30, 22, True),
    (0x0802DCB4, 0x83AEA88, 32, True),
    (0x0802E424, 0x83AEB1C, 27, True),
    (0x0802EBC0, 0x83AEB88, 15, True),
    (0x0802F030, 0x83AEBC4, 16, True),
    (0x0802F628, 0x83AEC04, 21, True),
    (0x0802F990, 0x83AEC58, 16, True),
    (0x0802FE50, 0x83AEC98, 16, True),
]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=Path('build/analysis/state0-callback-data-cpu.json'))
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    cpu = RoutineCpu(rom)
    state = {'target': None, 'calls': 0, 'gate_calls': 0}

    def hook(machine, address, size, user_data):
        if address == state['target']:
            state['calls'] += 1
        elif address == 0x0803EED8:
            state['gate_calls'] += 1
            machine.reg_write(arm_const.UC_ARM_REG_R0, 0)
        else:
            return
        machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
    cases = slots = 0
    for entry, root, count, clears in TABLES:
        for index in range(count):
            target = struct.unpack_from('<I', rom, root - 0x08000000 + index * 4)[0]
            assert target & 1 and target != (entry | 1)
            for marker in (0, 0x79, 0xFF):
                cpu.write(0x03000000, bytes(0x8000))
                work = bytearray([0xA5]) * 0x1B1
                work[0xAA] = index & 0xFF
                work[0xB5] = marker
                cpu.write(0x03001800, bytes(work))
                cpu.write(0x0300137C, struct.pack('<I', index))
                state.update(target=target & ~1, calls=0, gate_calls=0)
                registers = cpu.call(entry, timeout_us=0, instruction_limit=1000)
                assert state['calls'] == 1, (hex(entry), index, marker, state)
                assert state['gate_calls'] == int(entry == 0x08012970)
                if clears:
                    work[0xB5] = 0
                assert cpu.read(0x03001800, len(work)) == work, (hex(entry), index, marker)
                assert registers[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
                assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
                cases += 1
            slots += 1
    report = {'tables': len(TABLES), 'slots': slots, 'dispatch_cases': cases,
              'action_tables': sum(int(t[3]) for t in TABLES),
              'hooks': ['selected callback body', '0803EED8: return zero'],
              'scope': 'Original dispatcher selection, B5 clearing and preserved registers/stack; no callback-body or rendering execution.'}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()

