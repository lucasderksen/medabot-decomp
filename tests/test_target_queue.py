"""Priority queues count remaining intervals and bound repeated failed effort."""

from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from target_queue import rank_targets

BASE = 0x08000000


def draft(start, size, similarity=0.8):
    return {"start": f"{BASE+start:08X}", "end": f"{BASE+start+size:08X}",
            "similarity": similarity, "cflags": ["-fprologue-bugfix"]}


class TargetQueueTests(unittest.TestCase):
    def test_excludes_any_overlap_even_when_entry_start_is_uncovered(self):
        rows, reasons = rank_targets([draft(0, 64), draft(64, 64)],
                                     [{"start": 32, "end": 48}], BASE, 1024)
        self.assertEqual([row["start"] for row in rows], ["08000040"])
        self.assertEqual(reasons["overlaps_integrated_source"], 1)

    def test_small_data_invalid_bounds_and_duplicates_do_not_inflate_queue(self):
        source = draft(64, 64)
        rows, reasons = rank_targets([draft(0, 4), draft(2, 64), draft(1020, 64), source, source],
                                     [], BASE, 1024)
        self.assertEqual(len(rows), 1)
        self.assertEqual(reasons, {"below_minimum": 1, "invalid_bounds": 2, "duplicate_entry": 1})

    def test_byte_size_comes_from_interval_not_stale_metadata(self):
        source = draft(0, 256)
        source["bytes"] = 4
        rows, _ = rank_targets([source], [], BASE, 1024)
        self.assertEqual(rows[0]["bytes"], 256)
        self.assertEqual(rows[0]["score_evidence"], "historical harvest; not fresh verification")

    def test_equally_close_larger_target_has_more_payoff(self):
        rows, _ = rank_targets([draft(0, 64), draft(64, 256)], [], BASE, 1024)
        self.assertEqual(rows[0]["bytes"], 256)

    def test_untranslated_large_function_does_not_displace_a_promising_draft(self):
        untranslated = draft(0, 8192)
        untranslated.pop("similarity")
        rows, _ = rank_targets([untranslated, draft(8192, 256)], [], BASE, 10000)
        self.assertEqual(rows[0]["bytes"], 256)
        self.assertIsNone(rows[1]["historical_similarity"])

    def test_family_payoff_can_prioritize_a_smaller_seed(self):
        members = [(f"sub_{BASE+start:08X}", 64) for start in (0, 64, 128, 192)]
        families = {members[0][0]: members}
        rows, _ = rank_targets([draft(0, 64), draft(256, 128)], [], BASE, 1024, families=families)
        self.assertEqual(rows[0]["name"], "sub_08000000")
        self.assertEqual(rows[0]["family_candidate_bytes"], 256)

    def test_parked_draft_is_reconsidered_after_source_changes(self):
        ledger = [{"name": "sub_08000000", "minutes": 20, "draft_hash": "old"}]
        rows, reasons = rank_targets([draft(0, 64)], [], BASE, 1024, ledger=ledger,
                                     hashes={"sub_08000000": "old"})
        self.assertEqual(rows, [])
        self.assertEqual(reasons["parked_after_20_minutes"], 1)
        rows, _ = rank_targets([draft(0, 64)], [], BASE, 1024, ledger=ledger,
                               hashes={"sub_08000000": "new"})
        self.assertEqual(len(rows), 1)

    def test_explicit_ownership_prevents_duplicate_worker_work(self):
        rows, reasons = rank_targets([draft(0, 64)], [], BASE, 1024,
                                     assignments={"sub_08000000": "graphics"})
        self.assertEqual(rows, [])
        self.assertEqual(reasons["assigned_to_worker"], 1)

    def test_prior_effort_lowers_priority_without_changing_progress_evidence(self):
        rows, _ = rank_targets([draft(0, 64), draft(64, 64)], [], BASE, 1024,
                               ledger=[{"name": "sub_08000000", "minutes": 10, "draft_hash": "same"}],
                               hashes={"sub_08000000": "same"})
        self.assertEqual(rows[0]["name"], "sub_08000040")
        self.assertEqual(rows[1]["same_draft_minutes"], 10)


if __name__ == "__main__":
    unittest.main()
