"""Check unrooted banked-command storage and its internal pointer directory."""

import struct

from banked_scripts import decode
from common import find_rom


rom = find_rom().read_bytes()
start, end = 0x3D63DC, 0x3D67A9
commands = decode(rom, start, end)
boundaries = {command.offset for command in commands}
roots = struct.unpack_from('<160I', rom, 0x3D67AC)
switches = [command for command in commands if command.opcode == 0x2F]

assert len(commands) == 453
assert b''.join(command.encode() for command in commands) == rom[start:end]
assert len(set(roots)) == 160
assert all(root - 0x08000000 in boundaries for root in roots)
assert len(switches) == 1 and len(switches[0].operands) == 8
assert all(switches[0].offset + 1 + displacement in boundaries
           for displacement in switches[0].operands)
assert commands[-1].opcode == 0x06 and commands[-1].end == end
print('453 decoded commands, 160 root boundaries, and 8 switch targets verified; no runtime reader established')
