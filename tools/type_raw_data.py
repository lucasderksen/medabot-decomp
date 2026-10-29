"""Type every remaining raw data gap as a labelled array (AGENTS.md data rule, 29 October 2026).

    python tools/type_raw_data.py            # rewrite src/unknown_data_*.c and config/segments.json
    python tools/type_raw_data.py --dry-run  # only list what would be typed

Gaps before --from (the code region) are left alone: they are unmatched
functions, not data. Each gap becomes one array in its own section and one
segment entry. A gap that already has a name in config/symbols.json keeps it
(and loses its absolute symbol); all-zero gaps of one to three bytes that end
on a word boundary are named gAlignment_<address>, everything else
gUnknown_<address>. Arrays are grouped into one source file per megabyte.
Gaps listed in RECORD_TABLES are emitted with their established record shape.
Run tools/build.py afterwards; the full ROM must stay identical.
"""
import argparse
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SEGMENTS = ROOT / "config" / "segments.json"
SYMBOLS = ROOT / "config" / "symbols.json"
ROM = ROOT / "baserom.gba"
BASE = 0x08000000

# start: (symbol, element type, element size, dimensions, source, comment)
RECORD_TABLES = {
    0x3D772C: ("gSparseSceneRecords_083D772C", "u16", 2, (144, 449), "src/sparse_scene_records.c",
               "144 records of 898 bytes; only halfwords 1 (6 * i) and 13 (6 * i + 2) differ\n"
               " * between records. No reader is known; see docs/SCENE_ANIMATION.md."),
}
# Named gaps whose consumers declare a wider element type.
ELEMENT_TYPES = {"gLinkGeneratedPattern_087C68A0": ("u16", 2)}


def gaps(segments, size, first):
    result, offset = [], 0
    for entry in segments:
        start, end = int(entry["start"], 16), int(entry["end"], 16)
        if offset < start and offset >= first:
            result.append((offset, start))
        offset = max(offset, end)
    if offset < size:
        result.append((offset, size))
    return result


def rom_symbols(symbols):
    names = {}
    for name, value in symbols.items():
        if isinstance(value, dict) and value.get("kind") != "data":
            continue  # functions
        address = int(value["address"] if isinstance(value, dict) else value, 16)
        if BASE <= address < BASE + 0x1000000:
            names[address - BASE] = name
    return names


def values(data, size):
    return [int.from_bytes(data[i:i + size], "little") for i in range(0, len(data), size)]


def body(items, width, per_line, indent="    "):
    text = [f"0x{v:0{width}X}" for v in items]
    return ",\n".join(indent + ", ".join(text[i:i + per_line]) for i in range(0, len(text), per_line))


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("--from", dest="first", type=lambda v: int(v, 0), default=0x7E858,
                        help="First ROM offset that may hold data gaps (end of the code region)")
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()
    rom = ROM.read_bytes()
    segments = json.loads(SEGMENTS.read_text(encoding="utf-8"))
    symbols = json.loads(SYMBOLS.read_text(encoding="utf-8"))
    named = rom_symbols(symbols)
    files, added, used_symbols = {}, [], []
    for start, end in gaps(segments, len(rom), args.first):
        data = rom[start:end]
        if start in RECORD_TABLES:
            name, ctype, size, dims, source, comment = RECORD_TABLES[start]
            assert dims[0] * dims[1] * size == end - start, f"record shape does not cover {start:06X}"
            rows = values(data, size)
            lines = [f"/*\n * {comment}\n */", f"const {ctype} {name}[{dims[0]}][{dims[1]}] __attribute__((aligned({size}))) = {{"]
            for i in range(dims[0]):
                record = rows[i * dims[1]:(i + 1) * dims[1]]
                lines.append(f"    {{ /* {i}: ROM {BASE + start + i * dims[1] * size:08X} */\n{body(record, size * 2, 12, '        ')}\n    }},")
            lines[-1] = lines[-1].rstrip(",")
            lines.append("};")
            description = "Sparse 898-byte scene records, typed by their repeat; reader unknown"
        else:
            if start in named:
                name = named[start]
                used_symbols.append(name)
            elif end - start < 4 and end % 4 == 0 and not any(data):
                name = f"gAlignment_{BASE + start:08X}"
            else:
                name = f"gUnknown_{BASE + start:08X}"
            ctype, size = ELEMENT_TYPES.get(name, ("u8", 1))
            assert (end - start) % size == 0 and start % size == 0
            source = f"src/unknown_data_{start >> 20:X}.c"
            count = (end - start) // size
            lines = [f"const {ctype} {name}[{count}] __attribute__((aligned({size}))) = {{\n{body(values(data, size), size * 2, 16 // size)}\n}};"]
            description = ("Zero alignment bytes before a word boundary" if name.startswith("gAlignment_")
                           else "Raw bytes typed without a known consumer (AGENTS.md data rule)")
        files.setdefault(source, []).append("\n".join(lines))
        added.append({"name": f"data_{start:06x}", "start": f"0x{start:06X}", "end": f"0x{end:06X}", "kind": "c",
                      "compiler": "gcc", "cflags": [], "source": source, "input_section": f".rodata.{name}",
                      "category": "data", "description": description})
    print(f"{len(added)} gaps, {sum(int(e['end'], 16) - int(e['start'], 16) for e in added)} bytes, "
          f"{len(files)} source files, reused symbols: {', '.join(used_symbols) or 'none'}")
    if args.dry_run:
        return
    for source, arrays in files.items():
        header = ("/*\n * Remaining ROM data typed as labelled arrays without a verified consumer\n"
                  " * (AGENTS.md data rule, 29 October 2026). Generated by tools/type_raw_data.py;\n"
                  " * rename and retype entries as their readers are identified.\n */\n\n#include \"global.h\"\n")
        (ROOT / source).write_text(header + "\n" + "\n\n".join(arrays) + "\n", encoding="utf-8")
    segments = sorted(segments + added, key=lambda entry: int(entry["start"], 16))
    SEGMENTS.write_text(json.dumps(segments, indent=2) + "\n", encoding="utf-8")
    for name in used_symbols:
        del symbols[name]
    SYMBOLS.write_text(json.dumps(symbols, indent=2) + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()
