"""Bounded decoder for the native signed-word scene programs at 083D2FB0.

Lengths follow 0805424C. Decoding stored commands is distinct from executing
them: IDLE/TICK/END and RETURN do not simply advance by their stored width.
"""
from dataclasses import dataclass
import struct

WORD_COUNTS = {
    0: 1, 1: 5, 2: 1, 3: 6, 4: 1, 5: 2, 6: 4, 7: 4, 8: 4,
    9: 3, 10: 3, 11: 4, 12: 4, 13: 3, 14: 3, 15: 3,
    16: 18, 17: 18, 18: 18, 19: 7, 20: 7, 21: 9, 22: 9,
    23: 7, 24: 7, 25: 7, 26: 7, 27: 6, 28: 6, 29: 4, 30: 6,
    31: 5, 32: 5, 33: 5, 34: 3, 35: 1, 36: 5, 37: 1,
    128: 4, 129: 4, 130: 11, 131: 11, 132: 1, 133: 5,
    134: 8, 135: 8, 136: 2, 137: 4, 138: 7, 139: 1,
}


@dataclass(frozen=True)
class Command:
    offset: int
    words: tuple

    @property
    def opcode(self):
        return self.words[0]

    @property
    def end(self):
        return self.offset + len(self.words) * 4

    @property
    def target(self):
        if self.opcode == 34:
            return self.words[2]
        if self.opcode == 36:
            return self.words[4]
        return None


def command_at(data, offset, end=None):
    end = len(data) if end is None else end
    if not 0 <= offset < end <= len(data) or offset % 4 or end - offset < 4:
        raise ValueError('Invalid wordcode bounds or alignment')
    opcode = struct.unpack_from('<i', data, offset)[0]
    if opcode not in WORD_COUNTS:
        raise ValueError(f'Unknown scene opcode {opcode:X} at {offset:X}')
    count = WORD_COUNTS[opcode]
    if opcode == 36:
        if end - offset < count * 4:
            raise ValueError('Truncated scheduled-call command')
        mode = struct.unpack_from('<i', data, offset + 8)[0]
        if mode & 0xFF00 == 0x100:
            count += 2
    if count * 4 > end - offset:
        raise ValueError('Truncated scene command')
    return Command(offset, struct.unpack_from('<'+str(count)+'i', data, offset))


def decode_bank(data, start, end):
    commands = []
    offset = start
    while offset < end:
        command = command_at(data, offset, end)
        commands.append(command)
        offset = command.end
    if not commands or offset != end:
        raise ValueError('Empty or incomplete scene bank')
    return commands


def validate_roots(commands, roots, base=0x08000000):
    boundaries = {command.offset + base for command in commands}
    targets = {command.target for command in commands if command.target is not None}
    if not set(roots).issubset(boundaries) or not targets.issubset(boundaries):
        raise ValueError('Scene root or call target is outside command boundaries')
    return targets
