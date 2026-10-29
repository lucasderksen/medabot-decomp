"""Try wrapping brace-balanced statement ranges in `do { } while (0)` (register-allocation lever).

    python tools/try_wraps.py sub_0803F684 build/m2c/work.c -fprologue-bugfix 10

Each candidate is one tools/try_draft.py compile; the best variant is written to
build/variants/wbest_<name>.c. Scores come from try_draft row counts; a
score-0 result still has to be accepted with tools/accept_draft.py.
"""
import os
os.makedirs("build/variants", exist_ok=True)
import re, subprocess, sys
from c_source import function_body_lines

name, path = sys.argv[1], sys.argv[2]
flags = sys.argv[3] if len(sys.argv) > 3 else "-fprologue-bugfix"
maxspan = int(sys.argv[4]) if len(sys.argv) > 4 else 10
tag = name
src = open(path).read()
lines = src.split("\n")
start, end = function_body_lines(src, name)
decl = re.compile(r"^\s+(volatile\s+)?(u8|u16|u32|s8|s16|s32|struct|union|const|void|IntrFunc)\b[^=(]*;")


def indent(l):
    return len(l) - len(l.lstrip())


def is_start(i):
    l = lines[i].strip()
    if not l or l.startswith("else") or l.startswith("}") or l.endswith(":") or decl.match(lines[i]):
        return False
    if l.startswith("{"):
        return False
    return True


def is_end(i):
    l = lines[i].strip()
    if not (l.endswith(";") or l == "}"):
        return False
    nxt = lines[i + 1].strip() if i + 1 < len(lines) else ""
    if nxt.startswith("else") or nxt.startswith("while"):
        return False
    return True


cands = []
for a in range(start + 1, end):
    if not is_start(a):
        continue
    d = 0
    for b in range(a, min(end, a + maxspan)):
        d += lines[b].count("{") - lines[b].count("}")
        if d < 0:
            break
        if d == 0 and is_end(b) and indent(lines[b]) >= indent(lines[a]) - 0:
            # statement-level end: the line b must close the statement opened at a
            if lines[b].strip() == "}" and indent(lines[b]) != indent(lines[a]):
                continue
            # A `continue`/`break` aimed at an enclosing loop or switch would bind to the
            # new do/while(0) instead and change behaviour; skip such ranges (conservative:
            # a break is allowed only when the range opens its own loop or switch).
            body = "\n".join(lines[a:b + 1])
            if re.search(r"\bcontinue\b", body):
                continue
            if re.search(r"\bbreak\b", body) and not re.search(r"\b(for|while|do|switch)\b", body):
                continue
            cands.append((a, b))


def score(text):
    fn = "build/variants/_w_%s.c" % tag
    open(fn, "w").write(text)
    out = subprocess.run([sys.executable, "tools/try_draft.py", name, fn, "--cflags=" + flags],
                         capture_output=True, text=True).stdout
    if out.startswith("MATCH"):
        return 0
    m = re.search(r"(\d+) differing rows", out)
    return int(m.group(1)) if m else 9999


def wrapped(a, b):
    ind = " " * indent(lines[a])
    return lines[:a] + [ind + "do {"] + lines[a:b + 1] + [ind + "} while (0);"] + lines[b + 1:]


base = score(src)
print("base", base, "candidates", len(cands), flush=True)
results = []
for a, b in cands:
    new = "\n".join(wrapped(a, b))
    sc = score(new)
    results.append((sc, a, b))
    if sc == 0:
        open("build/variants/wbest_%s.c" % tag, "w").write(new)
        print("MATCH", a, b, flush=True)
        break
results.sort()
print(results[:6])
if results and results[0][0] < base and results[0][0] != 0:
    sc, a, b = results[0]
    open("build/variants/wbest_%s.c" % tag, "w").write("\n".join(wrapped(a, b)))
    print("best written", sc)
