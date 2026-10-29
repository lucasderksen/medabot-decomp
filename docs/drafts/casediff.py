"""Per-case diff of a big switch function: reference ROM vs candidate.elf.

usage: python casediff.py NAME START END TABLEOFF NCASES [ELF] [--show CASE...] [--all]
"""
import difflib
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "python"))
from common import tool  # noqa
import capstone

name = sys.argv[1]
start = int(sys.argv[2], 0)
end = int(sys.argv[3], 0)
tableoff = int(sys.argv[4], 0)
ncases = int(sys.argv[5], 0)
show = set(); shownames = set()
showall = "--all" in sys.argv
if "--show" in sys.argv:
    show = set(); shownames = set()
    for x in sys.argv[sys.argv.index("--show") + 1:]:
        if x.startswith("--"): continue
        try: show.add(int(x, 0))
        except ValueError: shownames.add(x)

rom = (ROOT / "baserom.gba").read_bytes()
ref = rom[start - 0x08000000:end - 0x08000000]

elf = Path(sys.argv[6]) if len(sys.argv) > 6 and not sys.argv[6].startswith("--") else ROOT / "build" / "m2c" / name / "match" / "candidate.elf"
nm = subprocess.run([tool("nm"), "-S", str(elf)], capture_output=True, text=True).stdout
addr = size = None
for line in nm.splitlines():
    parts = line.split()
    if len(parts) == 4 and parts[3] in (name, "m2c_" + name):
        addr, size = int(parts[0], 16), int(parts[1], 16)
with tempfile.TemporaryDirectory() as d:
    out = Path(d) / "x.bin"
    subprocess.run([tool("objcopy"), "-O", "binary", str(elf), str(out)], check=True)
    image = out.read_bytes()
# find lowest load address
hdr = subprocess.run([tool("objdump"), "-h", str(elf)], capture_output=True, text=True).stdout
lows = []
for line in hdr.splitlines():
    p = line.split()
    if len(p) >= 7 and re.fullmatch(r"\d+", p[0]):
        if int(p[2], 16) > 0:
            lows.append(int(p[4], 16))
base = min(x for x in lows if x >= 0x08000000)
cand = image[addr - base: addr - base + size]


def find_table(data, address):
    # locate "mov pc, r0" and literal "ldr r1, =table" before it
    engine = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
    engine.skipdata = True
    last = None
    for ins in engine.disasm(data[:0x200], address):
        m = re.fullmatch(r"r1, \[pc(?:, #(0x[0-9a-f]+|\d+))?\]", ins.op_str)
        if ins.mnemonic == "ldr" and m:
            lit = ((ins.address + 4) & ~3) + int(m.group(1) or "0", 0) - address
            last = int.from_bytes(data[lit:lit + 4], "little") - address
        if ins.mnemonic == "mov" and ins.op_str == "pc, r0":
            return last
    raise SystemExit("no table")


def segments(data, address, toff):
    entries = [int.from_bytes(data[toff + 4 * i: toff + 4 * i + 4], "little") - address for i in range(ncases)]
    return entries


def dis(data, address):
    engine = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
    engine.skipdata = True
    lines = []
    for ins in engine.disasm(data, address):
        lines.append([ins.address - address, ins.mnemonic, ins.op_str, ins.size])
    return lines


def normalize(lines, data, address, bounds):
    # bounds: sorted list of (offset, segname)
    def seg_of(off):
        cur = None
        for o, n in bounds:
            if o <= off:
                cur = (o, n)
        return cur

    out = []
    for off, mn, ops, sz in lines:
        if mn.startswith("b") and ops.startswith("#"):
            t = int(ops[1:], 0) - address
            s = seg_of(t)
            if not 0 <= t < len(data):
                ops = "<external>"
            else:
                ops = f"{s[1]}+0x{t - s[0]:X}" if s else f"+0x{t:X}"
        pool = re.fullmatch(r"(r\d+), \[pc(?:, #(0x[0-9a-f]+|\d+))?\]", ops)
        if mn == "ldr" and pool:
            lit = ((off + address + 4) & ~3) + int(pool.group(2) or "0", 0) - address
            if 0 <= lit <= len(data) - 4:
                v = int.from_bytes(data[lit:lit + 4], "little")
                if address <= v < address + len(data):
                    s = seg_of(v - address)
                    ops = f"{pool.group(1)}, ={s[1]}+0x{v - address - s[0]:X}"
                else:
                    ops = f"{pool.group(1)}, =0x{v:08X}"
        out.append((off, f"{mn} {ops}"))
    return out


rt = tableoff
ct = find_table(cand, addr)
re_ = segments(ref, start, rt)
ce = segments(cand, addr, ct)
# assign names to targets by first case using them
names_r, names_c = {}, {}
for i in range(ncases):
    names_r.setdefault(re_[i], f"c{i:X}")
    names_c.setdefault(ce[i], f"c{i:X}")
# align: segment name is defined by the reference's case grouping
rb = sorted([(o, n) for o, n in names_r.items()]) + [(0, "head"), (rt, "table"), (rt + 4 * ncases, "c1start")]
cb = sorted([(o, n) for o, n in names_c.items()]) + [(0, "head"), (ct, "table"), (ct + 4 * ncases, "c1start")]
rb = sorted(set(rb))
cb = sorted(set(cb))
# map candidate segment names to reference ones by case number
rname_by_case = {i: names_r[re_[i]] for i in range(ncases)}
cmap = {}
for i in range(ncases):
    cmap.setdefault(names_c[ce[i]], rname_by_case[i])
cb = [(o, cmap.get(n, n)) for o, n in cb]
rl = normalize(dis(ref, start), ref, start, rb)
cl = normalize(dis(cand, addr), cand, addr, cb)


def split(lines, bounds):
    res = {}
    bs = sorted(bounds)
    for i, (o, n) in enumerate(bs):
        e = bs[i + 1][0] if i + 1 < len(bs) else 1 << 30
        res.setdefault(n, []).extend([l for l in lines if o <= l[0] < e])
    return res, bs


rs, rbs = split(rl, rb)
cs, cbs = split(cl, cb)
total = 0
print(f"ref {len(ref):#x} bytes, cand {len(cand):#x} bytes")
for o, n in rbs:
    a = [x[1] for x in rs.get(n, [])]
    b = [x[1] for x in cs.get(n, [])]
    sm = difflib.SequenceMatcher(a=a, b=b, autojunk=False)
    rows = 0
    for tag, a0, a1, b0, b1 in sm.get_opcodes():
        if tag != "equal":
            rows += max(a1 - a0, b1 - b0)
    if n != "table":
        total += rows
    cases = [i for i in range(ncases) if rname_by_case[i] == n]
    lab = ",".join(f"{c:X}" for c in cases[:4]) + ("..." if len(cases) > 4 else "")
    print(f"{n:8s} cases[{lab:14s}] ref@{o:#06x} len {len(a):4d} cand len {len(b):4d} rows {rows}")
    want = showall or any(c in show for c in cases) or (n in shownames)
    if want and rows:
        rl2 = rs.get(n, [])
        cl2 = cs.get(n, [])
        for tag, a0, a1, b0, b1 in sm.get_opcodes():
            for k in range(max(a1 - a0, b1 - b0)):
                L = rl2[a0 + k] if a0 + k < a1 else None
                R = cl2[b0 + k] if b0 + k < b1 else None
                mark = " " if tag == "equal" else ("|" if L and R else ("<" if L else ">"))
                ls = f"{L[0]:5X} {L[1]}" if L else ""
                rs_ = f"{R[0]:5X} {R[1]}" if R else ""
                print(f"   {ls:42s} {mark} {rs_}")
print("total rows", total)
