"""Compile one draft under every agbcc flag profile already used in config/segments.json.

    python tools/try_flags.py sub_0806FDA4 build/lb9/da4_1.c

Each profile is one tools/try_draft.py compile; results are printed best first.
Only profiles that accepted segments already use are tried, so a match here is
consistent with the rest of the ROM. Re-run try_draft.py with the winning
--cflags before tools/accept_draft.py (try_draft remembers the last flags).
"""

import collections
import json
import re
import subprocess
import sys

from common import ROOT


def profiles():
    counts = collections.Counter(
        " ".join(entry.get("cflags") or [])
        for entry in json.loads((ROOT / "config/segments.json").read_text(encoding="utf-8"))
        if entry.get("compiler") == "agbcc")
    return [flags for flags, _ in counts.most_common()]


def score(name, path, flags):
    output = subprocess.run([sys.executable, str(ROOT / "tools/try_draft.py"), name, path, "--cflags=" + flags],
                            cwd=ROOT, capture_output=True, text=True).stdout
    if output.startswith("MATCH"):
        return 0, output.splitlines()[0]
    match = re.search(r"(\d+) reference bytes, (\d+) candidate bytes, (\d+) differing rows", output)
    if not match:
        return 99999, "compile failed"
    penalty = 0 if match.group(1) == match.group(2) else 1000
    return int(match.group(3)) + penalty, output.splitlines()[0]


def main():
    if len(sys.argv) != 3:
        raise SystemExit(__doc__)
    name, path = sys.argv[1], sys.argv[2]
    results = []
    for flags in profiles():
        rows, line = score(name, path, flags)
        results.append((rows, flags, line))
        print(f"{rows:6d}  {flags or '(no flags)'}", flush=True)
        if rows == 0:
            break
    results.sort()
    best = results[0]
    print(f"\nbest: {best[0]} with {best[1] or '(no flags)'!r}")
    # Leave the spec on the best profile so accept_draft sees it.
    score(name, path, best[1])
    return 0


if __name__ == "__main__":
    sys.exit(main())
