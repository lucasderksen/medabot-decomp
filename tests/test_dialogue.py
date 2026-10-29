import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from dialogue import decode


class DialogueTests(unittest.TestCase):
    def test_native_widths_and_roundtrip(self):
        data = bytes([1, 0xF7, 0xFF, 0xF8, 0xF9, 2, 0xFA, 9,
                      0xFB, 0, 0xFF, 3, 0xFC, 0xFD, 0xFE, 0xFF, 4])
        decoded = decode(data)
        self.assertEqual([item.offset for item in decoded], [0, 1, 3, 4, 6, 8, 12, 13, 14, 15])
        self.assertEqual([item.kind for item in decoded],
                         ["glyph", "delay_f7", "font_toggle", "insert", "delay_fa",
                          "portrait", "page", "newline", "skip", "end"])
        self.assertEqual(b"".join(item.encode() for item in decoded), data)

    def test_ff_portrait_operand_is_not_terminal(self):
        decoded = decode(bytes([0xFB, 0xFF, 0xFF, 0xFF, 1, 0xFF, 0]))
        self.assertEqual(len(decoded), 3)
        self.assertEqual(decoded[-1].offset, 5)

    def test_end_stops_before_neighboring_storage(self):
        decoded = decode(bytes([9, 0xFF, 2, 0xFF, 0xFF]))
        self.assertEqual(decoded[-1].end, 3)

    def test_explicit_bounds(self):
        data = bytes([0x99, 1, 0xFF, 0, 0x99])
        self.assertEqual(decode(data, 1, 4)[0].offset, 1)
        with self.assertRaises(ValueError):
            decode(data, 1, 3)

    def test_partial_commands_and_missing_end(self):
        for data in ([0xF7], [0xF9], [0xFB, 0, 1], [0xFF], [1, 2, 3], [0xFD]):
            with self.subTest(data=data), self.assertRaises(ValueError):
                decode(bytes(data))

    def test_glyph_domain(self):
        self.assertEqual(decode(bytes([134, 0xFF, 0]))[0].opcode, 134)
        for opcode in (135, 0xF6):
            with self.assertRaises(ValueError):
                decode(bytes([opcode, 0xFF, 0]))

    def test_position_limit_and_invalid_bounds(self):
        with self.assertRaises(ValueError):
            decode(bytes([1, 2, 0xFF, 0]), max_bytes=3)
        for bounds in ((-1, 4), (0, 5), (2, 2)):
            with self.assertRaises(ValueError):
                decode(bytes(4), *bounds)
        with self.assertRaises(ValueError):
            decode(bytes([0xFF, 0]), max_bytes=65537)


if __name__ == "__main__":
    unittest.main()
