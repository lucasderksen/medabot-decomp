"""Record decompilation progress from config/segments.json and render history charts.

Needs no ROM: coverage comes from the segment table alone. The "code region"
runs from the ROM start to the end of the last code (non-data C or assembly)
segment. It is provisional: it grows if code is found further on, and it still
contains copied data that may never become C. CI runs this on every
push to main and stores history.csv, progress.svg and badge.svg on the
`progress` branch.
"""

import argparse
import csv
import json
import sys
from datetime import datetime, timezone
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import load_segments, rom_config  # noqa: E402

FIELDS = ("date", "sha", "total", "game_c", "runtime_c", "data", "asm", "functions", "code_end", "code_done")
ALL = ("game_c", "runtime_c", "data", "asm")


def measure(segments=None):
    segments = load_segments() if segments is None else segments
    row = {"total": rom_config()["size"], "game_c": 0, "runtime_c": 0, "data": 0, "asm": 0, "functions": 0}
    row["code_end"] = max(s["end"] for s in segments if s.get("category") != "data")
    row["code_done"] = sum(min(s["end"], row["code_end"]) - s["start"] for s in segments if s["start"] < row["code_end"])
    for segment in segments:
        size = segment["end"] - segment["start"]
        category = segment.get("category")
        if segment["kind"] == "asm":
            row["asm"] += size
        elif category == "data":
            row["data"] += size
        elif category == "runtime":
            row["runtime_c"] += size
        else:
            row["game_c"] += size
            row["functions"] += 1
    return row


def percent(row, *keys):
    return 100 * sum(int(row[key]) for key in keys) / int(row["total"])


def code_percent(row):
    return 100 * int(row["code_done"]) / int(row["code_end"]) if row.get("code_end") else None


def read_history(path):
    if not path.exists():
        return []
    with path.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


def write_history(path, rows):
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, FIELDS, restval="")
        writer.writeheader()
        writer.writerows(rows)


def badge(label, value):
    left, right = 6 * len(label) + 12, 7 * len(value) + 12
    width = left + right
    return f"""<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="20" role="img" aria-label="{label}: {value}">
<rect width="{left}" height="20" fill="#555"/><rect x="{left}" width="{right}" height="20" fill="#3b82c4"/>
<g fill="#fff" font-family="Verdana,DejaVu Sans,sans-serif" font-size="11" text-anchor="middle">
<text x="{left / 2}" y="14">{label}</text><text x="{left + right / 2}" y="14">{value}</text></g></svg>
"""


def chart(rows):
    width, height, pad_left, pad_right, pad_top, pad_bottom = 760, 300, 64, 24, 40, 40
    plot_w, plot_h = width - pad_left - pad_right, height - pad_top - pad_bottom
    series = [("Code region in source", code_percent, "#2da44e"),
              ("Whole ROM in source", lambda row: percent(row, *ALL), "#d9822b")]
    peak = max(value for _, measure_row, _ in series for row in rows if (value := measure_row(row)) is not None)
    top = max(0.5, next(step for step in (0.5, 1, 2, 5, 10, 20, 25, 50, 100) if step >= peak * 1.15))
    count = len(rows)

    def point(index, value):
        x = pad_left + (plot_w * index / (count - 1) if count > 1 else plot_w / 2)
        return x, pad_top + plot_h * (1 - value / top)

    parts = [f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" width="{width}" height="{height}" font-family="Verdana,DejaVu Sans,sans-serif" font-size="11">',
             '<style>.bg{fill:#fff}.grid{stroke:#e3e6ea}.axis,.label{fill:#57606a}.title{fill:#1f2328}'
             '@media (prefers-color-scheme:dark){.bg{fill:#0d1117}.grid{stroke:#30363d}.axis,.label{fill:#8b949e}.title{fill:#e6edf3}}</style>',
             f'<rect class="bg" width="{width}" height="{height}" rx="6"/>']
    latest = rows[-1]
    parts.append(f'<text class="title" x="{pad_left}" y="24" font-size="14" font-weight="bold">Medabots decompilation: '
                 f'{code_percent(latest):.1f}% of code region, {percent(latest, *ALL):.2f}% of whole ROM</text>')
    for tick in range(5):
        value = top * tick / 4
        _, y = point(0, value)
        parts.append(f'<line class="grid" x1="{pad_left}" x2="{width - pad_right}" y1="{y:.1f}" y2="{y:.1f}"/>')
        parts.append(f'<text class="axis" x="{pad_left - 8}" y="{y + 4:.1f}" text-anchor="end">{value:g}%</text>')
    for label_index in sorted({0, count - 1}):
        x, _ = point(label_index, 0)
        parts.append(f'<text class="axis" x="{x:.1f}" y="{height - 16}" text-anchor="middle">{rows[label_index]["date"][:10]}</text>')
    for legend_index, (name, measure_row, color) in enumerate(series):
        coords = [point(index, value) for index, row in enumerate(rows) if (value := measure_row(row)) is not None]
        if not coords:
            continue
        path = " ".join(f"{x:.1f},{y:.1f}" for x, y in coords)
        parts.append(f'<polyline fill="none" stroke="{color}" stroke-width="2" points="{path}"/>')
        x, y = coords[-1]
        parts.append(f'<circle cx="{x:.1f}" cy="{y:.1f}" r="3" fill="{color}"/>')
        lx = width - pad_right - 330 + legend_index * 175
        parts.append(f'<rect x="{lx}" y="{height - 26}" width="10" height="10" fill="{color}"/>'
                     f'<text class="label" x="{lx + 14}" y="{height - 17}">{name}</text>')
    parts.append("</svg>\n")
    return "\n".join(parts)


def summary(row, previous):
    lines = ["## Decompilation progress", "",
             f"**{code_percent(row):.1f}%** of the provisional code region (0x0-0x{int(row['code_end']):X}) is in source; "
             f"**{percent(row, *ALL):.3f}%** of the whole {int(row['total']):,}-byte ROM "
             f"({percent(row, 'game_c'):.3f}% game C, {int(row['functions']):,} functions).", "",
             "| Kind | Bytes | % of ROM | Change |", "| --- | ---: | ---: | ---: |"]
    for name, key in (("Game C", "game_c"), ("Runtime C", "runtime_c"), ("Typed data", "data"), ("Assembly", "asm")):
        delta = int(row[key]) - int(previous[key]) if previous else 0
        lines.append(f"| {name} | {int(row[key]):,} | {percent(row, key):.3f}% | {delta:+,} |")
    if previous and previous.get("code_end"):
        lines.append(f"| Code region | {int(row['code_done']):,} / {int(row['code_end']):,} | {code_percent(row):.1f}% | {code_percent(row) - code_percent(previous):+.2f} pts |")
    lines += ["", "The code region ends at the last code segment and still holds copied data; treat it as provisional.",
              "A matching rebuild is a baseline; remaining bytes are still copied from the ROM with `.incbin`.", ""]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", type=Path, help="Directory holding history.csv; receives progress.svg, badge.svg and progress.json")
    parser.add_argument("--sha", default="local")
    parser.add_argument("--summary", type=Path, help="Append a Markdown report to this file (e.g. $GITHUB_STEP_SUMMARY)")
    args = parser.parse_args()

    row = {"date": datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ"), "sha": args.sha, **measure()}
    rows, previous = [], None
    if args.out:
        args.out.mkdir(parents=True, exist_ok=True)
        rows = [old for old in read_history(args.out / "history.csv") if old["sha"] != args.sha]
        previous = rows[-1] if rows else None
        rows.append({key: str(row[key]) for key in FIELDS})
        write_history(args.out / "history.csv", rows)
        (args.out / "progress.svg").write_text(chart(rows), encoding="utf-8")
        (args.out / "badge.svg").write_text(badge("code decompiled", f"{code_percent(row):.1f}%"), encoding="utf-8")
        (args.out / "progress.json").write_text(json.dumps(rows[-1], indent=2) + "\n", encoding="utf-8")
    report = summary(row, previous)
    if args.summary:
        with args.summary.open("a", encoding="utf-8") as handle:
            handle.write(report)
    print(report)
    print(f"STATUS=Code region {code_percent(row):.1f}% in source; whole ROM {percent(row, *ALL):.2f}%")


if __name__ == "__main__":
    main()
