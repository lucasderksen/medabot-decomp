"""Search C variations of an m2c draft with decomp-permuter-agbcc.

For near-misses (correct size, a few differing instructions) the permuter
randomly rewrites the draft (temporaries, statement order, types, ...) and keeps
variants that score closer to the reference. Score 0 means byte-identical code
for the function. Each function runs in its own isolated permuter process.
Windows compiler routing is also installed in spawned permutation workers.

    python tools/m2c_candidate.py 0x080191A4 --match       # creates the draft
    python tools/permute.py sub_080191A4 --cflags "-fprologue-bugfix -fno-regmove" --seconds 300
    python tools/permute.py --batch build/m2c/near_misses.json --jobs 12 --seconds 600

Inputs come from build/m2c/<name>/ (draft) and build/m2c/<name>.s (reference
assembly). Results: build/permuter/<name>/run-*/output-<score>-<n>/source.c. A score-0
source is still a candidate: compile it through tools/match.py and review it.
"""

import argparse
import json
import os
import re
import shutil
from pathlib import Path
import subprocess
import sys
import tempfile
import time

from common import ROOT, tool
from c_source import function_definition

PERMUTER = ROOT / "tools" / "downloads" / "permuter"
OUTPUT = ROOT / "build" / "permuter"


def strip_asm_labels(path):
    """Remove `asm("symbol")` declaration labels from a preprocessed file; return {name: symbol}."""
    aliases = {}
    if not Path(path).exists():  # preprocessing mocked out (tests)
        return aliases
    text = Path(path).read_text(encoding="utf-8")
    pattern = re.compile(r'\b(\w+)((?:\s*\[[^\]]*\])*)\s*(?:__asm__|asm)\s*\(\s*"\*?([^"]+)"\s*\)')

    def replace(match):
        if match.group(1) != match.group(3):
            aliases[match.group(1)] = match.group(3)
        return match.group(1) + match.group(2)

    Path(path).write_text(pattern.sub(replace, text), encoding="utf-8")
    return aliases


PIN = r'\s*(?:__asm__|asm)\s*\(\s*"(r\d+|sb|sl|fp|ip)"\s*\)'


def strip_register_pins(path):
    """Remove `register T x asm("rN")` pins (pycparser rejects them); return {name: register}.

    The `register` keyword stays, so apply_pins can find the declaration again
    in every variant and the permuter searches with the pins in place.
    """
    pins = {}
    if not Path(path).exists():  # preprocessing mocked out (tests)
        return pins
    text = Path(path).read_text(encoding="utf-8")

    def replace(match):
        pins[match.group(2)] = match.group(3)
        return match.group(1)

    Path(path).write_text(re.sub(r"(\bregister\b[^;{}()=]*?\b(\w+))" + PIN, replace, text), encoding="utf-8")
    return pins


def apply_pins(text, pins):
    """Put the stripped register pins back on their `register` declarations."""
    for name, register in pins.items():
        text = re.sub(rf"(\bregister\b[^;{{}}()=]*?\b{name})(?=\s*[=;,])", rf'\1 asm("{register}")', text)
    return text


def compile_candidate(source, output):
    """Called by the permuter for every variant: the real agbcc pipeline."""
    from compiler_agbcc import compile_source
    cflags = ["-w", *os.environ.get("MEDABOTS_PERMUTE_CFLAGS", "").split()]
    pins = dict(pair.split("=") for pair in os.environ.get("MEDABOTS_PERMUTE_PINS", "").split(",") if pair)
    if pins:
        Path(source).write_text(apply_pins(Path(source).read_text(encoding="utf-8"), pins), encoding="utf-8")
    try:
        compile_source(source, output, cflags)
        aliases = [pair for pair in os.environ.get("MEDABOTS_PERMUTE_ALIASES", "").split(",") if pair]
        if aliases:
            subprocess.run([tool("objcopy"), *[f"--redefine-sym={pair}" for pair in aliases], output],
                           check=True)
    finally:
        # compile_source keeps .i/.s beside the object; in %TEMP% they pile up by
        # the thousand (the permuter only deletes its own .c and .o).
        for suffix in (".i", ".s"):
            Path(output).with_suffix(suffix).unlink(missing_ok=True)


def normalize_reference(text, section, symbols, undefined):
    """Use unique equal-address seed aliases without changing relocation values.

    Names at the same address must not create an artificial scorer penalty.
    Keep full addresses: an odd data address and a Thumb function state bit
    are both meaningful. Ambiguous aliases and relocation expressions stay
    unchanged. The caller must also relink and byte-verify the entire target.
    """
    def address(value):
        value = value["address"] if isinstance(value, dict) else value
        return int(value, 0) if isinstance(value, str) else value

    choices = {}
    for name in undefined:
        if name in symbols:
            choices.setdefault(address(symbols[name]), set()).add(name)
    rewrites = {}
    words = re.compile(r"(?m)^(\s*\.word\s+)([A-Za-z_$][\w.$]*)([ \t]*)$")

    def replace(match):
        name = match[2]
        aliases = choices.get(address(symbols[name]), set()) if name in symbols else set()
        if len(aliases) == 1 and name not in aliases:
            replacement = next(iter(aliases))
            rewrites[name] = replacement
            return match[1] + replacement + match[3]
        return match[0]

    text = words.sub(replace, text)
    # Capstone prints the Thumb high-register ADD Rn, SP as Rn, SP, Rn.
    # GNU as needs its two-operand spelling; immediate SP additions and
    # different destinations are intentionally untouched. The full target
    # reconstruction gate below proves the instruction encoding unchanged.
    text = re.sub(r'(?m)^(\s*add[ \t]+)(r(?:[0-9]|1[0-2])),[ \t]*sp,[ \t]*\2[ \t]*$',
                  r'\1\2, sp', text)
    text = re.sub(r'(?m)^[ \t]*\.text[ \t]*$',
                  f'.section {section},"ax",%progbits', text)
    return text, rewrites


def prepare_reference(name, seed, cflags, directory):
    """Normalize scorer names, then prove the original target bytes unchanged."""
    from compiler_agbcc import compile_source
    from match import MatchSession, linker

    spec = json.loads(seed.with_name("spec.json").read_text(encoding="utf-8"))
    session = MatchSession()
    symbols = dict(session.symbols())
    symbols.update(spec.get("symbols", {}))
    text = (ROOT / "build/m2c" / f"{name}.s").read_text(encoding="utf-8")
    # A decoded odd ROM data word may have no canonical ELF name yet.
    for alias in re.findall(r"(?m)^\s*\.word\s+(D_[0-9A-Fa-f]{8})[ \t]*$", text):
        symbols.setdefault(alias, "0x" + alias[2:])
    seed_object = directory / "seed.o"
    # Search inputs may need warning cleanup; this is symbol extraction only.
    # Score-zero C still goes through verify() and its strict acceptance gate.
    compile_source(seed, seed_object, ["-w", *cflags])
    listing = subprocess.run([tool("readelf"), "-sW", seed_object],
                             capture_output=True, text=True, check=True).stdout
    undefined = {line.split()[-1] for line in listing.splitlines()
                 if len(line.split()) == 8 and line.split()[-2] == "UND"}
    section = f".text.m2c_{name}"
    text, rewrites = normalize_reference(text, section, symbols, undefined)
    target = directory / "target.s"
    target.write_text(text, encoding="utf-8")
    subprocess.run([tool("as"), "-mcpu=arm7tdmi", target, "-o", directory / "target.o"],
                   cwd=ROOT, check=True)
    symbols.pop(name, None)
    symbol_object = session.symbol_object(symbols, directory)
    entry = dict(spec["segments"][0], input_section=section)
    entry.update(start=int(entry["start"], 0), end=int(entry["end"], 0))
    script = directory / "target_check.ld"
    script.write_text(linker([entry], (directory / "target.o").as_posix(), symbols), encoding="utf-8")
    elf = directory / "target_check.elf"
    subprocess.run([tool("ld"), "-T", script, "-o", elf, directory / "target.o", symbol_object],
                   cwd=ROOT, capture_output=True, check=True)
    binary = directory / "target_check.bin"
    subprocess.run([tool("objcopy"), "-O", "binary", "-j", "." + entry["name"], elf, binary],
                   cwd=ROOT, capture_output=True, check=True)
    actual = binary.read_bytes()
    if actual != session.reference()[entry["start"]:entry["end"]]:
        raise ValueError(f"{name}: permutation reference reconstruction changed ROM bytes")
    (directory / "normalization.json").write_text(json.dumps({
        "rewrites": rewrites, "reference_bytes_verified": len(actual), "cflags": cflags
    }, indent=2) + "\n", encoding="utf-8")


def restore_inline_helpers(original, stripped, target):
    """Keep inline bodies: replacing them with declarations changes the seed."""
    pattern = r"^[^\n;{}]*\binline\b[^\n;{}]*?\b(\w+)\s*\([^;{}]*\)\s*\{"
    for found in re.finditer(pattern, original, re.M):
        name = found.group(1)
        if name == target:
            continue
        definition = function_definition(original, name)
        declaration = definition[:definition.index('{')].rstrip() + ';'
        if declaration not in stripped:
            raise ValueError(f"Inline helper declaration missing after stripping: {name}")
        stripped = stripped.replace(declaration, definition, 1)
    return stripped


def setup(name, cflags):
    draft = ROOT / "build" / "m2c" / name
    if not (draft / "candidate.c").exists():
        raise SystemExit(f"No draft for {name}; run tools/m2c_candidate.py <address> --match first.")
    parent = OUTPUT / name
    parent.mkdir(parents=True, exist_ok=True)
    # A different seed/profile must not inherit an older run's saved score or
    # score-zero source. Preserve those artifacts in their original directory.
    directory = Path(tempfile.mkdtemp(prefix="run-", dir=parent))
    base = directory / "base.c"
    subprocess.run([tool("gcc"), "-E", "-P", "-x", "c", "-std=gnu89", "-nostdinc", "-undef", "-D__attribute__(x)=",
                    "-Iinclude", f"-I{draft}", draft / "candidate.c", "-o", base], cwd=ROOT, check=True)
    function = f"m2c_{name}"
    # pycparser rejects `extern T view asm("symbol");` label views. Drop the labels
    # here and rename the C names back to their symbols in every compiled
    # variant (compile_candidate), so relocations match the real build.
    pins = strip_register_pins(base)
    (directory / "pins.txt").write_text(",".join(f"{k}={v}" for k, v in pins.items()), encoding="utf-8")
    aliases = strip_asm_labels(base)
    (directory / "asm_aliases.txt").write_text(",".join(f"{k}={v}" for k, v in aliases.items()), encoding="utf-8")
    original = base.read_text(encoding="utf-8") if base.exists() else None
    subprocess.run([sys.executable, PERMUTER / "strip_other_fns.py", base, function], cwd=ROOT, check=True)
    if original is not None:
        base.write_text(restore_inline_helpers(original, base.read_text(encoding="utf-8"), function), encoding="utf-8")
    prepare_reference(name, draft / "candidate.c", cflags, directory)
    (directory / "compile.sh").write_text("# Replaced by tools/permute.py on Windows.\n", encoding="utf-8")
    (directory / "settings.toml").write_text(f'func_name = "{function}"\ncompiler_type = "gcc"\n', encoding="utf-8")
    (directory / "cflags.txt").write_text(" ".join(cflags) + "\n", encoding="utf-8")
    return directory


def best_score(directory):
    scores = [int(path.name.split("-")[1]) for path in directory.glob("output-*-*") if path.is_dir()]
    return min(scores) if scores else None


def run(name, cflags, seconds, jobs=1):
    directory = setup(name, cflags)
    environment = dict(os.environ, MEDABOTS_PERMUTE_CFLAGS=" ".join(cflags))
    environment["MEDABOTS_PERMUTE_ALIASES"] = (directory / "asm_aliases.txt").read_text(encoding="utf-8")
    environment["MEDABOTS_PERMUTE_PINS"] = (directory / "pins.txt").read_text(encoding="utf-8")
    environment["PATH"] = str(Path(tool("objdump")).parent) + os.pathsep + environment["PATH"]
    # Every variant is compiled through temporary files. Keep them on the project
    # drive (not C:\...\Temp), one folder per function, removed after the run.
    scratch = directory / "tmp"
    shutil.rmtree(scratch, ignore_errors=True)
    scratch.mkdir(parents=True)
    environment.update(TEMP=str(scratch), TMP=str(scratch), TMPDIR=str(scratch))
    command = [sys.executable, "-u", __file__, "--run-permuter", str(directory), "--stop-on-zero", "--best-only", "--quiet"]
    if jobs > 1:
        command += ["-j", str(jobs)]
    log = (directory / "permuter.log").open("w", encoding="utf-8")
    process = subprocess.Popen(command, cwd=PERMUTER, env=environment, stdout=log, stderr=subprocess.STDOUT)
    try:
        process.wait(timeout=seconds)
    except subprocess.TimeoutExpired:
        # Kill the whole tree: -j runs leave multiprocessing helpers behind otherwise.
        if os.name == "nt":
            subprocess.run(["taskkill", "/T", "/F", "/PID", str(process.pid)], capture_output=True)
        process.kill()
        process.wait()
    log.close()
    shutil.rmtree(scratch, ignore_errors=True)
    score = best_score(directory)
    source = next((p / "source.c" for p in sorted(directory.glob("output-0-*"))), None)
    result = {"name": name, "cflags": cflags, "directory": str(directory), "best_score": score, "source": str(source) if source else None, "verified": False}
    if source:
        pins = dict(pair.split("=") for pair in environment["MEDABOTS_PERMUTE_PINS"].split(",") if pair)
        result.update(verify(name, source, cflags, pins))
    return result


def extract_function(text, function):
    """The permuter's definition of `function`, brace moved onto the signature line."""
    body = function_definition(text, function)
    return re.sub(r"\)\s*\n\{", ") {", body, count=1)


def verify(name, source, cflags, pins=None):
    """Byte-compare the score-0 variant via tools/match.py; on success replace the draft."""
    import contextlib
    import io
    from match import match
    draft = ROOT / "build" / "m2c" / name
    spec = json.loads((draft / "spec.json").read_text(encoding="utf-8"))
    function = extract_function(Path(source).read_text(encoding="utf-8"), f"m2c_{name}")
    candidate = (draft / "candidate.c").read_text(encoding="utf-8")
    old = extract_function(candidate, name)  # the draft defines `name`; a macro renames it to m2c_<name>
    permuted = apply_pins(function.replace(f"m2c_{name}", name), pins or {})
    verified_source = draft / "permuted.c"
    verified_source.write_text(candidate.replace(old, permuted), encoding="utf-8")
    spec.update(source=verified_source.relative_to(ROOT).as_posix(), cflags=["-w", *cflags])
    spec_path = draft / "permuted_spec.json"
    spec_path.write_text(json.dumps(spec, indent=2) + "\n", encoding="utf-8")
    with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
        matched = match(spec_path, draft / "permuted_match")
    from m2c_candidate import extra_sections
    extra = extra_sections(draft / "permuted_match" / "candidate.o", spec["segments"][0]["input_section"])
    if not matched or extra:
        return {"verified": False, "extra_sections": extra}
    # Variants are searched with -w; production builds use -Werror. Report
    # whether this one needs a cleanup (e.g. a const local assigned later).
    from compiler_agbcc import compile_source
    try:
        with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
            compile_source(verified_source, draft / "permuted_match" / "strict.o", cflags)
        clean = True
    except subprocess.CalledProcessError:
        clean = False
    # Integration (tools/m2c_integrate.py) reads the draft text and solved.json.
    draft_c = ROOT / "build" / "m2c" / f"{name}.c"
    draft_c.write_text(draft_c.read_text(encoding="utf-8").replace(extract_function(draft_c.read_text(encoding="utf-8"), name), permuted),
                       encoding="utf-8")
    segment = spec["segments"][0]
    solved_path = OUTPUT / "solved.json"
    solved = json.loads(solved_path.read_text(encoding="utf-8")) if solved_path.exists() else []
    solved = [entry for entry in solved if entry["name"] != name] + [
        {"name": name, "start": segment["start"], "end": segment["end"], "cflags": cflags, "compiles_with_werror": clean}]
    solved_path.write_text(json.dumps(solved, indent=2) + "\n", encoding="utf-8")
    return {"verified": True, "compiles_with_werror": clean}


def batch(path, jobs, seconds, all_kinds=False):
    entries = json.loads(Path(path).read_text(encoding="utf-8"))
    close = [entry for entry in entries if entry.get("kind") in ("registers only", "few rows (<=3)")]
    pending = entries if all_kinds or not close else close
    solved = set()
    for solved_path in (OUTPUT / "solved.json", ROOT / "build" / "m2c" / "manual_solved.json"):
        if solved_path.exists():
            solved |= {entry["name"] for entry in json.loads(solved_path.read_text(encoding="utf-8"))}
    pending = [entry for entry in pending if entry["name"] not in solved]
    print(f"Permuting {len(pending)} functions, {jobs} at a time, {seconds} s each", flush=True)
    running, results = [], []
    while pending or running:
        while pending and len(running) < jobs:
            entry = pending.pop(0)
            command = [sys.executable, __file__, entry["name"], f"--cflags={' '.join(entry['cflags'])}", "--seconds", str(seconds), "--jobs", "1", "--json"]
            running.append(subprocess.Popen(command, cwd=ROOT, stdout=subprocess.PIPE, text=True))
        time.sleep(2)
        for process in [p for p in running if p.poll() is not None]:
            running.remove(process)
            output = process.stdout.read().strip().splitlines()
            if output:
                result = json.loads(output[-1])
                results.append(result)
                print(json.dumps(result), flush=True)
    solved = [r for r in results if r["best_score"] == 0]
    print(f"\n{len(solved)} of {len(results)} reached score 0")
    (OUTPUT / "batch.json").write_text(json.dumps(results, indent=2) + "\n", encoding="utf-8")


def main():
    if len(sys.argv) == 5 and sys.argv[1] == "--compile":  # SOURCE -o OUTPUT, from the permuter
        compile_candidate(sys.argv[2], sys.argv[4])
        return 0
    if len(sys.argv) > 1 and sys.argv[1] == "--run-permuter":
        sys.argv = [str(PERMUTER / "permuter.py"), *sys.argv[2:]]
        from src.main import main as permuter_main  # noqa: imported from PERMUTER (cwd)
        return permuter_main()
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("name", nargs="?", help="Draft name, e.g. sub_080191A4")
    parser.add_argument("--cflags", default="-fprologue-bugfix")
    parser.add_argument("--seconds", type=int, default=300)
    parser.add_argument("--batch", help="near_misses.json-style list of {name, cflags}")
    parser.add_argument("--all-kinds", action="store_true", help="Batch: also try near-misses with many differing rows")
    parser.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 2) - 2))
    parser.add_argument("--json", action="store_true", help=argparse.SUPPRESS)
    args = parser.parse_args()
    if not (PERMUTER / "permuter.py").exists():
        raise SystemExit("decomp-permuter-agbcc is missing. Run python tools/bootstrap.py --permuter.")
    if args.batch:
        return batch(args.batch, args.jobs, args.seconds, args.all_kinds)
    if not args.name:
        parser.error("name is required unless --batch is given")
    result = run(args.name, args.cflags.split(), args.seconds, args.jobs)
    print(json.dumps(result) if args.json else
          f"{result['name']}: best score {result['best_score']}" + (f"; score-0 source {result['source']}" if result["source"] else ""))
    return 0


# The permuter runs "<dir>/compile.sh" directly, which Windows cannot execute.
# Route it to compile_candidate(); this runs at import time so it also applies
# in any process the permuter spawns.
# Windows spawn imports this file as __mp_main__ after the parent has already
# replaced --run-permuter in sys.argv with the permuter's own arguments.
if (len(sys.argv) > 1 and sys.argv[1] == "--run-permuter") or __name__ == "__mp_main__":
    sys.path.insert(0, str(PERMUTER))
    sys.path.insert(0, str(ROOT / "tools" / "python"))
    import src.compiler as _permuter_compiler

    class _Subprocess:
        def __getattr__(self, attribute):
            return getattr(subprocess, attribute)

        @staticmethod
        def check_call(command, **kwargs):
            if command and str(command[0]).endswith("compile.sh"):
                command = [sys.executable, __file__, "--compile", *map(str, command[1:])]
            return subprocess.check_call(command, **kwargs)

        @staticmethod
        def check_output(command, **kwargs):
            # The permuter preprocesses with a bare `cpp`; use the project's.
            if command and command[0] == "cpp":
                command = [tool("gcc"), "-E", "-x", "c", *command[1:]]
            return subprocess.check_output(command, **kwargs)

    _permuter_compiler.subprocess = _Subprocess()
    import src.preprocess as _permuter_preprocess
    _permuter_preprocess.subprocess = _Subprocess()

    import src.main as _permuter_main

    class _Os:
        """os, except compile.sh counts as executable (Windows has no exec bit)."""
        def __getattr__(self, attribute):
            return getattr(os, attribute)

        @staticmethod
        def stat(path, *args, **kwargs):
            result = os.stat(path, *args, **kwargs)
            if str(path).endswith("compile.sh"):
                return os.stat_result((result.st_mode | 0o100, *tuple(result)[1:]))
            return result

    _permuter_main.os = _Os()


if __name__ == "__main__":
    sys.exit(main())
