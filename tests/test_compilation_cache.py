"""Production object reuse must not bypass changed inputs or damaged artifacts."""
from contextlib import redirect_stdout
import hashlib
import io
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import compiler_agbcc as compiler


class CompilationCacheTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.source = self.root / "source.c"
        self.header = self.root / "included.h"
        self.source.write_bytes(b"source one")
        self.header.write_bytes(b"header one")
        self.binary = self.root / "compiler"
        self.binary.write_bytes(b"compiler one")
        self.assembler = self.root / "assembler"
        self.assembler.write_bytes(b"assembler one")
        self.output = self.root / "output.o"
        self.calls = []
        for mocker in (patch.object(compiler, "ROOT", self.root),
                       patch.object(compiler, "BINARY", self.binary),
                       patch.object(compiler, "tool", lambda name: self.assembler if name == "as" else "preprocessor"),
                       patch.object(compiler, "run", self.run_command)):
            mocker.start()
            self.addCleanup(mocker.stop)

    def run_command(self, command):
        self.calls.append(command[0])
        destination = Path(command[-1])
        if command[0] == "preprocessor":
            destination.write_bytes(self.source.read_bytes() + self.header.read_bytes())
        elif command[0] == self.binary:
            contents = Path(command[-3]).read_bytes()
            if b"invalid" in contents:
                raise subprocess.CalledProcessError(1, command)
            destination.write_text('.text\n' + repr((contents, command[1:-3], self.binary.read_bytes())))
        else:
            destination.write_bytes(hashlib.sha256(Path(command[-3]).read_bytes() + self.assembler.read_bytes()).digest())

    def compile(self, flags=(), cache=True):
        with redirect_stdout(io.StringIO()):
            compiler.compile_source(self.source, self.output, flags, cache=cache)

    def emissions(self):
        return self.calls.count(self.binary)

    def test_hits_still_preprocess_and_uncached_probes_always_compile(self):
        self.compile()
        original = self.output.read_bytes()
        self.compile()
        self.assertEqual(self.emissions(), 1)
        self.assertEqual(self.calls.count("preprocessor"), 2)
        self.assertEqual(self.output.read_bytes(), original)
        self.compile(cache=False)
        self.compile(cache=False)
        self.assertEqual(self.emissions(), 3)

    def test_source_header_flags_and_tools_invalidate_by_content(self):
        self.compile()
        for path in (self.source, self.header, self.binary, self.assembler):
            previous = self.emissions()
            path.write_bytes(path.read_bytes() + b" changed")
            self.compile()
            self.assertEqual(self.emissions(), previous + 1)
        self.compile(["-fprologue-bugfix"])
        self.assertEqual(self.emissions(), 6)
        self.compile(["-fprologue-bugfix"])
        self.assertEqual(self.emissions(), 6)

    def test_damaged_or_missing_artifacts_and_metadata_force_recompile(self):
        self.compile()
        for path in (self.output, self.output.with_suffix(".s"), self.output.with_suffix(".o.cache.json")):
            with self.subTest(path=path.name):
                previous = self.emissions()
                path.write_bytes(b"damaged")
                self.compile()
                self.assertEqual(self.emissions(), previous + 1)
                path.unlink()
                self.compile()
                self.assertEqual(self.emissions(), previous + 2)

    def test_changed_invalid_source_never_reuses_previous_object(self):
        self.compile()
        original = self.output.read_bytes()
        self.header.write_bytes(b"invalid header")
        for _ in range(2):
            with self.assertRaises(subprocess.CalledProcessError):
                self.compile()
        self.assertEqual(self.emissions(), 3)
        self.assertEqual(self.output.read_bytes(), original)


if __name__ == "__main__":
    unittest.main()
