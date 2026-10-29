"""The progress chart scales its axis for every coverage up to 100%."""

from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import progress_report


def row(done):
    return {'date': '2026-10-29T00:00:00Z', 'sha': 'x', 'total': '1000', 'game_c': str(done), 'runtime_c': '0',
            'data': '0', 'asm': '0', 'functions': '1', 'code_end': '1000', 'code_done': str(done)}


class ChartTests(unittest.TestCase):
    def test_near_complete_and_complete_coverage_use_a_100_percent_axis(self):
        for done in (999, 1000):
            chart = progress_report.chart([row(done)])
            self.assertIn('>100%</text>', chart)

    def test_low_coverage_keeps_a_tight_axis(self):
        self.assertIn('>2%</text>', progress_report.chart([row(10)]))


if __name__ == '__main__':
    unittest.main()
