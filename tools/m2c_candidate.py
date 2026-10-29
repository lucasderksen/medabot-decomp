"""Generate a first-draft C candidate for one Thumb function with m2c.

The function is decoded from the reference ROM by following its control flow
from the entry point, so literal pools and agbcc switch tables are emitted as
data instead of bogus instructions. Calls and literal-pool addresses are named
from the latest matching build/medabots.elf; unknown RAM/ROM addresses become
D_XXXXXXXX (data) or sub_XXXXXXXX (Thumb code) symbols. The result is a draft:
compile and compare it with tools/match.py before trusting anything.

    python tools/m2c_candidate.py 0x0801D5A8
    python tools/m2c_candidate.py 0x0801D5A8 --end 0x0801D61C --no-context

Unrecognized options are passed to m2c. Outputs build/m2c/<name>.s (unchanged
instruction reference) and build/m2c/<name>.c. Optional long-branch/stack
corrections use a separate <name>.m2c.s input and record their original sites.
"""

import argparse
import bisect
import json
import os
import re
import subprocess
import sys

from common import ROOT, find_rom, rom_config, tool

sys.path.insert(0, str(ROOT / "tools" / "python"))
M2C = ROOT / "tools" / "downloads" / "m2c"
OUTPUT = ROOT / "build" / "m2c"
BASE = int(rom_config()["rom_base"], 0)


class Symbols:
    """Address-sorted names from the matching ELF, used for calls and pools."""

    def __init__(self, listing=None):
        if listing is None:
            elf = ROOT / "build" / "medabots.elf"
            if not elf.exists():
                raise SystemExit("Run python tools/build.py first; symbols come from build/medabots.elf.")
            listing = subprocess.run([tool("nm"), "-S", "--defined-only", elf], capture_output=True, text=True, check=True).stdout
        configured = json.loads((ROOT / "config" / "symbols.json").read_text(encoding="utf-8"))
        thumb_names = {name for name, value in configured.items()
                       if isinstance(value, dict) and value.get("kind") == "thumb_function"}
        entries = {}
        self.function_addresses = set()
        for line in listing.splitlines():
            parts = line.split()
            if len(parts) < 3 or parts[-1].startswith(("$", ".", "__")) or "." in parts[-1]:
                continue
            address, name = int(parts[0], 16), parts[-1]
            is_function = parts[-2] in ("t", "T") or name in thumb_names or (
                parts[-2] in ("a", "A") and name.startswith("sub_"))
            if is_function:
                address &= ~1
                self.function_addresses.add(address)
            size = int(parts[1], 16) if len(parts) == 4 else 0
            if address not in entries or (entries[address][1] == 0 and size):
                entries[address] = (name, size)
        self.addresses = sorted(entries)
        self.entries = entries

    def exact(self, address):
        key = address & ~1 if self.is_function(address) else address
        entry = self.entries.get(key)
        return entry[0] if entry else None

    def is_function(self, address):
        if address in self.entries:
            return address in self.function_addresses
        normalized = address & ~1
        if normalized in self.function_addresses:
            return True
        index = bisect.bisect_right(self.addresses, address) - 1
        if index < 0:
            return False
        start = self.addresses[index]
        return start in self.function_addresses and address < start + self.entries[start][1]

    def containing(self, address):
        index = bisect.bisect_right(self.addresses, address) - 1
        if index < 0:
            return None
        start = self.addresses[index]
        name, size = self.entries[start]
        if start == address:
            return name
        if start < address < start + size:
            return f"{name}+0x{address - start:X}"
        return None


def is_memory(value):
    return 0x02000000 <= value < 0x04000000 or BASE <= value < BASE + 0x02000000


class LongBranchInstruction:
    """An input-only branch view of a reviewed BL; retain its four ROM bytes."""

    mnemonic = "b"

    def __init__(self, original):
        self.original = original

    def __getattr__(self, name):
        return getattr(self.original, name)


class StackAdjustmentInstruction:
    """Input-only immediate view of an exactly resolved register SP addition."""

    def __init__(self, original, delta):
        self.original = original
        self.mnemonic = 'sub' if delta < 0 else 'add'
        self.op_str = f'sp, #0x{abs(delta):X}'

    def __getattr__(self, name):
        return getattr(self.original, name)


def resolve_register_stack_adjustments(data, code, pools, targets):
    """Resolve a small set of literal operations within one straight-line block.

    Never carry constants across a call, branch, join, gap or unknown register
    write. Only non-flag-setting `add sp, rN` receives an input-only immediate
    view; the canonical instructions and other uses of rN remain unchanged.
    """
    result, records, values = dict(code), [], {}
    following = None
    for address, instruction in sorted(code.items()):
        if address != following or address in targets:
            values.clear()
        mnemonic, operands = instruction.mnemonic, instruction.op_str
        register_add = re.fullmatch(r'sp, (r\d+)', operands)
        if mnemonic == 'add' and register_add and register_add[1] in values:
            value = values[register_add[1]]
            delta = value if value < 0x80000000 else value - 0x100000000
            if delta and delta % 4 == 0:
                result[address] = StackAdjustmentInstruction(instruction, delta)
                records.append({'address': f'0x{address:08X}', 'register': register_add[1],
                                'delta': delta, 'rom_bytes': bytes(instruction.bytes).hex()})

        constant = None
        move_literal = re.fullmatch(r'(r\d+), #(0x[0-9a-f]+|\d+)', operands)
        move_register = re.fullmatch(r'(r\d+), (r\d+)', operands)
        shift = re.fullmatch(r'(r\d+), (r\d+), #(0x[0-9a-f]+|\d+)', operands)
        pool = re.fullmatch(r'(r\d+), \[pc(?:, #(0x[0-9a-f]+|\d+))?\]', operands)
        if mnemonic in ('mov', 'movs') and move_literal:
            constant = (move_literal[1], int(move_literal[2], 0) & 0xFFFFFFFF)
        elif mnemonic in ('mov', 'movs') and move_register and move_register[2] in values:
            constant = (move_register[1], values[move_register[2]])
        elif mnemonic in ('lsl', 'lsls') and shift and shift[2] in values and 0 <= int(shift[3], 0) < 32:
            constant = (shift[1], (values[shift[2]] << int(shift[3], 0)) & 0xFFFFFFFF)
        elif mnemonic == 'ldr' and pool:
            literal = ((address + 4) & ~3) + int(pool[2] or '0', 0)
            if literal in pools and 0 <= literal - BASE <= len(data) - 4:
                constant = (pool[1], word(data, literal))
        _, written = instruction.regs_access()
        written_names = {instruction.reg_name(register) for register in written}
        for register in written_names:
            values.pop(register, None)
        if constant is not None:
            values[constant[0]] = constant[1]
        if ('pc' in written_names or mnemonic in ('svc', 'swi')
                or (mnemonic.startswith('b') and mnemonic not in ('bic', 'bics'))
                or (mnemonic == 'pop' and 'pc' in operands)):
            values.clear()
        following = address + instruction.size
    return result, records


def decode(data, start, limit, long_branch_targets=()):
    """Follow Thumb control flow; optional targets are manually reviewed BL jumps."""
    import capstone
    long_branch_targets = set(long_branch_targets)
    for target in long_branch_targets:
        if target & 1 or not start <= target < limit:
            raise ValueError(f"Long-branch target {target:08X} must be an even address inside explicit function bounds")
    used_long_branch_targets = set()
    engine = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
    engine.detail = True
    code, pools, tables, targets = {}, set(), {}, set()
    work = [start]
    while work:
        address = work.pop()
        while start <= address < limit and address not in code:
            offset = address - BASE
            instruction = next(engine.disasm(data[offset:offset + 4], address, 1), None)
            if instruction is None:
                raise SystemExit(f"Cannot decode Thumb at {address:08X}; check the bounds and mode.")
            if instruction.mnemonic == "bl" and int(instruction.op_str[1:], 0) in long_branch_targets:
                used_long_branch_targets.add(int(instruction.op_str[1:], 0))
                instruction = LongBranchInstruction(instruction)
            code[address] = instruction
            mnemonic, operands = instruction.mnemonic, instruction.op_str
            following = address + instruction.size
            pool = re.fullmatch(r"(r\d+), \[pc(?:, #(0x[0-9a-f]+|\d+))?\]", operands)
            if mnemonic == "ldr" and pool:
                pools.add(((address + 4) & ~3) + int(pool.group(2) or "0", 0))
            if mnemonic == "bl":
                address = following
                continue
            if mnemonic.startswith("b") and mnemonic not in ("bx", "bic", "bics") and operands.startswith("#"):
                target = int(operands[1:], 0)
                targets.add(target)
                if mnemonic == "b":
                    address = target
                    continue
                work.append(target)
            elif mnemonic == "bx" or (mnemonic == "pop" and "pc" in operands):
                break
            elif mnemonic == "mov" and operands.startswith("pc,"):
                table = jump_table(data, code, address, pools, start, limit)
                tables[table[0]] = table[1]
                targets.update(table[1])
                work.extend(table[1])
                break
            address = following
    unused = long_branch_targets - used_long_branch_targets
    if unused:
        raise ValueError("Long-branch targets have no reachable BL sites: " + ", ".join(f"{a:08X}" for a in sorted(unused)))
    for target in long_branch_targets:
        if any(a < target < a + i.size for a, i in code.items()):
            raise ValueError(f"Long-branch target {target:08X} overlaps a decoded instruction")
    return code, pools, tables, targets


def jump_table(data, code, address, pools, start, limit):
    """Locate the agbcc switch table loaded before `mov pc, rN` and its entry count."""
    previous = sorted(a for a in code if a < address)[-8:]
    count = None
    table = None
    for candidate in reversed(previous):
        instruction = code[candidate]
        compare = re.fullmatch(r"r\d+, #(0x[0-9a-f]+|\d+)", instruction.op_str)
        if count is None and instruction.mnemonic == "cmp" and compare:
            count = int(compare.group(1), 0) + 1
        pool = re.fullmatch(r"r\d+, \[pc(?:, #(0x[0-9a-f]+|\d+))?\]", instruction.op_str)
        if table is None and instruction.mnemonic == "ldr" and pool:
            literal = ((candidate + 4) & ~3) + int(pool.group(1) or "0", 0)
            table = word(data, literal)
    if table is None or not start <= table < limit:
        raise SystemExit(f"Switch at {address:08X}: table not found; pass explicit bounds after inspecting it.")
    entries = []
    while count is None or len(entries) < count:
        target = word(data, table + 4 * len(entries))
        if not start <= target < limit or target & 1:
            break
        entries.append(target)
    return table, entries


def function_end(data, code, pools, tables):
    """End of the decoded function, including zero padding up to 4-byte alignment.

    agbcc aligns every function to 4 bytes, so a function ending on a 2-byte
    boundary is followed by a zero halfword that its section (and every accepted
    segment) includes.
    """
    end = max([a + i.size for a, i in code.items()] + [p + 4 for p in pools] +
              [t + 4 * len(e) for t, e in tables.items()])
    if end % 4 and data[end - BASE:end - BASE + 2] == bytes(2):
        end += 2
    return end


def word(data, address):
    return int.from_bytes(data[address - BASE:address - BASE + 4], "little")


def operand_text(instruction, symbols, pool_labels):
    mnemonic, operands = instruction.mnemonic, instruction.op_str
    if mnemonic == "bl":
        target = int(operands[1:], 0)
        return symbols.exact(target) or f"sub_{target:08X}"
    if mnemonic.startswith("b") and operands.startswith("#"):
        return f".L{int(operands[1:], 0):08X}"
    pool = re.fullmatch(r"(r\d+), \[pc(?:, #(0x[0-9a-f]+|\d+))?\]", operands)
    if mnemonic == "ldr" and pool:
        literal = ((instruction.address + 4) & ~3) + int(pool.group(2) or "0", 0)
        return f"{pool.group(1)}, {pool_labels[literal]}"
    return operands


def literal_text(value, symbols, start, limit, tables):
    if value in tables:
        return f".L{value:08X}"
    if start <= value < limit:
        return f".L{value:08X}"
    # Only function symbols have a Thumb tag. Odd byte-data addresses, including
    # absolute RAM aliases, must retain their actual address and offset.
    function = value & 1 and symbols.is_function(value)
    name = symbols.containing(value & ~1) if function else symbols.containing(value)
    if name:
        return name + ("+1" if function and "+" not in name else "")
    if is_memory(value):
        # An odd address alone does not establish a function. Direct BL targets
        # are named separately by operand_text; unknown pools stay opaque data.
        return f"D_{value:08X}"
    return f"0x{value:X}"


def render(name, data, start, end, code, pools, tables, targets, symbols):
    pool_labels = {address: f".L{address:08X}" for address in pools}
    lines = ["\t.syntax unified", "\t.thumb", ".text", "\t.align 2, 0", f"\t.globl {name}", "\t.thumb_func", f"{name}:"]
    address = start
    while address < end:
        if address in targets or address in pools or address in tables:
            if address != start:
                lines.append(f".L{address:08X}:")
        if address in code:
            instruction = code[address]
            lines.append(f"\t{instruction.mnemonic}\t{operand_text(instruction, symbols, pool_labels)}".rstrip())
            address += instruction.size
        elif address in tables:
            for target in tables[address]:
                lines.append(f"\t.word\t.L{target:08X}")
            address += 4 * len(tables[address])
        elif address in pools:
            lines.append(f"\t.word\t{literal_text(word(data, address), symbols, start, end, tables)}")
            address += 4
        else:
            lines.append(f"\t.short\t0x{int.from_bytes(data[address - BASE:address - BASE + 2], 'little'):04X}")
            address += 2
    return "\n".join(lines) + "\n"


def header_includes():
    return "".join(f'#include "{header.name}"\n' for header in sorted((ROOT / "include").glob("*.h")))


def context_file(production_context=False):
    """Preprocess the project headers into one m2c context file."""
    OUTPUT.mkdir(parents=True, exist_ok=True)
    source = OUTPUT / "context_input.c"
    source.write_text(header_includes(), encoding="utf-8")
    context = OUTPUT / "context.c"
    subprocess.run([tool("gcc"), "-E", "-P", "-x", "c", "-std=gnu89", "-nostdinc", "-undef",
                    "-D__attribute__(x)=", "-Iinclude", source, "-o", context], cwd=ROOT, check=True)
    if production_context:
        from production_signatures import from_repository
        text = context.read_text(encoding="utf-8")
        rows = from_repository(text)
        context = OUTPUT / "context_production.c"
        context.write_text(text + "\n/* Provisional signatures from active C definitions. */\n" +
                           "\n".join(row["prototype"] for row in rows) + "\n", encoding="utf-8")
        (OUTPUT / "context_production_signatures.json").write_text(
            json.dumps({"method": "Provisional source hints, not a ROM ABI audit; headers take priority.",
                        "signatures": rows}, indent=2) + "\n", encoding="utf-8")
    return context


def context_signatures(production_context):
    if not production_context:
        return []
    return json.loads((OUTPUT / "context_production_signatures.json").read_text(encoding="utf-8"))["signatures"]


def address(text):
    value = int(text, 0)
    return value + BASE if value < BASE else value


def generate(data, symbols, start, end=None, name=None, context=None, m2c_args=(), signature_hints=(), fix_pointer_strides=False,
             long_branch_targets=(), fix_register_stack=False, declare_stack_arrays=False, recover_stack_constants=False,
             fix_argument_slots=False):
    """Decode one function and run m2c; return (name, start, end, assembly path, m2c result)."""
    start &= ~1
    if fix_argument_slots and (declare_stack_arrays or recover_stack_constants):
        raise ValueError("Argument-slot rendering cannot yet combine with stack-array/join drivers")
    long_branch_targets = tuple(long_branch_targets)
    if long_branch_targets and end is None:
        raise ValueError("Long-branch hints require an explicit exclusive function end")
    code, pools, tables, targets = decode(data, start, end or start + 0x4000)
    if end is None:
        end = function_end(data, code, pools, tables)
    name = name or symbols.exact(start) or f"sub_{start:08X}"
    semantic = None
    if long_branch_targets:
        semantic = decode(data, start, end, long_branch_targets)
    elif fix_register_stack:
        semantic = (code, pools, tables, targets)
    stack_adjustments = []
    if fix_register_stack:
        semantic_code, stack_adjustments = resolve_register_stack_adjustments(data, semantic[0], semantic[1], semantic[3])
        semantic = (semantic_code, *semantic[1:])
    OUTPUT.mkdir(parents=True, exist_ok=True)
    assembly = OUTPUT / f"{name}.s"
    assembly.write_text(render(name, data, start, end, code, pools, tables, targets, symbols), encoding="utf-8")
    m2c_input = assembly
    if semantic is not None:
        m2c_input = OUTPUT / f"{name}.m2c.s"
        m2c_input.write_text(render(name, data, start, end, *semantic, symbols), encoding="utf-8")
        sites = [{"address": f"0x{a:08X}", "target": f"0x{int(i.op_str[1:], 0):08X}",
                  "rom_bytes": bytes(i.bytes).hex()} for a, i in sorted(semantic[0].items())
                 if isinstance(i, LongBranchInstruction)]
        if long_branch_targets:
            (OUTPUT / f"{name}.branch_hints.json").write_text(json.dumps({
                "method": "Manual input-only BL-to-branch hints; caller must prove saved-LR return and no live BL link value",
                "start": f"0x{start:08X}", "end": f"0x{end:08X}",
                "targets": [f"0x{t:08X}" for t in sorted(set(long_branch_targets))], "sites": sites,
                "reference": assembly.name, "m2c_input": m2c_input.name}, indent=2) + "\n", encoding="utf-8")
        if fix_register_stack:
            (OUTPUT / f"{name}.stack_adjustments.json").write_text(json.dumps({
                "method": "Input-only register SP additions resolved from exact block-local constants; review stack layout",
                "start": f"0x{start:08X}", "end": f"0x{end:08X}", "adjustments": stack_adjustments,
                "reference": assembly.name, "m2c_input": m2c_input.name}, indent=2) + "\n", encoding="utf-8")
    driver = ROOT / 'tools' / 'm2c_stride_driver.py' if fix_pointer_strides else M2C / 'm2c.py'
    if declare_stack_arrays:
        driver = ROOT / 'tools' / 'm2c_stack_arrays_driver.py'
    if recover_stack_constants:
        driver = ROOT / 'tools' / 'm2c_stack_join_driver.py'
    if fix_argument_slots:
        driver = ROOT / 'tools' / 'm2c_argument_slots_driver.py'
    command = [sys.executable, str(driver), "--target", "gba", "--valid-syntax"]
    if declare_stack_arrays:
        command += ['--stack-array-report', str(OUTPUT / f'{name}.stack_arrays.json')]
        if recover_stack_constants:
            command += ['--declare-stack-arrays']
    if recover_stack_constants:
        command += ['--stack-join-report', str(OUTPUT / f'{name}.stack_joins.json')]
    if fix_pointer_strides and (declare_stack_arrays or recover_stack_constants):
        command += ['--fix-pointer-strides']
    if fix_argument_slots and fix_pointer_strides:
        command += ['--fix-pointer-strides']
    if context:
        command += ["--context", str(context)]
    command += [arg for arg in m2c_args if arg != "--"] + [str(m2c_input)]
    result = subprocess.run(command, capture_output=True, text=True, cwd=ROOT)
    if fix_argument_slots:
        repairs = [json.loads(line.split(' ', 1)[1]) for line in result.stderr.splitlines()
                   if line.startswith('ARG_SLOT_RENDER_REPAIR ')]
        (OUTPUT / f'{name}.argument_slots.json').write_text(json.dumps({
            'method': 'Rendering-only unsigned fillers for observed ARM word-slot gaps; inferred arguments still require review',
            'reference': assembly.name, 'm2c_input': m2c_input.name, 'repairs': repairs,
        }, indent=2) + '\n', encoding='utf-8')
    if result.returncode == 0 and signature_hints:
        from production_signatures import used_declarations
        result.stdout = used_declarations(result.stdout, signature_hints, name) + result.stdout
    (OUTPUT / f"{name}.c").write_text(result.stdout, encoding="utf-8")
    return name, start, end, assembly, result


def try_match(name, start, end, assembly, c_text, cflags=(), session=None):
    """Compile the draft with the real agbcc profile and compare it via tools/match.py."""
    from match import match
    directory = OUTPUT / name
    directory.mkdir(parents=True, exist_ok=True)
    macros = (M2C / "m2c_macros.h").read_text(encoding="utf-8")
    # The project defines no 64-bit types; m2c's header expects s64.
    macros = macros.replace("typedef s64 M2C_UNK64;", "typedef long long M2C_UNK64;\ntypedef float f32;\ntypedef double f64;")
    (directory / "m2c_macros.h").write_text(macros, encoding="utf-8")
    # Rename the draft after the headers so a different guessed signature
    # cannot conflict with an existing prototype. The bytes are unaffected.
    section = f"m2c_{name}"
    source = directory / "candidate.c"
    source.write_text(f'{header_includes()}#include "m2c_macros.h"\n#define {name} {section}\n\n{c_text}', encoding="utf-8")
    # Placeholder names encode their addresses; define the ones the ELF lacks.
    values = set(re.findall(r"\b(?:D|sub)_([0-9A-F]{8})\b", assembly.read_text(encoding="utf-8")))
    # Drafts are full of loose casts; -w keeps -Werror from rejecting them. It
    # does not change code generation, but accepted source must build without it.
    spec = {"source": source.relative_to(ROOT).as_posix(), "compiler": "agbcc", "cflags": ["-w", *cflags],
            "segments": [{"name": name, "start": f"0x{start - BASE:X}", "end": f"0x{end - BASE:X}",
                          "input_section": f".text.{section}"}],
            # sub_ placeholders are Thumb code: a plain address would make the
            # linker treat calls as ARM interworking and insert a veneer.
            "symbols": {**{f"D_{value}": f"0x{value}" for value in values},
                        **{f"sub_{value}": {"address": f"0x{int(value, 16) | 1:08X}", "kind": "thumb_function"} for value in values}}}
    spec_path = directory / "spec.json"
    spec_path.write_text(json.dumps(spec, indent=2) + "\n", encoding="utf-8")
    matched = match(spec_path, directory / "match", session=session)
    result = json.loads((directory / "match" / "results.json").read_text(encoding="utf-8"))[0]
    extra = extra_sections(directory / "match" / "candidate.o", f".text.{section}")
    if matched and extra:
        # match.py discards extra sections, but production has nowhere to put them.
        result["extra_sections"] = extra
        matched = False
    return matched, result, spec_path


def extra_sections(obj, keep):
    """Non-empty sections other than `keep` (and metadata) that an object emits."""
    listing = subprocess.run([tool("objdump"), "-h", obj], capture_output=True, text=True, check=True).stdout
    extra = []
    for line in listing.splitlines():
        fields = line.split()
        if len(fields) >= 3 and fields[0].isdigit():
            name, size = fields[1], int(fields[2], 16)
            if size and name != keep and not name.startswith(".ARM."):
                extra.append(name)
    return extra


def similarity(name, data, start, end):
    """Fraction of reference bytes reproduced at the same offsets (crude, for ranking drafts)."""
    actual = (OUTPUT / name / "match" / f"{name}.bin").read_bytes()
    expected = data[start - BASE:end - BASE]
    return sum(a == b for a, b in zip(actual, expected)) / max(len(actual), len(expected))


def matched_functions():
    """Accepted single-function agbcc segments, as (start, end, name, cflags)."""
    from common import load_segments
    result = []
    for segment in load_segments():
        section = segment.get("input_section", "")
        if (segment["kind"] == "c" and segment.get("compiler") == "agbcc" and not segment.get("category")
                and not segment.get("nonmatching") and section.startswith(".text.")):
            result.append((BASE + segment["start"], BASE + segment["end"], section[len(".text."):], segment.get("cflags", [])))
    return result


def evaluate(data, symbols, count, seed, production_context=False, fix_pointer_strides=False):
    """Measure m2c on accepted functions, whose correct bytes are known."""
    import contextlib
    import io
    import random
    from match import batch_session
    session = batch_session()
    context = context_file(production_context)
    hints = context_signatures(production_context)
    rows = []
    # Each function is compiled with the flags its accepted source uses.
    for start, end, name, cflags in random.Random(seed).sample(matched_functions(), count):
        row = {"name": name, "start": f"{start:08X}", "bytes": end - start, "cflags": cflags, "compiled": False, "exact": False}
        try:
            name, start, _, assembly, result = generate(data, symbols, start, end, name, context, signature_hints=hints,
                                                       fix_pointer_strides=fix_pointer_strides)
            row["m2c_clean"] = result.returncode == 0 and "M2C_ERROR" not in result.stdout
            with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
                matched, comparison, _ = try_match(name, start, end, assembly, result.stdout, cflags, session=session)
            row.update(compiled=True, exact=matched, same_size=comparison["expected_size"] == comparison["actual_size"],
                       similarity=round(similarity(name, data, start, end), 3))
        except (SystemExit, subprocess.CalledProcessError, ValueError, OSError, KeyError) as error:
            row["error"] = (str(error).splitlines() or [type(error).__name__])[0][:160]
        rows.append(row)
        print(json.dumps(row), flush=True)
    total = len(rows)
    print(f"\n{total} accepted functions: {sum(r['compiled'] for r in rows)} compiled, "
          f"{sum(r.get('same_size', False) for r in rows)} correct size, {sum(r['exact'] for r in rows)} exact without edits, "
          f"mean byte similarity {sum(r.get('similarity', 0) for r in rows) / total:.1%}")
    (OUTPUT / "evaluation.json").write_text(json.dumps(rows, indent=2) + "\n", encoding="utf-8")


def code_gaps():
    """Unmatched intervals (copied or NONMATCH) inside the provisional code region, as GBA addresses."""
    from common import load_segments
    segments = [s for s in load_segments() if not s.get("nonmatching")]
    code_end = max(s["end"] for s in segments if s.get("category") != "data")
    gaps, cursor = [], 0
    for segment in segments:
        if segment["start"] > cursor and cursor < code_end:
            gaps.append((BASE + cursor, BASE + min(segment["start"], code_end)))
        cursor = max(cursor, segment["end"])
    return gaps


def entry_points(data, gaps):
    """Likely Thumb function entries in copied gaps: gap starts, BL targets and Thumb pointers."""
    starts = [start for start, _ in gaps]
    def gap_of(address):
        index = bisect.bisect_right(starts, address) - 1
        return gaps[index] if index >= 0 and address < gaps[index][1] else None
    found = {start: "gap start" for start, _ in gaps}
    code_end = gaps[-1][1] - BASE
    for offset in range(0, code_end - 3, 2):
        high, low = int.from_bytes(data[offset:offset + 2], "little"), int.from_bytes(data[offset + 2:offset + 4], "little")
        if high & 0xF800 == 0xF000 and low & 0xF800 == 0xF800:
            displacement = ((high & 0x7FF) << 12) | ((low & 0x7FF) << 1)
            displacement -= 0x800000 if displacement & 0x400000 else 0
            target = BASE + offset + 4 + displacement
            if gap_of(target):
                found.setdefault(target, "BL target")
    for offset in range(0, len(data) - 3, 4):
        value = int.from_bytes(data[offset:offset + 4], "little")
        if value & 1 and gap_of(value & ~1):
            found.setdefault(value & ~1, "Thumb pointer")
    return {address: (reason, gap_of(address)) for address, reason in sorted(found.items())}


_WORKER = {}
PROFILES = (["-fprologue-bugfix"], [], ["-fprologue-bugfix", "-fno-rerun-loop-opt"], ["-fno-rerun-loop-opt"],
            ["-O1", "-fprologue-bugfix"], ["-fprologue-bugfix", "-fno-regmove"])


def _harvest_setup(context, signature_hints=(), fix_pointer_strides=False):
    """Per-process state for parallel harvesting."""
    from match import batch_session
    session = batch_session()
    _WORKER.update(data=session.reference(), symbols=Symbols(), context=context, session=session,
                   signature_hints=signature_hints, fix_pointer_strides=fix_pointer_strides)


def _harvest_entry(task):
    """Decode, translate and compare one entry; return its report row."""
    import contextlib
    import io
    address, reason, gap_end = task
    data, symbols, context = _WORKER["data"], _WORKER["symbols"], _WORKER["context"]
    row = {"start": f"{address:08X}", "reason": reason, "exact": False}
    try:
        with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
            if data[address - BASE:address - BASE + 2] == b"\0\0":
                raise ValueError("starts with alignment padding")
            # agbcc aligns every function to 4 bytes (all 1,669 accepted ones are).
            if address % 4:
                raise ValueError("not 4-byte aligned")
            code, pools, tables, _ = decode(data, address, gap_end)
            first = code[address]
            mnemonics = [instruction.mnemonic for instruction in code.values()]
            if "pop" in mnemonics and "push" not in mnemonics:
                raise ValueError("pops without a prologue: a fragment of another function")
            end = function_end(data, code, pools, tables)
            if end > gap_end or any(a < address or a >= gap_end for a in code):
                raise ValueError("decoded past the copied gap")
            row.update(end=f"{end:08X}", bytes=end - address, first=f"{first.mnemonic} {first.op_str}")
            name = f"sub_{address:08X}"
            _, _, _, assembly, result = generate(data, symbols, address, end, name, context,
                                                 signature_hints=_WORKER.get("signature_hints", ()),
                                                 fix_pointer_strides=_WORKER.get("fix_pointer_strides", False))
            if result.returncode or "M2C_ERROR" in result.stdout:
                raise ValueError("m2c could not translate it")
            # Profiles observed in accepted segments, most common first.
            for cflags in PROFILES:
                matched, comparison, spec = try_match(name, address, end, assembly, result.stdout, cflags, session=_WORKER["session"])
                score = similarity(name, data, address, end)
                same_size = comparison["expected_size"] == comparison["actual_size"]
                # Prefer a profile that gets the size right: those drafts are
                # near-misses the permuter can finish.
                if (same_size, score) >= (row.get("same_size", False), row.get("similarity", -1)):
                    row.update(similarity=round(score, 3), cflags=cflags, same_size=same_size)
                if matched:
                    row.update(exact=True, cflags=cflags, spec=spec.relative_to(ROOT).as_posix())
                    break
    except (SystemExit, subprocess.CalledProcessError, ValueError, OSError, KeyError, StopIteration) as error:
        row["error"] = (str(error).splitlines() or [type(error).__name__])[0][:120]
    return row


def harvest(data, limit, jobs, production_context=False, fix_pointer_strides=False):
    """Try m2c on likely entries in copied code; stage exact matches for review."""
    from concurrent.futures import ProcessPoolExecutor
    context = context_file(production_context)
    hints = context_signatures(production_context)
    entries = entry_points(data, code_gaps())
    tasks = [(address, reason, gap[1]) for address, (reason, gap) in list(entries.items())[:limit]]
    print(f"{len(entries)} candidate entries in copied code gaps; trying {len(tasks)} with {jobs} processes", flush=True)
    with ProcessPoolExecutor(jobs, initializer=_harvest_setup, initargs=(context, hints, fix_pointer_strides)) as pool:
        rows = list(pool.map(_harvest_entry, tasks, chunksize=4))
    # Overlapping exact results: keep the earliest entry, as a sequential scan would.
    claimed = []
    for row in rows:
        if row["exact"]:
            start, end = int(row["start"], 16), int(row["end"], 16)
            if any(s < end and start < e for s, e in claimed):
                row.update(exact=False, error="overlaps an earlier exact match")
            else:
                claimed.append((start, end))
                print(json.dumps(row), flush=True)
    exact = [row for row in rows if row["exact"]]
    near = sorted((row for row in rows if row.get("same_size") and not row["exact"]), key=lambda row: -row["similarity"])
    print(f"\n{len(rows)} entries tried: {len(exact)} exact without edits, {sum(r['bytes'] for r in exact):,} bytes; "
          f"{len(near)} more drafts have the correct size (closest first in harvest.json)")
    rows.sort(key=lambda row: (not row["exact"], not row.get("same_size"), -row.get("similarity", 0)))
    (OUTPUT / "harvest.json").write_text(json.dumps(rows, indent=2) + "\n", encoding="utf-8")


def near_misses():
    """Classify correct-size harvest drafts by asm_diff markers into build/m2c/near_misses.json."""
    import collections
    import contextlib
    import io
    from asm_diff import diff
    from match import match
    data = find_rom().read_bytes()
    rows = json.loads((OUTPUT / "harvest.json").read_text(encoding="utf-8"))
    report = []
    for row in (r for r in rows if r.get("same_size") and not r["exact"]):
        name = f"sub_{row['start']}"
        spec_path = OUTPUT / name / "spec.json"
        spec = json.loads(spec_path.read_text(encoding="utf-8"))
        spec["cflags"] = ["-w", *row["cflags"]]  # the harvest leaves the last profile tried
        spec_path.write_text(json.dumps(spec, indent=2) + "\n", encoding="utf-8")
        try:
            with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
                match(spec_path, OUTPUT / name / "match")
        except (subprocess.CalledProcessError, ValueError, OSError):
            continue
        start, end = int(row["start"], 16), int(row["end"], 16)
        actual = (OUTPUT / name / "match" / f"{spec['segments'][0]['name']}.bin").read_bytes()
        marks = collections.Counter(mark for mark, _, _ in diff(data[start - BASE:end - BASE], actual, start))
        differing = sum(count for mark, count in marks.items() if mark != " ")
        kind = "registers only" if set(marks) - {" "} == {"r"} else "few rows (<=3)" if differing <= 3 else "other"
        report.append({"name": name, "start": row["start"], "end": row["end"], "bytes": row["bytes"], "kind": kind,
                       "differing_rows": differing, "cflags": row["cflags"]})
    report.sort(key=lambda r: (r["kind"] == "other", r["differing_rows"]))
    (OUTPUT / "near_misses.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(collections.Counter(r["kind"] for r in report))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("start", nargs="?", help="Function entry (GBA address or ROM offset, Thumb)")
    parser.add_argument("--end", help="Exclusive end; default: the last decoded instruction, pool word or table entry")
    parser.add_argument("--name", help="Function name; default: ELF symbol or sub_XXXXXXXX")
    parser.add_argument("--no-context", action="store_true", help="Do not pass project headers to m2c")
    parser.add_argument("--production-context", action="store_true",
                        help="Add conservative primitive signatures from active C definitions as provisional hints")
    parser.add_argument("--fix-pointer-strides", action="store_true",
                        help="Render known divisible typed-pointer byte immediates in C element units (drafts still need review)")
    parser.add_argument("--long-branch-target", type=address, action="append", default=[], metavar="ADDRESS",
                        help="Treat BLs to one reviewed local destination as m2c-only branches; repeat for more targets, requires --end")
    parser.add_argument("--fix-register-stack", action="store_true",
                        help="Resolve exactly known register SP additions in a separate m2c input (review inferred locals)")
    parser.add_argument("--declare-stack-arrays", action="store_true",
                        help="Declare fixed arrays from a reviewed _m2c_stack_NAME context (single function only)")
    parser.add_argument("--recover-stack-constants", action="store_true",
                        help="Recover agreed literal stack words at CFG joins for known scalar/pointer callees (single function only)")
    parser.add_argument("--fix-argument-slots", action="store_true",
                        help="Retain unused earlier ARM word-argument slots in unknown signatures (single function only)")
    parser.add_argument("--match", action="store_true", help="Compile the draft with agbcc and compare it via tools/match.py")
    parser.add_argument("--cflags", default="-fprologue-bugfix", help="Extra agbcc flags for --match (default: the dominant game profile)")
    parser.add_argument("--evaluate", type=int, metavar="N", help="Measure m2c on N random accepted functions")
    parser.add_argument("--seed", type=int, default=1)
    parser.add_argument("--near-misses", action="store_true",
                        help="Classify correct-size harvest drafts into build/m2c/near_misses.json for tools/permute.py")
    parser.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 2) - 2), help="Parallel processes for --harvest")
    parser.add_argument("--harvest", type=int, nargs="?", const=100000, metavar="LIMIT",
                        help="Try likely entries in copied code; stage exact matches (build/m2c/harvest.json)")
    parser.add_argument("--rom")
    args, m2c_args = parser.parse_known_args()
    if args.fix_argument_slots and (args.harvest is not None or args.evaluate is not None or
                                   args.declare_stack_arrays or args.recover_stack_constants):
        parser.error("--fix-argument-slots currently supports single functions without stack-array/join drivers")
    if args.no_context and args.production_context:
        parser.error("--production-context requires project header context")
    if args.long_branch_target and (not args.end or args.harvest is not None or args.evaluate is not None or args.near_misses):
        parser.error("--long-branch-target requires a single function with explicit --end")
    if args.fix_register_stack and (args.harvest is not None or args.evaluate is not None or args.near_misses):
        parser.error("--fix-register-stack requires a single function")
    if args.declare_stack_arrays and (args.harvest is not None or args.evaluate is not None or args.near_misses):
        parser.error("--declare-stack-arrays requires a single function")
    if args.recover_stack_constants and (args.harvest is not None or args.evaluate is not None or args.near_misses):
        parser.error("--recover-stack-constants requires a single function")
    if not (M2C / "m2c.py").exists():
        raise SystemExit("m2c is missing. Run python tools/bootstrap.py --m2c.")
    data = find_rom(args.rom).read_bytes()
    symbols = Symbols()
    cflags = args.cflags.split()
    if args.near_misses:
        return near_misses()
    if args.harvest:
        return harvest(data, args.harvest, args.jobs, args.production_context, args.fix_pointer_strides)
    if args.evaluate:
        return evaluate(data, symbols, args.evaluate, args.seed, args.production_context, args.fix_pointer_strides)
    if not args.start:
        parser.error("start is required unless --evaluate is given")

    context = None if args.no_context else context_file(args.production_context)
    hints = context_signatures(args.production_context)
    end = address(args.end) if args.end else None
    name, start, end, assembly, result = generate(data, symbols, address(args.start), end, args.name, context, m2c_args,
                                                signature_hints=hints, fix_pointer_strides=args.fix_pointer_strides,
                                                long_branch_targets=args.long_branch_target, fix_register_stack=args.fix_register_stack,
                                                declare_stack_arrays=args.declare_stack_arrays,
                                                recover_stack_constants=args.recover_stack_constants,
                                                fix_argument_slots=args.fix_argument_slots)
    print(f"// {name}: {start:08X}..{end:08X} ({end - start} bytes); verify these bounds before use")
    m2c_input = assembly.with_suffix('.m2c.s') if args.long_branch_target or args.fix_register_stack else assembly
    print(f"// m2c input {m2c_input.relative_to(ROOT).as_posix()}, output build/m2c/{name}.c")
    if args.long_branch_target:
        print(f"// unchanged BL reference {assembly.relative_to(ROOT).as_posix()}; review {name}.branch_hints.json")
    if args.fix_register_stack:
        print(f"// unchanged instruction reference {assembly.relative_to(ROOT).as_posix()}; review {name}.stack_adjustments.json")
    if args.declare_stack_arrays:
        print(f"// reviewed fixed stack-array declarations recorded in {name}.stack_arrays.json")
    if args.fix_argument_slots:
        print(f"// observed argument-slot rendering recorded in {name}.argument_slots.json; review inferred parameters")
    print(result.stdout, end="")
    if result.returncode:
        print(result.stderr, end="", file=sys.stderr)
        return result.returncode
    if args.match:
        matched, _, spec = try_match(name, start, end, assembly, result.stdout, cflags)
        print(f"// {'MATCH' if matched else 'MISMATCH'}; byte similarity {similarity(name, data, start, end):.1%}; "
              f"spec {spec.relative_to(ROOT).as_posix()}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
