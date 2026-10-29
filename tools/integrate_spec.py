"""Integrate a verified tools/match.py spec into the production build (root only).

Copies the spec's source to src/<name>.c, adds its segments (with the spec's
compiler and cflags) to config/segments.json, adds the spec's extra symbols to
config/symbols.json when they are missing, and removes absolute symbols for
functions that are now defined in C. Run tools/build.py afterwards; the full
ROM comparison decides acceptance.

    python tools/match.py build/experiments/x/delivery.json --output-dir build/experiments/x/check
    python tools/integrate_spec.py build/experiments/x/delivery.json --name continued_f488
"""

import argparse
import json
from pathlib import Path
import shutil

from common import ROOT, load_segments

SEGMENTS = ROOT / "config" / "segments.json"
SYMBOLS = ROOT / "config" / "symbols.json"


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("spec", help="A spec that tools/match.py reports as fully matching")
    parser.add_argument("--name", required=True, help="Production source stem: src/<name>.c")
    parser.add_argument("--description", default="Exact ordinary C integrated from a verified staged delivery")
    args = parser.parse_args()

    spec_path = Path(args.spec)
    spec = json.loads(spec_path.read_text(encoding="utf-8"))
    source = ROOT / spec["source"]
    target = ROOT / "src" / f"{args.name}.c"
    if target.exists():
        raise SystemExit(f"{target.relative_to(ROOT)} already exists.")
    segments = json.loads(SEGMENTS.read_text(encoding="utf-8"))
    occupied = [(s["start"], s["end"]) for s in load_segments(entries=segments)]
    new = []
    for entry in spec["segments"]:
        start, end = int(entry["start"], 0) & 0xFFFFFF, int(entry["end"], 0) & 0xFFFFFF
        if any(s < end and start < e for s, e in occupied):
            raise SystemExit(f"{entry['name']} overlaps an existing segment.")
        new.append({"name": entry["name"], "start": f"0x{start:06X}", "end": f"0x{end:06X}", "kind": "c",
                    "compiler": spec.get("compiler", "agbcc"), "cflags": spec.get("cflags", []),
                    "source": f"src/{args.name}.c", "input_section": entry["input_section"], "description": args.description})

    shutil.copyfile(source, target)
    segments = sorted(segments + new, key=lambda entry: int(entry["start"], 0))
    SEGMENTS.write_text(json.dumps(segments, indent=2) + "\n", encoding="utf-8")
    symbols = json.loads(SYMBOLS.read_text(encoding="utf-8"))
    added = {name: value for name, value in spec.get("symbols", {}).items() if name not in symbols}
    symbols.update(added)
    defined = {entry["input_section"][len(".text."):] for entry in new if entry["input_section"].startswith(".text.")}
    removed = [name for name in defined if symbols.pop(name, None) is not None]
    SYMBOLS.write_text(json.dumps(symbols, indent=2) + "\n", encoding="utf-8")
    total = sum(int(e["end"], 16) - int(e["start"], 16) for e in new)
    print(f"Integrated {len(new)} segments ({total:,} bytes) as {target.relative_to(ROOT).as_posix()}; "
          f"{len(added)} symbols added, {len(removed)} now defined in C.")


if __name__ == "__main__":
    main()
