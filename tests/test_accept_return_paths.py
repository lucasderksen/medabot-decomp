import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from accept_draft import verify_return_paths
from common import tool


@unittest.skipUnless(Path(tool("gcc")).is_file(), "Cross-compiler is not installed")
class ReturnPathDiagnosticsTests(unittest.TestCase):
    def check_source(self, source):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source_path = root / "candidate.i"
            source_path.write_text(source, encoding="utf-8")
            verify_return_paths(source_path, root / "diagnostic.s")

    def test_return_before_default_does_not_cover_default(self):
        # The exact control-flow error found in the rejected 08015390 search:
        # default jumps past the apparent fallback return.
        with self.assertRaises(subprocess.CalledProcessError) as caught:
            self.check_source("""unsigned candidate(unsigned first, unsigned type) {
                switch (type) {
                case 0: return 1;
                return first;
                default: ;
                }
            }
            """)
        self.assertIn("control reaches end of non-void", caught.exception.stderr)

    def test_explicit_default_preserves_incoming_word(self):
        self.check_source("""unsigned candidate(unsigned first, unsigned type) {
            switch (type) {
            case 0: return 1;
            default: return first;
            }
        }
        """)


if __name__ == "__main__":
    unittest.main()
