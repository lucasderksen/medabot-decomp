"""Check equipment animation frame selection and tile copies against the ROM."""
import json
import struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn

rom = find_rom().read_bytes()
cpu = RoutineCpu(rom)
copies = []

def hook(machine, address, size, user):
    if address != 0x0807CCC4:
        return
    source, destination, control = (machine.reg_read(reg) for reg in
        (arm_const.UC_ARM_REG_R0, arm_const.UC_ARM_REG_R1, arm_const.UC_ARM_REG_R2))
    assert control & 0x04000000 and not control & 0x01000000
    size = (control & 0x1FFFFF) * 4
    copies.append((source, destination, control))
    machine.mem_write(destination, bytes(machine.mem_read(source, size)))
    machine.reg_write(arm_const.UC_ARM_REG_PC, machine.reg_read(arm_const.UC_ARM_REG_LR))

cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
tiles = bytes((i * 37 + (i >> 8)) & 255 for i in range(0x9000))
cpu.write(0x02027000, tiles)
cases = 0
restarts = 0
for animation in range(11):
    width = rom[0x3C4238 + animation]
    sequence = rom[0x3C4243 + animation * 128:0x3C4243 + (animation + 1) * 128]
    for phase in range(128):
        for counter in (0, 1, 2, 254, 255):
            work = bytearray([0xA5] * 0x90)
            work[0x7C:0x80] = bytes([phase, counter, 0xAB, 0xCD])
            cpu.write(0x03001800, bytes(work))
            expected_tiles = bytearray([0xA5] * (16 * 32 + 8))
            cpu.write(0x0600801C, bytes(expected_tiles))
            work[0x7D] = (counter + 1) & 255
            expected_copies = []
            if work[0x7D] > 2:
                work[0x7D] = 0
                work[0x7C] = (phase + 1) & 127
                frame = sequence[work[0x7C]]
                if frame == 255:
                    work[0x7C] = 0
                    frame = sequence[0]
                    restarts += 1
                work[0x7E:0x80] = bytes([width, frame])
                source = width * frame * 32
                expected_tiles[4:4 + width * 32] = tiles[source:source + width * 32]
                expected_copies = [(0x02027000 + source, 0x06008020, 0x04000000 | width * 8)]
            copies.clear()
            result = cpu.call(0x08043FEC, (animation,))
            assert copies == expected_copies, (animation, phase, counter)
            assert cpu.read(0x03001800, len(work)) == work
            assert cpu.read(0x0600801C, len(expected_tiles)) == expected_tiles
            assert result[4:12] == tuple(0xAB000000 | i for i in range(4, 12))
            assert cpu.engine.reg_read(arm_const.UC_ARM_REG_SP) == 0x03007F00
            cases += 1
report = dict(cases=cases, restart_cases=restarts,
              host_models=['0807CCC4 CpuSet word copy'],
              scope='All 11 animations x 128 stored positions x 5 counter values; native frame selection and copy helper; guarded tile/work RAM and preserved registers checked. BIOS transfer modeled, not hardware timing.')
Path('build/more/equipment_animation_cpu.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps(report))
