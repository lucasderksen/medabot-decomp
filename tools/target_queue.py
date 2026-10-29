"""Rank remaining drafts by byte payoff, historical similarity and prior effort.

Scores are scheduling heuristics, never matching evidence. Entire intervals
overlapping integrated source are excluded. Optional families require equal
instruction/register shape AND equal relative branch destinations.

    python tools/target_queue.py --families --min-bytes 250 --limit 30
    python tools/target_queue.py --record sub_08026D98 --minutes 20 --note "15 rows; park"
"""

import argparse
import collections
from datetime import datetime, timezone
import hashlib
import json
import math
from pathlib import Path

from common import ROOT, find_rom, load_segments, rom_config


def address(value, base):
    number = int(value, 16) if isinstance(value, str) else value
    return number - base if number >= base else number


def rank_targets(harvest, segments, base, size, minimum=32, families=None,
                 ledger=(), hashes=None, assignments=None, include_parked=False):
    families, hashes, assignments = families or {}, hashes or {}, assignments or {}
    ranked, excluded, seen = [], collections.Counter(), set()
    for draft in harvest:
        if "end" not in draft:
            excluded["unknown_bounds"] += 1
            continue
        start, end = address(draft["start"], base), address(draft["end"], base)
        name = f"sub_{base + start:08X}"
        if not 0 <= start < end <= size or start % 4 or end % 4:
            excluded["invalid_bounds"] += 1
            continue
        if any(start < segment["end"] and end > segment["start"] for segment in segments if not segment.get("nonmatching")):
            excluded["overlaps_integrated_source"] += 1
            continue
        if end - start < minimum:
            excluded["below_minimum"] += 1
            continue
        if name in seen:
            excluded["duplicate_entry"] += 1
            continue
        seen.add(name)
        if name in assignments:
            excluded["assigned_to_worker"] += 1
            continue
        trials = [trial for trial in ledger if trial["name"] == name
                  and trial.get("draft_hash") == hashes.get(name)]
        minutes = sum(trial["minutes"] for trial in trials)
        if minutes >= 20 and not include_parked:
            excluded["parked_after_20_minutes"] += 1
            continue
        members = families.get(name, [(name, end-start)])
        potential = sum(length for _, length in members)
        measured = isinstance(draft.get("similarity"), (int, float)) and math.isfinite(draft["similarity"])
        similarity = max(0.0, min(1.0, float(draft["similarity"]))) if measured else 0.0
        score = potential * (0.25 + similarity) ** 2 / (1 + math.sqrt((end-start)/256))
        # A large untranslated function is not automatically a promising match.
        if not measured or draft.get("error"):
            score *= 0.1
        score /= 1 + minutes / 20
        ranked.append({"name": name, "start": f"{base+start:08X}", "end": f"{base+end:08X}",
                       "bytes": end-start, "historical_similarity": similarity if measured else None,
                       "score_evidence": "historical harvest; not fresh verification",
                       "historical_same_size": draft.get("same_size"),
                       "cflags": draft.get("cflags", []), "family_members": [member for member, _ in members],
                       "family_candidate_bytes": potential, "same_draft_minutes": minutes,
                       "priority_score": round(score, 3), "draft_hash": hashes.get(name),
                       "attempt_budget_minutes": 20})
    ranked.sort(key=lambda row: (-row["priority_score"], -row["bytes"], row["name"]))
    return ranked, dict(excluded)


def clone_families(harvest, segments, data, base):
    from clone_transfer import shape
    from m2c_candidate import decode
    groups = collections.defaultdict(list)
    for draft in harvest:
        if "end" not in draft:
            continue
        start, end = address(draft["start"], base), address(draft["end"], base)
        if not 0 <= start < end <= len(data) or start % 4 or end % 4 or end-start <= 8:
            continue
        if any(start < segment["end"] and end > segment["start"] for segment in segments if not segment.get("nonmatching")):
            continue
        try:
            code, _, _, _ = decode(data, base+start, base+end)
        except (SystemExit, ValueError):
            continue
        branches = tuple((offset-(base+start), int(instruction.op_str[1:], 0)-(base+start))
                         for offset, instruction in sorted(code.items())
                         if instruction.mnemonic.startswith("b") and instruction.mnemonic != "bl"
                         and instruction.op_str.startswith("#"))
        groups[(shape(code), branches)].append((f"sub_{base+start:08X}", end-start))
    return {name: members for members in groups.values() if len(members) > 1 for name, _ in members}


def build_path(path):
    path = path.resolve()
    if not path.is_relative_to(ROOT / "build"):
        raise ValueError("Queue and effort artifacts must stay in build/.")
    path.parent.mkdir(parents=True, exist_ok=True)
    return path


def draft_hash(name):
    source = ROOT / "build/m2c" / f"{name}.c"
    return hashlib.sha256(source.read_bytes()).hexdigest() if source.is_file() else None


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--harvest", type=Path, default=ROOT / "build/m2c/harvest.json")
    parser.add_argument("--output", type=Path, default=ROOT / "build/target_queue.json")
    parser.add_argument("--ledger", type=Path, default=ROOT / "build/target_effort.json")
    parser.add_argument("--assignments", type=Path, help="JSON mapping function names to active workers; explicit to avoid stale ownership")
    parser.add_argument("--families", action="store_true")
    parser.add_argument("--min-bytes", type=int, default=32)
    parser.add_argument("--limit", type=int, default=30)
    parser.add_argument("--include-parked", action="store_true")
    parser.add_argument("--record", help="Function name whose bounded attempt finished")
    parser.add_argument("--minutes", type=float)
    parser.add_argument("--note", default="")
    args = parser.parse_args()
    ledger_path = build_path(args.ledger)
    ledger = json.loads(ledger_path.read_text()) if ledger_path.is_file() else []
    if args.record:
        import re
        if not re.fullmatch(r"sub_[0-9A-F]{8}", args.record) or args.minutes is None or not math.isfinite(args.minutes) or args.minutes <= 0:
            parser.error("--record needs sub_XXXXXXXX and a positive finite --minutes")
        ledger.append({"name": args.record, "minutes": args.minutes, "note": args.note,
                       "draft_hash": draft_hash(args.record), "date": datetime.now(timezone.utc).isoformat()})
        ledger_path.write_text(json.dumps(ledger, indent=2) + "\n")
        print(f"Recorded {args.minutes:g} minutes on {args.record}; unchanged drafts park at 20 minutes.")
        return
    if args.min_bytes <= 8 or args.limit < 1:
        parser.error("--min-bytes must exceed 8 and --limit must be positive")
    config, segments = rom_config(), load_segments()
    base = int(config["rom_base"], 0)
    harvest = json.loads(args.harvest.read_text())
    families = clone_families(harvest, segments, find_rom().read_bytes(), base) if args.families else {}
    hashes = {f"sub_{base+address(row['start'],base):08X}": draft_hash(f"sub_{base+address(row['start'],base):08X}") for row in harvest}
    assignments = json.loads(args.assignments.read_text()) if args.assignments else {}
    rows, excluded = rank_targets(harvest, segments, base, config["size"], args.min_bytes, families,
                                 ledger, hashes, assignments, args.include_parked)
    report = {"created_utc": datetime.now(timezone.utc).isoformat(),
              "ranking": "family bytes * (0.25 + historical similarity)^2 / (1 + sqrt(bytes/256)) / (1 + same-draft minutes/20); untranslated/error drafts receive a 0.1 factor",
              "note": "Scheduling heuristic, not probability or matching evidence. Fresh isolated and full-ROM gates are required.",
              "remaining_targets": len(rows), "remaining_candidate_bytes": sum(row["bytes"] for row in rows),
              "excluded": excluded, "targets": rows[:args.limit]}
    build_path(args.output).write_text(json.dumps(report, indent=2) + "\n")
    for row in report["targets"]:
        similarity = f"{row['historical_similarity']:.3f}" if row["historical_similarity"] is not None else "unknown"
        print(f"{row['name']}  {row['bytes']:4} bytes  score {row['priority_score']:7.1f}  family {len(row['family_members'])}  historical similarity {similarity}")
    print(f"{len(rows)} targets; {report['remaining_candidate_bytes']:,} candidate bytes; exclusions {excluded}")


if __name__ == "__main__":
    main()
