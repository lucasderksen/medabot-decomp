"""List the matched C functions whose code most resembles a NONMATCH function.

The game often repeats a routine with small changes (two scroll setups, two
battle-side renderers). A matched sibling's source is the best draft for an
unmatched function: sub_08064EB4 and sub_08020B4C both matched once their
siblings' source forms were copied. Instructions come from the ROM in the
tools/asm_diff.py form, with registers and immediates masked, and are compared
with difflib's sequence ratio.

    python tools/find_siblings.py                 # every NONMATCH function
    python tools/find_siblings.py sub_08045E6C --top 8
"""

import argparse
import difflib
import re
import sys

from asm_diff import BASE, disassemble
from common import find_rom, load_segments

REGISTER = re.compile(r"\b(?:r\d+|sb|sl|ip|fp|lr)\b")
NUMBER = re.compile(r"[+-]?0x[0-9A-Fa-f]+|#-?\d+")


def shape(rom, segment):
    """Instruction texts with registers and immediates masked."""
    rows = disassemble(rom[segment["start"]:segment["end"]], BASE + segment["start"])
    return [NUMBER.sub("N", REGISTER.sub("R", text)) for _, _, text in rows]


def c_functions(segments):
    for segment in segments:
        section = segment.get("input_section", "")
        if segment.get("kind") == "c" and section.startswith(".text."):
            yield section[len(".text."):], segment


def siblings(target, pool, top):
    """Best (ratio, name, segment) matches for one instruction shape."""
    scored = []
    for name, segment, sequence in pool:
        if not 0.6 < len(sequence) / max(len(target), 1) < 1.6:
            continue
        matcher = difflib.SequenceMatcher(None, target, sequence, autojunk=False)
        if matcher.real_quick_ratio() < 0.4 or matcher.quick_ratio() < 0.4:
            continue
        scored.append((matcher.ratio(), name, segment))
    scored.sort(key=lambda item: -item[0])
    return scored[:top]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("names", nargs="*", help="NONMATCH functions (default: all)")
    parser.add_argument("--top", type=int, default=3)
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    functions = list(c_functions(load_segments()))
    targets = [(name, segment) for name, segment in functions
               if (name in args.names if args.names else segment.get("nonmatching"))]
    pool = [(name, segment, shape(rom, segment)) for name, segment in functions if not segment.get("nonmatching")]
    for name, segment in targets:
        target = shape(rom, segment)
        print(f"== {name} ({len(target)} instructions)")
        for ratio, sibling, other in siblings(target, pool, args.top):
            print(f"  {ratio:.2f}  {sibling}  {other.get('source')}  [{' '.join(other.get('cflags', []))}]")
    return 0


if __name__ == "__main__":
    sys.exit(main())
