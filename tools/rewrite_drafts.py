"""Apply learned source rewrites to unfinished m2c drafts and keep exact results.

Hand-fixing drafts shows recurring agbcc idioms that m2c does not reproduce.
Each transform below rewrites a draft's text; every applicable combination is
compiled with the draft's best profile (and the dominant -fprologue-bugfix)
through tools/match.py. A byte-exact variant that also compiles with -Werror is
written to build/m2c/<name>.c and recorded in build/m2c/manual_solved.json for
tools/m2c_integrate.py.

    python tools/rewrite_drafts.py              # all non-exact harvest drafts
    python tools/rewrite_drafts.py --skip-near  # leave permuter targets alone

Transforms (add new ones as hand fixes reveal them):
- hoist_indexed_global: `((i << n) + gTable)` becomes `(table + (i << n))`
  with `table` loaded into a local first, so agbcc loads the address before
  shifting the index (seen in many gSetupBuffer_03000590 record accesses).
- hoist_indexed_global_late: the same, assigned just before first use.
- reorder_indexed_global: the same operand swap without the temporary.
- hoist_field_global: M2C_FIELD(&gWork, ...) goes through a local byte
  pointer assigned just before first use (`work = gUnknown_...;`).
- hoist_array_global, hoist_offset_global: array bases and `gTable + 0x40`
  through a local assigned before first use.
- sink_phi_store: put a following store in each branch, retaining the assigned
  value and its conversion for subsequent uses (verified on 08016554).
- simplify_extension_shifts: shift pairs become (s16)/(u8)... casts.
- widen_parameters: s8/u8/s16/u16 parameters become s32/u32, removing the
  entry extensions agbcc adds for narrow parameter types.
- widen_locals: the same for m2c's narrow var_/temp_ locals.
- invert_if_return: `if (c) return A; return B;` with the branches swapped.
- hoist_member_array: `gWork.bytes[...]` through a local member pointer.
- fix_scaled_unknown: m2c scales indexes into unknown (4-byte) globals twice;
  rewritten as byte arithmetic in m2c's operand order.
- goto_to_while: `loop_N: if (c) { body; goto loop_N; }` as a while loop.
- invert_early_return: `if (c) return X; rest; return Y;` with the branch inverted.
- sink_pointer_phi: `p = &X; v = A;` per branch plus `*p = v;` become per-branch stores.
- read_key_low_byte: try byte reads for key globals when the ROM uses LDRB.
- captured_key_identity: unsigned mask-1/4 identity using each RAM snapshot once.
- share_full_width_zero, share_zero_at_first_store: shared integer-store/return zero.
- sink_pointer_initialization: combine adjacent address assignment and pure store.
"""

import argparse
import contextlib
from concurrent.futures import ProcessPoolExecutor
import io
from itertools import combinations
from functools import lru_cache
import hashlib
import json
import os
import re
import subprocess
import sys
import time

from common import ROOT

OUTPUT = ROOT / "build" / "m2c"
MANUAL = OUTPUT / "manual_solved.json"
INDEX_EXPR = r"([\w.\[\]>-]+(?: \+ \d+)?)"
INDEXED = re.compile(r"\(\(" + INDEX_EXPR + r" << (\d+)\) \+ (g\w+)\)")
ASSIGNED = re.compile(r"= \(" + INDEX_EXPR + r" << (\d+)\) \+ (g\w+);")
NARROW_PARAM = re.compile(r"\b(s8|u8|s16|u16) (arg\d+)\b")
FIELD_GLOBAL = re.compile(r"M2C_FIELD\(&(g\w+), ")


def indexed_symbols(text):
    return sorted({m.group(3) for m in INDEXED.finditer(text)} | {m.group(3) for m in ASSIGNED.finditer(text)})


def replace_indexed(text, symbol, replacement):
    """Rewrite `((i << n) + symbol)` and `= (i << n) + symbol;` with `replacement` for the base."""
    symbol = re.escape(symbol)
    text = re.sub(r"\(\(" + INDEX_EXPR + r" << (\d+)\) \+ " + symbol + r"\)",
                  lambda m: f"({replacement} + ({m.group(1)} << {m.group(2)}))", text)
    return re.sub(r"= \(" + INDEX_EXPR + r" << (\d+)\) \+ " + symbol + ";",
                  lambda m: f"= {replacement} + ({m.group(1)} << {m.group(2)});", text)


def function_header(lines, name):
    return next((i for i, line in enumerate(lines) if re.search(r"\b" + re.escape(name) + r"\([^)]*\) \{$", line)), None)


def declare_first(text, name, declaration):
    lines = text.split("\n")
    header = function_header(lines, name)
    if header is None:
        return None
    lines.insert(header + 1, f"    {declaration}")
    return "\n".join(lines)


def assign_before_first_use(text, name, value, local, pattern):
    """Declare `local` at the top and assign `value` right before the first line matching `pattern`."""
    lines = text.split("\n")
    header = function_header(lines, name)
    if header is None:
        return None
    first = next((i for i in range(header + 1, len(lines)) if re.search(pattern, lines[i])), None)
    if first is None:
        return None
    indent = re.match(r"\s*", lines[first]).group(0)
    lines.insert(first, f"{indent}{local} = (u8 *) {value};")
    lines.insert(header + 1, f"    u8 *{local};")
    return "\n".join(lines)


def hoist_indexed_global(text, name):
    symbols = indexed_symbols(text)
    if not symbols:
        return None
    for index, symbol in enumerate(symbols):
        local = f"base{index}"
        text = replace_indexed(text, symbol, local)
        text = declare_first(text, name, f"u8 *{local} = (u8 *) {symbol};")
        if text is None:
            return None
    return text


def hoist_indexed_global_late(text, name):
    symbols = indexed_symbols(text)
    if not symbols:
        return None
    for index, symbol in enumerate(symbols):
        local = f"late{index}"
        text = assign_before_first_use(text, name, symbol, local, r"<< \d+\) \+ " + re.escape(symbol) + r"\b")
        if text is None:
            return None
        text = replace_indexed(text, symbol, local)
    return text


def reorder_indexed_global(text, name):
    symbols = indexed_symbols(text)
    if not symbols:
        return None
    for symbol in symbols:
        text = replace_indexed(text, symbol, symbol)
    return text


def hoist_field_global(text, name):
    symbols = sorted({m.group(1) for m in FIELD_GLOBAL.finditer(text)})
    if not symbols:
        return None
    for index, symbol in enumerate(symbols):
        local = f"work{index}"
        text = assign_before_first_use(text, name, f"&{symbol}", local, "&" + re.escape(symbol) + r"\b")
        if text is None:
            return None
        text = text.replace(f"M2C_FIELD(&{symbol}, ", f"M2C_FIELD({local}, ")
    return text


def widen_parameters(text, name):
    """m2c types parameters by their use (s8, u16, ...); agbcc then extends them on
    entry. Originals often took full-width ints and only truncated on store."""
    signature = re.search(r"\b" + re.escape(name) + r"\(([^)]*)\) \{", text)
    if not signature or not NARROW_PARAM.search(signature.group(1)):
        return None
    widened = NARROW_PARAM.sub(lambda m: f"{'s32' if m.group(1)[0] == 's' else 'u32'} {m.group(2)}", signature.group(1))
    return text.replace(signature.group(0), signature.group(0).replace(signature.group(1), widened), 1)


PHI_STORE = re.compile(
    r"(?P<indent>[ ]+)if \((?P<cond>.+)\) \{\n[ ]+(?P<var>\w+) = (?P<a>[^;\n]+);\n(?P=indent)\} else \{\n"
    r"[ ]+(?P=var) = (?P<b>[^;\n]+);\n(?P=indent)\}\n(?P=indent)(?P<target>[^=\n]+?) = (?P=var);\n")
ARRAY_GLOBAL = re.compile(r"(?<![\w.>])(g\w+)\[")


def sink_phi_store(text, name):
    """Move the immediate store into every branch without dropping the phi value.

    Retaining `v = A` preserves its type conversion, any volatile access, and
    later uses such as a second frame-field store. No memory event is added on
    any path. Restrict the rewrite to the named function and exhaustive simple
    branches; labels, intervening statements and partial chains stay untouched.
    """
    span = _function_body(text, name)
    if span is None:
        return None
    start, end = span
    lines = text[start:end].split("\n")
    code_lines = _code_only(text[start:end]).split("\n")
    changed = False
    index = 0
    while index < len(lines):
        opening = re.fullmatch(r"( +)if \((.+)\) \{", code_lines[index])
        if not opening:
            index += 1
            continue
        indent = opening.group(1)
        branches, cursor, variable = [], index, None
        # Each branch: header line, one `v = X;` line, then `} else ... {` or `}`.
        while cursor + 2 < len(lines):
            body = re.fullmatch(r" +(\w+) = ([^;]+);", code_lines[cursor + 1])
            if not body or (variable and body.group(1) != variable):
                break
            variable = body.group(1)
            branches.append((lines[cursor], lines[cursor + 1]))
            closing = code_lines[cursor + 2]
            if closing == indent + "}":
                cursor += 3
                break
            if not re.fullmatch(re.escape(indent) + r"\} else (if \(.+\) )?\{", closing):
                break
            cursor += 2
        else:
            index += 1
            continue
        final_else = len(branches) >= 2 and code_lines[cursor - 1] == indent + "}" and "} else {" in code_lines[cursor - 3]
        store = re.fullmatch(re.escape(indent) + r"([^=]+?) = " + re.escape(variable or "") + ";", code_lines[cursor]) \
            if cursor < len(lines) and variable else None
        if not final_else or not store:
            index += 1
            continue
        rewritten = []
        # Copy the original statements, not reconstructed expressions. Keeping
        # assignment and store distinct also keeps their sequence points.
        for header, assignment in branches:
            rewritten += [header, assignment, indent + "    " + lines[cursor].lstrip()]
        rewritten.append(indent + "}")
        lines[index:cursor + 1] = rewritten
        code_lines[index:cursor + 1] = _code_only("\n".join(rewritten)).split("\n")
        changed = True
        index += len(rewritten)
    return text[:start] + "\n".join(lines) + text[end:] if changed else None


UNKNOWN_SYMBOL = re.compile(r"^extern M2C_UNK (\w+);", re.M)


def fix_scaled_unknown(text, name):
    """m2c types unknown globals as 4-byte M2C_UNK, so its `*((i * 4) + &D_X)` and
    `&D_X + 1` scale by 4 a second time. Rewrite them as byte arithmetic, keeping
    m2c's operand order (index first), which matches agbcc's load order."""
    unknown = set(UNKNOWN_SYMBOL.findall(text))
    if not unknown:
        return None
    output, position, changed = [], 0, False
    for match in re.finditer(r"(\*?)\(\(", text):
        if match.start() < position:
            continue
        inner_open = match.end() - 1
        inner_close = _balanced_end(text, inner_open)
        if inner_close is None:
            continue
        scaled = re.fullmatch(r"(.+) \* ([124])", text[inner_open + 1:inner_close - 1], re.S)
        tail = re.match(r" \+ &(\w+)\)", text[inner_close:])
        if not scaled or not tail or tail.group(1) not in unknown:
            continue
        address = f"(({scaled.group(1)} * {scaled.group(2)}) + (u8 *)&{tail.group(1)})"
        if match.group(1):
            address = f"*({ {'4': 's32', '2': 's16', '1': 's8'}[scaled.group(2)]} *){address}"
        output.append(text[position:match.start()] + address)
        position = inner_close + tail.end()
        changed = True
    text = "".join(output) + text[position:]
    for symbol in unknown:
        text, count = re.subn(r"(?<!\(u8 \*\))&" + re.escape(symbol) + r" \+ (0x[0-9A-Fa-f]+|\d+)\b", lambda m: f"(u8 *)&{symbol} + {m.group(1)}", text)
        changed |= bool(count)
        # A shifted index is already a byte offset. This also covers function
        # arguments without an extra outer pair of parentheses.
        text, count = re.subn(r"((?:<<|>>) (?:0x[0-9A-Fa-f]+|\d+)\) \+ )&" + re.escape(symbol) + r"\b",
                              lambda m: m.group(1) + f"(u8 *)&{symbol}", text)
        changed |= bool(count)
    return text if changed else None


def read_key_low_byte(text, name):
    """Some callers intentionally read only the low byte of the u16 key globals.

    Keep declarations, writes and existing address expressions intact. This is
    a candidate transform: callers needing the high byte fail the byte gate.
    """
    lines = text.split("\n")
    header = function_header(lines, name)
    if header is None:
        return None
    prefix = "\n".join(lines[:header + 1])
    body = "\n".join(lines[header + 1:])
    pattern = r"(?<![\w&])(gHeldKeys|gNewKeys|gRepeatedKeys)\b(?!\s*(?:=(?!=)|[+*/%&|^<>-]=|\+\+|--))"
    body, count = re.subn(pattern, lambda m: f"(*(u8 *)&{m.group(1)})", body)
    return prefix + "\n" + body if count else None


MEMBER_ARRAY = re.compile(r"(?<![\w.>])(g\w+)\.(\w+)\[")


def hoist_member_array(text, name):
    """`gWork.bytes[0xAA]` through `work = gWork.bytes;` assigned before first use,
    so `&gWork.bytes[0x45]` stays a run-time add instead of one folded literal."""
    members = sorted(set(MEMBER_ARRAY.findall(text)))
    if not members:
        return None
    for index, (symbol, member) in enumerate(members):
        local = f"member{index}"
        lines = text.split("\n")
        header = function_header(lines, name)
        if header is None:
            return None
        pattern = r"(?<![\w.>])" + re.escape(symbol) + r"\." + re.escape(member) + r"\["
        first = next((i for i in range(header + 1, len(lines)) if re.search(pattern, lines[i])), None)
        if first is None:
            return None
        indent = re.match(r"\s*", lines[first]).group(0)
        lines = re.sub(pattern, f"{local}[", "\n".join(lines)).split("\n")
        lines[first:first] = [f"{indent}{local} = {symbol}.{member};"]
        lines.insert(header + 1, f"    __typeof__(&{symbol}.{member}[0]) {local};")
        text = "\n".join(lines)
    return text


IF_RETURN = re.compile(r"(?P<indent>[ ]+)if \((?P<cond>.+)\) \{\n[ ]+return (?P<a>[^;\n]+);\n(?P=indent)\}\n"
                       r"(?P=indent)return (?P<b>[^;\n]+);\n")


def invert_if_return(text, name):
    """`if (c) return A; return B;` becomes `if (!(c)) return B; return A;`; the
    branch layout agbcc emits follows the source order."""
    if not IF_RETURN.search(text):
        return None
    return IF_RETURN.sub(lambda m: f"{m['indent']}if (!({m['cond']})) {{\n{m['indent']}    return {m['b']};\n"
                                   f"{m['indent']}}}\n{m['indent']}return {m['a']};\n", text)


def sink_pointer_phi(text, name):
    """m2c merges different stores from an if/else into `p = &X; v = A;` in each
    branch and one `*p = v;` afterwards. The original stored in each branch."""
    lines = text.split("\n")
    for index, line in enumerate(lines):
        opening = re.fullmatch(r"( +)if \((.+)\) \{", line)
        if not opening:
            continue
        indent = opening.group(1)
        # Branch headers of an if / else if / else chain at this indent.
        headers, cursor = [index], index + 1
        while cursor < len(lines):
            if lines[cursor] == indent + "}":
                break
            if re.fullmatch(re.escape(indent) + r"\} else (if \(.+\) )?\{", lines[cursor]):
                headers.append(cursor)
            elif lines[cursor].startswith(indent) and not lines[cursor].startswith(indent + " ") and lines[cursor].strip():
                break
            cursor += 1
        close = cursor
        if close >= len(lines) - 1 or lines[close] != indent + "}" or len(headers) < 2 or lines[headers[-1]] != indent + "} else {":
            continue
        store = re.fullmatch(re.escape(indent) + r"\*(\w+) = (\w+);", lines[close + 1])
        if not store:
            continue
        pointer, value = store.groups()
        rewritten = []
        for position, header in enumerate(headers):
            last = headers[position + 1] if position + 1 < len(headers) else close
            body = lines[header + 1:last]
            assigned = {}
            for statement in body[-2:]:
                found = re.fullmatch(r" +(\w+) = (.+);", statement)
                if found:
                    assigned[found.group(1)] = found.group(2)
            if len(body) < 2 or set(assigned) != {pointer, value}:
                rewritten = None
                break
            address = assigned[pointer]
            simple = re.fullmatch(r"&([\w.\[\]>-]+)", address)
            target = simple.group(1) if simple else f"*({address})"
            rewritten += [lines[header], *body[:-2], f"{indent}    {target} = {assigned[value]};"]
        if rewritten is None:
            continue
        lines[index:close + 2] = rewritten + [indent + "}"]
        return "\n".join(lines)
    return None


def goto_to_while(text, name):
    """m2c's `loop_N: if (c) { body; goto loop_N; }` is a while loop; agbcc lays
    out `while (c) body` with the test after the body."""
    lines = text.split("\n")
    changed = False
    index = 0
    while index < len(lines):
        label = re.fullmatch(r"(loop_\d+):", lines[index])
        if not label or index + 1 >= len(lines):
            index += 1
            continue
        opening = re.fullmatch(r"( +)if \((.+)\) \{", lines[index + 1])
        if not opening:
            index += 1
            continue
        indent = opening.group(1)
        close = next((i for i in range(index + 2, len(lines)) if lines[i] == indent + "}"), None)
        if close is None or lines[close - 1].strip() != f"goto {label.group(1)};":
            index += 1
            continue
        body = lines[index + 2:close - 1]
        if any(label.group(1) in line for line in body):
            index += 1
            continue
        lines[index:close + 1] = [f"{indent}while ({opening.group(2)}) {{", *body, indent + "}"]
        changed = True
        index += len(body) + 2
    return "\n".join(lines) if changed else None


def invert_early_return(text, name):
    """`if (c) { return X; } rest...; return Y; }` at function level becomes
    `if (!(c)) { rest...; return Y; } return X;`."""
    lines = text.split("\n")
    header = function_header(lines, name)
    if header is None:
        return None
    end = next((i for i in range(header + 1, len(lines)) if lines[i] == "}"), None)
    for index in range(header + 1, (end or 0) - 3):
        opening = re.fullmatch(r"    if \((.+)\) \{", lines[index])
        if not opening or not re.fullmatch(r"        return [^;]+;", lines[index + 1]) or lines[index + 2] != "    }":
            continue
        rest = lines[index + 3:end]
        if not rest or not rest[-1].startswith("    return ") or any(re.match(r"\w+:", line) for line in rest):
            continue
        inverted = [f"    if (!({opening.group(1)})) {{", *["    " + line if line else line for line in rest], "    }",
                    "    " + lines[index + 1].strip()]
        lines[index:end] = inverted
        return "\n".join(lines)
    return None


NARROW_LOCAL = re.compile(r"^(    )(s8|u8|s16|u16) ((?:var|temp)_\w+);$", re.M)


def widen_locals(text, name):
    """m2c types locals by their stores; a u8 counter makes agbcc truncate after
    every update, where the original used a full-width int."""
    if not NARROW_LOCAL.search(text):
        return None
    return NARROW_LOCAL.sub(lambda m: f"{m.group(1)}{'s32' if m.group(2)[0] == 's' else 'u32'} {m.group(3)};", text)


def hoist_array_global(text, name):
    """Index global arrays through a local base pointer assigned before first use
    (`base = gRecords; record = &base[i];`)."""
    symbols = sorted(set(ARRAY_GLOBAL.findall(text)))
    if not symbols:
        return None
    for index, symbol in enumerate(symbols):
        local = f"array{index}"
        lines = text.split("\n")
        header = function_header(lines, name)
        if header is None:
            return None
        pattern = r"(?<![\w.>])" + re.escape(symbol) + r"\["
        first = next((i for i in range(header + 1, len(lines)) if re.search(pattern, lines[i])), None)
        if first is None:
            return None
        indent = re.match(r"\s*", lines[first]).group(0)
        lines = re.sub(pattern, f"{local}[", "\n".join(lines)).split("\n")
        lines[first:first] = [f"{indent}{local} = {symbol};"]
        lines.insert(header + 1, f"    __typeof__({symbol}[0]) *{local};")
        text = "\n".join(lines)
    return text


SHIFT_CAST = re.compile(r"\((s32|u32)\) \(")


def _balanced_end(text, open_index):
    """Index just past the parenthesis that closes text[open_index] == '('."""
    depth = 0
    for index in range(open_index, len(text)):
        depth += {"(": 1, ")": -1}.get(text[index], 0)
        if depth == 0:
            return index + 1
    return None


def simplify_extension_shifts(text, name):
    """`(s32) (e << 0x10) >> 0x13` is `(s16) e >> 3`; `(u32) (e << 0x18) >> 0x17` is
    `(u8) e << 1`. m2c spells extensions as shift pairs, which agbcc compiles
    differently from the casts the original source used."""
    output, position, changed = [], 0, False
    for match in SHIFT_CAST.finditer(text):
        if match.start() < position:
            continue
        inner_open = match.end() - 1
        inner_close = _balanced_end(text, inner_open)
        if inner_close is None:
            continue
        inner = text[inner_open + 1:inner_close - 1]
        left = re.fullmatch(r"(.+) << 0x(10|18)", inner, re.S)
        after = re.match(r" >> 0x([0-9A-Fa-f]+)", text[inner_close:])
        if not left or not after:
            continue
        width, right = int(left.group(2), 16), int(after.group(1), 16)
        cast = {("s32", 0x10): "s16", ("s32", 0x18): "s8", ("u32", 0x10): "u16", ("u32", 0x18): "u8"}[(match.group(1), width)]
        expression = f"({cast}) ({left.group(1)})"
        if right > width:
            expression = f"({expression} >> {right - width})"
        elif right < width:
            if cast.startswith("s"):
                continue  # a signed left shift has no clean cast spelling
            expression = f"({expression} << {width - right})"
        output.append(text[position:match.start()] + expression)
        position = inner_close + after.end()
        changed = True
    if not changed:
        return None
    return "".join(output) + text[position:]


OFFSET_GLOBAL = re.compile(r"(?<![\w.>&])(g\w+) \+ (0x[0-9A-Fa-f]+|\d+)\b")


def hoist_offset_global(text, name):
    """`p = gTable + 0x40` folds into one literal; the original loaded the base
    into a local first and added the offset at run time."""
    symbols = sorted({m.group(1) for m in OFFSET_GLOBAL.finditer(text)})
    if not symbols:
        return None
    for index, symbol in enumerate(symbols):
        local = f"offset{index}"
        lines = text.split("\n")
        header = function_header(lines, name)
        if header is None:
            return None
        pattern = r"(?<![\w.>&])" + re.escape(symbol) + r" \+ (0x[0-9A-Fa-f]+|\d+)\b"
        first = next((i for i in range(header + 1, len(lines)) if re.search(pattern, lines[i])), None)
        if first is None:
            return None
        indent = re.match(r"\s*", lines[first]).group(0)
        lines = re.sub(pattern, lambda m: f"{local} + {m.group(1)}", "\n".join(lines)).split("\n")
        lines[first:first] = [f"{indent}{local} = {symbol};"]
        lines.insert(header + 1, f"    __typeof__(&({symbol})[0]) {local};")
        text = "\n".join(lines)
    return text



INTEGER_TYPE = r"(?:u8|s8|u16|s16|u32|s32|unsigned int|signed int|int)"


def _code_only(text):
    """Mask comments and strings without changing offsets (these rules parse C code)."""
    pattern = r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''
    return re.sub(pattern, lambda m: "".join("\n" if c == "\n" else " " for c in m[0]), text, flags=re.S)


def _function_body(text, name):
    code = _code_only(text)
    signature = re.search(r"\b" + re.escape(name) + r"\([^;{}]*\)\s*\{", code)
    if signature is None:
        return None
    opening = signature.end() - 1
    depth = 1
    for index in range(opening + 1, len(code)):
        depth += {"{": 1, "}": -1}.get(code[index], 0)
        if depth == 0:
            return opening + 1, index
    return None


def _fresh_local(text, prefix):
    name, suffix = prefix, 0
    while re.search(r"\b" + re.escape(name) + r"\b", text):
        suffix += 1
        name = f"{prefix}{suffix}"
    return name


def captured_key_identity(text, name):
    """Try (key & mask) & key for verified masks 1/4 and unsigned snapshots.

    Direct key reads are captured at their existing evaluation point, once per
    original read. This does not hoist, narrow, merge or repeat any RAM read.
    """
    span = _function_body(text, name)
    if span is None:
        return None
    start, end = span
    body, code = text[start:end], _code_only(text[start:end])
    unsigned = set(re.findall(r"^    (?:u32|unsigned int) (\w+)(?:\s*=|\s*;)", code, re.M))
    # Ignore a name that can denote a shadowed declaration or volatile storage.
    unsigned = {local for local in unsigned if len(re.findall(
        r"\b(?:" + INTEGER_TYPE + r")\s+" + re.escape(local) + r"\b", code)) == 1}
    # An already-expanded local is excluded, making the transform idempotent.
    unsigned = {local for local in unsigned if not re.search(
        r"\(\s*" + re.escape(local) + r"\s*&\s*[14]u\s*\)\s*&\s*" + re.escape(local) + r"\b", code)}
    global_read = r"(?:gHeldKeys|gNewKeys|gRepeatedKeys|\(\*\(u8\s*\*\)\s*&(?:gHeldKeys|gNewKeys|gRepeatedKeys)\))"
    operands = [global_read, *[re.escape(local) for local in sorted(unsigned)]]
    value = "(?:" + "|".join(operands) + ")"
    mask = r"(?:[14][uU]?|0x0*[14][uU]?)\b"
    pattern = re.compile(r"(?<![\w&])(?:(?P<left>" + value + r")\s*&\s*(?P<left_mask>" + mask +
                         r")|(?P<right_mask>" + mask + r")\s*&\s*(?P<right>" + value + r"))(?![\w])")
    replacements = []
    captured_locals = []
    for match in pattern.finditer(code):
        if body[match.start():match.end()] != code[match.start():match.end()]:
            continue  # preserve inline comments/string literals exactly
        before, after = code[:match.start()].rstrip(), code[match.end():].lstrip()
        # Reject an operand/mask embedded in arithmetic or a unary expression;
        # e.g. key & 1 << 2 means key & 4, not (key & 1) << 2.
        if before and before[-1] not in "([=,?:{|&^" and not re.search(r"\breturn$", before):
            continue
        if before.endswith(("==", "!=", "<=", ">=")):
            continue
        if after and after[0] in "+-*/%[.!=<>":
            continue
        operand = match['left'] or match['right']
        mask_value = int((match['left_mask'] or match['right_mask']).rstrip('uU'), 0)
        # A direct RAM operand inside an existing capture cannot be re-expanded.
        if operand in unsigned:
            replacement = f"(({operand} & {mask_value}u) & {operand})"
        else:
            # Independent locals preserve defined calls with multiple key
            # arguments: reusing one would introduce unsequenced writes.
            occupied = text + "\n" + "\n".join(f"u32 {local};" for local in captured_locals)
            captured = _fresh_local(occupied, "rewriteKeys")
            captured_locals.append(captured)
            replacement = f"(({captured} = {operand}), ({captured} & {mask_value}u) & {captured})"
        replacements.append((match.start(), match.end(), replacement))
    if not replacements:
        return None
    for left, right, replacement in reversed(replacements):
        body = body[:left] + replacement + body[right:]
    if captured_locals:
        body = "".join(f"\n    u32 {local};" for local in captured_locals) + body
    return text[:start] + body + text[end:]


def _top_level_integer_members(body):
    fields, depth = set(), 0
    for line in _code_only(body).splitlines():
        if depth == 0:
            match = re.match(r"\s*" + INTEGER_TYPE + r"\s+(\w+)(?:\[[^\]]+\])?;", line)
            if match:
                fields.add(match[1])
        depth += line.count("{") - line.count("}")
    return fields


@lru_cache(maxsize=1)
def _frame_integer_fields():
    """Use established top-level field types, refusing nested union/pointer fields."""
    code = _code_only((ROOT / 'include' / 'frame.h').read_text(encoding='utf-8'))
    opening = code.index('{', code.index('struct FrameObject'))
    depth, closing = 1, opening + 1
    while closing < len(code) and depth:
        depth += {'{': 1, '}': -1}.get(code[closing], 0)
        closing += 1
    return _top_level_integer_members(code[opening + 1:closing - 1])


def _scalar_lvalue(target, body):
    """Recognize integer locals and explicitly typed scalar memory; refuse unknown fields."""
    target = target.strip()
    if re.fullmatch(r"\w+", target):
        declarations = re.findall(r"\b" + INTEGER_TYPE + r"\s*(\*?\s*)" + re.escape(target) + r"\s*(?:[;=])", body)
        return len(declarations) == 1 and "*" not in declarations[0]
    if target.startswith("M2C_FIELD(") and target.endswith(")"):
        return bool(re.search(r",\s*(?:volatile\s+)?" + INTEGER_TYPE + r"\s*\*\s*,", target))
    if re.match(r"^\*\s*\(\s*(?:volatile\s+)?" + INTEGER_TYPE + r"\s*\*\s*\)", target):
        return True
    pointer = re.fullmatch(r"\*(\w+)|([A-Za-z_]\w*)\[[^\]\n;]+\]", target)
    if pointer:
        local = pointer[1] or pointer[2]
        return bool(re.search(r"\b(?:volatile\s+)?" + INTEGER_TYPE + r"\s*\*\s*" + re.escape(local) + r"\s*[;=]", body))
    frame = re.fullmatch(r'(gFrameObjects(?:\[[^\]\n;]+\])?|\w+)(?:->|\.)(\w+)(?:\[[^\]\n;]+\])?', target)
    if frame and frame[2] in _frame_integer_fields():
        if frame[1].startswith('gFrameObjects'):
            return True
        local = re.escape(frame[1])
        declarations = re.findall(r'\bstruct\s+\w+\s*\*?\s*' + local + r'\b', body)
        if len(declarations) == 1 and re.search(r'\bstruct FrameObject\s*\*?\s*' + local + r'\b', body):
            return True
    # These project backing arrays are explicitly u8 arrays in the headers.
    return bool(re.fullmatch(r"gState0(?:Transfer|Typed)Work\.bytes\[[^\n;]+\]", target))


def _zero_replacements(text, name):
    span = _function_body(text, name)
    if span is None:
        return None
    start, end = span
    body, code = text[start:end], _code_only(text[start:end])
    sites = []
    for match in re.finditer(r"^(?P<indent> +)(?P<target>[^;\n]+?) = 0;", code, re.M):
        if body[match.start():match.end()] == code[match.start():match.end()] and _scalar_lvalue(match['target'], code):
            sites.append((match.start(), match.end(), match['indent'], match['target']))
    signature = _code_only(text[:start]).splitlines()[-1]
    if re.match(r"\s*" + INTEGER_TYPE + r"\s+" + re.escape(name) + r"\(", signature):
        for match in re.finditer(r"^( +)return 0;", code, re.M):
            if body[match.start():match.end()] == code[match.start():match.end()]:
                sites.append((match.start(), match.end(), match[1], None))
    sites.sort()
    return (start, end, body, code, sites) if len(sites) >= 2 else None


def _share_zero(text, name, first_store):
    found = _zero_replacements(text, name)
    if found is None:
        return None
    start, end, body, code, sites = found
    zero = _fresh_local(text, "rewriteZero")
    if first_store:
        first = sites[0]
        # Straight-line initialization must dominate every replacement. Refuse
        # branches, labels and loops before the first top-level zero store.
        prefix = code[:first[0]]
        if first[2] != "    " or first[3] is None or re.search(r"[{}:]|\b(?:if|for|while|do|goto|return|switch)\b", prefix):
            return None
    for position, (left, right, indent, target) in reversed(list(enumerate(sites))):
        value = f"({zero} = 0)" if first_store and position == 0 else zero
        statement = f"{target} = {value};" if target is not None else f"return {value};"
        body = body[:left] + indent + statement + body[right:]
    declaration = f"u32 {zero};" if first_store else f"u32 {zero} = 0;"
    return text[:start] + "\n    " + declaration + body + text[end:]


def share_full_width_zero(text, name):
    """Reuse a full-width zero for proven integer stores and integer returns."""
    return _share_zero(text, name, False)


def share_zero_at_first_store(text, name):
    """Initialize the shared zero inside the first dominating integer store."""
    return _share_zero(text, name, True)


def sink_pointer_initialization(text, name):
    """Adjacent p = &object->field; *p = 0; becomes *(p = &object->field) = 0.

    Only literals and ordinary integer locals are allowed; value expressions
    with a RAM read could change their order relative to the address.
    """
    span = _function_body(text, name)
    if span is None:
        return None
    start, end = span
    body, code = text[start:end], _code_only(text[start:end])
    pattern = re.compile(r"^(?P<indent> +)(?P<pointer>\w+) = (?P<address>&[\w.>\[\] +*-]+);\n"
                         r"(?P=indent)\*(?P=pointer) = (?P<value>(?:0x[0-9A-Fa-f]+|\d+)[uU]?|[A-Za-z_]\w*);", re.M)
    for match in pattern.finditer(code):
        if body[match.start():match.end()] != code[match.start():match.end()]:
            continue
        if not re.search(r"\b(?:volatile\s+)?" + INTEGER_TYPE + r"\s*\*\s*" + re.escape(match['pointer']) + r"\s*[;=]", code):
            continue
        if re.fullmatch(r"[A-Za-z_]\w*", match['value']):
            value = re.escape(match['value'])
            ordinary = re.findall(r"^    " + INTEGER_TYPE + r" " + value + r"\s*[;=]", code, re.M)
            all_declarations = re.findall(r"\b" + INTEGER_TYPE + r"\s+" + value + r"\b", code)
            if len(ordinary) != 1 or len(all_declarations) != 1:
                continue
        # No calls, increments, dereferences or arithmetic in the address.
        if not re.fullmatch(r"&\w+(?:->\w+|\.\w+|\[(?:\w+|0x[0-9A-Fa-f]+|\d+)\])*", match['address']):
            continue
        replacement = f"{match['indent']}*({match['pointer']} = {match['address']}) = {match['value']};"
        body = body[:match.start()] + replacement + body[match.end():]
        return text[:start] + body + text[end:]
    return None

TRANSFORMS = [read_key_low_byte, hoist_indexed_global, hoist_indexed_global_late, reorder_indexed_global, hoist_field_global,
              hoist_array_global, hoist_offset_global, sink_phi_store, simplify_extension_shifts, widen_parameters,
              widen_locals, invert_if_return, hoist_member_array, fix_scaled_unknown, goto_to_while,
              invert_early_return, sink_pointer_phi, captured_key_identity, share_full_width_zero,
              share_zero_at_first_store, sink_pointer_initialization]
EXCLUSIVE = {hoist_indexed_global, hoist_indexed_global_late, reorder_indexed_global}  # same expression


MAX_COMBINATION = 3  # transforms applied together
MAX_VARIANTS = 40    # bounded per-draft total
NEW_TRANSFORMS = {captured_key_identity, share_full_width_zero, share_zero_at_first_store, sink_pointer_initialization, sink_phi_store}
PRIORITY_VARIANTS = 12  # reserved for learned rules and their interactions
EXCLUSIVE_ZERO = {share_full_width_zero, share_zero_at_first_store}


def variants(text, name, transforms=None):
    """Bounded generation: reserve learned slots, then stop at the filled budget."""
    initial = {}
    for transform in TRANSFORMS if transforms is None else transforms:
        current = transform(text, name)
        if current is not None:
            initial[transform] = current
    applicable = list(initial)
    seen = {text}

    def generate(learned):
        for size in range(1, min(MAX_COMBINATION, len(applicable)) + 1):
            for combo in combinations(applicable, size):
                members = set(combo)
                if bool(NEW_TRANSFORMS & members) != learned:
                    continue
                if len(EXCLUSIVE & members) > 1 or len(EXCLUSIVE_ZERO & members) > 1:
                    continue
                if size == 1:
                    current = initial[combo[0]]
                else:
                    current = text
                    for transform in combo:
                        current = transform(current, name)
                        if current is None:
                            break
                if current is not None and current not in seen:
                    seen.add(current)
                    yield ("+".join(t.__name__ for t in combo), current)

    learned = generate(True)
    results = []
    # Atomic learned variants come first. Hold at most the final40 strings,
    # besides the one applicability result per transform; do not materialize
    # hundreds of discarded combinations.
    if NEW_TRANSFORMS & set(applicable):
        for _ in range(min(PRIORITY_VARIANTS, MAX_VARIANTS)):
            item = next(learned, None)
            if item is None:
                break
            results.append(item)
    old = generate(False)
    while len(results) < MAX_VARIANTS:
        item = next(old, None)
        if item is None:
            break
        results.append(item)
    # If few old combinations apply, fill the remaining slots with learned
    # combinations. A legacy-only call therefore still gets up to40 old rows.
    while len(results) < MAX_VARIANTS:
        item = next(learned, None)
        if item is None:
            break
        results.append(item)
    return results


def compiler_profiles(best, label=None, all_profiles=False):
    """Bounded learned controls keep O2's expensive passes (which remove orphan data)."""
    choices = [list(best), ["-fprologue-bugfix"]]
    if all_profiles or label == "original_profile_control" or "captured_key_identity" in (label or "").split("+"):
        choices += [["-O2", "-fprologue-bugfix", "-fno-force-mem"],
                    ["-O2", "-fprologue-bugfix", "-fno-force-mem", "-fno-cse-skip-blocks"]]
    result = []
    for flags in choices:
        if flags not in result:
            result.append(flags)
    return result


TRIED = OUTPUT / "rewrite_tried.json"  # name -> hashes of (batch context, text, cflags)


def context_fingerprint(root=ROOT):
    """Hash compilation/type/link context once for each immutable batch process."""
    paths = list((root / "include").rglob("*.h"))
    paths += [root / "tools" / "downloads" / "agbcc" / ("agbcc.exe" if os.name == "nt" else "agbcc"),
              root / "tools" / "downloads" / "m2c" / "m2c_macros.h",
              root / "tools" / "compiler_agbcc.py", root / "config" / "symbols.json",
              root / "build" / "medabots.elf"]
    digest = hashlib.sha256()
    for path in sorted(paths):
        digest.update(path.relative_to(root).as_posix().encode("utf-8") + b"\0")
        digest.update(path.read_bytes() if path.is_file() else b"<missing>")
        digest.update(b"\0")
    return digest.hexdigest()


@lru_cache(maxsize=1)
def rewrite_context():
    return context_fingerprint()


def variant_key(text, cflags, context):
    payload = context + "\n" + " ".join(cflags) + "\n" + text
    # v2 keys never alias the previous text+flags-only cache entries.
    return "v2:" + hashlib.sha256(payload.encode("utf-8")).hexdigest()[:24]


def attempt(task):
    """Try every untried variant with the draft's profiles; return (name, result or None, tried keys)."""
    name, best, tried = task[:3]
    options = task[3:]
    mode = options[0] if options else "all"
    limit = options[1] if len(options) > 1 else MAX_VARIANTS
    all_profiles = options[2] if len(options) > 2 else False
    tried = set(tried)
    result = _attempt(name, best, tried, mode, limit, all_profiles)
    return name, result, sorted(tried)


def _attempt(name, best, tried, mode="all", limit=MAX_VARIANTS, all_profiles=False):
    sys.path.insert(0, str(ROOT / "tools"))
    from compiler_agbcc import compile_source
    from m2c_candidate import extra_sections, try_match
    from match import batch_session
    draft = (OUTPUT / f"{name}.c").read_text(encoding="utf-8")
    spec = json.loads((OUTPUT / name / "spec.json").read_text(encoding="utf-8"))
    segment = spec["segments"][0]
    start, end = int(segment["start"], 0) + 0x08000000, int(segment["end"], 0) + 0x08000000
    assembly = OUTPUT / f"{name}.s"
    if mode == "legacy":
        profiles = [best] + ([["-fprologue-bugfix"]] if best != ["-fprologue-bugfix"] else [])
        choices = variants(draft, name, [t for t in TRANSFORMS if t not in NEW_TRANSFORMS])
    else:
        choices = variants(draft, name)
        if mode == "learned":
            names = {t.__name__ for t in NEW_TRANSFORMS}
            choices = [row for row in choices if names & set(row[0].split("+"))]
        choices = [("original_profile_control", draft)] + choices
    session = batch_session()
    context = rewrite_context()
    for label, text in choices[:limit]:
        if mode != "legacy":
            profiles = compiler_profiles(best, label, all_profiles)
        for cflags in profiles:
            key = variant_key(text, cflags, context)
            if key in tried:
                continue
            tried.add(key)
            try:
                with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
                    matched, _, _ = try_match(name, start, end, assembly, text, cflags, session=session)
                    if not matched:
                        continue
                    compile_source(OUTPUT / name / "candidate.c", OUTPUT / name / "match" / "strict.o", cflags)
                    if extra_sections(OUTPUT / name / "match" / "strict.o", segment["input_section"]):
                        continue
            except (subprocess.CalledProcessError, ValueError, OSError, KeyError):
                continue
            return {"name": name, "start": segment["start"], "end": segment["end"], "cflags": cflags,
                    "rule": label, "text": text}
    return None


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--skip-near", action="store_true", help="Skip build/m2c/near_misses.json (permuter targets)")
    parser.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 2) - 2))
    parser.add_argument("--names", nargs="+", help="Only these named drafts (bounded evaluation)")
    parser.add_argument("--limit", type=int, help="Maximum number of selected drafts")
    modes = parser.add_mutually_exclusive_group()
    modes.add_argument("--learned-only", action="store_true", help="New rules plus unmodified profile controls")
    modes.add_argument("--legacy-only", action="store_true", help="Previous rule/profile set for comparison")
    parser.add_argument("--all-profiles", action="store_true", help="Try learned O2 controls for every variant (costly; opt-in)")
    parser.add_argument("--variant-limit", type=int, default=MAX_VARIANTS, help="Variant cap per draft (1..40)")
    args = parser.parse_args()
    if not 1 <= args.variant_limit <= MAX_VARIANTS or (args.limit is not None and args.limit < 1):
        parser.error("variant-limit must be 1..40 and limit must be positive")
    mode = "learned" if args.learned_only else "legacy" if args.legacy_only else "all"
    started = time.perf_counter()
    rows = json.loads((OUTPUT / "harvest.json").read_text(encoding="utf-8"))
    solved = json.loads(MANUAL.read_text(encoding="utf-8")) if MANUAL.exists() else []
    skip = {entry["name"] for entry in solved}
    if args.skip_near:  # whatever tools/permute.py may be working on
        for queue in ("near_misses.json", "permute_queue.json", "hand_queue.json"):
            if (OUTPUT / queue).exists():
                skip |= {entry["name"] for entry in json.loads((OUTPUT / queue).read_text(encoding="utf-8"))}
    tasks = [(f"sub_{row['start']}", row["cflags"]) for row in rows
             if not row["exact"] and "bytes" in row and "similarity" in row and "cflags" in row]
    tasks = [(name, cflags) for name, cflags in tasks if name not in skip and (OUTPUT / f"{name}.c").exists()
             and (OUTPUT / name / "spec.json").exists()]
    if args.names:
        requested = set(args.names)
        tasks = [(name, flags) for name, flags in tasks if name in requested]
    if args.limit is not None:
        tasks = tasks[:args.limit]
    print(f"{len(tasks)} drafts selected ({mode}; at most {args.variant_limit} variants each)", flush=True)
    cache = json.loads(TRIED.read_text(encoding="utf-8")) if TRIED.exists() else {}
    with ProcessPoolExecutor(args.jobs) as pool:
        outcomes = list(pool.map(attempt, [(name, cflags, cache.get(name, []), mode, args.variant_limit, args.all_profiles) for name, cflags in tasks]))
    probes = sum(len(set(tried) - set(cache.get(name, []))) for name, _, tried in outcomes)
    for name, _, tried in outcomes:
        cache[name] = tried
    TRIED.write_text(json.dumps(cache) + "\n", encoding="utf-8")
    results = [result for _, result, _ in outcomes if result]
    for result in results:
        (OUTPUT / f"{result['name']}.c").write_text(result.pop("text"), encoding="utf-8")
        print(json.dumps(result), flush=True)
    names_solved = {result["name"] for result in results}
    # Re-read: tools/accept_draft.py may have added entries while this ran.
    solved = json.loads(MANUAL.read_text(encoding="utf-8")) if MANUAL.exists() else []
    solved = [entry for entry in solved if entry["name"] not in names_solved] + [
        {key: result[key] for key in ("name", "start", "end", "cflags")} for result in results]
    MANUAL.write_text(json.dumps(solved, indent=2) + "\n", encoding="utf-8")
    total_bytes = sum(int(result["end"], 0) - int(result["start"], 0) for result in results)
    print(f"{probes} new probes; {len(results)} strict matches / {total_bytes} bytes; {time.perf_counter() - started:.2f}s", flush=True)
    print(f"\n{len(results)} drafts became exact; {len(solved)} manual/rewritten functions await tools/m2c_integrate.py")


if __name__ == "__main__":
    main()
