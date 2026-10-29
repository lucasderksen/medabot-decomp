"""Show an instruction-level diff for a tools/match.py result.

match.py reports only differing bytes. This aligns the reference and candidate
Thumb disassembly of each requested section, so register-allocation, ordering
and literal differences are visible at a glance:

    python tools/match.py spec.json --output-dir build/experiments/foo
    python tools/asm_diff.py spec.json --output-dir build/experiments/foo

Markers: `|` differs, `<` only in the reference, `>` only in the candidate,
`r` same instruction apart from registers. Branch targets are shown relative to
the section start so that a shifted function still aligns.
"""

import argparse
import difflib
import json
from pathlib import Path
import re
import sys

from common import ROOT, find_rom, rom_config

sys.path.insert(0, str(ROOT / "tools" / "python"))
BASE = int(rom_config()["rom_base"], 0)


def disassemble(data, address):
    import capstone
    engine = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
    engine.skipdata = True
    lines = []
    for instruction in engine.disasm(data, address):
        operands = instruction.op_str
        if instruction.mnemonic.startswith("b") and operands.startswith("#"):
            operands = f"+0x{int(operands[1:], 0) - address:X}"
        pool = re.fullmatch(r"(r\d+), \[pc(?:, #(0x[0-9a-f]+|\d+))?\]", operands)
        if instruction.mnemonic == "ldr" and pool:
            # Show the loaded value: pool offsets shift whenever the size changes.
            literal = ((instruction.address + 4) & ~3) + int(pool.group(2) or "0", 0) - address
            if 0 <= literal <= len(data) - 4:
                value = int.from_bytes(data[literal:literal + 4], "little")
                inside = address <= value < address + len(data)
                operands = f"{pool.group(1)}, =" + (f"+0x{value - address:X}" if inside else f"0x{value:08X}")
        lines.append((instruction.address - address, instruction.bytes.hex(), f"{instruction.mnemonic} {operands}".strip()))
    return lines


def registers_only(left, right):
    pattern = r"\b(r\d+|sb|sl|fp|ip|sp|lr|pc)\b"
    return left != right and re.sub(pattern, "R", left) == re.sub(pattern, "R", right)


def diff(expected, actual, address):
    reference, candidate = disassemble(expected, address), disassemble(actual, address)
    matcher = difflib.SequenceMatcher(a=[line[2] for line in reference], b=[line[2] for line in candidate], autojunk=False)
    rows = []
    for tag, a0, a1, b0, b1 in matcher.get_opcodes():
        for index in range(max(a1 - a0, b1 - b0)):
            left = reference[a0 + index] if a0 + index < a1 else None
            right = candidate[b0 + index] if b0 + index < b1 else None
            if tag == "equal":
                mark = " "  # same instruction; the encoding may differ only by a shifted pool offset
            elif left and right:
                mark = "r" if registers_only(left[2], right[2]) else "|"
            else:
                mark = "<" if left else ">"
            rows.append((mark, left, right))
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("spec", help="The JSON spec given to tools/match.py")
    parser.add_argument("--output-dir", default="build/experiments/match", help="The --output-dir given to tools/match.py")
    parser.add_argument("--all", action="store_true", help="Also print matching sections")
    parser.add_argument("--rom")
    args = parser.parse_args()
    reference = find_rom(args.rom).read_bytes()
    output = Path(args.output_dir)
    output = output if output.is_absolute() else ROOT / output
    results = json.loads((output / "results.json").read_text(encoding="utf-8"))
    for result in results:
        if result["matched"] and not args.all:
            continue
        start, end = int(result["start"], 0) if isinstance(result["start"], str) else result["start"], None
        end = int(result["end"], 0) if isinstance(result["end"], str) else result["end"]
        start &= 0xFFFFFF
        end &= 0xFFFFFF
        expected = reference[start:end]
        actual = (output / f"{result['name']}.bin").read_bytes()
        rows = diff(expected, actual, BASE + start)
        changed = sum(mark != " " for mark, _, _ in rows)
        print(f"== {result['name']} {BASE + start:08X}: {len(expected)} reference bytes, {len(actual)} candidate bytes, "
              f"{changed} differing instruction rows")
        for mark, left, right in rows:
            left_text = f"{left[0]:4X} {left[2]}" if left else ""
            right_text = f"{right[0]:4X} {right[2]}" if right else ""
            print(f"{left_text:<38} {mark} {right_text}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
