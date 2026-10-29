"""Resolve a git merge conflict in config/symbols.json and config/segments.json.

Worker branches each add segments and remove now-defined symbols. Git's
line merge conflicts when those edits are adjacent; this applies both sides'
changes to the common base instead:

    git merge work/lean_a          # conflicts in config/*.json
    python tools/merge_config.py   # resolves and stages them

Segments are merged by name (each side's additions, removals and edits); a
name edited differently on both sides, or overlapping intervals, abort.
"""

import json
import subprocess
import sys

from common import ROOT


def stage(path, number):
    result = subprocess.run(["git", "show", f":{number}:{path}"], cwd=ROOT, capture_output=True, text=True)
    return json.loads(result.stdout) if result.returncode == 0 else None


def merge_dicts(base, ours, theirs, label):
    merged = dict(base)
    for side in (ours, theirs):
        for key in set(base) - set(side):
            merged.pop(key, None)
        for key, value in side.items():
            if base.get(key) != value:
                other = theirs if side is ours else ours
                if key in other and other[key] != value and base.get(key) != other[key]:
                    raise SystemExit(f"{label}: {key} changed differently on both sides")
                merged[key] = value
    return merged


def resolve_defined():
    """Drop absolute symbols now defined in C (also after a clean line merge)."""
    path = ROOT / "config/symbols.json"
    symbols = json.loads(path.read_text(encoding="utf-8"))
    segments = json.loads((ROOT / "config/segments.json").read_text(encoding="utf-8"))
    defined = {entry["input_section"][len(".text."):] for entry in segments
               if entry.get("input_section", "").startswith(".text.")}
    stale = [key for key in symbols if key in defined]
    if not stale:
        return False
    for key in stale:
        symbols.pop(key)
    path.write_text(json.dumps(symbols, indent=2) + "\n", encoding="utf-8")
    print("dropped symbols defined in C: " + ", ".join(stale))
    return True


def main():
    changed = False
    for name in ("config/segments.json", "config/symbols.json"):
        base, ours, theirs = (stage(name, n) for n in (1, 2, 3))
        if ours is None or theirs is None:
            if name.endswith("symbols.json") and not resolve_defined():
                continue
            changed = True
            continue
        base = base or ([] if isinstance(ours, list) else {})
        if isinstance(ours, list):
            key = lambda entries: {entry["name"]: entry for entry in entries}
            merged = list(merge_dicts(key(base), key(ours), key(theirs), name).values())
            merged.sort(key=lambda entry: int(entry["start"], 0))
            for previous, current in zip(merged, merged[1:]):
                if int(current["start"], 0) < int(previous["end"], 0):
                    raise SystemExit(f"{name}: {previous['name']} overlaps {current['name']}")
        else:
            merged = merge_dicts(base, ours, theirs, name)
            # One side may add an absolute symbol for a callee the other side
            # has just defined in C; the definition wins.
            segments = json.loads((ROOT / "config/segments.json").read_text(encoding="utf-8"))
            defined = {entry["input_section"][len(".text."):] for entry in segments
                       if entry.get("input_section", "").startswith(".text.")}
            merged = {key: value for key, value in merged.items() if key not in defined}
        (ROOT / name).write_text(json.dumps(merged, indent=2) + "\n", encoding="utf-8")
        subprocess.run(["git", "add", name], cwd=ROOT, check=True)
        print(f"resolved {name}")
        changed = True
    if not changed:
        print("no config conflicts to resolve")
    return 0


if __name__ == "__main__":
    sys.exit(main())
