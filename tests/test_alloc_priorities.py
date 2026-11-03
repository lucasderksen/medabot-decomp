"""alloc_priorities parses agbcc's -dg dump into a priority-ordered table."""

from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from alloc_priorities import priorities

GREG = """Register 22, refs = 9, live_length = 244, size = 1
Register 23, refs = 9, live_length = 234, size = 1
Register 275, refs = 7, live_length = 218, size = 1

;; Register dispositions:
22 in 9  23 in 8
"""


class AllocPrioritiesTests(unittest.TestCase):
    def test_orders_by_global_alloc_priority_and_names_registers(self):
        rows = priorities(GREG)
        self.assertEqual([(regno, hard) for _, regno, _, _, hard in rows], [(23, "r8"), (22, "sb"), (275, "MEM")])
        self.assertAlmostEqual(rows[0][0], 3 * 9 / 234)


if __name__ == "__main__":
    unittest.main()
