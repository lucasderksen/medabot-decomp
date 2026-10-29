"""Batch matching caches setup, while reference and symbol changes stay checked."""

import hashlib
import json
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from common import ROOT, validate_rom
from match import MatchSession, match


class MatchSessionTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory(dir=ROOT / "build")
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        (self.root / "config").mkdir()
        (self.root / "build").mkdir()
        self.rom = self.root / "baserom.gba"
        self.data = bytes(range(32))
        self.rom.write_bytes(self.data)
        self.config = {"name": "test", "revision": 0, "size": len(self.data),
                       "sha256": hashlib.sha256(self.data).hexdigest()}
        self.symbols_path = self.root / "config/symbols.json"
        self.symbols_path.write_text('{"gRam": "0x03000000"}')
        self.baseline = self.root / "build/medabots.elf"
        self.baseline.write_bytes(b"version1")
        self.assembler = self.root / "assembler"
        self.assembler.write_bytes(b"assembler1")
        self.symbol_reads = []
        self.assemblies = []
        for mocker in (
            patch("match.ROOT", self.root),
            patch("match.rom_config", lambda: self.config),
            patch("match.find_rom", lambda path=None: self.rom),
            patch("match.validate_rom", lambda data: validate_rom(data, self.config)),
            patch("match.read_symbols", self.read_symbols),
            patch("match.tool", lambda name: str(self.assembler)),
            patch("match.run", self.assemble),
        ):
            mocker.start()
            self.addCleanup(mocker.stop)

    def read_symbols(self, path):
        self.symbol_reads.append(Path(path).read_bytes())
        address = "0x08000001" if self.symbol_reads[-1] == b"version1" else "0x08000005"
        return {"function": {"address": address, "kind": "thumb_function"}}

    def assemble(self, command, **kwargs):
        source = Path(command[-3])
        target = Path(command[-1])
        contents = source.read_bytes() + self.assembler.read_bytes()
        self.assemblies.append(contents)
        target.write_bytes(hashlib.sha256(contents).digest())

    def test_invalid_initial_reference_is_rejected(self):
        self.rom.write_bytes(bytes([255]) + self.data[1:])
        with self.assertRaisesRegex(ValueError, "SHA-256"):
            MatchSession()

    def test_verified_reference_is_immutable_and_configuration_checked(self):
        session = MatchSession()
        self.rom.write_bytes(b"corrupted after session construction")
        self.assertEqual(session.reference(), self.data)
        self.config["sha256"] = "changed"
        with self.assertRaisesRegex(ValueError, "configuration changed"):
            session.reference()

    def test_other_reference_path_requires_another_session(self):
        session = MatchSession()
        with self.assertRaisesRegex(ValueError, "one verified ROM"):
            session.reference(self.root / "other.gba")

    def test_baseline_symbols_reused_without_override_leaks(self):
        session = MatchSession()
        first = session.symbols()
        first["function"]["address"] = "0xDEADBEEF"
        first.pop("gRam")
        second = session.symbols()
        self.assertEqual(second["function"]["address"], "0x08000001")
        self.assertIn("gRam", second)
        self.assertEqual(len(self.symbol_reads), 1)

    def test_baseline_content_change_invalidates_even_with_same_size_and_mtime(self):
        session = MatchSession()
        session.symbols()
        stamp = self.baseline.stat()
        self.baseline.write_bytes(b"version2")
        os.utime(self.baseline, ns=(stamp.st_atime_ns, stamp.st_mtime_ns))
        self.assertEqual(session.symbols()["function"]["address"], "0x08000005")
        self.assertEqual(len(self.symbol_reads), 2)

    def test_changed_absolute_symbol_configuration_invalidates(self):
        session = MatchSession()
        session.symbols()
        self.symbols_path.write_text('{"gRam": "0x03000004"}')
        self.assertEqual(session.symbols()["gRam"], "0x03000004")

    def test_removed_baseline_does_not_keep_its_symbols(self):
        session = MatchSession()
        self.assertIn("function", session.symbols())
        self.baseline.unlink()
        self.assertNotIn("function", session.symbols())

    def test_cached_symbol_object_restores_output_and_invalidates_for_changes(self):
        session = MatchSession()
        output = self.root / "output"
        output.mkdir()
        symbols = {"function": {"address": "0x08000001", "kind": "thumb_function"}}
        target = session.symbol_object(symbols, output)
        original = target.read_bytes()
        target.write_bytes(b"stale or corrupt output")
        self.assertEqual(session.symbol_object(symbols, output).read_bytes(), original)
        self.assertEqual(len(self.assemblies), 1)
        symbols["function"]["address"] = "0x08000005"
        self.assertNotEqual(session.symbol_object(symbols, output).read_bytes(), original)
        self.assertEqual(len(self.assemblies), 2)
        self.assembler.write_bytes(b"assembler2")
        session.symbol_object(symbols, output)
        self.assertEqual(len(self.assemblies), 3)

    def test_changed_candidate_is_recompiled_and_previous_match_is_not_reused(self):
        self.config["rom_base"] = "0x08000000"
        source = self.root / "source.c"
        source.write_text("correct")
        spec = self.root / "spec.json"
        spec.write_text(json.dumps({"source": str(source), "compiler": "agbcc", "cflags": [],
                                   "segments": [{"name": "candidate", "start": "0x0", "end": "0x20",
                                                 "input_section": ".text.candidate"}]}))
        session = MatchSession()
        compilations = []

        def compile_source(path, target, flags):
            text = Path(path).read_text()
            compilations.append(text)
            Path(target).write_bytes(self.data if text == "correct" else bytes([255]) + self.data[1:])

        def commands(command, **kwargs):
            from types import SimpleNamespace
            if "--no-check-sections" in command:
                Path(command[command.index("-o") + 1]).write_bytes(Path(command[-2]).read_bytes())
            elif "-d" in command:
                return SimpleNamespace(stdout="disassembly")
            elif "-j" in command:
                Path(command[-1]).write_bytes(Path(command[-2]).read_bytes())
            else:
                self.assemble(command, **kwargs)
            return SimpleNamespace(stdout="")

        def symbols(path):
            return {} if Path(path).name == "candidate.o" else self.read_symbols(path)

        with patch("compiler_agbcc.compile_source", compile_source), patch("match.run", commands), patch("match.read_symbols", symbols):
            output = self.root / "build/probe"
            self.assertTrue(match(spec, output, session=session))
            source.write_text("incorrect")
            self.assertFalse(match(spec, output, session=session))
            self.assertEqual(compilations, ["correct", "incorrect"])
            self.assertFalse(json.loads((output / "results.json").read_text())[0]["matched"])


if __name__ == "__main__":
    unittest.main()
