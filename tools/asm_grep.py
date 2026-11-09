"""Find an instruction pattern in the already-matching C functions.

When a NONMATCH function needs an instruction shape that C does not seem to
produce, some matched function usually produces it already; its source then
shows the idiom. Instructions are disassembled from the ROM in the
tools/asm_diff.py form (`ldr r3, =0x0000FFFF`, `adds r1, r3, #0`), one per line,
and PATTERN is a Python regular expression searched over each function's
listing (multiline mode, so `\\n` separates consecutive instructions and
backreferences tie registers together):

    python tools/asm_grep.py 'ldr (r\\d), =0x0000FFFF\\nadds (r\\d), \\1, #0\\nands'
    python tools/asm_grep.py 'bl .*\\nldr (r\\d), =(0x06\\w+)\\n(?:.*\\n){0,8}?ldr r\\d, =\\2' --flags=-fprologue-bugfix

Prints each hit as function, source file, compiler flags and the matched
instructions with offsets. Only matching C segments are searched, so every hit
comes with C that produces it.
"""

import argparse
import re
import sys

from asm_diff import BASE, disassemble
from common import find_rom, load_segments


def matched_functions(segments):
    for segment in segments:
        section = segment.get("input_section", "")
        if (segment.get("kind") == "c" and section.startswith(".text.") and not segment.get("nonmatching")
                and segment.get("compiler", "agbcc") == "agbcc"):
            yield section[len(".text."):], segment


def search(pattern, rom, segments, flags=None):
    """Yield (name, segment, [(offset, text)]) for each function whose listing matches."""
    expression = re.compile(pattern, re.M)
    for name, segment in matched_functions(segments):
        if flags is not None and " ".join(segment.get("cflags", [])) != flags:
            continue
        start, end = segment["start"], segment["end"]
        rows = disassemble(rom[start:end], BASE + start)
        text, offsets = "", []
        for offset, _, instruction in rows:
            offsets.append((len(text), offset, instruction))
            text += instruction + "\n"
        for match in expression.finditer(text):
            hit = [(offset, instruction) for position, offset, instruction in offsets
                   if match.start() <= position < max(match.end(), match.start() + 1)]
            yield name, segment, hit


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("pattern", help="Regular expression over newline-separated instructions")
    parser.add_argument("--flags", help="Only functions compiled with exactly these cflags (space-separated)")
    parser.add_argument("--limit", type=int, default=20, help="Stop after this many hits (0: no limit)")
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    count = 0
    for name, segment, hit in search(args.pattern, rom, load_segments(), args.flags):
        count += 1
        print(f"== {name}  {segment.get('source')}  [{' '.join(segment.get('cflags', []))}]")
        for offset, instruction in hit:
            print(f"  {offset:4X} {instruction}")
        if args.limit and count >= args.limit:
            break
    print(f"{count} hit(s)", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
