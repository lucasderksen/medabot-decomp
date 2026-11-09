"""Rename functions and data symbols everywhere they are referenced.

    python tools/rename.py sub_0801234C=DescriptiveName [OLD=NEW ...]
    python tools/rename.py --file names.txt          # one OLD=NEW (or OLD NEW) per line, # comments
    python tools/rename.py --alias sub_0807CEC8=__udivsi3   # (already applied)

With --alias, OLD is an address alias in config/symbols.json for a routine
that already has a name (libgcc entry points): references move to NEW and the
alias entry is removed. No file may use both names, because their declarations
may disagree.

Each OLD must be a matching function (a segment whose input section is
`.text.OLD`) or a RAM/ROM data symbol listed in config/symbols.json, whose
address stays recorded there under the new name. NONMATCH functions are
refused because their file names carry the address name. NEW must be a C
identifier that occurs nowhere in the tracked tree yet. Every whole-word
occurrence is replaced in tracked text files (sources, headers, assembly,
config, docs and tools), except tests/, whose fixtures use their own synthetic
names. config/segments.json keeps the address of every function, so a renamed
function can still be found by address.
Run tools/build.py afterwards; the ROM must stay byte-identical.
"""

import argparse
import json
import re
import subprocess
import sys

from common import ROOT, tool

IDENTIFIER = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
# tests/ fixtures use synthetic names; this file's own examples must not be rewritten.
SKIP_PREFIXES = ("tests/", "tools/rename.py")


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


def validate(pairs, segments, files, symbols=None):
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
        data_symbol = isinstance((symbols or {}).get(old), str)
        if segment is None and not data_symbol:
            errors.append(f"{old}: no segment has input section .text.{old}, and no data symbol in config/symbols.json")
        elif segment is not None and segment.get("nonmatching"):
            errors.append(f"{old}: NONMATCH function (its files are named after it); match it first")
        if not IDENTIFIER.match(new):
            errors.append(f"{new}: not a C identifier")
        elif new in olds or re.search(rf"\b{re.escape(new)}\b", corpus):
            errors.append(f"{new}: already used in the tree")
    return errors


def elf_addresses():
    """Symbol addresses (Thumb bit cleared) from the last full build."""
    elf = ROOT / "build" / "medabots.elf"
    if not elf.exists():
        raise SystemExit("--alias needs build/medabots.elf; run tools/build.py first.")
    output = subprocess.run([tool("nm"), str(elf)], capture_output=True, text=True, check=True).stdout
    return {parts[2]: int(parts[0], 16) & ~1 for parts in (line.split() for line in output.splitlines()) if len(parts) == 3}


def validate_aliases(pairs, symbols, files, addresses):
    errors = []
    for old, new in pairs:
        entry = symbols.get(old)
        if not (isinstance(entry, dict) and entry.get("kind") == "thumb_function"):
            errors.append(f"{old}: not a thumb_function alias in config/symbols.json")
        if new in symbols:
            errors.append(f"{new}: also defined in config/symbols.json")
        if new not in addresses:
            errors.append(f"{new}: not a symbol of build/medabots.elf")
        elif isinstance(entry, dict) and int(entry["address"], 16) & ~1 != addresses[new]:
            errors.append(f"{old}: alias address {entry['address']} is not the address of {new}")
        # Declarations of the two names may disagree, so no source may use both.
        both = [str(path.relative_to(ROOT)) for path, text in files
                if path.relative_to(ROOT).parts[0] in ("src", "include", "asm")
                and re.search(rf"\b{re.escape(old)}\b", text) and re.search(rf"\b{re.escape(new)}\b", text)]
        if both:
            errors.append(f"{old}/{new}: both used in {', '.join(both)}")
    return errors


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("pairs", nargs="*", help="OLD=NEW")
    parser.add_argument("--file", help="File with one OLD=NEW pair per line")
    parser.add_argument("--alias", action="store_true", help="OLD is a symbols.json alias of the existing NEW")
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
    symbols_path = ROOT / "config" / "symbols.json"
    symbols = json.loads(symbols_path.read_text(encoding="utf-8"))
    errors = validate_aliases(pairs, symbols, files, elf_addresses()) if args.alias else validate(pairs, segments, files, symbols)
    if errors:
        raise SystemExit("Refused:\n  " + "\n  ".join(errors))

    mapping = dict(pairs)
    if args.alias:
        # Drop the alias entries first so the whole-word pass below does not
        # turn them into a second definition of NEW.
        for old, _ in pairs:
            del symbols[old]
        if not args.dry_run:
            symbols_path.write_text(json.dumps(symbols, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
        files = [(path, symbols_path.read_text(encoding="utf-8") if path == symbols_path else text)
                 for path, text in files]
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
    print(f"{'Would rename' if args.dry_run else 'Renamed'} {len(pairs)} symbols in {changed} files.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
