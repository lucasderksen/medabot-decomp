"""Tests for failure cases that could compromise a matching-ROM baseline."""

import contextlib
import hashlib
import io
from pathlib import Path
import struct
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from analyze import offset, xrefs
from build import compare, generate_linker, generate_symbol_assembly, object_path
from common import layout, load_segments, validate_rom
from match import comparison_result, elf_symbols


def segment(name, start, end):
    return {"name": name, "start": start, "end": end, "kind": "c", "source": f"src/{name}.c", "input_section": f".text.{name}"}


class RomValidationTests(unittest.TestCase):
    def setUp(self):
        self.data = bytes(range(32))
        self.config = {"name": "synthetic test ROM", "revision": 0, "size": 32, "sha256": hashlib.sha256(self.data).hexdigest()}

    def test_correct_rom(self):
        self.assertEqual(validate_rom(self.data, self.config), self.config["sha256"])

    def test_single_corrupt_byte_rejected(self):
        with self.assertRaisesRegex(ValueError, "SHA-256"):
            validate_rom(bytes([255]) + self.data[1:], self.config)

    def test_wrong_size_rejected(self):
        with self.assertRaisesRegex(ValueError, "size"):
            validate_rom(self.data[:-1], self.config)


class ManifestTests(unittest.TestCase):
    def test_elf_symbol_import_preserves_thumb_state(self):
        listing = """
          1: 080000c0 68 FUNC GLOBAL DEFAULT 2 AgbMain
          2: 0800025d 508 FUNC GLOBAL DEFAULT 3 GameMain
          3: 03001380 0 NOTYPE GLOBAL DEFAULT ABS gOamShadow
          4: 00000000 0 NOTYPE GLOBAL DEFAULT UND Missing
          5: 08000104 0 FUNC LOCAL DEFAULT 2 local_function
        """
        symbols = elf_symbols(listing)
        self.assertEqual(symbols["GameMain"]["kind"], "thumb_function")
        self.assertEqual(symbols["GameMain"]["address"], "0x0800025D")
        self.assertEqual(symbols["AgbMain"], "0x080000C0")
        self.assertEqual(symbols["gOamShadow"], "0x03001380")
        self.assertNotIn("Missing", symbols)
        self.assertNotIn("local_function", symbols)

    def test_assembly_and_c_objects_do_not_collide(self):
        self.assertNotEqual(object_path("asm/main.s"), object_path("src/main.c"))

    def test_every_byte_covered_once(self):
        entries = load_segments(16, [segment("a", 2, 4), segment("b", 8, 10)])
        covered = layout(entries, 16)
        self.assertEqual([address for item in covered for address in range(item["start"], item["end"])], list(range(16)))

    def test_overlap_rejected(self):
        with self.assertRaisesRegex(ValueError, "overlaps"):
            load_segments(16, [segment("a", 2, 8), segment("b", 6, 10)])

    def test_outside_rom_rejected(self):
        for start, end in ((-2, 4), (8, 18), (4, 4), (6, 4)):
            with self.subTest(start=start, end=end), self.assertRaises(ValueError):
                load_segments(16, [segment("bad", start, end)])

    def test_duplicate_name_rejected(self):
        with self.assertRaisesRegex(ValueError, "duplicate"):
            load_segments(16, [segment("same", 2, 4), segment("same", 8, 10)])

    def test_shared_source_compiler_settings_must_agree(self):
        first = segment("a", 2, 4)
        second = segment("b", 8, 10)
        second["source"] = first["source"]
        for field, value in (("compiler", "agbcc"), ("cflags", ["-fprologue-bugfix"]), ("kind", "asm")):
            changed = dict(second, **{field: value})
            with self.subTest(field=field), self.assertRaisesRegex(ValueError, "compiled once"):
                load_segments(16, [first, changed])
        self.assertEqual(len(load_segments(16, [first, second])), 2)

    def test_generated_linker_enforces_source_size(self):
        entries = load_segments(16, [segment("a", 2, 4)])
        script = generate_linker(layout(entries, 16), 0x08000000)
        self.assertIn(".a 0x08000002", script)
        self.assertIn("ASSERT(SIZEOF(.a) == 0x2", script)
        self.assertIn("ASSERT(SIZEOF(.unexpected) == 0", script)

    def test_copied_thumb_function_retains_symbol_type(self):
        symbols = {"CopiedFunction": {"address": "0x08001001", "kind": "thumb_function"}, "gRam": "0x03000000"}
        assembly = generate_symbol_assembly(symbols)
        self.assertIn(".type CopiedFunction, %function", assembly)
        self.assertIn(".thumb_set CopiedFunction, 0x08001001", assembly)
        linker = generate_linker([], 0x08000000, symbols)
        self.assertNotIn("CopiedFunction =", linker)
        self.assertIn("gRam = 0x03000000", linker)


class ComparisonTests(unittest.TestCase):
    def check(self, reference, rebuilt):
        with contextlib.redirect_stdout(io.StringIO()):
            return compare(reference, rebuilt, [{"name": "test", "start": 0, "end": len(reference)}])

    def test_changed_byte_fails(self):
        self.assertFalse(self.check(b"abcd", b"abXd"))

    def test_truncated_and_extended_outputs_fail(self):
        self.assertFalse(self.check(b"abcd", b"abc"))
        self.assertFalse(self.check(b"abcd", b"abcde"))

    def test_identical_output_succeeds(self):
        self.assertTrue(self.check(b"abcd", b"abcd"))

    def test_isolated_candidate_wrong_size_always_fails(self):
        entry = dict(name="candidate", start=16, end=20)
        for actual in (b"", b"abc", b"abcde", b"abXd"):
            with self.subTest(actual=actual):
                result = comparison_result(entry, b"abcd", actual)
                self.assertFalse(result["matched"])
                self.assertEqual(result["expected_size"], 4)
                self.assertEqual(result["actual_size"], len(actual))
        self.assertTrue(comparison_result(entry, b"abcd", b"abcd")["matched"])


class AnalysisTests(unittest.TestCase):
    def test_gba_address_and_offset_equivalent(self):
        self.assertEqual(offset("0x08000004", 32), offset("0x4", 32))
        with self.assertRaises(ValueError):
            offset("0x08000040", 32)

    def test_signed_thumb_bl_and_odd_function_pointer(self):
        data = bytearray(32)
        # BL at +0x10 back to +0x04. Signed 23-bit displacement is -16.
        displacement = (-16) & 0x7FFFFF
        struct.pack_into("<HH", data, 16, 0xF000 | (displacement >> 12), 0xF800 | ((displacement >> 1) & 0x7FF))
        struct.pack_into("<I", data, 24, 0x08000005)
        report = xrefs(data, "0x08000005", "0x0", "0x20")
        self.assertIn("BL   08000010", report)
        self.assertIn("WORD 08000018: 08000005", report)

    def test_ram_literal_references(self):
        data = bytearray(32)
        struct.pack_into("<I", data, 8, 0x0300178C)
        report = xrefs(data, "0x0300178C", "0x0", "0x20")
        self.assertIn("WORD 08000008: 0300178C", report)
        with self.assertRaises(ValueError):
            xrefs(data, "0x100000000", "0x0", "0x20")


if __name__ == "__main__":
    unittest.main()
