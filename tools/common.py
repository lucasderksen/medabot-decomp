"""Shared ROM validation, segment layout, and tool discovery."""

import hashlib
import json
import os
from pathlib import Path
import shutil

ROOT = Path(__file__).resolve().parents[1]
ROM_CONFIG = ROOT / "config" / "rom.json"
SEGMENTS_CONFIG = ROOT / "config" / "segments.json"


def rom_config():
    return json.loads(ROM_CONFIG.read_text(encoding="utf-8"))


def validate_rom(data, config=None):
    config = config or rom_config()
    if len(data) != config["size"]:
        raise ValueError(f"Wrong ROM size: {len(data)} bytes; expected {config['size']}.")
    digest = hashlib.sha256(data).hexdigest()
    if digest != config["sha256"]:
        raise ValueError(f"Wrong ROM SHA-256: {digest}; expected {config['sha256']}. Only {config['name']} revision {config['revision']} is supported.")
    return digest


def find_rom(path=None):
    if path:
        candidate = Path(path).resolve()
        validate_rom(candidate.read_bytes())
        return candidate
    canonical = ROOT / "baserom.gba"
    if canonical.exists():
        validate_rom(canonical.read_bytes())
        return canonical
    for candidate in sorted(ROOT.glob("*.gba")):
        try:
            validate_rom(candidate.read_bytes())
        except ValueError:
            continue
        return candidate
    raise ValueError("Place your Medabots Metabee Europe revision 0 dump in the project root, or pass --rom PATH.")


def prepare_rom(path=None):
    original = find_rom(path)
    canonical = ROOT / "baserom.gba"
    if original != canonical:
        if canonical.exists():
            validate_rom(canonical.read_bytes())
        else:
            temporary = ROOT / "baserom.gba.tmp"
            shutil.copyfile(original, temporary)
            validate_rom(temporary.read_bytes())
            temporary.replace(canonical)
    return canonical


def nonmatching(segment):
    """A NONMATCH function (include/global.h): original assembly in a C file, still unmatched code."""
    return bool(segment.get("nonmatching"))


def replace_nonmatching(entries, start, end):
    """Drop NONMATCH entries overlapping [start, end), with their C file and assembly.

    A newly matched function replaces its NONMATCH version; returns the kept entries.
    """
    kept = []
    for entry in entries:
        lo, hi = (int(entry[key], 0) if isinstance(entry[key], str) else entry[key] for key in ("start", "end"))
        if nonmatching(entry) and lo < end and start < hi:
            (ROOT / entry["source"]).unlink(missing_ok=True)
            (ROOT / "asm" / "non_matching" / f"{entry['name']}.inc").unlink(missing_ok=True)
        else:
            kept.append(entry)
    return kept


def load_segments(size=None, entries=None):
    size = rom_config()["size"] if size is None else size
    entries = json.loads(SEGMENTS_CONFIG.read_text(encoding="utf-8")) if entries is None else entries
    result = []
    names = set()
    sources = {}
    end = 0
    for entry in entries:
        entry = dict(entry)
        entry["start"] = int(entry["start"], 0) if isinstance(entry["start"], str) else entry["start"]
        entry["end"] = int(entry["end"], 0) if isinstance(entry["end"], str) else entry["end"]
        if not end <= entry["start"] < entry["end"] <= size:
            raise ValueError(f"Segment {entry['name']} is unsorted, overlaps another segment, or lies outside the ROM.")
        if entry["name"] in names or not entry["name"].replace("_", "").isalnum():
            raise ValueError(f"Invalid or duplicate segment name: {entry['name']}")
        if entry["kind"] not in ("asm", "c"):
            raise ValueError(f"Unsupported segment kind: {entry['kind']}")
        settings = (entry["kind"], entry.get("compiler", "gcc"), tuple(entry.get("cflags", [])))
        source = entry["source"]
        if source in sources and sources[source] != settings:
            raise ValueError(f"Inconsistent compiler settings for source {source}; each source is compiled once.")
        sources[source] = settings
        names.add(entry["name"])
        end = entry["end"]
        result.append(entry)
    return result


def layout(segments, size):
    """Cover every byte exactly once, inserting explicit incbin gaps."""
    result = []
    offset = 0
    for segment in segments:
        if offset < segment["start"]:
            result.append({"name": f"raw_{offset:06x}", "start": offset, "end": segment["start"], "kind": "raw"})
        result.append(segment)
        offset = segment["end"]
    if offset < size:
        result.append({"name": f"raw_{offset:06x}", "start": offset, "end": size, "kind": "raw"})
    return result


def tool(name):
    filename = f"arm-none-eabi-{name}" + (".exe" if os.name == "nt" else "")
    override = os.environ.get("ARM_TOOLCHAIN")
    candidates = []
    if override:
        candidates.append(Path(override) / filename)
    candidates.append(ROOT / "tools" / "toolchain" / "bin" / filename)
    for candidate in candidates:
        if candidate.is_file():
            return str(candidate)
    external = shutil.which(f"arm-none-eabi-{name}")
    if external:
        return external
    raise ValueError(f"Missing {filename}. Run python tools/bootstrap.py or set ARM_TOOLCHAIN to your toolchain's bin directory.")
