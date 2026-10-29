from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from frame_commands import State, analyze, initialize, tick


class FrameCommandTests(unittest.TestCase):
    def test_preview_skips_controls_without_executing_them(self):
        data = bytes([0xFD, 9, 0, 2, 0x12, 0x34, 0xFF])
        state = initialize(data)
        self.assertEqual(state, State(frame=0x1234))
        flags, sounds = tick(data, state, 0)
        self.assertEqual((flags, sounds, state.delay, state.offset), (0, [9], 1, 6))

    def test_delay_stopping_and_unused_tail(self):
        data = bytes([2, 0xAB, 0xCD, 0xFF, 0x91])
        state = initialize(data)
        tick(data, state, 0)
        self.assertEqual((state.delay, state.offset), (1, 3))
        tick(data, state, 0)
        self.assertEqual(state.delay, 0)
        tick(data, state, 0)
        self.assertEqual(state.stopped, 255)
        self.assertEqual(tick(b"", state, 0x1234), (0x1234, []))

    def test_two_byte_jump_to_an_ordinary_frame(self):
        data = bytes([1, 3, 4, 0xFE, 0])
        self.assertEqual([node["offset"] for node in analyze(data)["nodes"]], [0, 3])
        state = initialize(data)
        tick(data, state, 0)
        tick(data, state, 0)
        self.assertEqual((state.frame, state.offset, state.delay), (0x304, 3, 0))

    def test_flags_affect_record_zero_and_clear_returns_immediately(self):
        data = bytes([0xFC, 0xA5, 0x5A, 1, 1, 2, 0xFB, 2, 0, 0, 3, 4, 0xFF])
        analyze(data)
        state = initialize(data)
        flags, sounds = tick(data, state, 0x8123)
        self.assertEqual((flags, sounds, state.delay, state.offset), (0xC123, [], 0, 6))
        flags, sounds = tick(data, state, flags)
        self.assertEqual((flags, sounds, state.delay, state.offset), (0x8123, [], 2, 9))
        self.assertEqual(state.frame, 0x102)

    def test_byte_offset_wrap_is_part_of_the_format(self):
        data = bytearray(256)
        data[0] = 1
        data[1] = 0xFF
        data[3:5] = bytes([0xFE, 171])
        # FE 171 * 3 wraps to byte offset one.
        self.assertEqual([node["offset"] for node in analyze(data)["nodes"]], [0, 3, 1])
        state = State(offset=3)
        tick(data, state, 0)
        self.assertEqual((state.offset, state.stopped), (1, 255))

    def test_truncated_operands_outside_target_and_missing_preview(self):
        for data in (b"", b"\x01\x02", b"\x01\x02\x03\xfe",
                     b"\x01\x02\x03\xfe\x7f", b"\xff"):
            with self.assertRaises(ValueError):
                analyze(data)

    def test_zero_delay_control_cycle_is_rejected(self):
        data = bytes([0, 1, 2, 0xFE, 0])
        with self.assertRaisesRegex(ValueError, "cannot return"):
            analyze(data)
        with self.assertRaisesRegex(ValueError, "instruction bound"):
            tick(data, initialize(data), 0, 8)


if __name__ == "__main__":
    unittest.main()
