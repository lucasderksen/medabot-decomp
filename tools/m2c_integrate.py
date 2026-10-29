"""Integrate exact m2c harvest results into production source (root only).

Reads build/m2c/harvest.json, keeps exact drafts outside --exclude ranges, and
rewrites them as ordinary C: placeholder D_XXXXXXXX globals become
gUnknown_XXXXXXXX with addresses in config/symbols.json, m2c's unknown types
become fixed-width types, and drafts still needing m2c macros are skipped.
Functions go into new src/m2c_harvest_<n>.c files (one compiler profile per
file, no conflicting declarations) and config/segments.json gains their
entries; existing harvest files are never rewritten. Run tools/build.py
afterwards. If it fails, discard the new files and config changes
(git checkout config; remove the new file) and rerun with --drop START.

    python tools/m2c_integrate.py --exclude 0x0801D5A8-0x0801DAEC
"""

import argparse
import json
import re

from common import ROOT, load_segments
from clone_transfer import file_scope_types

SEGMENTS = ROOT / "config" / "segments.json"
SYMBOLS = ROOT / "config" / "symbols.json"
HARVEST = ROOT / "build" / "m2c" / "harvest.json"
SOLVED = ROOT / "build" / "permuter" / "solved.json"  # drafts fixed by tools/permute.py, byte-verified
MANUAL = ROOT / "build" / "m2c" / "manual_solved.json"  # drafts finished by hand (tools/accept_draft.py)
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "void", "u8", "u16", "u32", "s8", "s16", "s32", "volatile", "const"}
TYPES = {"M2C_UNK": "s32", "M2C_UNK8": "s8", "M2C_UNK16": "s16", "M2C_UNK32": "s32"}


def parse_range(text):
    start, end = (int(part, 0) for part in text.split("-"))
    return start & 0xFFFFFF, end & 0xFFFFFF


def split_draft(text, name):
    """Return (declarations, function body, other top-level lines) from m2c output."""
    # Keep the opening brace on the signature line and the body on the next
    # line, including compact accepted definitions containing nested blocks.
    text = re.sub(r"(\b" + re.escape(name) + r"\([^;{]*\))\s*\{", r"\1 {\n", text, count=1)
    lines = text.strip().splitlines()
    index = next(i for i, line in enumerate(lines) if re.search(rf"\b{name}\(", line) and line.rstrip().endswith("{"))
    header = [line.rstrip() for line in lines[:index] if line.strip()]
    declarations = [re.sub(r"\s*/\* extern \*/$", "", line.strip()) for line in header if line.lstrip().startswith("extern") or "/* extern */" in line]
    other = [line for line in header if not (line.lstrip().startswith("extern") or "/* extern */" in line)]
    # m2c suggests inferred layouts as anonymous `struct { ... };` blocks. They
    # declare nothing the function can use, so they are dropped.
    text_other = "\n".join(other)
    text_other = re.sub(r"^struct \{.*?^\};[^\n]*$", "", text_other, flags=re.S | re.M)
    other = [line for line in text_other.splitlines() if line.strip()]
    return declarations, "\n".join(lines[index:]).strip(), other


def expand_fields(text):
    """Rewrite M2C_FIELD(expr, type *, offset) as the plain cast it stands for."""
    while (index := text.find("M2C_FIELD(")) >= 0:
        depth, position, arguments, current = 0, index + len("M2C_FIELD("), [], ""
        while True:
            char = text[position]
            if char == "," and depth == 0:
                arguments.append(current.strip())
                current = ""
            elif char == ")" and depth == 0:
                arguments.append(current.strip())
                break
            else:
                depth += char in "(["
                depth -= char in ")]"
                current += char
            position += 1
        expr, type_pointer, offset = arguments
        text = text[:index] + f"(*({type_pointer})((u8 *)({expr}) + {offset}))" + text[position + 1:]
    return text


def normalize(text):
    text = expand_fields(text)
    text = re.sub(r"\bD_([0-9A-F]{8})\b", r"gUnknown_\1", text)
    for old, new in TYPES.items():
        text = re.sub(rf"\b{old}\b", new, text)
    return text


def declared_name(declaration):
    declaration = re.sub(r"__typeof__\([^()]*\)", "T", declaration)  # clone transfer's typed placeholders
    # `extern T name asm("symbol");` names `name`, not `asm` (otherwise every
    # asm-label view collapses into one "asm" declaration and the rest are dropped).
    declaration = re.sub(r"\basm\s*\(\s*\"[^\"]*\"\s*\)", "", declaration)
    # Function pointers and arrays of them: `void (*name[])(void);`
    pointer = re.search(r"\(\s*\*\s*(?:(?:const|volatile|__restrict|__restrict__)\s+)*(\w+)", declaration)
    if pointer:
        return pointer.group(1)
    match = re.search(r"\b(\w+)\s*(?:\(|\[|;)", declaration)
    return match.group(1) if match else None


def declared_names(declaration):
    """Names in one extern declaration, ignoring commas inside declarators."""
    declaration = re.sub(r"/\*.*?\*/", "", declaration)
    parts, start, depth = [], 0, 0
    for index, char in enumerate(declaration):
        if char in "([{":
            depth += 1
        elif char in ")]}":
            depth -= 1
        elif char in ",;" and depth == 0:
            parts.append(declaration[start:index])
            start = index + 1
    parts.append(declaration[start:])
    return [name for part in parts if part.strip() and (name := declared_name(part.rstrip("; ") + ";"))]


def private_types(other):
    """Return named type definitions, rejecting other top-level draft output."""
    text = "\n".join(other)
    declarations = file_scope_types(text)
    remainder = text
    names = {}
    for declaration in declarations:
        remainder = remainder.replace(declaration, "", 1)
        tags = [f"{kind} {tag}" for kind, tag in re.findall(r"\b(struct|union|enum)\s+(\w+)\s*\{", declaration)]
        if declaration.startswith("typedef"):
            alias = re.search(r"\b(\w+)\s*;$", declaration)
            # A callback typedef ends in its argument list, not the alias.
            alias_name = alias.group(1) if alias else declared_name(declaration)
            if not alias_name:
                return None
            tags.append(f"typedef {alias_name}")
        for tag in tags:
            if tag in names and names[tag] != declaration:
                return None
            names[tag] = declaration
    return names if not remainder.strip() else None


def headers_for(used):
    """global.h plus every header declaring an identifier the source uses."""
    chosen = ["global.h"]
    for header in sorted((ROOT / "include").glob("*.h")):
        text = header.read_text(encoding="utf-8")
        declared = set(re.findall(r"\b(\w+)\s*\(", text)) | set(re.findall(r"\b(\w+)\s*(?:\[[^\]]*\]\s*)*;", text))
        declared |= set(re.findall(r"\b(?:struct|union|enum)\s+(\w+)", text)) | set(re.findall(r"}\s*(\w+)\s*;", text))
        if header.name != "global.h" and used & (declared - KEYWORDS):
            chosen.append(header.name)
    return chosen


def latest_exact_rows(rows):
    """Manual refinements take precedence over earlier harvest/permuter results."""
    latest = {}
    for row in rows:
        if row.get("exact"):
            latest[int(row["start"], 16)] = row
    return list(latest.values())


def collect_symbols(files, known_names):
    """Carry declared match-spec aliases, preserving data addresses exactly."""
    defined = {function['name'] for unit in files for function in unit['functions']}
    result = {}
    for unit in files:
        for function in unit['functions']:
            for declaration in function['declarations']:
                for name in declared_names(declaration):
                    if name in known_names or name in defined:
                        continue
                    entry = function.get('symbols', {}).get(name)
                    if entry is None:
                        found = re.fullmatch(r'(?:gUnknown|sub)_([0-9A-F]{8})', name)
                        if not found:
                            continue
                        address = int(found.group(1), 16)
                        entry = {'address': f'0x{address | 1:08X}', 'kind': 'thumb_function'} if name.startswith('sub_') else f'0x{address:08X}'
                    address = int(entry['address'] if isinstance(entry, dict) else entry, 0)
                    if not 0 <= address <= 0xFFFFFFFF:
                        raise ValueError(f'Invalid match-spec address for {name}')
                    if isinstance(entry, dict) and entry.get('kind') not in ('data', 'thumb_function', 'arm_function'):
                        raise ValueError(f'Invalid match-spec symbol kind for {name}')
                    if name in result and result[name] != entry:
                        raise ValueError(f'Conflicting match-spec aliases for {name}')
                    result[name] = entry
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--exclude", action="append", default=[], help="Skip ROM range START-END (assigned to another agent)")
    parser.add_argument("--drop", action="append", default=[], help="Skip function START (it broke the build)")
    parser.add_argument("--prefix", default="m2c_harvest",
                        help="New source file stem, e.g. m2c_lean_a for a worker; keeps parallel worktrees from colliding")
    args = parser.parse_args()

    excluded = [parse_range(text) for text in args.exclude]
    dropped = {int(text, 0) & 0xFFFFFF for text in args.drop}
    # Only add: earlier harvest files are accepted source and stay as they are.
    segments = json.loads(SEGMENTS.read_text(encoding="utf-8"))
    occupied = [(segment["start"], segment["end"]) for segment in load_segments(entries=segments)]
    symbols = json.loads(SYMBOLS.read_text(encoding="utf-8"))
    # Names already defined somewhere: absolute symbols, or functions in source.
    known_names = set(symbols) | {entry["name"] for entry in segments}
    known_names |= {entry["input_section"][len(".text."):] for entry in segments if entry.get("input_section", "").startswith(".text.")}

    accepted, skipped = [], []
    rows = json.loads(HARVEST.read_text(encoding="utf-8")) if HARVEST.exists() else []
    for solved_path in (SOLVED, MANUAL):
        if not solved_path.exists():
            continue
        for entry in json.loads(solved_path.read_text(encoding="utf-8")):
            base = 0x08000000
            rows.append({"exact": True, "cflags": entry["cflags"], "start": f"{base + int(entry['start'], 0):08X}",
                         "end": f"{base + int(entry['end'], 0):08X}", "name": entry.get("name")})
    for row in latest_exact_rows(rows):
        start, end = int(row["start"], 16) & 0xFFFFFF, int(row["end"], 16) & 0xFFFFFF
        # Accepted drafts keep their own name (e.g. CopyTilemap); harvest rows are sub_ADDR.
        name = row.get("name") or f"sub_{int(row['start'], 16):08X}"
        reason = None
        if start in dropped:
            reason = "dropped after build failure"
        elif any(s < end and start < e for s, e in excluded):
            reason = "inside an assigned range"
        elif any(s < end and start < e for s, e in occupied):
            reason = "already integrated"
        if reason:
            skipped.append((name, reason))
            continue
        draft_path = ROOT / "build" / "m2c" / f"{name}.c"
        if not draft_path.exists():
            skipped.append((name, "draft file missing"))
            continue
        draft = draft_path.read_text(encoding="utf-8")
        declarations, body, other = split_draft(normalize(draft), name)
        if reason is None and "M2C_" in body + "".join(declarations):
            reason = "needs m2c macros"
        types = private_types(other)
        if reason is None and types is None:
            reason = "unsupported top-level draft declarations"
        if reason:
            skipped.append((name, reason))
            continue
        spec_path = ROOT / 'build' / 'm2c' / name / 'spec.json'
        spec = json.loads(spec_path.read_text(encoding='utf-8')) if spec_path.exists() else {}
        draft_symbols = {normalize(symbol): entry for symbol, entry in spec.get('symbols', {}).items()}
        accepted.append(dict(name=name, start=start, end=end, cflags=row["cflags"], declarations=declarations, types=types, body=body, symbols=draft_symbols,
                             bytes=end - start))
        occupied.append((start, end))

    # Pack functions into files: one compiler profile each, no conflicting declarations.
    files = []
    for function in sorted(accepted, key=lambda f: f["start"]):
        names = {name: d for d in function["declarations"] for name in declared_names(d)}
        for unit in files:
            if unit["cflags"] != function["cflags"] or function["name"] in unit["declared"]:
                continue
            if any(unit["declared"].get(n, d) != d for n, d in names.items()) or any(n in unit["defined"] for n in names):
                continue
            if any(unit["types"].get(n, d) != d for n, d in function["types"].items()):
                continue
            break
        else:
            unit = {"cflags": function["cflags"], "declared": {}, "types": {}, "defined": set(), "functions": []}
            files.append(unit)
        unit["declared"].update(names)
        unit["types"].update(function["types"])
        unit["defined"].add(function["name"])
        unit["functions"].append(function)

    first_index = 1 + max([int(path.stem.rsplit("_", 1)[1]) for path in (ROOT / "src").glob(f"{args.prefix}_*.c")
                           if path.stem.rsplit("_", 1)[1].isdigit()], default=-1)
    # Check alias conflicts before writing any source or configuration files.
    new_symbols = collect_symbols(files, known_names)
    for index, unit in enumerate(files, first_index):
        source = f"src/{args.prefix}_{index}.c"
        defined = unit["defined"]
        prototypes = [f"{f['body'].splitlines()[0].rstrip(' {')};" for f in unit["functions"]]
        lines = ["/*", " * Byte-verified functions derived from m2c drafts, source rewrites and clones.",
                 " * Names and types are provisional;",
                 " * see docs/M2C.md.", " */", ""]
        used = set(re.findall(r"\b[A-Za-z_]\w*\b", "\n".join(list(unit["types"].values()) + [f["body"] for f in unit["functions"]])))
        lines += [f'#include "{header}"' for header in headers_for(used)] + [""]
        lines += list(dict.fromkeys(unit["types"].values())) + ([""] if unit["types"] else [])
        lines += [d for d in sorted(set(unit["declared"].values())) if set(declared_names(d)) - defined]
        lines += [""] + prototypes + [""]
        for function in unit["functions"]:
            lines += [function["body"], ""]
            segments.append({"name": function["name"], "start": f"0x{function['start']:06X}", "end": f"0x{function['end']:06X}",
                             "kind": "c", "compiler": "agbcc", "cflags": function["cflags"], "source": source,
                             "input_section": f".text.{function['name']}",
                             "description": "byte-verified m2c-derived candidate; names and types provisional"})
        (ROOT / source).write_text("\n".join(lines).rstrip() + "\n", encoding="utf-8")

    segments.sort(key=lambda entry: int(entry["start"], 0))
    SEGMENTS.write_text(json.dumps(segments, indent=2) + "\n", encoding="utf-8")
    symbols.update(new_symbols)
    # Functions now defined in C must not also be absolute symbols.
    for function in accepted:
        symbols.pop(function["name"], None)
    SYMBOLS.write_text(json.dumps(symbols, indent=2) + "\n", encoding="utf-8")
    total = sum(f["bytes"] for f in accepted)
    print(f"Integrated {len(accepted)} functions ({total:,} bytes) into {len(files)} files; {len(new_symbols)} new symbols.")
    for name, reason in skipped:
        print(f"  skipped {name}: {reason}")


if __name__ == "__main__":
    main()
