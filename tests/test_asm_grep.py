"""asm_grep finds instruction shapes across matched C functions only."""

from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import asm_diff  # noqa: F401,E402  (puts tools/python, where capstone is installed, on the path)

try:
    import capstone  # noqa: F401
except ImportError:  # the disassembler is an optional analysis dependency
    capstone = None


@unittest.skipIf(capstone is None, "capstone not installed (python tools/bootstrap.py --analysis)")
class AsmGrepTests(unittest.TestCase):
    def test_finds_constant_copy_in_matched_functions_only(self):
        from asm_grep import search
        # ldr r3, [pc, #4]; adds r1, r3, #0; ands r0, r1; bx lr; .word 0xFFFF
        code = bytes.fromhex("014b" "191c" "0840" "7047" "ffff0000")
        rom = code + code
        segments = [
            {"name": "a", "start": 0, "end": 12, "kind": "c", "compiler": "agbcc", "input_section": ".text.Matched", "cflags": []},
            {"name": "b", "start": 12, "end": 24, "kind": "c", "compiler": "agbcc", "input_section": ".text.sub_0800000C",
             "nonmatching": True},
        ]
        hits = list(search(r"ldr (r\d), =0x0000FFFF\nadds r\d, \1, #0", rom, segments))
        self.assertEqual([name for name, _, _ in hits], ["Matched"])
        self.assertEqual([text for _, text in hits[0][2]], ["ldr r3, =0x0000FFFF", "adds r1, r3, #0"])


if __name__ == "__main__":
    unittest.main()
