"""Accept a hand-finished m2c draft for integration.

Workflow for a function m2c gets close to but not exact:

    python tools/m2c_candidate.py 0x0801234C --match          # draft + build/m2c/sub_0801234C/
    (edit the m2c part of build/m2c/sub_0801234C/candidate.c)
    python tools/match.py build/m2c/sub_0801234C/spec.json --output-dir build/m2c/sub_0801234C/match
    python tools/asm_diff.py build/m2c/sub_0801234C/spec.json --output-dir build/m2c/sub_0801234C/match
    python tools/accept_draft.py sub_0801234C

This re-runs the byte comparison, requires a clean compile with the production
flags (-Werror, no -w), copies the edited code back to build/m2c/<name>.c and
records the function in build/m2c/manual_solved.json, which
tools/m2c_integrate.py reads alongside the harvest and the permuter results.
"""

import argparse
import contextlib
import io
import json
import subprocess
import sys

from common import ROOT, tool

OUTPUT = ROOT / "build" / "m2c"
SOLVED = OUTPUT / "manual_solved.json"


def verify_return_paths(preprocessed, diagnostic_assembly):
    """Check C return paths without using diagnostic output in the ROM build.

    agbcc does not support -Wreturn-type. The modern cross-compiler needs a
    compilation pass (-S), rather than -fsyntax-only, to diagnose fallthrough.
    Read the same preprocessed source that already passed production agbcc.
    """
    result = subprocess.run(
        [tool("gcc"), "-S", "-std=gnu89", "-Werror=return-type",
         str(preprocessed), "-o", str(diagnostic_assembly)],
        cwd=ROOT, capture_output=True, text=True)
    result.check_returncode()


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("name", help="Draft name, e.g. sub_0801234C")
    parser.add_argument("--cflags", help="Override the spec's compiler flags (without -w)")
    parser.add_argument("--fall-off-end", action="store_true",
                        help="Allow a non-void function to fall off the end like the reference (AGENTS.md);"
                        " the draft must carry a 'Falls off the end like the reference' comment")
    args = parser.parse_args()
    from compiler_agbcc import compile_source
    from match import match

    directory = OUTPUT / args.name
    spec_path = directory / "spec.json"
    spec = json.loads(spec_path.read_text(encoding="utf-8"))
    cflags = args.cflags.split() if args.cflags is not None else [flag for flag in spec["cflags"] if flag != "-w"]
    spec["cflags"] = ["-w", *cflags]
    spec_path.write_text(json.dumps(spec, indent=2) + "\n", encoding="utf-8")
    with contextlib.redirect_stdout(io.StringIO()):
        if not match(spec_path, directory / "match"):
            raise SystemExit("Not byte-identical; see tools/asm_diff.py.")
    from m2c_candidate import extra_sections
    section = spec["segments"][0]["input_section"]
    extra = extra_sections(directory / "match" / "candidate.o", section)
    if extra:
        raise SystemExit(f"Matches, but also emits {extra}; production has no place for extra data.")
    try:
        compile_source(directory / "candidate.c", directory / "match" / "strict.o", cflags)
    except subprocess.CalledProcessError:
        raise SystemExit("Matches, but does not compile with -Werror; fix the warnings first.")
    if args.fall_off_end:
        if "Falls off the end like the reference" not in (directory / "candidate.c").read_text(encoding="utf-8"):
            raise SystemExit("--fall-off-end needs a 'Falls off the end like the reference' comment naming the callers.")
    else:
        try:
            verify_return_paths(directory / "match" / "strict.i", directory / "match" / "return-check.s")
        except subprocess.CalledProcessError as error:
            raise SystemExit("Matches, but C return-path diagnostics failed:\n" + (error.stderr or str(error)))
    # The m2c output (as edited) follows the renaming macro in candidate.c.
    candidate = (directory / "candidate.c").read_text(encoding="utf-8")
    marker = f"#define {args.name} m2c_{args.name}\n"
    if marker not in candidate:
        raise SystemExit(f"{marker.strip()} not found in candidate.c.")
    (OUTPUT / f"{args.name}.c").write_text(candidate.split(marker, 1)[1].lstrip("\n"), encoding="utf-8")
    segment = spec["segments"][0]
    solved = json.loads(SOLVED.read_text(encoding="utf-8")) if SOLVED.exists() else []
    solved = [entry for entry in solved if entry["name"] != args.name] + [
        {"name": args.name, "start": segment["start"], "end": segment["end"], "cflags": cflags}]
    SOLVED.write_text(json.dumps(solved, indent=2) + "\n", encoding="utf-8")
    print(f"Accepted {args.name} ({int(segment['end'], 0) - int(segment['start'], 0)} bytes, cflags {cflags}); "
          f"{len(solved)} manual functions await tools/m2c_integrate.py")
    return 0


if __name__ == "__main__":
    sys.exit(main())
