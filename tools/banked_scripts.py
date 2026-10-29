"""Bounded storage decoder for the native banked event commands.

Opcode names remain numeric where their full meaning is unknown. Operand counts
come from matched handlers 0804B73C..0804D83C. Commands 80 and 81 immediately
dispatch the following command; this decoder represents that chain linearly.
2F reads one of up to eight displacement bytes using a three-bit RAM selector.
Its stored table extent is inferred from its forward targets, then checked
against all command boundaries by the inventory generator.
"""
from dataclasses import dataclass


# Operands, excluding the following opcode fetched by commands 80/81.
OPERANDS = (
    0, 3, 3, 0, 1, 0, 0, 1, 1, 1, 1, 5, 5, 1, 0, 1,
    4, 1, 2, 2, 0, 0, 2, 3, 2, 2, 2, 0, 1, 0, 1, 5,
    5, 4, 2, 2, 2, 1, 2, 3, 1, 1, 1, 5, 1, 2, 3, 1,
    2, 1, 1, 3, 3, 1, 2, 2, 3, 3, 2, 2, 1, 1, 2, 2,
    1, 1, 0, 2, 1, 1, 0, 0, 1, 0, 2, 3, 3, 2, 3, 1,
    3, 2, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 2, 1, 1, 1,
    3, 0, 0, 3, 0, 0, 2, 2, 2, 2, 0, 1, 5, 2, 5, 2,
    0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 3, 0, 1, 1, 1,
    0, 8, 0, 2, 1, 0, 8, 0, 2,
)


@dataclass(frozen=True)
class Command:
    offset: int
    opcode: int
    operands: bytes

    @property
    def end(self):
        return self.offset + 1 + len(self.operands)

    def encode(self):
        return bytes([self.opcode]) + self.operands


def decode(data, start=0, end=None):
    """Decode one bounded storage span; this does not simulate control flow."""
    end = len(data) if end is None else end
    if not 0 <= start <= end <= len(data):
        raise ValueError("Invalid banked-command storage bounds")
    if end - start > 0x10000:
        raise ValueError("Storage exceeds the native 16-bit cursor window")
    commands = []
    while start < end:
        opcode = data[start]
        if opcode >= len(OPERANDS):
            raise ValueError(f"Undefined banked opcode {opcode:02X} at {start:X}")
        count = OPERANDS[opcode]
        if opcode == 0x2F:
            count = 8
            for i in range(8):
                if i >= count:
                    break
                if start + 1 + i >= end:
                    raise ValueError(f"Truncated dispatch table at {start:X}")
                value = data[start + 1 + i]
                if value > i:
                    count = min(count, value)
        if start + 1 + count > end:
            raise ValueError(f"Truncated banked opcode {opcode:02X} at {start:X}")
        command = Command(start, opcode, bytes(data[start + 1:start + 1 + count]))
        commands.append(command)
        start = command.end
    return commands


def script_address(offset, bank, position=0):
    """0804D83C arithmetic, including both native halfword narrowings."""
    return 0x08765EC0 + ((offset - 0x4000) & 0xFFFF) + (bank << 14) + (position & 0xFFFF)
