"""A failed candidate must not destroy the last verified research artifacts."""

from contextlib import ExitStack, redirect_stdout
import io
from pathlib import Path
import subprocess
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import build


class BuildPublicationTests(unittest.TestCase):
    def test_transient_windows_lock_retains_old_file_until_success(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "candidate.elf"
            destination = Path(directory) / "published.elf"
            source.write_bytes(b"verified candidate")
            destination.write_bytes(b"previous verified")
            original_replace = Path.replace
            lock = PermissionError("sharing violation")
            lock.winerror = 32
            blocked = True

            def replace_after_reader_closes(path, target):
                nonlocal blocked
                if blocked:
                    blocked = False
                    self.assertEqual(destination.read_bytes(), b"previous verified")
                    self.assertEqual(source.read_bytes(), b"verified candidate")
                    raise lock
                return original_replace(path, target)

            with patch.object(Path, "replace", autospec=True, side_effect=replace_after_reader_closes), patch.object(build.time, "sleep"):
                build.replace_verified_artifact(source, destination)
            self.assertEqual(destination.read_bytes(), b"verified candidate")
            self.assertFalse(source.exists())

    def test_persistent_windows_lock_fails_and_retains_both_files(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "candidate.elf"
            destination = Path(directory) / "published.elf"
            source.write_bytes(b"verified candidate")
            destination.write_bytes(b"previous verified")
            lock = PermissionError("access denied")
            lock.winerror = 5
            with patch.object(Path, "replace", side_effect=lock) as replacement, patch.object(build.time, "sleep"):
                with self.assertRaises(PermissionError):
                    build.replace_verified_artifact(source, destination)
                self.assertLessEqual(replacement.call_count, 20)
            self.assertEqual(destination.read_bytes(), b"previous verified")
            self.assertEqual(source.read_bytes(), b"verified candidate")

    def test_unrelated_publication_error_is_not_retried(self):
        with patch.object(Path, "replace", side_effect=FileNotFoundError("missing candidate")) as replacement, patch.object(build.time, "sleep") as sleep:
            with self.assertRaises(FileNotFoundError):
                build.replace_verified_artifact(Path("missing"), Path("published"))
            replacement.assert_called_once()
            sleep.assert_not_called()

    def test_only_a_matching_candidate_replaces_published_artifacts(self):
        for outcome in ("link_error", "mismatch", "match"):
            with self.subTest(outcome=outcome), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                output = root / "build"
                output.mkdir()
                reference = bytes(range(16))
                rom = root / "reference.bin"
                rom.write_bytes(reference)
                previous = {suffix: ("previous " + suffix).encode() for suffix in ("elf", "map", "disasm", "gba")}
                for suffix, data in previous.items():
                    (output / ("medabots." + suffix)).write_bytes(data)

                def fake_run(command):
                    if command[0] == "ld":
                        if outcome == "link_error":
                            raise subprocess.CalledProcessError(1, command)
                        Path(command[command.index("-o") + 1]).write_bytes(b"candidate elf")
                        Path(command[command.index("-Map") + 1]).write_bytes(b"candidate map")
                    elif command[0] == "objcopy":
                        Path(command[-1]).write_bytes(reference if outcome == "match" else reference[:-1] + b"\xff")

                segments = [dict(name="test", start=0, end=16, kind="asm", source="asm/test.s", input_section=".text")]
                with ExitStack() as stack:
                    for name, value in (("ROOT", root), ("prepare_rom", lambda _: rom),
                                        ("rom_config", lambda: dict(size=16, rom_base="0x08000000")),
                                        ("load_segments", lambda: segments), ("tool", lambda name: name),
                                        ("run", fake_run)):
                        stack.enter_context(patch.object(build, name, value))
                    stack.enter_context(patch.object(build.subprocess, "run", return_value=SimpleNamespace(stdout="candidate disasm")))
                    with redirect_stdout(io.StringIO()):
                        if outcome == "link_error":
                            with self.assertRaises(subprocess.CalledProcessError):
                                build.build()
                        else:
                            self.assertEqual(build.build(), outcome == "match")

                if outcome == "match":
                    self.assertEqual((output / "medabots.gba").read_bytes(), reference)
                    self.assertEqual((output / "medabots.elf").read_bytes(), b"candidate elf")
                    self.assertEqual((output / "medabots.map").read_bytes(), b"candidate map")
                    self.assertEqual((output / "medabots.disasm").read_text(), "candidate disasm")
                else:
                    for suffix, data in previous.items():
                        self.assertEqual((output / ("medabots." + suffix)).read_bytes(), data)
                    if outcome == "mismatch":
                        self.assertNotEqual((output / "candidate/medabots.gba").read_bytes(), reference)
