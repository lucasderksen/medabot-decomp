"""Check original scene asset fallback and transfer requests for every slot.

Native palette-loader routines execute with MMIO mapped as ordinary memory.
DMA register writes are recorded, not emulated. Selector helpers return the
chosen directory slot (and FF after one palette); BIOS decompression is stubbed
and its source/destination arguments are recorded. No rendering claim is made.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct

from common import find_rom
from cpu import RoutineCpu, arm_const, unicorn


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=Path("build/analysis/scene-assets-cpu.json"))
    args = parser.parse_args()
    rom = find_rom().read_bytes()
    tiles = struct.unpack_from("<336I", rom, 0x3F7E80)
    palettes = struct.unpack_from("<336I", rom, 0x3F83C0)
    cpu = RoutineCpu(rom)
    cpu.engine.mem_map(0x04000000, 0x1000)
    state = {"index": 0, "dma": [], "copies": []}

    def hook(engine, address, size, user_data):
        if address == 0x08048684:
            value = state["index"] if engine.reg_read(arm_const.UC_ARM_REG_R0) == 0 else 255
        elif address == 0x08048210:
            value = state["index"]
        elif address == 0x0807CCD8:
            state["copies"].append((engine.reg_read(arm_const.UC_ARM_REG_R0),
                                     engine.reg_read(arm_const.UC_ARM_REG_R1)))
            value = 0
        else:
            return
        engine.reg_write(arm_const.UC_ARM_REG_R0, value)
        engine.reg_write(arm_const.UC_ARM_REG_PC, engine.reg_read(arm_const.UC_ARM_REG_LR))

    def dma(engine, access, address, size, value, user_data):
        if address == 0x040000DC and size == 4:
            source, destination = struct.unpack("<II", cpu.read(0x040000D4, 8))
            state["dma"].append((source, destination, value))

    cpu.engine.hook_add(unicorn.UC_HOOK_CODE, hook)
    cpu.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, dma, begin=0x040000D4, end=0x040000DF)
    cases = dma_count = copy_count = 0
    for index in range(336):
        palette = palettes[index] or palettes[1]
        tile = tiles[index] or tiles[1]
        for address, expected_dma, expected_copies in (
            (0x080486B0, [] if index == 255 else [(palette, 0x05000200, 0x84000008)], []),
            (0x08048708, ([] if index == 255 else [(palette, 0x0202F800, 0x84000008)]) +
             [(0x085FB684, 0x0202F9C0, 0x84000008)], []),
            (0x0804877C, [(palette, 0x05000200 + i * 32, 0x84000008) for i in range(12)], []),
            (0x080482CC, [], [(tile, 0x06010000 + i * 0x900) for i in range(12)]),
        ):
            state.update(index=index, dma=[], copies=[])
            cpu.call(address, (index,), instruction_limit=100000, timeout_us=0)
            if state["dma"] != expected_dma or state["copies"] != expected_copies:
                raise ValueError(f"Transfer requests differ: routine {address:X}, slot {index}")
            cases += 1
            dma_count += len(expected_dma)
            copy_count += len(expected_copies)
    report = {"rom_sha256": hashlib.sha256(rom).hexdigest(), "slots": 336,
              "cases": cases, "dma_requests": dma_count, "decompression_requests": copy_count,
              "null_slots": sum(value == 0 for value in palettes), "scope": __doc__}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"All {cases} native loader cases agree: {dma_count} DMA requests, "
          f"{copy_count} decompression requests, including 189 fallback slots.")


if __name__ == "__main__":
    main()
