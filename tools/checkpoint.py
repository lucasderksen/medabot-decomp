"""Verify the integrated tree and commit it as one accepted batch.

Runs the full-ROM build and the unit tests in this invocation; only if both
pass are all non-ignored changes committed, with the progress change in the
message. A failed build commits nothing (an older build/medabots.gba is never
taken as proof). Root uses this after each integration:

    python tools/checkpoint.py "Match state0 map phase callbacks" --push
"""

import argparse
import json
import subprocess
import sys

from common import ROOT, load_segments
from progress_report import ALL, code_percent, measure, percent


def run(*args, **kwargs):
    return subprocess.run(list(args), cwd=ROOT, **kwargs)


def committed_progress():
    """Measure the segment table of HEAD, or None before the first commit."""
    shown = run("git", "show", "HEAD:config/segments.json", capture_output=True, text=True)
    return None if shown.returncode else measure(load_segments(entries=json.loads(shown.stdout)))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("message", help="One-line summary of the accepted batch")
    parser.add_argument("--push", action="store_true", help="Push the commit to the tracked remote branch")
    args = parser.parse_args()

    if run(sys.executable, "tools/build.py").returncode:
        raise SystemExit("Build did not match; nothing committed.")
    if run(sys.executable, "-m", "unittest", "discover", "-s", "tests", "-q").returncode:
        raise SystemExit("Tests failed; nothing committed.")

    run("git", "add", "-A", check=True)
    if not run("git", "diff", "--cached", "--quiet").returncode:
        print("No changes to commit.")
        return

    now, before = measure(), committed_progress()
    lines = [args.message, "", "Full ROM match: all bytes identical; unit tests pass.",
             f"Code region: {code_percent(now):.2f}% in source; whole ROM: {percent(now, *ALL):.3f}%."]
    if before:
        lines.append(f"Change: {int(now['game_c']) - int(before['game_c']):+,} game C bytes, "
                     f"{int(now['functions']) - int(before['functions']):+,} functions, "
                     f"{int(now['data']) - int(before['data']):+,} typed data bytes.")
    run("git", "commit", "-q", "-F", "-", input="\n".join(lines) + "\n", text=True, check=True)
    run("git", "log", "-1", "--stat", "--format=%h %s", check=True)
    if args.push:
        run("git", "push", check=True)


if __name__ == "__main__":
    main()
