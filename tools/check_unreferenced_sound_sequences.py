"""Check the decoded boundaries and loop targets of two unrooted streams."""

import struct

from common import find_rom


rom = find_rom().read_bytes()
controls = {0xE3: 1, 0xFA: 1, 0xFB: 4, 0xFE: 1, 0xF4: 4}
cases = ((0xB40CF, 0xB41AC, 0xB40CF, 108),
         (0xB8B55, 0xB8BD0, 0xB8B71, 60))
for start, end, target, count in cases:
    for entry_mode in (0, 2):
        pc, mode, boundaries = start, entry_mode, set()
        while pc < end:
            boundaries.add(pc)
            op = rom[pc]
            if op in controls:
                length = controls[op]
            elif op == 0x80:
                length = 1
            elif op & 0xF0 == 0xD0:
                length = 0
            else:
                assert op < 0x80 and mode in (0, 2)
                length = 1
            assert pc + 1 + length <= end
            if op == 0xFE:
                mode = rom[pc + 1]
            if op == 0xF4:
                assert pc + 5 == end
                assert struct.unpack_from('<I', rom, pc + 1)[0] == 0x08000000 + target
            pc += 1 + length
        assert pc == end and target in boundaries and len(boundaries) == count

print('Four assumed-mode decodes verify 344 bytes and both internal jump targets')
