"""Greedy search over local declaration order and integer types.

    python tools/try_decls.py sub_08038BC0 build/m2c/work.c -fprologue-bugfix

Best variant: build/variants/dbest_<name>.c. Accept matches with tools/accept_draft.py.
"""
import os
os.makedirs("build/variants", exist_ok=True)
import re, subprocess, sys
from c_source import function_body_lines

name, path = sys.argv[1], sys.argv[2]
flags = sys.argv[3] if len(sys.argv) > 3 else "-fprologue-bugfix"
src = open(path).read()
TYPES = ["u8", "u16", "u32", "s8", "s16", "s32"]


def score(text):
    fn = "build/variants/_d_%s.c" % name
    open(fn, "w").write(text)
    out = subprocess.run([sys.executable, "tools/try_draft.py", name, fn, "--cflags=" + flags],
                         capture_output=True, text=True).stdout
    if out.startswith("MATCH"):
        return 0
    m = re.search(r"(\d+) reference bytes, (\d+) candidate bytes, (\d+) differing rows", out)
    if not m:
        return 9999
    return int(m.group(3)) + (0 if m.group(1) == m.group(2) else 500)


def variants(text):
    lines = text.split("\n")
    start, _ = function_body_lines(text, name)
    decls = []
    i = start + 1
    while i < len(lines) and re.match(r"^\s+(volatile\s+)?(const\s+)?(u8|u16|u32|s8|s16|s32|struct \w+|union \w+|IntrFunc)\b[^(]*;\s*$", lines[i]):
        decls.append(i)
        i += 1
    out = []
    # move each declaration to the top / bottom / swap neighbours
    for k in range(len(decls)):
        for j in range(len(decls)):
            if j == k:
                continue
            block = [lines[d] for d in decls]
            item = block.pop(k)
            block.insert(j, item)
            new = lines[:decls[0]] + block + lines[decls[-1] + 1:]
            out.append(("move %d->%d" % (k, j), "\n".join(new)))
    # type changes on simple scalar declarations without initializer
    for d in decls:
        m = re.match(r"^(\s+)(u8|u16|u32|s8|s16|s32)(\s+\w+\s*(=[^;]*)?;\s*)$", lines[d])
        if not m:
            continue
        for t in TYPES:
            if t == m.group(2):
                continue
            new = list(lines)
            new[d] = m.group(1) + t + m.group(3)
            out.append(("type %d %s" % (d, t), "\n".join(new)))
    return out


cur = src
best = score(cur)
print("base", best, flush=True)
improved = True
while improved and best > 0:
    improved = False
    for label, text in variants(cur):
        sc = score(text)
        if sc < best:
            best, cur = sc, text
            improved = True
            print("improved", label, sc, flush=True)
            open("build/variants/dbest_%s.c" % name, "w").write(cur)
            if sc == 0:
                print("MATCH", flush=True)
                break
            break
print("final", best)
