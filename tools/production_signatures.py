"""Conservative, optional m2c hints from active C definitions.

These are provisional source signatures, not an independent ROM ABI audit.
Only primitive signatures of definitions selected by the segment manifest
are eligible. Project headers always take priority.
"""

import json
import re
from pathlib import Path

from common import ROOT

# A caller prototype for this copied-ROM helper omits an incoming R3 use.
# Keep it excluded even if a future provisional definition is integrated.
EXCLUDED_NAMES = {"sub_08060D28"}
PRIMITIVES = {
    "void", "char", "signed char", "unsigned char", "short", "short int",
    "signed short", "signed short int", "unsigned short", "unsigned short int",
    "int", "signed", "signed int", "unsigned", "unsigned int", "long",
    "long int", "signed long", "signed long int", "unsigned long",
    "unsigned long int", "s8", "u8", "s16", "u16", "s32", "u32",
}
DEFINITION = re.compile(
    r"(?m)^[ \t]*(?P<storage>(?:static|extern)\s+)?"
    r"(?P<return>[A-Za-z_]\w*(?:[ \t]+[A-Za-z_]\w*)*(?:[ \t]*\*)?)"
    r"[ \t]+(?P<name>[A-Za-z_]\w*)[ \t]*\((?P<params>[^(){};]*)\)"
    r"[ \t\r\n]*\{"
)


def clean_source(text):
    """Hide comments and literals while retaining offsets and line numbers."""
    return re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                  lambda m: re.sub(r"[^\n]", " ", m[0]), text, flags=re.S)


def primitive_type(text):
    text = re.sub(r"\s+", " ", text.strip())
    text = re.sub(r"\s*\*\s*", " *", text)
    # Parameter names are removed separately; only const-qualified void
    # pointers are accepted, with no private pointee types or function pointers.
    if text in PRIMITIVES:
        return text
    if text in ("void *", "const void *", "void const *"):
        return text
    return None


def parameter_type(text):
    direct = primitive_type(text)
    if direct:
        return direct
    match = re.fullmatch(r"(.+?)\s*\b[A-Za-z_]\w*", text.strip())
    return primitive_type(match[1]) if match else None


def definitions(text):
    clean = clean_source(text)
    # Raw conditional definitions cannot establish which spelling is active.
    if re.search(r"(?m)^\s*#\s*(?:if|ifdef|ifndef|elif|else)\b", clean):
        return []
    rows = []
    depth, previous = 0, 0
    for match in DEFINITION.finditer(clean):
        between = clean[previous:match.start()]
        depth += between.count("{") - between.count("}")
        previous = match.start()
        if depth or (match["storage"] or "").strip() == "static":
            continue
        result = primitive_type(match["return"])
        params = match["params"].strip()
        if result is None or not params:
            continue
        parameters = [] if params == "void" else [parameter_type(p) for p in params.split(",")]
        if any(p is None or p == "void" for p in parameters):
            continue
        rows.append({"name": match["name"],
                     "prototype": result + " " + match["name"] + "(" +
                                  (", ".join(parameters) if parameters else "void") + ");",
                     "line": text[:match.start()].count("\n") + 1})
    return rows


def collect(segments, sources, header_context, excluded=EXCLUDED_NAMES):
    """Select unambiguous external primitive definitions actually linked."""
    active = {}
    for segment in segments:
        section = segment.get("input_section", "")
        if segment.get("kind") != "c" or segment.get("category") == "data" or not section.startswith(".text."):
            continue
        active.setdefault(segment["source"], set()).add(section[len(".text."):])
    header_names = set(re.findall(r"\b[A-Za-z_]\w*\b", header_context))
    found = {}
    for source, names in sorted(active.items()):
        for row in definitions(sources[source]):
            name = row["name"]
            if name not in names or name in header_names or name in excluded:
                continue
            row["source"] = source
            found.setdefault(name, []).append(row)
    # Duplicate definitions are excluded even when their primitive prototypes
    # happen to agree: source preprocessing or symbol ownership needs review.
    return [rows[0] for name, rows in sorted(found.items()) if len(rows) == 1]


def from_repository(header_context, root=ROOT):
    root = Path(root)
    segments = json.loads((root / "config/segments.json").read_text(encoding="utf-8"))
    paths = {s["source"] for s in segments if s.get("kind") == "c" and
             s.get("input_section", "").startswith(".text.")}
    sources = {p: (root / p).read_text(encoding="utf-8") for p in paths}
    return collect(segments, sources, header_context)


def used_declarations(c_text, rows, entry):
    """Expose only used supplementary hints in the standalone draft too."""
    clean = clean_source(c_text)
    # Calls such as `return callee(value);` inside a body are not prototypes.
    # Mask brace contents before looking for existing external declarations.
    depth = 0
    top_level = []
    for character in clean:
        if character == "{":
            depth += 1
            top_level.append("{")
        elif character == "}":
            depth -= 1
            top_level.append("}")
        else:
            top_level.append(character if depth == 0 or character == "\n" else " ")
    top_level = "".join(top_level)
    declarations = []
    for row in rows:
        name = row["name"]
        if name == entry or not re.search(r"\b" + re.escape(name) + r"\b", clean):
            continue
        # m2c normally omits declarations already in its context. If it emits
        # one anyway, preserve that output for review instead of duplicating it.
        if re.search(r"(?m)^[ \t]*(?:extern\s+)?[A-Za-z_][\w \t*]*\b" +
                     re.escape(name) + r"\s*\([^;{}]*\)\s*;", top_level):
            continue
        declarations.append("extern " + row["prototype"])
    return "\n".join(declarations) + ("\n\n" if declarations else "")
