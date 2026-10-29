"""Pure checks for emulator frame decoding; no core or ROM is needed."""

from pathlib import Path
import struct
import sys
import tempfile
import unittest
import zlib

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from emulator import png_rgb, rgb_pixels


class PixelTests(unittest.TestCase):
    def test_16_bit_formats_and_padded_rows(self):
        for pixel_format, red, green, blue in ((0, 0x7C00, 0x03E0, 0x001F), (2, 0xF800, 0x07E0, 0x001F)):
            with self.subTest(pixel_format=pixel_format):
                raw = struct.pack("<4H", red, green, blue, 0xFFFF)
                self.assertEqual(rgb_pixels(raw, 3, 1, 8, pixel_format), b"\xff\x00\x00\x00\xff\x00\x00\x00\xff")

    def test_32_bit_format_and_invalid_pitch(self):
        raw = struct.pack("<2I", 0x00123456, 0x00ABCDEF)
        self.assertEqual(rgb_pixels(raw, 2, 1, 8, 1), b"\x12\x34\x56\xab\xcd\xef")
        with self.assertRaises(ValueError):
            rgb_pixels(raw, 2, 1, 4, 1)
        with self.assertRaises(ValueError):
            rgb_pixels(raw, 2, 1, 8, 99)
        with self.assertRaises(ValueError):
            rgb_pixels(raw[:-1], 2, 1, 8, 1)
        with self.assertRaises(ValueError):
            rgb_pixels(raw, 0, 1, 8, 1)

    def test_png_preserves_pixels(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "frame.png"
            png_rgb(path, 2, 1, b"\x12\x34\x56\xab\xcd\xef")
            blob = path.read_bytes()
            self.assertEqual(blob[:8], b"\x89PNG\r\n\x1a\n")
            offset, compressed = 8, b""
            while offset < len(blob):
                size = struct.unpack_from(">I", blob, offset)[0]
                kind, payload = blob[offset + 4:offset + 8], blob[offset + 8:offset + 8 + size]
                crc = struct.unpack_from(">I", blob, offset + 8 + size)[0]
                self.assertEqual(crc, zlib.crc32(kind + payload))
                if kind == b"IDAT":
                    compressed += payload
                offset += size + 12
            self.assertEqual(zlib.decompress(compressed), b"\0\x12\x34\x56\xab\xcd\xef")
