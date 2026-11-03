"""Function renames are refused unless the old name is a matching function and the new one is unused."""

from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from rename import parse_pairs, validate

SEGMENTS = [
    {"name": "sub_08000100", "input_section": ".text.sub_08000100", "kind": "c"},
    {"name": "sub_08000200", "input_section": ".text.sub_08000200", "kind": "c", "nonmatching": True},
    {"name": "graphics_data", "input_section": ".rodata.graphics", "kind": "c"},
]
FILES = [(Path("src/a.c"), "void sub_08000100(void) { ExistingName(); }\n")]


class RenameTests(unittest.TestCase):
    def test_parse_pairs_accepts_both_forms_and_comments(self):
        self.assertEqual(parse_pairs(["a=B", "c D  # note", "# only a comment", ""]),
                         [("a", "B"), ("c", "D")])

    def test_accepts_matching_function_and_fresh_name(self):
        self.assertEqual(validate([("sub_08000100", "FreshName")], SEGMENTS, FILES), [])

    def test_refuses_unknown_nonmatching_and_used_names(self):
        errors = validate([("sub_08000300", "A1"), ("sub_08000200", "B1"),
                           ("sub_08000100", "ExistingName")], SEGMENTS, FILES)
        self.assertEqual(len(errors), 3)
        self.assertIn("no segment", errors[0])
        self.assertIn("NONMATCH", errors[1])
        self.assertIn("already used", errors[2])

    def test_accepts_data_symbols_but_not_function_aliases(self):
        symbols = {"gUnknown_03000100": "0x03000100", "sub_08000400": {"address": "0x08000401", "kind": "thumb_function"}}
        self.assertEqual(validate([("gUnknown_03000100", "gFreshWord")], SEGMENTS, FILES, symbols), [])
        self.assertEqual(len(validate([("sub_08000400", "Fresh")], SEGMENTS, FILES, symbols)), 1)

    def test_refuses_duplicate_targets_and_bad_identifiers(self):
        errors = validate([("sub_08000100", "9bad")], SEGMENTS, FILES)
        self.assertTrue(any("identifier" in error for error in errors))
        errors = validate([("sub_08000100", "Same"), ("sub_08000100", "Same")], SEGMENTS, FILES)
        self.assertTrue(any("twice" in error for error in errors))


if __name__ == "__main__":
    unittest.main()
