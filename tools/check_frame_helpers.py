"""Optional bounded CPU checks for reconstructed order/coordinate helpers."""

import random
import struct

from common import ROOT, find_rom
from cpu import RoutineCpu


def check():
    rom = find_rom().read_bytes()
    cpu = RoutineCpu(rom)
    rng = random.Random(0x1520)
    for count in (0, 1, 2, 3, 7, 16, 64, 128):
        for iteration in range(8):
            entries = [(i, rng.randrange(256), 0xA000 + i) for i in range(count)]
            cpu.write(0x02000000, b"".join(struct.pack("<BBH", *entry) for entry in entries) + bytes(512))
            cpu.call(0x08002060, (0x02000000, count))
            result = list(struct.iter_unpack("<BBH", cpu.read(0x02000000, count * 4)))
            assert [row[1] for row in result] == sorted((row[1] for row in entries), reverse=True)
            assert sorted(row[:2] for row in result) == sorted(row[:2] for row in entries)
            assert [row[2] for row in result] == [row[2] for row in entries]
    for iteration in range(128):
        angle = rng.randrange(65536)
        x = rng.randrange(-20000, 20001)
        y = rng.randrange(-20000, 20001)
        sine = struct.unpack_from("<h", rom, 0x75250 + (angle & 1023) * 2)[0]
        cosine = struct.unpack_from("<h", rom, 0x75250 + ((angle & 1023) + 256) * 2)[0]
        cpu.write(0x02001000, struct.pack("<ii", x, y))
        cpu.write(0x02001100, bytes(24) + struct.pack("<H", angle) + bytes(38))
        cpu.call(0x08001FF8, (0x02001000, 0x02001004, 0x02001100))
        actual = struct.unpack("<ii", cpu.read(0x02001000, 8))
        expected = (int((x * cosine - y * sine) / 16384), int((x * sine + y * cosine) / 16384))
        assert actual == expected, (angle, x, y, actual, expected)
    print("PASS: 64 order cases, 128 coordinate cases; trailing halfwords stay in place.")


if __name__ == "__main__":
    check()
