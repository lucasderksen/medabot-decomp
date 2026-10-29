"""Optional CPU checks: original Le routines against the bounded host decoder."""

from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from common import find_rom
from cpu import RoutineCpu, unicorn
from le_codec import decode


@unittest.skipIf(unicorn is None, "Optional Unicorn dependency is absent")
class OriginalCompressionCpuTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try:
            cls.rom = find_rom().read_bytes()
        except (ValueError, OSError) as error:
            raise unittest.SkipTest(f"Matching local ROM required: {error}")

    def setUp(self):
        self.cpu = RoutineCpu(self.rom)

    def check_stream(self, stream_address, expected, destination):
        # Both neighbors test preservation by the halfword destination path.
        self.cpu.write(destination - 1, bytes([0xA5]) * (len(expected) + 2))
        registers = self.cpu.call(0x080009BC, (stream_address, destination))
        self.assertEqual(registers[0], len(expected))
        self.assertEqual(self.cpu.read(destination, len(expected)), expected)
        self.assertEqual(self.cpu.read(destination - 1, 1), b"\xA5")
        self.assertEqual(self.cpu.read(destination + len(expected), 1), b"\xA5")
        self.assertEqual(registers[4:12], tuple(0xAB000000 | i for i in range(4, 12)))

    def test_code_referenced_assets_in_both_destination_paths(self):
        for start in (0x4C1E24, 0x4C200C, 0x4C2150, 0x4C22E8, 0x4871A4, 0x4C8034):
            expected, _ = decode(self.rom, start)
            for destination in (0x02010000, 0x06001000, 0x06001001):
                with self.subTest(start=hex(start), destination=hex(destination)):
                    self.check_stream(0x08000000 + start, expected, destination)

    def test_synthetic_literals_and_overlapping_copies(self):
        vectors = ((4, b"\x0Babcd"), (6, b"\x06a\x0C"), (9, b"\xABABCDEF\x00\x00\x00"), (1, b"\x02z"))
        for size, payload in vectors:
            encoded = b"Le" + size.to_bytes(3, "little") + b"\xFF" + payload
            self.cpu.write(0x02000000, encoded)
            expected, _ = decode(encoded)
            for destination in (0x02010000, 0x06001000, 0x06001001):
                with self.subTest(size=size, destination=hex(destination)):
                    self.check_stream(0x02000000, expected, destination)

    def test_invalid_signature_returns_zero_without_writes(self):
        self.cpu.write(0x02000000, b"XX\x01\x00\x00\x00\x02z")
        self.cpu.write(0x02010000, b"unchanged")
        self.assertEqual(self.cpu.call(0x080009BC, (0x02000000, 0x02010000))[0], 0)
        self.assertEqual(self.cpu.read(0x02010000, 9), b"unchanged")


if __name__ == "__main__":
    unittest.main()
