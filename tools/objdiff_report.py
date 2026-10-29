"""Write an objdiff-format progress report (report.json) from config/segments.json.

Needs no ROM. Trackers such as bytematch.dev read this file from the
`A8BP_report` CI artifact (see .github/workflows/progress.yml). The build
compares every byte of the ROM, so each source segment counts as matched and
complete; only the `.incbin` gaps before the end of the last code segment are
unmatched code (one function each).

    python tools/objdiff_report.py -o build/A8BP/report.json

Units are source files (path without extension); the gaps form the unit
`incbin`. Code is every non-data segment and gap up to the end of the code
region. Data is every typed data segment plus the cartridge header.
Categories: `game` (game C and gaps), `runtime` (libgcc, libc) and `asm`
(hand-written startup, BIOS and trampoline assembly).
"""

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import load_segments  # noqa: E402

ROM_BASE = 0x08000000
VERSION = 2
CATEGORIES = (("game", "Game code"), ("runtime", "Runtime libraries"), ("asm", "Hand-written assembly"))


def classify(segment):
    """(category, is_code) for one segment."""
    if segment.get("category") == "data" or segment["name"] == "header":
        return None, False
    if segment.get("category") == "runtime" or segment["name"].startswith("libgcc_"):
        return "runtime", True
    if segment["kind"] == "asm":
        return "asm", True
    return "game", True


def function_name(segment):
    section = segment.get("input_section", "")
    return section[len(".text."):] if section.startswith(".text.") else segment["name"]


def gaps(segments, end):
    position = 0
    for segment in segments:
        if segment["start"] >= end:
            break
        if segment["start"] > position:
            yield position, segment["start"]
        position = segment["end"]
    if position < end:
        yield position, end


def empty():
    return {"total_code": 0, "matched_code": 0, "total_data": 0, "matched_data": 0,
            "total_functions": 0, "matched_functions": 0, "total_units": 0, "complete_units": 0}


def finish(counts):
    """objdiff's JSON measures: 64-bit sizes as strings, percentages as floats."""
    def percent(part, whole):
        return round(100 * part / whole, 6) if whole else 100.0
    code = percent(counts["matched_code"], counts["total_code"])
    data = percent(counts["matched_data"], counts["total_data"])
    return {
        "fuzzy_match_percent": code,
        "total_code": str(counts["total_code"]),
        "matched_code": str(counts["matched_code"]),
        "matched_code_percent": code,
        "total_data": str(counts["total_data"]),
        "matched_data": str(counts["matched_data"]),
        "matched_data_percent": data,
        "total_functions": counts["total_functions"],
        "matched_functions": counts["matched_functions"],
        "matched_functions_percent": percent(counts["matched_functions"], counts["total_functions"]),
        "complete_code": str(counts["matched_code"]),
        "complete_code_percent": code,
        "complete_data": str(counts["matched_data"]),
        "complete_data_percent": data,
        "total_units": counts["total_units"],
        "complete_units": counts["complete_units"],
    }


def item(name, start, end, matched):
    return {"name": name, "size": str(end - start), "fuzzy_match_percent": 100.0 if matched else 0.0,
            "metadata": {"virtual_address": str(ROM_BASE + start)}}


def build(segments):
    code_end = max(s["end"] for s in segments if classify(s)[1])
    units = {}

    def unit(name, source=None):
        if name not in units:
            units[name] = {"counts": empty(), "categories": set(), "functions": [], "sections": [], "source": source}
        return units[name]

    for segment in segments:
        category, code = classify(segment)
        source = segment["source"]
        entry = unit(source.rsplit(".", 1)[0], source)
        size = segment["end"] - segment["start"]
        counts = entry["counts"]
        if code:
            counts["total_code"] += size
            counts["matched_code"] += size
            counts["total_functions"] += 1
            counts["matched_functions"] += 1
            entry["categories"].add(category)
            entry["functions"].append(item(function_name(segment), segment["start"], segment["end"], True))
        else:
            counts["total_data"] += size
            counts["matched_data"] += size
            entry["sections"].append(item(segment.get("input_section", segment["name"]), segment["start"], segment["end"], True))
    for start, end in gaps(segments, code_end):
        entry = unit("incbin")
        entry["counts"]["total_code"] += end - start
        entry["counts"]["total_functions"] += 1
        entry["categories"].add("game")
        entry["functions"].append(item(f"sub_{ROM_BASE + start:08X}", start, end, False))

    report_units, top = [], empty()
    by_category = {key: empty() for key, _ in CATEGORIES}
    for name, entry in units.items():
        counts = entry["counts"]
        counts["total_units"] = 1
        counts["complete_units"] = int(counts["matched_code"] == counts["total_code"] and counts["matched_data"] == counts["total_data"])
        for target in [top] + [by_category[key] for key in entry["categories"]]:
            for key, value in counts.items():
                target[key] += value
        metadata = {"complete": bool(counts["complete_units"]), "progress_categories": sorted(entry["categories"])}
        if entry["source"]:
            metadata["source_path"] = entry["source"]
        report_unit = {"name": name, "measures": finish(counts), "metadata": metadata}
        if entry["sections"]:
            report_unit["sections"] = entry["sections"]
        if entry["functions"]:
            report_unit["functions"] = entry["functions"]
        report_units.append(report_unit)
    return {
        "measures": finish(top),
        "units": report_units,
        "version": VERSION,
        "categories": [{"id": key, "name": label, "measures": finish(by_category[key])} for key, label in CATEGORIES],
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("-o", "--output", type=Path, default=Path("build/A8BP/report.json"))
    args = parser.parse_args()
    report = build(load_segments())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, separators=(",", ":")) + "\n", encoding="utf-8")
    measures = report["measures"]
    print(f"{args.output}: code {measures['matched_code_percent']:.2f}% ({measures['matched_code']}/{measures['total_code']} bytes), "
          f"data {measures['matched_data_percent']:.2f}%, functions {measures['matched_functions']}/{measures['total_functions']}, "
          f"units {measures['complete_units']}/{measures['total_units']}")


if __name__ == "__main__":
    main()
