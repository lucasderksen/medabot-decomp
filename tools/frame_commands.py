"""Bounded model of 08040B90/08040BD8 frame commands, not the scene VM.

Offsets and delays are bytes. Controls do not all read three bytes even
though sequential advancement is three; a terminal FE needs only two.
"""

from dataclasses import dataclass


def _read(data, offset, size):
    if offset < 0 or offset + size > len(data):
        raise ValueError(f"Frame command read outside stream at {offset:#x}")
    return data[offset:offset + size]


def preview(data):
    """Initializer skips controls by three, without executing their branches."""
    offset, seen = 0, set()
    while offset not in seen:
        seen.add(offset)
        opcode = _read(data, offset, 1)[0]
        if opcode <= 0xFA:
            command = _read(data, offset, 3)
            return command[1] * 256 + command[2]
        offset = (offset + 3) & 255
    raise ValueError("Initializer never reaches an ordinary frame command")


def analyze(data):
    """Check reachable byte reads and reject a control cycle that cannot yield."""
    if not 0 < len(data) <= 256:
        raise ValueError("This inventory checker limits spans to 1..256 bytes")
    first_frame = preview(data)
    nodes, order, offset = {}, [], 0
    while offset not in nodes:
        opcode = _read(data, offset, 1)[0]
        size = 3 if opcode <= 0xFA else (2 if opcode in (0xFB, 0xFD, 0xFE) else 1)
        command = _read(data, offset, size)
        target = None if opcode == 0xFF else (
            (command[1] * 3) & 255 if opcode == 0xFE else (offset + 3) & 255)
        node = {"offset": offset, "opcode": opcode, "read_bytes": size,
                "next": target, "yields": opcode == 0xFB or 0 < opcode <= 0xFA}
        nodes[offset] = node
        order.append(offset)
        if target is None:
            break
        offset = target
    else:
        cycle = order[order.index(offset):]
        if not any(nodes[position]["yields"] for position in cycle):
            raise ValueError("Frame-command cycle cannot return from a tick")
    return {"first_frame": first_frame, "nodes": list(nodes.values())}


@dataclass
class State:
    delay: int = 0
    offset: int = 0
    stopped: int = 0
    frame: int = 0


def initialize(data):
    return State(frame=preview(data))


def tick(data, state, flags_zero, instruction_limit=256):
    """Advance one call; return record-zero flags and requested sound IDs.

    Sound dispatch is recorded, not executed. Device/audio behavior is outside
    this model. Call analyze first for a static span/control-flow check.
    """
    sounds = []
    if state.stopped == 255:
        return flags_zero, sounds
    for _ in range(instruction_limit):
        if state.delay:
            state.delay = (state.delay - 1) & 255
            return flags_zero, sounds
        opcode = _read(data, state.offset, 1)[0]
        if opcode <= 0xFA:
            command = _read(data, state.offset, 3)
            state.delay = opcode
            state.frame = command[1] * 256 + command[2]
        elif opcode == 0xFB:
            flags_zero &= 0xBFFF
            state.delay = _read(data, state.offset + 1, 1)[0]
            state.offset = (state.offset + 3) & 255
            return flags_zero, sounds
        elif opcode == 0xFC:
            flags_zero |= 0x4000
        elif opcode == 0xFD:
            sounds.append(_read(data, state.offset + 1, 1)[0])
        elif opcode == 0xFE:
            state.offset = (_read(data, state.offset + 1, 1)[0] * 3) & 255
            continue
        else:
            state.stopped = 255
            return flags_zero, sounds
        state.offset = (state.offset + 3) & 255
    raise ValueError("Frame-command tick exceeds its instruction bound")
