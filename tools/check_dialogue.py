"""Check dialogue storage boundaries against isolated original Thumb handlers.

Executes 0803FD28 and its actual text/control handlers. BIOS copies, text-map
drawing and sound calls are stubbed; no rendered-pixel or device claim is made.
Portrait mode 2 skips transitions, delay FF avoids timer waits, A accepts pages,
and inserted names contain one A. This checks command advancement and terminal
positions under that explicit state, not every interactive playback path.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn
from dialogue import decode

WORK = 0x03000440
SYNTHETIC = 0x02010000


def prepare_cpu(rom):
    cpu = RoutineCpu(rom)
    cpu.engine.mem_map(0x04000000, 0x1000)
    counts = {}

    def stub(engine, address, size, user_data):
        counts[address] = counts.get(address, 0) + 1
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))

    for address in (0x0807CCC4, 0x0807CCC0, 0x0803F15C, 0x08074DE0):
        cpu.engine.hook_add(unicorn.UC_HOOK_CODE, stub, begin=address, end=address)
    return cpu, counts


def check(cpu, data, address):
    instructions = decode(data)
    terminal = instructions[-1].offset
    boundaries = {item.offset for item in instructions}
    work = bytearray(0x28)
    work[1] = 2
    work[4] = 4
    struct.pack_into("<I", work, 8, address)
    work[0x1A] = 0xFF
    cpu.write(WORK, bytes(work))
    cpu.write(0x03001798, b"\x01\x00")
    for target in (0x03002B74, WORK + 0x9E, WORK + 0xB2, WORK + 0xC6, WORK + 0xDA):
        cpu.write(target, b"\x01\xFE\xFE\xFE")
    for calls in range(1, len(instructions) * 4 + 33):
        try:
            cpu.call(0x0803FD28, instruction_limit=min(5000000, 10000 + len(instructions) * 2000), timeout_us=0)
        except ValueError as error:
            state = cpu.read(WORK, 0x28).hex()
            raise ValueError(f"Dialogue {address:X}, call {calls}, work {state}: {error}") from error
        actual = cpu.read(WORK, 0x28)
        position = struct.unpack_from("<H", actual, 0xC)[0]
        if position not in boundaries:
            raise ValueError(f"Position {position:X} is not a command boundary at {address:X}")
        if actual[4] == 5:
            if position != terminal:
                raise ValueError(f"Terminal differs at {address:X}: {position:X} != {terminal:X}")
            return {"address": hex(address), "bytes": instructions[-1].end,
                    "terminal": terminal, "calls": calls,
                    "sha256": hashlib.sha256(data[:instructions[-1].end]).hexdigest()}
    raise ValueError(f"Dialogue did not terminate at {address:X}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--inventory", type=Path, help="Survey JSON containing decoded {start,end} rows")
    parser.add_argument("--limit", type=int, default=64)
    parser.add_argument("--output", type=Path, default=Path("build/analysis/dialogue-cpu.json"))
    args = parser.parse_args()
    if args.limit < 1:
        parser.error("limit must be positive")
    rom = find_rom().read_bytes()
    cpu, counts = prepare_cpu(rom)
    synthetic = [bytes([opcode, *operands, 0xFF, 4]) for opcode, operands in
                 [(1, []), (0xF7, [0xFF]), (0xF8, []), (0xF9, [0]),
                  (0xF9, [4]), (0xF9, [255]), (0xFA, [0xFF]),
                  (0xFB, [0xFF, 0xFF, 0xFF]), (0xFC, []), (0xFD, []), (0xFE, [])]]
    synthetic += [bytes([0xFF, mode]) for mode in range(5)]
    results = []
    for data in synthetic:
        cpu.write(SYNTHETIC, data)
        results.append(check(cpu, data, SYNTHETIC))
    native = []
    if args.inventory:
        rows = json.loads(args.inventory.read_text())["decoded"]
        # Long messages exercise wrapping; distributed entries cover all banks.
        longest = sorted(rows, key=lambda row: row["end"] - row["start"], reverse=True)[:args.limit // 2]
        distributed = rows[::max(1, len(rows) // max(1, args.limit - len(longest)))][:args.limit - len(longest)]
        selected = {row["start"]: row for row in longest + distributed}
        for row in selected.values():
            native.append(check(cpu, rom[row["start"]:row["end"]], 0x08000000 + row["start"]))
    report = {"rom_sha256": hashlib.sha256(rom).hexdigest(), "synthetic": results,
              "native": native, "stub_calls": {hex(a): n for a, n in counts.items()},
              "scope": __doc__}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"{len(results)} synthetic and {len(native)} native messages agree with original Thumb boundaries.")


if __name__ == "__main__":
    main()
