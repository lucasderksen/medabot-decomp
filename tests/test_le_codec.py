"""Synthetic streams cover each Le command and malformed-data rejection."""

from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from le_codec import decode, scan


def stream(size, payload, reserved=0):
    return b"Le" + size.to_bytes(3, "little") + bytes([reserved]) + payload


class LeCodecTests(unittest.TestCase):
    def test_literal_commands_and_consumed_length(self):
        # Flag 0B: triple literal, single literal, then unused command bits.
        encoded = stream(4, b"\x0BabcdTRAILING")
        self.assertEqual(decode(encoded), (b"abcd", 11))

    def test_short_overlapping_backreference(self):
        # Single 'a', then distance1/count5; overlap must read freshly written bytes.
        encoded = stream(6, b"\x06a\x0C")
        self.assertEqual(decode(encoded), (b"aaaaaa", 9))

    def test_long_backreference_and_next_flag_group(self):
        # ABC + D + E + F, then distance5/count3 -> BCD.
        encoded = stream(9, b"\xABABCDEF\x00\x00\x00")
        self.assertEqual(decode(encoded), (b"ABCDEFBCD", 16))

    def test_zero_size_and_ignored_sixth_header_byte(self):
        self.assertEqual(decode(stream(0, b"", 255)), (b"", 6))

    def test_offset_in_larger_buffer(self):
        self.assertEqual(decode(b"prefix" + stream(1, b"\x02z"), 6), (b"z", 8))

    def test_scan_reports_valid_nonempty_candidates(self):
        data = b"prefix" + stream(1, b"\x02z") + stream(0, b"") + b"Le"
        results = scan(data)
        self.assertEqual(len(results), 1)
        self.assertEqual(results[0]["rom_offset"], "0x000006")
        self.assertEqual(results[0]["compressed_bytes_consumed"], 8)
        self.assertEqual(results[0]["decoded_bytes"], 1)

    def test_truncated_input_rejected(self):
        for data in (b"Le", stream(1, b""), stream(3, b"\x03ab"), stream(3, b"\x00\x00")):
            with self.subTest(data=data), self.assertRaisesRegex(ValueError, "Truncated"):
                decode(data)

    def test_invalid_references_and_size_rejected(self):
        for data in (stream(3, b"\x00\x00\x00"), stream(2, b"\x03abc")):
            with self.subTest(data=data), self.assertRaises(ValueError):
                decode(data)
        with self.assertRaisesRegex(ValueError, "limit"):
            decode(stream(100, b""), max_output=99)
        with self.assertRaisesRegex(ValueError, "signature"):
            decode(b"XX\x00\x00\x00\x00")


if __name__ == "__main__":
    unittest.main()
