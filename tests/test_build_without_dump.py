"""Without a cartridge dump the build checks its output against the documented hashes."""

import hashlib
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import build


def config_for(data):
    return {'size': len(data), 'sha1': hashlib.sha1(data).hexdigest(), 'sha256': hashlib.sha256(data).hexdigest()}


class HashComparisonTests(unittest.TestCase):
    def test_documented_hashes_match(self):
        data = bytes(range(256)) * 4
        self.assertTrue(build.compare_hash(data, config_for(data)))

    def test_any_changed_byte_fails(self):
        data = bytearray(bytes(range(256)) * 4)
        config = config_for(bytes(data))
        data[100] ^= 1
        self.assertFalse(build.compare_hash(bytes(data), config))

    def test_wrong_size_fails(self):
        data = bytes(1024)
        self.assertFalse(build.compare_hash(data + b'\0', config_for(data)))

    def test_header_needs_no_dump(self):
        header = (Path(build.ROOT) / 'asm' / 'header.s').read_text(encoding='utf-8')
        self.assertNotIn('baserom', header)


if __name__ == '__main__':
    unittest.main()
