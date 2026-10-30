"""Compile source sections, link the complete ROM, and enforce an exact match."""

import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import time

from common import ROOT, layout, load_segments, prepare_rom, rom_config, tool

CFLAGS = ["-mcpu=arm7tdmi", "-mthumb", "-O2", "-falign-functions=2", "-ffreestanding", "-fno-builtin", "-fno-ident", "-fno-unwind-tables", "-fno-asynchronous-unwind-tables", "-ffunction-sections", "-fdata-sections", "-Wall", "-Wextra", "-Werror", "-Iinclude"]


def run(command):
    print("+ " + " ".join(str(part) for part in command), flush=True)
    subprocess.run(command, cwd=ROOT, check=True)


def object_path(source):
    """Keep assembly/C files with the same stem in distinct object paths."""
    return (Path("build/obj") / (source + ".o")).as_posix()


def generate_linker(entries, base, symbols=None):
    lines = ["OUTPUT_ARCH(arm)", "ENTRY(AgbMain)", "SECTIONS", "{"]
    for entry in entries:
        section = f".{entry['name']}"
        if entry["kind"] == "raw":
            obj, input_section = "build/obj/remainder.o", section
        else:
            obj = object_path(entry["source"])
            input_section = entry["input_section"]
        lines.append(f"  {section} 0x{base + entry['start']:08X} : {{ {obj}({input_section}) }}")
        lines.append(f'  ASSERT(SIZEOF({section}) == 0x{entry["end"] - entry["start"]:X}, "Size mismatch: {entry["name"]}")')
    # NONMATCH functions (include/global.h) assemble the original code; agbcc can
    # still emit constants for their dead C attempt, which must not reach the ROM.
    dead = " ".join(f"{object_path(entry['source'])}(.rodata)" for entry in entries if entry.get("nonmatching"))
    if dead:
        lines.append(f"  /DISCARD/ : {{ {dead} }}")
    lines += [
        "  .unexpected : { *(.text) *(.text.*) *(.data) *(.data.*) *(.rodata*) *(.bss*) *(COMMON) *(.glue_7) *(.glue_7t) *(.vfp11_veneer) *(.v4_bx) *(.iplt) *(.rel.iplt) *(.igot.plt) }",
        '  ASSERT(SIZEOF(.unexpected) == 0, "Unexpected code/data: add it to config/segments.json")',
        "  /DISCARD/ : { *(.ARM.attributes) *(.comment) *(.note*) *(.ARM.exidx*) *(.ARM.extab*) }",
        "}",
    ]
    for name, address in (symbols or {}).items():
        if isinstance(address, dict):
            if address.get("kind") == "thumb_function":
                continue
            address = address["address"]
        lines.append(f"{name} = {address};")
    return "\n".join(lines) + "\n"


def generate_symbol_assembly(symbols):
    """Copied Thumb functions need ELF type/state metadata to avoid ARM veneers."""
    lines = [".syntax unified", ".cpu arm7tdmi", ".thumb"]
    for name, entry in symbols.items():
        if isinstance(entry, dict) and entry.get("kind") == "thumb_function":
            lines += [f".global {name}", f".type {name}, %function", f".thumb_set {name}, {entry['address']}"]
    return "\n".join(lines) + "\n"


def compare(reference, rebuilt, entries):
    print(f"Reference: {hashlib.sha256(reference).hexdigest()}")
    print(f"Rebuilt:   {hashlib.sha256(rebuilt).hexdigest()}")
    differences = []
    for entry in entries:
        start, end = entry["start"], entry["end"]
        if reference[start:end] != rebuilt[start:end]:
            differences.append(entry["name"])
            print(f"MISMATCH: {entry['name']} (0x{start:06X}-0x{end:06X})")
    if reference == rebuilt:
        print(f"MATCH: all {len(reference):,} bytes are identical.")
        return True
    if len(reference) != len(rebuilt):
        print(f"Size mismatch: expected {len(reference)}, got {len(rebuilt)}.")
    count = 0
    for offset, (expected, actual) in enumerate(zip(reference, rebuilt)):
        if expected != actual:
            print(f"  ROM +0x{offset:06X}: expected {expected:02X}, got {actual:02X}")
            count += 1
            if count == 12:
                break
    return False


def replace_verified_artifact(source, destination):
    """Allow brief Windows reader/scanner locks without publishing unverified data."""
    for attempt in range(20):
        try:
            source.replace(destination)
            return
        except OSError as error:
            if getattr(error, "winerror", None) not in (5, 32, 33) or attempt == 19:
                raise
            time.sleep(0.1)


def compare_hash(rebuilt, config):
    """Without a dump: the rebuilt image must have the documented size, SHA-1 and SHA-256."""
    print(f"Rebuilt:   {hashlib.sha256(rebuilt).hexdigest()}")
    if (len(rebuilt) == config["size"] and hashlib.sha1(rebuilt).hexdigest() == config["sha1"]
            and hashlib.sha256(rebuilt).hexdigest() == config["sha256"]):
        print(f"MATCH: all {len(rebuilt):,} bytes match the documented SHA-1 and SHA-256 (no dump supplied).")
        return True
    print("MISMATCH: the rebuilt image does not have the documented hashes. Supply your dump for a byte-level comparison.")
    return False


def build(rom_path=None):
    config = rom_config()
    segments = load_segments()
    entries = layout(segments, config["size"])
    # Source covers every byte, so a dump is only needed for .incbin gaps and for
    # byte-level diagnostics; without one the result is checked by hash.
    try:
        reference_path = prepare_rom(rom_path)
    except ValueError:
        if rom_path or any(entry["kind"] == "raw" for entry in entries) or any(ROOT.glob("*.gba")):
            raise
        reference_path = None
    base = int(config["rom_base"], 0)
    output = ROOT / "build"
    (output / "obj").mkdir(parents=True, exist_ok=True)
    candidate = output / "candidate"
    candidate.mkdir(exist_ok=True)
    raw = [".syntax unified", ".cpu arm7tdmi"]
    for entry in entries:
        if entry["kind"] == "raw":
            raw += [f'.section .{entry["name"]}, "a", %progbits', f'.incbin "baserom.gba", 0x{entry["start"]:X}, 0x{entry["end"] - entry["start"]:X}']
    (output / "remainder.s").write_text("\n".join(raw) + "\n", encoding="utf-8")
    symbols_path = ROOT / "config" / "symbols.json"
    symbols = json.loads(symbols_path.read_text(encoding="utf-8")) if symbols_path.exists() else {}
    (output / "rom.ld").write_text(generate_linker(entries, base, symbols), encoding="utf-8")
    (output / "symbols.s").write_text(generate_symbol_assembly(symbols), encoding="utf-8")
    objects = []
    compiled = set()
    for entry in segments:
        source = entry["source"]
        if source in compiled:
            continue
        compiled.add(source)
        obj = object_path(source)
        (ROOT / obj).parent.mkdir(parents=True, exist_ok=True)
        objects.append(obj)
        if entry["kind"] == "c":
            compiler = entry.get("compiler", "gcc")
            if compiler == "agbcc":
                from compiler_agbcc import compile_source
                compile_source(source, obj, entry.get("cflags", []), cache=True)
            elif compiler == "old_agbcc":
                from compiler_libgcc import compile_source
                compile_source(source, obj, entry.get("cflags", []))
            elif compiler == "gcc":
                run([tool("gcc"), *CFLAGS, *entry.get("cflags", []), "-c", source, "-o", obj])
            else:
                raise ValueError(f"Unsupported compiler: {compiler}")
        else:
            run([tool("as"), "-mcpu=arm7tdmi", source, "-o", obj])
    run([tool("as"), "-mcpu=arm7tdmi", "build/remainder.s", "-o", "build/obj/remainder.o"])
    run([tool("as"), "-mcpu=arm7tdmi", "build/symbols.s", "-o", "build/obj/symbols.o"])
    # The object list exceeds the Windows command-line limit, so it goes through
    # a response file in link order (forward slashes: backslashes are escapes).
    link_objects = candidate / "link_objects.rsp"
    link_objects.write_text("\n".join(Path(item).as_posix() for item in [*objects, "build/obj/remainder.o", "build/obj/symbols.o"]) + "\n", encoding="utf-8")
    run([tool("ld"), "--no-warn-rwx-segments", "--orphan-handling=error", "-T", "build/rom.ld", "-Map", candidate / "medabots.map", "-o", candidate / "medabots.elf", f"@{link_objects}"])
    run([tool("objcopy"), "-O", "binary", candidate / "medabots.elf", candidate / "medabots.gba"])
    # One -j per segment exceeds the Windows command-line limit, so the section
    # list goes through a response file (names contain no quotes or spaces).
    sections = candidate / "disasm_sections.rsp"
    sections.write_text("\n".join(f"-j .{entry['name']}" for entry in segments) + "\n", encoding="utf-8")
    listing_command = [tool("objdump"), "-d", f"@{sections}", candidate / "medabots.elf"]
    listing = subprocess.run(listing_command, cwd=ROOT, check=True, capture_output=True, text=True)
    (candidate / "medabots.disasm").write_text(listing.stdout, encoding="utf-8")
    rebuilt = (candidate / "medabots.gba").read_bytes()
    matched = compare(reference_path.read_bytes(), rebuilt, entries) if reference_path else compare_hash(rebuilt, config)
    if matched:
        for suffix in ("elf", "map", "disasm", "gba"):
            replace_verified_artifact(candidate / ("medabots." + suffix), output / ("medabots." + suffix))
    else:
        print("Failed candidate retained in build/candidate; published build files remain from the last successful comparison.")
    return matched


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", help="Path to the supported cartridge dump")
    args = parser.parse_args()
    try:
        matched = build(args.rom)
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        print(f"Build failed: {error}", file=sys.stderr)
        return 1
    return 0 if matched else 1


if __name__ == "__main__":
    sys.exit(main())
