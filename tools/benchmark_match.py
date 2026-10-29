"""Compare uncached and session-based probes, checking their verdicts and bytes.

Both modes compile and link every candidate. Alternating their order limits
filesystem warm-up bias. A shortened reference interval is also probed so the
session must return a fresh mismatch rather than reuse a previous match.

    python tools/benchmark_match.py build/m2c/sub_0806B2B8/spec.json --repetitions 6
"""

import argparse
import contextlib
import io
import json
from pathlib import Path
import time

from common import ROOT
from match import MatchSession, match


def benchmark(spec_path, output, repetitions):
    output = output.resolve()
    if not output.is_relative_to(ROOT / "build"):
        raise ValueError("Benchmark artifacts must stay in build/.")
    output.mkdir(parents=True, exist_ok=True)
    spec = json.loads(spec_path.read_text(encoding="utf-8"))
    if len(spec["segments"]) != 1:
        raise ValueError("Choose a single-function spec for this benchmark.")
    negative = json.loads(json.dumps(spec))
    segment = negative["segments"][0]
    start, end = int(segment["start"], 0), int(segment["end"], 0)
    if end - start <= 4:
        raise ValueError("Choose a function larger than four bytes.")
    segment["end"] = hex(end - 4)
    negative_path = output / "shortened_reference.json"
    negative_path.write_text(json.dumps(negative, indent=2) + "\n", encoding="utf-8")
    name = segment["name"]
    started = time.perf_counter()
    session = MatchSession()
    setup_seconds = time.perf_counter() - started
    totals = {"uncached": 0.0, "session": setup_seconds}
    samples = {"uncached": [], "session": []}
    for iteration in range(repetitions):
        path = spec_path if iteration % 2 == 0 else negative_path
        outputs = {}
        modes = ("uncached", "session") if iteration % 2 == 0 else ("session", "uncached")
        for mode in modes:
            directory = output / mode
            before = time.perf_counter()
            with contextlib.redirect_stdout(io.StringIO()):
                verdict = match(path, directory, session=session if mode == "session" else None)
            elapsed = time.perf_counter() - before
            totals[mode] += elapsed
            samples[mode].append(elapsed)
            outputs[mode] = (verdict, (directory / f"{name}.bin").read_bytes(),
                             json.loads((directory / "results.json").read_text()))
        if outputs["uncached"] != outputs["session"]:
            raise ValueError("Session and uncached probe results differ.")
        if iteration % 2 and outputs["session"][0]:
            raise ValueError("Shortened reference was incorrectly accepted.")
    report = {"spec": spec_path.as_posix(), "repetitions_per_mode": repetitions,
              "session_setup_seconds": setup_seconds, "seconds": totals,
              "samples_seconds": samples, "speed_ratio": totals["uncached"] / totals["session"],
              "identical_results": True, "shortened_reference_rejected": True,
              "session_stats": session.stats,
              "note": "Matching probes only; strict acceptance and full-ROM validation remain separate gates."}
    (output / "report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("spec", type=Path)
    parser.add_argument("--repetitions", type=int, default=6)
    parser.add_argument("--output", type=Path, default=ROOT / "build/match_benchmark")
    args = parser.parse_args()
    if args.repetitions < 2:
        parser.error("At least two repetitions are required to exercise a mismatch.")
    print(json.dumps(benchmark(args.spec, args.output, args.repetitions), indent=2))


if __name__ == "__main__":
    main()
