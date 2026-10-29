"""Inspect the reference ROM and report source coverage without inflating progress."""

import argparse
import hashlib
import json
import re
import struct
import sys

from common import ROOT, find_rom, load_segments, rom_config


def offset(value, size):
    value = int(value, 0) if isinstance(value, str) else value
    base = int(rom_config()["rom_base"], 0)
    if value >= base:
        value -= base
    if not 0 <= value <= size:
        raise ValueError(f"Address outside ROM: {value:#x}")
    return value


def info(data):
    config = rom_config()
    branch = struct.unpack_from("<I", data)[0]
    delta = branch & 0xFFFFFF
    if delta & 0x800000:
        delta -= 1 << 24
    report = {
        "name": config["name"],
        "size": len(data),
        "sha1": hashlib.sha1(data).hexdigest(),
        "sha256": hashlib.sha256(data).hexdigest(),
        "title": data[0xA0:0xAC].decode("ascii"),
        "game_code": data[0xAC:0xB0].decode("ascii"),
        "maker_code": data[0xB0:0xB2].decode("ascii"),
        "revision": data[0xBC],
        "header_checksum_valid": data[0xBD] == (-sum(data[0xA0:0xBD]) - 0x19) & 0xFF,
        "arm_entrypoint": f"0x{int(config['rom_base'], 0) + 8 + delta * 4:08X}",
        "save_library_signatures": [m.group().decode("ascii") for m in re.finditer(rb"(?:EEPROM|FLASH1M|FLASH|SRAM)_V[0-9]{3}", data)],
    }
    return json.dumps(report, indent=2) + "\n"


def progress():
    segments = load_segments()
    unmatched = sum(s["end"] - s["start"] for s in segments if s.get("nonmatching"))
    counts = {kind: sum(s["end"] - s["start"] for s in segments if not s.get("nonmatching") and ("data" if s.get("category") == "data" else s["kind"]) == kind) for kind in ("c", "asm", "data")}
    runtime = sum(s["end"] - s["start"] for s in segments if s["kind"] == "c" and s.get("category") == "runtime")
    total = rom_config()["size"]
    lines = [f"Reference ROM: {total:,} bytes", f"Matching C code intervals: {counts['c']:,} bytes (includes literal pools)", f"Typed data intervals: {counts['data']:,} bytes", f"Assembly/header intervals: {counts['asm']:,} bytes (header includes 156 copied logo bytes)", f"Nonmatching functions (original assembly in NONMATCH, src/non_matching/): {unmatched:,} bytes", f"Remaining incbin intervals: {total - sum(counts.values()) - unmatched:,} bytes", "", "A complete matching rebuild is a baseline; it does not mean the game is fully decompiled.", ""]
    if runtime:
        lines.insert(2, f"  Game C: {counts['c'] - runtime:,} bytes; imported compiler-runtime C: {runtime:,} bytes")
    for segment in segments:
        lines.append(f"{segment['kind']:3} {segment['start']:06X}-{segment['end']:06X} {segment['end'] - segment['start']:4} bytes  {segment['source']}")
    return "\n".join(lines) + "\n"


def disassemble(data, start, length, mode):
    sys.path.insert(0, str(ROOT / "tools" / "python"))
    try:
        import capstone
    except ImportError as error:
        raise ValueError("Capstone is needed for disasm. Run python tools/bootstrap.py --analysis.") from error
    start = offset(start, len(data))
    if length <= 0 or start + length > len(data):
        raise ValueError("Disassembly range lies outside the ROM or has nonpositive length.")
    base = int(rom_config()["rom_base"], 0)
    engine = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_ARM if mode == "arm" else capstone.CS_MODE_THUMB)
    engine.skipdata = True
    engine.detail = True
    lines = ["; Linear disassembly only: literal pools/data can decode as bogus instructions."]
    for instruction in engine.disasm(data[start:start + length], base + start):
        annotation = ""
        if instruction.id and instruction.mnemonic == "ldr":
            for operand in instruction.operands:
                if operand.type == capstone.arm.ARM_OP_MEM and operand.mem.base == capstone.arm.ARM_REG_PC:
                    pc = instruction.address + (8 if mode == "arm" else 4)
                    if mode == "thumb":
                        pc &= ~3
                    literal = pc + operand.mem.disp
                    if base <= literal <= base + len(data) - 4:
                        value = struct.unpack_from("<I", data, literal - base)[0]
                        annotation = f"  ; [{literal:08X}] = {value:08X}"
        lines.append(f"{instruction.address:08X}: {instruction.bytes.hex():10} {instruction.mnemonic:8} {instruction.op_str}{annotation}")
    return "\n".join(lines) + "\n"


def xrefs(data, target, start, end):
    base = int(rom_config()["rom_base"], 0)
    value = int(target, 0) if isinstance(target, str) else target
    if not 0 <= value <= 0xFFFFFFFF:
        raise ValueError("Reference target must be a 32-bit address or ROM offset.")
    destination = base + value if value < len(data) else value
    destination &= ~1
    begin = offset(start, len(data))
    stop = offset(end, len(data))
    if begin % 2 or stop % 2 or begin > stop:
        raise ValueError("Thumb scan bounds must be even and ordered.")
    lines = [f"Candidate references to 0x{destination:08X}; validate code/data boundaries before naming functions."]
    for index in range(0, len(data) - 3, 4):
        pointer = struct.unpack_from("<I", data, index)[0]
        if pointer in (destination, destination | 1):
            lines.append(f"WORD {base + index:08X}: {pointer:08X}")
    for index in range(begin, min(stop, len(data) - 3), 2):
        high, low = struct.unpack_from("<HH", data, index)
        if high & 0xF800 == 0xF000 and low & 0xF800 == 0xF800:
            displacement = ((high & 0x7FF) << 12) | ((low & 0x7FF) << 1)
            if displacement & 0x400000:
                displacement -= 0x800000
            if base + index + 4 + displacement == destination:
                lines.append(f"BL   {base + index:08X}")
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", help="Reference ROM path; default: locate the supported dump")
    parser.add_argument("--output", help="Write analysis text to this file")
    commands = parser.add_subparsers(dest="command", required=True)
    commands.add_parser("info")
    commands.add_parser("progress")
    disasm_parser = commands.add_parser("disasm")
    disasm_parser.add_argument("--start", required=True, help="ROM offset or GBA address")
    disasm_parser.add_argument("--size", type=lambda text: int(text, 0), required=True)
    disasm_parser.add_argument("--mode", choices=("arm", "thumb"), default="thumb")
    xrefs_parser = commands.add_parser("xrefs")
    xrefs_parser.add_argument("target")
    xrefs_parser.add_argument("--start", default="0x25C")
    xrefs_parser.add_argument("--end", default="0x7CCC0", help="Provisional Thumb scan limit; false positives are possible")
    args = parser.parse_args()
    try:
        if args.command == "progress":
            result = progress()
        else:
            data = find_rom(args.rom).read_bytes()
            if args.command == "info":
                result = info(data)
            elif args.command == "disasm":
                result = disassemble(data, args.start, args.size, args.mode)
            else:
                result = xrefs(data, args.target, args.start, args.end)
        if args.output:
            from pathlib import Path
            destination = Path(args.output)
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_text(result, encoding="utf-8")
        else:
            print(result, end="")
        return 0
    except (ValueError, OSError) as error:
        print(f"Analysis failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
