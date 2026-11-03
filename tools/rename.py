"""Rename functions everywhere they are referenced.

    python tools/rename.py sub_08074DE0=PlaySoundEffect sub_08040CD0=FillTilemapRect
    python tools/rename.py --file names.txt          # one OLD=NEW (or OLD NEW) per line, # comments

Each OLD must be a matching function (a segment whose input section is
`.text.OLD`); NONMATCH functions are refused because their file names carry
the address name. NEW must be a C identifier that occurs nowhere in the
tracked tree yet. Every whole-word occurrence is replaced in tracked text files
(sources, headers, assembly, config, docs and tools), except tests/, whose
fixtures use their own synthetic names. config/segments.json keeps the address
of every function, so a renamed function can still be found by address.
Run tools/build.py afterwards; the ROM must stay byte-identical.
"""

import argparse
import json
import re
import subprocess
import sys

from common import ROOT

IDENTIFIER = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
SKIP_PREFIXES = ("tests/",)


def tracked_text_files():
    names = subprocess.run(["git", "ls-files", "-z"], cwd=ROOT, capture_output=True, check=True).stdout
    for name in names.decode().split("\0"):
        if not name or name.startswith(SKIP_PREFIXES):
            continue
        path = ROOT / name
        try:
            text = path.read_bytes().decode("utf-8")
        except (UnicodeDecodeError, IsADirectoryError, FileNotFoundError):
            continue
        yield path, text


def parse_pairs(items):
    pairs = []
    for item in items:
        item = item.split("#", 1)[0].strip()
        if not item:
            continue
        old, new = re.split(r"\s*=\s*|\s+", item, maxsplit=1)
        pairs.append((old, new.strip()))
    return pairs


def validate(pairs, segments, files):
    functions = {}
    for segment in segments:
        section = segment.get("input_section", "")
        if section.startswith(".text."):
            functions[section[len(".text."):]] = segment
    olds, news = [old for old, _ in pairs], [new for _, new in pairs]
    errors = []
    for duplicates, label in ((olds, "renamed twice"), (news, "used twice")):
        errors += [f"{name}: {label}" for name in {n for n in duplicates if duplicates.count(n) > 1}]
    corpus = "\n".join(text for _, text in files)
    for old, new in pairs:
        segment = functions.get(old)
        if segment is None:
            errors.append(f"{old}: no segment has input section .text.{old}")
        elif segment.get("nonmatching"):
            errors.append(f"{old}: NONMATCH function (its files are named after it); match it first")
        if not IDENTIFIER.match(new):
            errors.append(f"{new}: not a C identifier")
        elif new in olds or re.search(rf"\b{re.escape(new)}\b", corpus):
            errors.append(f"{new}: already used in the tree")
    return errors


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("pairs", nargs="*", help="OLD=NEW")
    parser.add_argument("--file", help="File with one OLD=NEW pair per line")
    parser.add_argument("--dry-run", action="store_true", help="Report the files that would change")
    args = parser.parse_args()
    items = list(args.pairs)
    if args.file:
        items += open(args.file, encoding="utf-8").read().splitlines()
    pairs = parse_pairs(items)
    if not pairs:
        parser.error("nothing to rename")

    segments = json.loads((ROOT / "config" / "segments.json").read_text(encoding="utf-8"))
    files = list(tracked_text_files())
    errors = validate(pairs, segments, files)
    if errors:
        raise SystemExit("Refused:\n  " + "\n  ".join(errors))

    mapping = dict(pairs)
    pattern = re.compile(r"\b(" + "|".join(map(re.escape, mapping)) + r")\b")
    changed = 0
    for path, text in files:
        new_text = pattern.sub(lambda m: mapping[m.group(1)], text)
        if new_text != text:
            changed += 1
            if args.dry_run:
                print(path.relative_to(ROOT))
            else:
                path.write_bytes(new_text.encode("utf-8"))
    print(f"{'Would rename' if args.dry_run else 'Renamed'} {len(pairs)} functions in {changed} files.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
