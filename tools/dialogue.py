"""Decode the native linear dialogue format used by 0803FD28.

08040038 consumes one glyph; 080402B4 consumes F9 plus a buffer selector;
080407A4/0804070C consume F7/FA plus a delay; 0803FEB8 consumes FB plus
three portrait fields. F8/FC/FD/FE occupy one byte. FF and its callback mode
are the terminal instruction (08040820/080408D0). Runtime wrapping and waits
can revisit an instruction; this is a storage decoder, not a playback model.
"""
from dataclasses import dataclass

GLYPH_COUNT = 135
OPERANDS = {0xF7: 1, 0xF8: 0, 0xF9: 1, 0xFA: 1, 0xFB: 3,
            0xFC: 0, 0xFD: 0, 0xFE: 0, 0xFF: 1}
NAMES = {0xF7: "delay_f7", 0xF8: "font_toggle", 0xF9: "insert",
         0xFA: "delay_fa", 0xFB: "portrait", 0xFC: "page",
         0xFD: "newline", 0xFE: "skip", 0xFF: "end"}


@dataclass(frozen=True)
class Instruction:
    offset: int
    opcode: int
    operands: bytes

    @property
    def kind(self):
        return NAMES.get(self.opcode, "glyph")

    @property
    def end(self):
        return self.offset + 1 + len(self.operands)

    def encode(self):
        return bytes([self.opcode]) + self.operands


def decode(data, start=0, end=None, *, max_bytes=65536):
    """Return a complete instruction tuple, failing on missing/partial FF.

    Bounds are explicit storage bounds. Values above the two known glyph
    banks' 134th index are held rather than guessed to be text. Each operand
    remains a byte even if it equals FF or another command opcode.
    """
    end = len(data) if end is None else end
    if not 0 <= start < end <= len(data) or not 0 < max_bytes <= 65536:
        raise ValueError("Invalid dialogue bounds or position limit")
    limit = min(end, start + max_bytes)
    position = start
    instructions = []
    while position < limit:
        opcode = data[position]
        count = OPERANDS.get(opcode, 0)
        if opcode not in OPERANDS and opcode >= GLYPH_COUNT:
            raise ValueError(f"Unknown glyph {opcode:02X} at {position:X}")
        if position + 1 + count > limit:
            raise ValueError(f"Truncated {NAMES.get(opcode, 'glyph')} at {position:X}")
        instruction = Instruction(position, opcode, bytes(data[position + 1:position + 1 + count]))
        instructions.append(instruction)
        position = instruction.end
        if opcode == 0xFF:
            return tuple(instructions)
    raise ValueError("No terminal dialogue instruction within bounds")
