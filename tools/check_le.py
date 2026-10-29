"""Optional CPU comparison of Le stream candidates against the host decoder.

This validates bytes and return values using ordinary mapped memory. It does not
simulate GBA devices or establish that a candidate stream is used by the game.
"""

import argparse
import hashlib
import json
from pathlib import Path
import sys

from common import find_rom
from cpu import RoutineCpu
from le_codec import decode, scan


def check_stream(cpu, rom, item, max_output):
    start = int(item["rom_offset"], 0)
    expected, consumed = decode(rom, start, max_output)
    if hashlib.sha256(expected).hexdigest() != item["decoded_sha256"]:
        raise ValueError(f"Stale decoded hash at ROM +0x{start:06X}")
    if consumed != item["compressed_bytes_consumed"]:
        raise ValueError(f"Stale consumed length at ROM +0x{start:06X}")
    preserved = tuple(0xAB000000 | register for register in range(4, 12))
    for destination in (0x02010000, 0x06001001):
        cpu.write(destination - 1, b"\xA5" * (len(expected) + 2))
        registers = cpu.call(0x080009BC, (0x08000000 + start, destination))
        if registers[0] != len(expected):
            raise ValueError(f"Returned length mismatch at ROM +0x{start:06X}")
        if cpu.read(destination, len(expected)) != expected:
            raise ValueError(f"Output mismatch at ROM +0x{start:06X}, destination 0x{destination:08X}")
        if cpu.read(destination - 1, 1) != b"\xA5" or cpu.read(destination + len(expected), 1) != b"\xA5":
            raise ValueError(f"Neighbor byte changed at ROM +0x{start:06X}")
        if registers[4:12] != preserved:
            raise ValueError(f"Callee-saved register changed at ROM +0x{start:06X}")
    return {"rom_offset": f"0x{start:06X}", "byte_path": True, "odd_halfword_path": True}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", help="Matching local dump or rebuilt cartridge")
    parser.add_argument("--inventory", help="Use a previously generated le_codec.py JSON inventory")
    parser.add_argument("--max-output", type=lambda value: int(value, 0), default=128 * 1024)
    parser.add_argument("--limit", type=int, help="Check only the first N candidates")
    parser.add_argument("--output", default="build/analysis/le-inventory-cpu-results.json")
    args = parser.parse_args()
    try:
        if args.max_output <= 0 or (args.limit is not None and args.limit <= 0):
            raise ValueError("Output limit and candidate limit must be positive")
        rom = find_rom(args.rom).read_bytes()
        inventory = json.loads(Path(args.inventory).read_text(encoding="utf-8")) if args.inventory else scan(rom, args.max_output)
        if args.limit is not None:
            inventory = inventory[:args.limit]
        if not inventory:
            raise ValueError("No candidate streams to check")
        cpu = RoutineCpu(rom)
        results = []
        for index, item in enumerate(inventory, 1):
            results.append(check_stream(cpu, rom, item, args.max_output))
            if index % 100 == 0:
                print(f"{index}/{len(inventory)} candidate streams agree in both CPU paths.", flush=True)
        report = {
            "rom_sha256": hashlib.sha256(rom).hexdigest(),
            "candidate_count": len(results), "results": results,
            "note": "Isolated CPU check; candidate validity does not prove game usage or asset roles.",
        }
        destination = Path(args.output)
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        print(f"MATCH: all {len(results)} candidate streams, both CPU paths, return sizes, registers, and neighboring bytes.")
        return 0
    except (ImportError, OSError, ValueError, KeyError) as error:
        print(f"Le CPU check failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())

