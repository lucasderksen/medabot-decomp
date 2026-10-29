"""Try a hand-written version of an m2c draft function and show the result.

Replaces the function definition in build/m2c/<name>/candidate.c with the
code read from FILE (or stdin), optionally replaces the draft's extern block,
compiles it through tools/match.py and prints the differing instruction rows.

    python tools/try_draft.py sub_08048B70 new.c --cflags="-fprologue-bugfix"
    python tools/accept_draft.py sub_08048B70      # once it matches

FILE holds one complete function definition (any extern declarations it
needs may precede it; they replace the draft's). A src/non_matching/ file
works as it is: its NONMATCH wrapper and #include lines are dropped.
"""

import argparse
import contextlib
import io
import json
from pathlib import Path
import re
import sys

from common import ROOT

OUTPUT = ROOT / "build" / "m2c"


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("name")
    parser.add_argument("file", nargs="?", help="Replacement code; default stdin")
    parser.add_argument("--cflags", help="Compiler flags (without -w); default: keep the spec's")
    parser.add_argument("--full", action="store_true", help="Print the whole aligned diff")
    args = parser.parse_args()
    from asm_diff import BASE, diff
    from common import find_rom
    from match import match

    directory = OUTPUT / args.name
    candidate_path = directory / "candidate.c"
    candidate = candidate_path.read_text(encoding="utf-8")
    marker = f"#define {args.name} m2c_{args.name}\n"
    prefix, _ = candidate.split(marker, 1)
    code = Path(args.file).read_text(encoding="utf-8") if args.file else sys.stdin.read()
    # A src/non_matching/ file: try its C attempt as an ordinary definition.
    code = re.sub(r'^NONMATCH\("[^"]*",\s*(.*)\)\s*$', r"\1", code, flags=re.M)
    code = re.sub(r"^END_NONMATCH\s*$", "", code, flags=re.M)
    code = "\n".join(line for line in code.splitlines() if not line.lstrip().startswith("#include"))
    if not re.search(rf"\b{args.name}\s*\(", code):
        raise SystemExit(f"The replacement does not define {args.name}.")
    candidate_path.write_text(prefix + marker + "\n" + code.strip() + "\n", encoding="utf-8")

    spec_path = directory / "spec.json"
    spec = json.loads(spec_path.read_text(encoding="utf-8"))
    if args.cflags is not None:
        spec["cflags"] = ["-w", *args.cflags.split()]
        spec_path.write_text(json.dumps(spec, indent=2) + "\n", encoding="utf-8")
    try:
        with contextlib.redirect_stdout(io.StringIO()):
            matched = match(spec_path, directory / "match")
    except Exception as error:  # compile errors are the common case here
        print(f"Compile/link failed: {error}")
        return 1
    segment = spec["segments"][0]
    start, end = int(segment["start"], 0), int(segment["end"], 0)
    expected = find_rom().read_bytes()[start:end]
    actual = (directory / "match" / f"{segment['name']}.bin").read_bytes()
    rows = diff(expected, actual, BASE + start)
    print(f"{'MATCH' if matched else 'MISMATCH'}: {len(expected)} reference bytes, {len(actual)} candidate bytes, "
          f"{sum(mark != ' ' for mark, _, _ in rows)} differing rows (cflags {spec['cflags'][1:]})")
    for mark, left, right in rows:
        if args.full or mark != " ":
            left_text = f"{left[0]:4X} {left[2]}" if left else ""
            right_text = f"{right[0]:4X} {right[2]}" if right else ""
            print(f"{left_text:<38} {mark} {right_text}")
    return 0 if matched else 1


if __name__ == "__main__":
    sys.exit(main())
