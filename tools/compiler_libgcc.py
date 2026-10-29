"""Pinned old-agbcc variant used for the recovered GNU compiler runtime.

This is the upstream OLD_COMPILER build, compiled without source patches. Its
runtime settings follow libgcc/Makefile: -O2 and no Thumb interworking option.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import shlex
import shutil

import compiler_agbcc as normal
from common import ROOT, tool

BINARY = normal.DOWNLOAD_DIR / ("old_agbcc.exe" if os.name == "nt" else "old_agbcc")
METADATA = normal.DOWNLOAD_DIR / "old-provenance.json"
CFLAGS = ["-O2", "-ffunction-sections"]
CPPFLAGS = ["-E", "-P", "-x", "c", "-std=gnu89", "-nostdinc", "-undef", "-Isrc/libgcc/include", "-Iinclude"]


def bootstrap(force=False):
    if BINARY.is_file() and METADATA.is_file() and not force:
        metadata = json.loads(METADATA.read_text(encoding="utf-8"))
        if metadata.get("commit") == normal.COMMIT and metadata.get("binary_sha256") == hashlib.sha256(BINARY.read_bytes()).hexdigest():
            return BINARY
    normal.bootstrap()
    host_cc = normal._executable("gcc", "AGBCC_HOST_CC")
    make = normal._executable("make", "AGBCC_MAKE")
    source_gcc = normal.SOURCE_DIR / "gcc"
    if os.name == "nt":
        configured = os.environ.get("AGBCC_BASH")
        bash = Path(configured) if configured else Path(os.environ.get("ProgramFiles", "C:/Program Files")) / "Git/bin/bash.exe"
        if not bash.is_file():
            raise OSError("Git Bash is required on Windows; set AGBCC_BASH to its bash.exe")
        prefix = 'export PATH="$(cygpath -u ' + shlex.quote(str(host_cc.parent)) + '):$PATH"; '
        for target in ("clean", "old"):
            command = prefix + shlex.quote(make.as_posix()) + " " + target + " -j1 " + shlex.quote("CC=" + host_cc.as_posix())
            normal.run([bash, "--noprofile", "--norc", "-c", command], cwd=source_gcc)
    else:
        normal.run([make, "clean"], cwd=source_gcc)
        normal.run([make, "old", "-j1", "CC=" + str(host_cc)], cwd=source_gcc)
    shutil.copy2(source_gcc / BINARY.name, BINARY)
    metadata = {
        "upstream": normal.UPSTREAM, "commit": normal.COMMIT,
        "compiler_version": normal.VERSION, "target": "old",
        "host_compiler": normal.run([host_cc, "--version"], capture_output=True, text=True).stdout.splitlines()[0],
        "source_patches": [], "binary_sha256": hashlib.sha256(BINARY.read_bytes()).hexdigest(),
    }
    METADATA.write_text(json.dumps(metadata, indent=2) + "\n", encoding="utf-8")
    print(f"Built old_agbcc {normal.VERSION}: {BINARY}")
    return BINARY


def compile_source(source, output, cflags=()):
    if not BINARY.is_file():
        raise OSError("old_agbcc is missing; run python tools/compiler_libgcc.py bootstrap")
    output = Path(output)
    if not output.is_absolute():
        output = ROOT / output
    output.parent.mkdir(parents=True, exist_ok=True)
    preprocessed, generated = output.with_suffix(".i"), output.with_suffix(".s")
    normal.run([tool("gcc"), *CPPFLAGS, source, "-o", preprocessed])
    normal.run([BINARY, *CFLAGS, *cflags, preprocessed, "-o", generated])
    generated.write_text(normal._zero_align_executable_sections(generated.read_text(encoding="utf-8")), encoding="utf-8")
    normal.run([tool("as"), "-mcpu=arm7tdmi", generated, "-o", output])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    install = commands.add_parser("bootstrap")
    install.add_argument("--force", action="store_true")
    compile_parser = commands.add_parser("compile")
    compile_parser.add_argument("source")
    compile_parser.add_argument("output")
    args = parser.parse_args()
    if args.command == "bootstrap":
        bootstrap(args.force)
    else:
        compile_source(args.source, args.output)


if __name__ == "__main__":
    main()

