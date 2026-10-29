"""Derive C for unsolved functions from accepted twins with the same instruction shape.

Game code repeats itself: per-slot handlers and state steps that differ only in
constants, call targets or globals. For every unsolved harvest function whose
instruction sequence (registers and mnemonics, immediates ignored) equals an
accepted function's, this copies the twin's C and substitutes what differs:
immediates and literal-pool constants by value, call targets and global
addresses by symbol name. The candidate is compiled with the twin's compiler
profile; a byte-exact, -Werror-clean result is written to build/m2c/<name>.c
and recorded in build/m2c/manual_solved.json for tools/m2c_integrate.py.

    python tools/clone_transfer.py

Run it after each integration: newly accepted functions become twins for the
remaining members of their family.
"""

import argparse
import collections
import contextlib
import io
import json
import re
import subprocess
import sys

from common import ROOT, find_rom
from c_source import function_definition

sys.path.insert(0, str(ROOT / "tools" / "python"))
OUTPUT = ROOT / "build" / "m2c"
MANUAL = OUTPUT / "manual_solved.json"
IMMEDIATE = re.compile(r"#(-?(?:0x[0-9a-f]+|\d+))")


def shape(code):
    """Instruction sequence with immediates and pool offsets erased."""
    return tuple(f"{code[a].mnemonic} {IMMEDIATE.sub('#', code[a].op_str)}" for a in sorted(code))


def describe(data, code, start, symbols, fold_constants=False):
    """Per instruction: immediates, the loaded literal or the call target, as comparable values."""
    from m2c_candidate import word
    values = []
    addresses = sorted(code)
    for address in addresses:
        instruction = code[address]
        pool = re.fullmatch(r"(r\d+), \[pc(?:, #(0x[0-9a-f]+|\d+))?\]", instruction.op_str)
        if instruction.mnemonic == "ldr" and pool:
            literal = word(data, ((address + 4) & ~3) + int(pool.group(2) or "0", 0))
            values.append(("literal", literal))
        elif instruction.mnemonic == "bl":
            values.append(("call", int(instruction.op_str[1:], 0)))
        elif instruction.mnemonic.startswith("b") and instruction.op_str.startswith("#"):
            values.append(("branch", int(instruction.op_str[1:], 0) - start))
        else:
            values.append(("imm", tuple(int(v, 0) for v in IMMEDIATE.findall(instruction.op_str))))
    if fold_constants:
        for index, address in enumerate(addresses[:-1]):
            instruction, next_instruction = code[address], code[addresses[index + 1]]
            move = re.fullmatch(r"(r\d+), #(0x[0-9a-f]+|\d+)", instruction.op_str)
            shift = re.fullmatch(r"(r\d+), (r\d+), #(0x[0-9a-f]+|\d+)", next_instruction.op_str)
            if (instruction.mnemonic == "movs" and next_instruction.mnemonic == "lsls"
                    and addresses[index + 1] == address + 2 and move and shift
                    and move.group(1) == shift.group(1) == shift.group(2)):
                values[index] = ("imm", (int(move.group(2), 0) << int(shift.group(3), 0),))
                values[index + 1] = ("imm", ())
    return values


def number_pattern(value):
    """C spellings of an integer literal (decimal or hex, optional U suffix)."""
    spellings = {str(value), hex(value), f"0x{value:X}"}
    return r"(?<![\w.])(?:" + "|".join(re.escape(s) for s in sorted(spellings, key=len, reverse=True)) + r")[uU]?(?![\w.])"


def substitute(text, twin_values, target_values, symbols):
    """Apply the differences between twin and target to the twin's C, or None if impossible."""
    numbers, names = {}, {}
    for (kind, twin), (_, target) in zip(twin_values, target_values):
        if twin == target or kind == "branch":
            if kind == "branch" and twin != target:
                return None  # different control flow layout
            continue
        if kind == "imm":
            for a, b in zip(twin, target):
                if a != b and numbers.setdefault(a, b) != b:
                    return None
        else:
            twin_name = symbols.exact(twin & ~1) if twin >= 0x02000000 else None
            target_name = symbols.exact(target & ~1) if target >= 0x02000000 else None
            if twin_name and not target_name and 0x02000000 <= target < 0x0A000000 and not target & 1:
                # Same placeholder names m2c_candidate gives unknown addresses.
                target_name = f"sub_{target:08X}" if kind == "call" else f"D_{target:08X}"
            if twin_name and target_name:
                if names.setdefault(twin_name, target_name) != target_name:
                    return None
            elif numbers.setdefault(twin, target) != target:
                return None
    declarations = []
    for twin_name, target_name in names.items():
        declared_here = re.search(r"^extern [^\n]*\b" + re.escape(twin_name) + r"\b", text, re.M)
        text = re.sub(r"\b" + re.escape(twin_name) + r"\b", target_name, text)
        if not declared_here and re.fullmatch(r"(?:D|sub)_[0-9A-F]{8}", target_name):
            # The twin's declaration comes from a header; give the placeholder its type.
            declarations.append(f"extern __typeof__({twin_name}) {target_name};")
    text = "\n".join(declarations) + ("\n" if declarations else "") + text
    # A changed member offset may be implied by a private layout's padding,
    # rather than written as a second literal in the body. Replace spellings
    # that exist and let the complete byte comparison validate the result.
    numbers = {twin: target for twin, target in numbers.items()
               if re.search(number_pattern(twin), text)}
    # Substitute in one pass: a mapping 1 -> 2, 2 -> 3 must leave the former
    # 1 as 2, rather than applying the second replacement to it again.
    if numbers:
        pattern = "|".join(number_pattern(twin) for twin in numbers)
        def replace_number(match):
            target = numbers[int(match.group(0).rstrip("uU"), 0)]
            return f"0x{target:X}" if target > 9 else str(target)
        text = re.sub(pattern, replace_number, text)
    return text


def file_scope_types(text):
    """Keep local type declarations needed by a copied function.

    A twin may use an observed partial struct defined in its .c file rather
    than a shared header. Do not copy variables or other function bodies.
    """
    declarations = []
    # Comments and strings can contain braces or semicolons. Replace them
    # with spaces while preserving offsets and line boundaries.
    masked = re.sub(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'",
                    lambda m: re.sub(r'[^\n]', ' ', m.group(0)), text, flags=re.S)
    pattern = re.compile(r'^(?:typedef\b|(?:struct|union|enum)\s+\w+\s*\{)', re.M)
    for match in pattern.finditer(masked):
        # Ignore declarations inside a function or another type.
        prefix = masked[:match.start()]
        if prefix.count('{') != prefix.count('}'):
            continue
        depth = 0
        for position in range(match.start(), len(masked)):
            char = masked[position]
            depth += char == '{'
            depth -= char == '}'
            if char == ';' and depth == 0:
                declaration = text[match.start():position + 1]
                if declaration.startswith('typedef') or re.search(r'\}\s*;$', declaration):
                    declarations.append(declaration)
                break
    return declarations


def function_text(source, name):
    """File-local types, externs and the definition of `name`."""
    text = (ROOT / source).read_text(encoding="utf-8")
    try:
        definition = function_definition(text, name)
    except ValueError:
        return None
    externs = [line for line in text.splitlines() if line.startswith("extern ")]
    return "\n".join(file_scope_types(text) + externs) + "\n\n" + definition + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--include-queued", action="store_true",
                        help="Also try drafts in old hand/permuter queues; use only when no worker owns them")
    args = parser.parse_args()
    from m2c_candidate import BASE, Symbols, decode, generate, try_match
    from compiler_agbcc import compile_source
    from match import batch_session
    session = batch_session()
    data = find_rom().read_bytes()
    symbols = Symbols()
    segments = json.loads((ROOT / "config" / "segments.json").read_text(encoding="utf-8"))
    twins = collections.defaultdict(list)
    for segment in segments:
        section = segment.get("input_section", "")
        if segment["kind"] != "c" or segment.get("compiler") != "agbcc" or segment.get("category") or not section.startswith(".text."):
            continue
        start, end = BASE + int(segment["start"], 0), BASE + int(segment["end"], 0)
        try:
            code, _, _, _ = decode(data, start, end)
        except SystemExit:
            continue
        twins[shape(code)].append((section[len(".text."):], segment, start, describe(data, code, start, symbols),
                                   describe(data, code, start, symbols, fold_constants=True)))
    rows = json.loads((OUTPUT / "harvest.json").read_text(encoding="utf-8"))
    done = {int(s["start"], 0) for s in segments}
    solved = json.loads(MANUAL.read_text(encoding="utf-8")) if MANUAL.exists() else []
    skip = {entry["name"] for entry in solved}
    for queue in (() if args.include_queued else ("permute_queue.json", "hand_queue.json")):
        # Preserve active workers' drafts by default; root can reclaim stale queues explicitly.
        if (OUTPUT / queue).exists():
            skip |= {entry["name"] for entry in json.loads((OUTPUT / queue).read_text(encoding="utf-8"))}
    results = []
    for row in rows:
        name = f"sub_{row['start']}"
        if row["exact"] or "end" not in row or name in skip or (int(row["start"], 16) - BASE) in done:
            continue
        start, end = int(row["start"], 16), int(row["end"], 16)
        try:
            code, _, _, _ = decode(data, start, end)
        except SystemExit:
            continue
        candidates = twins.get(shape(code))
        if not candidates:
            continue
        target_values = describe(data, code, start, symbols)
        folded_target_values = describe(data, code, start, symbols, fold_constants=True)
        for twin_name, segment, twin_start, twin_values, folded_twin_values in candidates:
            text = function_text(segment["source"], twin_name)
            if text is None:
                continue
            cflags = segment.get("cflags", [])
            sources = list(dict.fromkeys(filter(None, [substitute(text, twin_values, target_values, symbols),
                substitute(text, folded_twin_values, folded_target_values, symbols)])))
            accepted_text = None
            for variant in sources:
                variant = re.sub(r"\b" + re.escape(twin_name) + r"\b", name, variant)
                try:
                    with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
                        _, _, _, assembly, _ = generate(data, symbols, start, end, name)
                        matched, _, _ = try_match(name, start, end, assembly, variant, cflags, session=session)
                        if not matched:
                            continue
                        compile_source(OUTPUT / name / "candidate.c", OUTPUT / name / "match" / "strict.o", cflags)
                except (subprocess.CalledProcessError, ValueError, OSError, KeyError, SystemExit):
                    continue
                accepted_text = variant
                break
            if accepted_text is None:
                continue
            (OUTPUT / f"{name}.c").write_text(accepted_text, encoding="utf-8")
            results.append({"name": name, "start": f"0x{start - BASE:X}", "end": f"0x{end - BASE:X}", "cflags": cflags})
            print(f"{name} from {twin_name}", flush=True)
            break
    solved = json.loads(MANUAL.read_text(encoding="utf-8")) if MANUAL.exists() else []
    names = {result["name"] for result in results}
    solved = [entry for entry in solved if entry["name"] not in names] + results
    MANUAL.write_text(json.dumps(solved, indent=2) + "\n", encoding="utf-8")
    print(f"\n{len(results)} functions derived from twins; {len(solved)} await tools/m2c_integrate.py")


if __name__ == "__main__":
    main()
