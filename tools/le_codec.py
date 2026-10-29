"""Decode the game's custom Le graphics streams for offline research.

Derived from ROM routines 0x08000A0C and 0x08000B14. This bounded decoder
rejects malformed streams rather than reproducing the original unchecked memory
accesses. The sixth header byte is skipped by the original routines.
"""

import argparse
import hashlib
import json
from pathlib import Path
import sys

from common import find_rom
from analyze import offset as rom_offset


def decode(data, offset=0, max_output=1024 * 1024):
    if offset < 0 or offset + 6 > len(data):
        raise ValueError("Truncated Le header or invalid offset.")
    if data[offset:offset + 2] != b"Le":
        raise ValueError("Invalid Le signature.")
    size = int.from_bytes(data[offset + 2:offset + 5], "little")
    if size > max_output:
        raise ValueError(f"Le output size {size} exceeds limit {max_output}.")
    cursor = offset + 6
    output = bytearray()

    def take(count):
        nonlocal cursor
        if cursor + count > len(data):
            raise ValueError("Truncated Le command data.")
        result = data[cursor:cursor + count]
        cursor += count
        return result

    while len(output) < size:
        flags = take(1)[0]
        for _ in range(4):
            command = flags & 3
            flags >>= 2
            if command == 0:
                value = int.from_bytes(take(2), "little")
                distance, count = (value & 0xFFF) + 5, (value >> 12) + 3
            elif command == 1:
                value = take(1)[0]
                distance, count = (value & 3) + 1, (value >> 2) + 2
            else:
                count = 1 if command == 2 else 3
                distance = None
            if len(output) + count > size:
                raise ValueError("Le command overruns the declared output size.")
            if distance is None:
                output.extend(take(count))
            else:
                if distance > len(output):
                    raise ValueError("Le backreference precedes the output buffer.")
                for _ in range(count):
                    output.append(output[-distance])
            if len(output) == size:
                break
    return bytes(output), cursor - offset


def scan(data, max_output=128 * 1024):
    """Find decodable nonempty streams; validity alone does not prove usage."""
    results = []
    cursor = 0
    while True:
        start = data.find(b"Le", cursor)
        if start < 0:
            return results
        cursor = start + 2
        try:
            output, consumed = decode(data, start, max_output)
        except ValueError:
            continue
        if not output:
            continue
        results.append({"rom_offset": f"0x{start:06X}", "header_byte_5": data[start + 5], "compressed_bytes_consumed": consumed, "decoded_bytes": len(output), "decoded_sha256": hashlib.sha256(output).hexdigest()})


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", help="Supported cartridge dump; default: local baserom")
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--start", help="ROM offset or GBA address")
    mode.add_argument("--scan", action="store_true", help="Inventory candidate streams; code references need separate verification")
    parser.add_argument("--output", help="Write decoded binary data, or a JSON scan inventory, here")
    parser.add_argument("--max-output", type=lambda value: int(value, 0), default=1024 * 1024)
    args = parser.parse_args()
    try:
        data = find_rom(args.rom).read_bytes()
        if args.scan:
            candidates = scan(data, args.max_output)
            if args.output:
                destination = Path(args.output)
                destination.parent.mkdir(parents=True, exist_ok=True)
                destination.write_text(json.dumps(candidates, indent=2) + "\n", encoding="utf-8")
            print(json.dumps({"candidate_streams": len(candidates), "max_output_per_stream": args.max_output, "output": args.output, "note": "Decodable candidate streams; verify callers and boundaries before assigning asset roles."}, indent=2))
            return 0
        start = rom_offset(args.start, len(data))
        output, consumed = decode(data, start, args.max_output)
        if args.output:
            destination = Path(args.output)
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_bytes(output)
        print(json.dumps({"rom_offset": f"0x{start:06X}", "header_byte_5": data[start + 5], "compressed_bytes_consumed": consumed, "decoded_bytes": len(output), "output": args.output}, indent=2))
        return 0
    except (ValueError, OSError) as error:
        print(f"Le decode failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
