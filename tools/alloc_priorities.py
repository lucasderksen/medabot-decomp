"""Show global-allocation priorities for the last compiled draft of a function.

agbcc's global.c allocates pseudos in order of
    floor_log2(refs) * refs / live_length
(refs weighted by loop depth, live length from flow before combine), and a
`do { } while (0)` around a use counts as one more loop level. When a
near-miss differs only in which pseudo got which register, this table shows
the order the compiler used, so the needed change in refs or live length can
be computed instead of guessed (sub_08052784: the counters needed to outrank
the strength-reduced givs).

    python tools/try_draft.py sub_08052784 src/non_matching/sub_08052784.c
    python tools/alloc_priorities.py sub_08052784 --min-live 30

Each row: pseudo, refs, live length, priority and the hard register it got
(MEM when spilled). Pass --pseudo N to print the RTL insns that set or use N.
"""

import argparse
import math
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

from common import ROOT
from compiler_agbcc import BINARY

REGISTER_NAMES = {str(i): f"r{i}" for i in range(8)}
REGISTER_NAMES.update({"8": "r8", "9": "sb", "10": "sl", "11": "fp", "12": "ip"})


def priorities(greg_text):
    dispositions = greg_text[greg_text.index(";; Register dispositions"):]
    assigned = dict(re.findall(r"(\d+) in (\d+)", dispositions))
    rows = []
    for regno, refs, live in re.findall(r"Register (\d+), refs = (\d+), live_length = (\d+)", greg_text):
        refs, live = int(refs), int(live)
        priority = (int(math.log2(refs)) if refs > 0 else 0) * refs / live if live else 0.0
        hard = assigned.get(regno)
        rows.append((priority, int(regno), refs, live, REGISTER_NAMES.get(hard, f"hr{hard}") if hard else "MEM"))
    return sorted(rows, reverse=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("name")
    parser.add_argument("--cflags", default=None, help="Compiler flags (default: the spec's, from tools/try_draft.py)")
    parser.add_argument("--min-live", type=int, default=0, help="Only pseudos living at least this many insns")
    parser.add_argument("--pseudo", type=int, help="Also print the insns that mention this pseudo")
    args = parser.parse_args()
    directory = ROOT / "build" / "m2c" / args.name
    source = directory / "match" / "candidate.i"
    if not source.exists():
        raise SystemExit(f"{source} is missing; run tools/try_draft.py {args.name} <file> first.")
    if args.cflags is None:
        import json
        spec = json.loads((directory / "spec.json").read_text(encoding="utf-8"))
        cflags = [flag for flag in spec["cflags"] if flag != "-w"]
    else:
        cflags = args.cflags.split()
    with tempfile.TemporaryDirectory() as scratch:
        copy = Path(scratch) / "c.i"
        shutil.copy(source, copy)
        subprocess.run([str(BINARY), "-O2", "-mthumb-interwork", "-ffunction-sections", "-w", *cflags,
                        "-dg", str(copy), "-o", str(Path(scratch) / "c.s")], check=True, cwd=scratch)
        greg = (Path(scratch) / "c.i.greg").read_text(encoding="utf-8", errors="replace")
    print(f"{'pseudo':>6} {'refs':>5} {'live':>5} {'priority':>9}  reg")
    for priority, regno, refs, live, hard in priorities(greg):
        if live >= args.min_live:
            print(f"{regno:>6} {refs:>5} {live:>5} {priority:>9.3f}  {hard}")
    if args.pseudo is not None:
        pattern = re.compile(rf"\(reg(?:/[a-z]+)*:\w+ {args.pseudo}\)")
        for block in re.split(r"\n(?=\()", greg):
            if pattern.search(block) and block.startswith("(insn"):
                print(" ".join(block.split())[:160])
    return 0


if __name__ == "__main__":
    sys.exit(main())
