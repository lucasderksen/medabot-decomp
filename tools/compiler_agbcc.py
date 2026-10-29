"""Pinned historical Thumb compiler bootstrap and C compilation adapter.

Only downloads/build products below tools/downloads/agbcc are generated. The
compiler is upstream pret/agbcc, reporting GCC 2.9-arm-000512. ARM binutils and
the C preprocessor come from the project's existing arm-none-eabi toolchain.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import shutil
import subprocess

from common import ROOT, tool


UPSTREAM = "https://github.com/pret/agbcc.git"
COMMIT = "da598c1d918402c42c0c0d7128ba14567f3175e9"
VERSION = "2.9-arm-000512"
DOWNLOAD_DIR = ROOT / "tools" / "downloads" / "agbcc"
SOURCE_DIR = DOWNLOAD_DIR / "source"
BINARY = DOWNLOAD_DIR / ("agbcc.exe" if os.name == "nt" else "agbcc")
METADATA = DOWNLOAD_DIR / "provenance.json"
CFLAGS = ["-O2", "-mthumb-interwork", "-ffunction-sections", "-Werror"]
CPPFLAGS = ["-E", "-P", "-x", "c", "-std=gnu89", "-nostdinc", "-undef", "-Iinclude"]
# `asm(".include " "\"path\"")` as NONMATCH (include/global.h) expands in preprocessed C.
ASM_INCLUDE = re.compile(r'\.include[ "]*\\"([^"\\]+)\\"')


def run(command, cwd=ROOT, **kwargs):
    print("+ " + " ".join(str(part) for part in command), flush=True)
    return subprocess.run([str(part) for part in command], cwd=cwd, check=True, **kwargs)


def _executable(name, override=None):
    value = os.environ.get(override) if override else None
    located = shutil.which(value or name)
    if not located:
        raise OSError(f"{value or name} is required to build agbcc")
    return Path(located).resolve()


def bootstrap(force=False):
    """Build upstream's normal Thumb compiler, without the ARM/libc targets."""
    if BINARY.is_file() and METADATA.is_file() and not force:
        metadata = json.loads(METADATA.read_text(encoding="utf-8"))
        if metadata.get("commit") == COMMIT:
            return BINARY
    DOWNLOAD_DIR.mkdir(parents=True, exist_ok=True)
    git = _executable("git")
    host_cc = _executable("gcc", "AGBCC_HOST_CC")
    make = _executable("make", "AGBCC_MAKE")
    if not SOURCE_DIR.is_dir():
        run([git, "init", SOURCE_DIR])
        run([git, "remote", "add", "origin", UPSTREAM], cwd=SOURCE_DIR)
    run([git, "fetch", "--depth", "1", "origin", COMMIT], cwd=SOURCE_DIR)
    run([git, "checkout", "--detach", COMMIT], cwd=SOURCE_DIR)
    actual_commit = run([git, "rev-parse", "HEAD"], cwd=SOURCE_DIR, capture_output=True, text=True).stdout.strip()
    if actual_commit != COMMIT:
        raise ValueError("The downloaded agbcc source is not the pinned commit")
    source_gcc = SOURCE_DIR / "gcc"
    if os.name == "nt":
        configured_bash = os.environ.get("AGBCC_BASH")
        bash = Path(configured_bash) if configured_bash else Path(os.environ.get("ProgramFiles", "C:/Program Files")) / "Git" / "bin" / "bash.exe"
        if not bash.is_file():
            raise OSError("Git Bash is required on Windows; set AGBCC_BASH to its bash.exe")
        # Git Bash prepends its own DLL directory on startup. Put the MinGW
        # compiler directory first inside bash, or cc1 can silently fail.
        prefix = 'export PATH="$(cygpath -u ' + shlex.quote(str(host_cc.parent)) + '):$PATH"; '
        make_command = shlex.quote(make.as_posix())
        cc_assignment = shlex.quote("CC=" + host_cc.as_posix())
        for target in ("clean", "normal"):
            run([bash, "--noprofile", "--norc", "-c", prefix + make_command + " " + target + " -j1 " + cc_assignment], cwd=source_gcc)
    else:
        run([make, "clean"], cwd=source_gcc)
        run([make, "normal", "-j1", "CC=" + str(host_cc)], cwd=source_gcc)
    built = source_gcc / BINARY.name
    shutil.copy2(built, BINARY)
    host_version = run([host_cc, "--version"], capture_output=True, text=True).stdout.splitlines()[0]
    metadata = {
        "upstream": UPSTREAM,
        "commit": COMMIT,
        "compiler_version": VERSION,
        "host_compiler": host_version,
        "source_patches": [],
        "binary_sha256": hashlib.sha256(BINARY.read_bytes()).hexdigest(),
        "target": "normal",
    }
    METADATA.write_text(json.dumps(metadata, indent=2) + "\n", encoding="utf-8")
    print(f"Built agbcc {VERSION}: {BINARY}")
    return BINARY


def _zero_align_executable_sections(assembly):
    """Make historical zero-fill alignment explicit for modern GNU as.

    pret builds append .align 2,0 to generated assembly for this reason. With
    function sections, apply it to each executable section. The compiler's
    instructions, constants, and relocations are left as emitted.
    """
    sections = []
    for line in assembly.splitlines():
        if re.match(r"\s*\.text(?:\s|$)", line):
            name = ".text"
        else:
            match = re.match(r'\s*\.section\s+([^,\s]+)\s*,\s*"([^"]*)"', line)
            if not match or "x" not in match.group(2):
                continue
            name = match.group(1)
        if name not in sections:
            sections.append(name)
    suffix = ["", "@ Explicit historical zero-fill alignment for modern GNU as."]
    for section in sections:
        suffix += [f'.section {section},"ax",%progbits', ".align 2, 0"]
    return assembly.rstrip() + "\n" + "\n".join(suffix) + "\n"


def _compilation_key(source, preprocessed, cflags):
    """Content identity after preprocessing, including the emitting toolchain."""
    inputs = {
        "source": str((ROOT / source).resolve()),
        "preprocessed": hashlib.sha256(preprocessed.read_bytes()).hexdigest(),
        "compiler": hashlib.sha256(BINARY.read_bytes()).hexdigest(),
        "assembler": hashlib.sha256(Path(tool("as")).read_bytes()).hexdigest(),
        "adapter": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "cflags": [*CFLAGS, *cflags],
        "assembler_flags": ["-mcpu=arm7tdmi"],
        # NONMATCH functions (include/global.h) assemble these files in place.
        "assembler_includes": {path: hashlib.sha256((ROOT / path).read_bytes()).hexdigest()
                               for path in sorted(set(ASM_INCLUDE.findall(preprocessed.read_text(encoding="utf-8"))))
                               if (ROOT / path).is_file()},
    }
    return hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest()


def _cached_compilation(manifest, key, output, generated):
    try:
        recorded = json.loads(manifest.read_text(encoding="utf-8"))
        return (isinstance(recorded, dict) and recorded.get("key") == key
                and recorded.get("object") == hashlib.sha256(output.read_bytes()).hexdigest()
                and recorded.get("assembly") == hashlib.sha256(generated.read_bytes()).hexdigest())
    except (OSError, ValueError):
        return False


def compile_source(source, output, cflags=(), *, cache=False):
    """Compile ordinary C, optionally reusing an intact production object.

    Preprocessing always runs. Isolated matching/strict probes default to fresh
    compilation; the full build opts into content-checked object reuse.
    """
    if not BINARY.is_file():
        raise OSError("agbcc is missing; run python tools/compiler_agbcc.py bootstrap")
    output = Path(output)
    if not output.is_absolute():
        output = ROOT / output
    output.parent.mkdir(parents=True, exist_ok=True)
    preprocessed = output.with_suffix(".i")
    generated = output.with_suffix(".s")
    run([tool("gcc"), *CPPFLAGS, source, "-o", preprocessed])
    manifest = output.with_suffix(output.suffix + ".cache.json")
    key = _compilation_key(source, preprocessed, cflags) if cache else None
    if cache and _cached_compilation(manifest, key, output, generated):
        print(f"CACHE agbcc {source}", flush=True)
        return
    run([BINARY, *CFLAGS, *cflags, preprocessed, "-o", generated])
    emitted = generated.read_text(encoding="utf-8")
    generated.write_text(_zero_align_executable_sections(emitted), encoding="utf-8")
    run([tool("as"), "-mcpu=arm7tdmi", generated, "-o", output])
    if cache:
        manifest.write_text(json.dumps({
            "key": key,
            "object": hashlib.sha256(output.read_bytes()).hexdigest(),
            "assembly": hashlib.sha256(generated.read_bytes()).hexdigest(),
        }, indent=2) + "\n", encoding="utf-8")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)
    install = subparsers.add_parser("bootstrap", help="download pinned source and build agbcc")
    install.add_argument("--force", action="store_true")
    compile_parser = subparsers.add_parser("compile", help="compile one C source file")
    compile_parser.add_argument("source")
    compile_parser.add_argument("output")
    args = parser.parse_args()
    if args.command == "bootstrap":
        bootstrap(args.force)
    else:
        compile_source(args.source, args.output)


if __name__ == "__main__":
    main()
