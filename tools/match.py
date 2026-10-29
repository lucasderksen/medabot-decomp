"""Compile and compare isolated source candidates without changing the ROM build.

A JSON spec contains source, compiler/cflags, segments (name/start/end/section),
and optional additional symbols. Existing build/medabots.elf supplies known
function/data addresses. Extra candidate sections are deliberately discarded;
only the requested intervals are assessed. Production integration still requires
the complete tools/build.py comparison. Wrong-size candidate sections are linked
only for diagnostics and always fail comparison; they do not suppress results
for the other requested functions.
"""

import argparse
import copy
from collections import OrderedDict
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys

from build import CFLAGS, generate_symbol_assembly
from common import ROOT, find_rom, load_segments, rom_config, tool, validate_rom


def run(command, **kwargs):
    return subprocess.run([str(part) for part in command], cwd=ROOT, check=True, **kwargs)


def elf_symbols(listing):
    """Read global definitions with the actual ELF Thumb-state bit retained."""
    symbols = {}
    for line in listing.splitlines():
        fields = line.split()
        if len(fields) != 8 or not fields[0].endswith(":"):
            continue
        _, value, _, kind, binding, _, index, name = fields
        if binding not in ("GLOBAL", "WEAK") or index == "UND":
            continue
        address = int(value, 16)
        if kind == "FUNC" and address & 1:
            symbols[name] = {"address": f"0x{address:08X}", "kind": "thumb_function"}
        else:
            symbols[name] = f"0x{address:08X}"
    return symbols


def read_symbols(path):
    return elf_symbols(run([tool("readelf"), "-sW", path], capture_output=True, text=True).stdout)


class MatchSession:
    """Reuse verified reference bytes and linker setup during a batch of probes.

    Candidate compilation, linking and complete byte comparisons always run.
    Baseline/configuration changes invalidate symbol setup by content, and cached
    symbol objects are tied to the assembler's contents. No match verdict is cached.
    """

    def __init__(self, rom_path=None):
        self.rom_path = find_rom(rom_path).resolve()
        self._reference = self.rom_path.read_bytes()
        self._digest = validate_rom(self._reference)
        self._symbols_key = None
        self._symbols = {}
        self._stubs = OrderedDict()
        self.stats = {"symbol_reads": 0, "stub_assemblies": 0, "stub_hits": 0}

    def reference(self, rom_path=None):
        if rom_path is not None and Path(rom_path).resolve() != self.rom_path:
            raise ValueError("A match session uses one verified ROM; create a new session for another path.")
        config = rom_config()
        if len(self._reference) != config["size"] or self._digest != config["sha256"]:
            raise ValueError("ROM configuration changed; create a new match session.")
        return self._reference

    def symbols(self):
        configuration = (ROOT / "config/symbols.json").read_bytes()
        baseline = ROOT / "build/medabots.elf"
        baseline_digest = hashlib.sha256(baseline.read_bytes()).digest() if baseline.is_file() else None
        key = (configuration, baseline_digest)
        if key != self._symbols_key:
            symbols = json.loads(configuration)
            if baseline_digest is not None:
                symbols.update(read_symbols(baseline))
                self.stats["symbol_reads"] += 1
            self._symbols = symbols
            self._symbols_key = key
        # Per-candidate overrides and removals must not mutate the shared baseline.
        return copy.deepcopy(self._symbols)

    def symbol_object(self, symbols, output):
        source, target = output / "symbols.s", output / "symbols.o"
        assembly = generate_symbol_assembly(symbols)
        source.write_text(assembly, encoding="utf-8")
        assembler = Path(tool("as"))
        key = (hashlib.sha256(assembly.encode()).digest(), hashlib.sha256(assembler.read_bytes()).digest())
        if key in self._stubs:
            object_bytes = self._stubs.pop(key)
            target.write_bytes(object_bytes)
            self._stubs[key] = object_bytes
            self.stats["stub_hits"] += 1
        else:
            run([assembler, "-mcpu=arm7tdmi", source, "-o", target])
            self._stubs[key] = target.read_bytes()
            self.stats["stub_assemblies"] += 1
            while len(self._stubs) > 8:
                self._stubs.popitem(last=False)
        return target


_BATCH_SESSION = None


def batch_session():
    """One lazy session per Python worker process, for long-running probe tools."""
    global _BATCH_SESSION
    if _BATCH_SESSION is None:
        _BATCH_SESSION = MatchSession()
    return _BATCH_SESSION


def linker(entries, candidate, symbols):
    base = int(rom_config()["rom_base"], 0)
    lines = ["OUTPUT_ARCH(arm)", "SECTIONS", "{"]
    for entry in entries:
        section = f".{entry['name']}"
        lines += [
            f"  {section} 0x{base + entry['start']:08X} : {{ {candidate}({entry['input_section']}) }}",
        ]
    lines += ["  /DISCARD/ : { *(*) }", "}"]
    for name, value in symbols.items():
        if not re.fullmatch(r"[A-Za-z_$][A-Za-z0-9_.$]*", name):
            raise ValueError(f"Invalid linker symbol name: {name}")
        if isinstance(value, dict):
            if value.get("kind") == "thumb_function":
                continue
            value = value["address"]
        lines.append(f"{name} = 0x{int(value, 0):08X};")
    return "\n".join(lines) + "\n"


def comparison_result(entry, expected, actual):
    """Report every section, including truncation/extension, without accepting it."""
    return dict(
        name=entry["name"], start=entry["start"], end=entry["end"],
        matched=actual == expected,
        expected_size=len(expected), actual_size=len(actual),
        expected_sha256=hashlib.sha256(expected).hexdigest(),
        actual_sha256=hashlib.sha256(actual).hexdigest(),
    )


def match(spec_path, output_dir, rom_path=None, session=None):
    spec = json.loads(Path(spec_path).read_text(encoding="utf-8"))
    source = spec["source"]
    compiler = spec.get("compiler", "agbcc")
    cflags = spec.get("cflags", [])
    entries = load_segments(entries=[dict(entry, source=source, kind=spec.get("kind", "c"), compiler=compiler, cflags=cflags) for entry in spec["segments"]])
    output = Path(output_dir).resolve()
    if not output.is_relative_to(ROOT / "build"):
        raise ValueError("Candidate output directory must be inside this project's build/ directory.")
    reference = find_rom(rom_path).read_bytes() if session is None else session.reference(rom_path)
    output.mkdir(parents=True, exist_ok=True)
    # A compilation/link failure must not leave a previous successful report.
    (output / "results.json").unlink(missing_ok=True)
    candidate = output / "candidate.o"
    if entries[0]["kind"] == "asm":
        run([tool("as"), "-mcpu=arm7tdmi", source, "-o", candidate])
    elif compiler == "agbcc":
        from compiler_agbcc import compile_source
        compile_source(source, candidate, cflags)
    elif compiler == "old_agbcc":
        from compiler_libgcc import compile_source
        compile_source(source, candidate, cflags)
    elif compiler == "gcc":
        run([tool("gcc"), *CFLAGS, *cflags, "-c", source, "-o", candidate])
    else:
        raise ValueError(f"Unsupported compiler: {compiler}")

    if session is None:
        symbols = json.loads((ROOT / "config/symbols.json").read_text(encoding="utf-8"))
        baseline = ROOT / "build/medabots.elf"
        if baseline.is_file():
            symbols.update(read_symbols(baseline))
    else:
        symbols = session.symbols()
    symbols.update(spec.get("symbols", {}))
    for name in read_symbols(candidate):
        symbols.pop(name, None)
    if session is None:
        symbols_source = output / "symbols.s"
        symbols_object = output / "symbols.o"
        symbols_source.write_text(generate_symbol_assembly(symbols), encoding="utf-8")
        run([tool("as"), "-mcpu=arm7tdmi", symbols_source, "-o", symbols_object])
    else:
        symbols_object = session.symbol_object(symbols, output)
    script = output / "candidate.ld"
    script.write_text(linker(entries, candidate.as_posix(), symbols), encoding="utf-8")
    elf = output / "candidate.elf"
    # Keep original addresses even if a candidate extends into the next section.
    # Each ELF section is extracted separately and compared in full below. This
    # option is deliberately confined to the isolated diagnostic linker; the
    # production ROM linker still enforces sizes and rejects overlaps.
    run([tool("ld"), "--no-check-sections", "-T", script, "-Map", output / "candidate.map", "-o", elf, candidate, symbols_object])
    listing = run([tool("objdump"), "-d", elf], capture_output=True, text=True).stdout
    (output / "candidate.disasm").write_text(listing, encoding="utf-8")
    results = []
    for entry in entries:
        binary = output / f"{entry['name']}.bin"
        run([tool("objcopy"), "-O", "binary", "-j", f".{entry['name']}", elf, binary])
        expected = reference[entry["start"]:entry["end"]]
        actual = binary.read_bytes()
        result = comparison_result(entry, expected, actual)
        matched = result["matched"]
        results.append(result)
        print(f"{'MATCH' if matched else 'MISMATCH'} {entry['name']}: {len(expected)} reference bytes, {len(actual)} emitted bytes")
        if not matched:
            differences = [(entry["start"] + i, a, b) for i, (a, b) in enumerate(zip(expected, actual)) if a != b]
            for address, a, b in differences[:12]:
                print(f"  ROM +0x{address:06X}: expected {a:02X}, got {b:02X}")
    (output / "results.json").write_text(json.dumps(results, indent=2) + "\n", encoding="utf-8")
    return all(result["matched"] for result in results)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("spec", help="JSON candidate specification")
    parser.add_argument("--output-dir", default="build/experiments/match")
    parser.add_argument("--rom")
    args = parser.parse_args()
    try:
        return 0 if match(args.spec, args.output_dir, args.rom) else 1
    except (ValueError, OSError, KeyError, subprocess.CalledProcessError) as error:
        print(f"Candidate verification failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
