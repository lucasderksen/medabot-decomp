"""Check map metadata consumers against original Thumb, without device emulation.

Cell and exit queries execute without stubs. Tile-animation DMA requests are
recorded in ordinary mapped MMIO memory, not performed. Selector routines execute
against actual ROM tables and controlled RAM. Includes map 81's scan into map 82
and tile-sequence indices 128/255 that read adjacent native storage.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, unicorn

BASE = 0x08000000
WORK = 0x030057E0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=Path("build/analysis/map-metadata-cpu.json"))
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    cpu = RoutineCpu(rom)
    cpu.engine.mem_map(0x04000000, 0x1000)
    pointers = {name: struct.unpack_from("<" + str(count) + "I", rom, address)
                for name, count, address in (("animation", 256, 0x409480), ("cells", 192, 0x40F880),
                    ("exits", 192, 0x412E60), ("selectors", 192, 0x413160), ("indirect", 16, 0x413EE0))}
    state = {"map": -1, "dma": [], "map81_cross_reads": 0}

    def dma(engine, access, address, size, value, user_data):
        if address == 0x040000DC and size == 4:
            source, destination = struct.unpack("<II", cpu.read(0x040000D4, 8))
            state["dma"].append((source, destination, value))

    def cross_read(engine, access, address, size, value, user_data):
        if state["map"] == 81:
            state["map81_cross_reads"] += 1

    cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, dma, begin=0x040000D4, end=0x040000DF)
    marker = BASE + 0x409880 + 82 * 128 + 2
    cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ, cross_read, begin=marker, end=marker)

    def prepare(map_index):
        cpu.write(WORK, bytes(0xCC0))
        cpu.write(WORK + 0x7FE, bytes([map_index]))
        state.update(map=map_index, dma=[])

    cells = exits = animations = selectors = 0
    for map_index in range(192):
        start = pointers["cells"][map_index] - BASE
        records = []
        while rom[start + 2]:
            records.append(tuple(rom[start:start + 4]))
            start += 4
        targets = {(record[0], record[1]) for record in records} | {(254, 254)}
        for x, y in targets:
            for direction in range(4):
                prepare(map_index)
                px = x + (1 if direction == 2 else -1 if direction == 3 else 0)
                py = y + (1 if direction == 0 else -1 if direction == 1 else 0)
                invalid = not (0 <= px < 256 and 0 <= py < 256)
                cpu.write(WORK + 0x800, struct.pack("<HH", 512, 512))
                cpu.write(WORK + 0xC56, bytes([px & 255, py & 255]))
                # Both source views alias object 47 byte 20 at this address.
                cpu.write(0x03003810, bytes([direction]))
                expected = -1
                if not invalid:
                    for rx, ry, flags, value in records:
                        if rx == x and ry == y:
                            expected = value
                            if value and not (flags & (2, 1, 8, 4)[direction]):
                                expected = -1
                            if expected != -1:
                                break
                result = cpu.call(0x08052624, instruction_limit=100000, timeout_us=0)[0]
                if result != (expected & 0xFFFFFFFF):
                    raise ValueError(f"Cell query differs: map {map_index}, cell {x},{y}, direction {direction}")
                cells += 1

        start = pointers["exits"][map_index] - BASE
        records = []
        while rom[start] != 255:
            records.append(tuple(rom[start:start + 8])); start += 8
        for x, y in {(r[0], r[1]) for r in records} | {(254, 254)}:
            prepare(map_index)
            cpu.write(0x03006D3B, b"\xA5")
            matches = [r for r in records if r[0] == x and r[1] == y]
            expected = matches[-1][3] >> 4 if matches else 0xA5
            result = cpu.call(0x08052C68, (x, y), instruction_limit=100000, timeout_us=0)[0]
            if result != bool(matches) or cpu.read(0x03006D3B, 1) != bytes([expected]):
                raise ValueError(f"Exit query differs: map {map_index}, cell {x},{y}")
            exits += 1

        source = pointers["animation"][map_index] - BASE
        units, frames, total = rom[source:source + 3]
        length = rom[source + 3:source + 131].index(255)
        for index in sorted({0, max(0, length - 1), length, 127, 128, 255}):
            for enabled, timer in ((0, 0), (1, 0), (1, 1)):
                prepare(map_index)
                cpu.write(0x030057DC, struct.pack("<I", 0x02010000))
                cpu.write(WORK + 0xC34, bytes([enabled, index, timer]))
                expected_index, expected_timer, requests = index, timer, []
                if enabled and total:
                    if timer:
                        expected_timer -= 1
                    else:
                        if rom[source + 3 + expected_index] == 255:
                            expected_index = 0
                        frame = rom[source + 3 + expected_index]
                        requests = [(0x02010000 + frame * units * 32, 0x06009020, 0x80000000 | units * 16)]
                        expected_index = (expected_index + 1) & 255
                        expected_timer = 2
                cpu.call(0x08048174, instruction_limit=100000, timeout_us=0)
                if (cpu.read(WORK + 0xC35, 2) != bytes([expected_index, expected_timer])
                        or state["dma"] != requests):
                    raise ValueError(f"Tile animation differs: map {map_index}, index {index}, timer {timer}")
                animations += 1

    def translated(value, choices):
        if value == 0:
            value = rom[0x3D2B26]
        elif 0xD0 <= value <= 0xDF:
            slot = value - 0xD0
            value = rom[pointers["indirect"][slot] - BASE + choices[slot]]
        if value != 255 and value > 0xBF:
            value = (value - 0xC0) * 2 + 53
        return value

    for choice in (0, 12, 13, 255):
        choices = [choice] * 16
        for slot in range(16):
            prepare(0)
            cpu.write(WORK + 0xC38, bytes(choices))
            cpu.write(0x03006D3E, b"\x0D")
            expected = translated(0xD0 + slot, choices)
            result = cpu.call(0x08048210, (0xD0 + slot,), instruction_limit=100000, timeout_us=0)[0]
            if result != expected:
                raise ValueError(f"Indirect selector differs: slot {slot}, choice {choice}")
            selectors += 1
        for map_index in range(192):
            for position in range(14):
                prepare(map_index)
                cpu.write(WORK + 0xC38, bytes(choices))
                cpu.write(0x03006D3E, b"\x0D")
                value = rom[pointers["selectors"][map_index] - BASE + position]
                expected = translated(value, choices)
                result = cpu.call(0x08048684, (position,), instruction_limit=100000, timeout_us=0)[0]
                if result != expected:
                    raise ValueError(f"Map selector differs: map {map_index}, position {position}")
                selectors += 1
    if not state["map81_cross_reads"]:
        raise ValueError("Map 81 cross-boundary marker read was not exercised")
    report = {"rom_sha256": hashlib.sha256(rom).hexdigest(), "cell_queries": cells,
              "exit_queries": exits, "tile_animation_cases": animations, "selector_cases": selectors,
              "map81_cross_marker_reads": state["map81_cross_reads"], "scope": __doc__}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"Native checks pass: {cells} cell queries, {exits} exits, {animations} tile-animation cases, "
          f"{selectors} selectors; map 81's adjacent marker read preserved.")


if __name__ == "__main__":
    main()
