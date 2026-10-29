from pathlib import Path
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from lz77_codec import decode

def stream(size,payload):
    return b'\x10'+size.to_bytes(3,'little')+payload

class Lz77Tests(unittest.TestCase):
    def test_literals_multiple_flags_and_consumed_extent(self):
        data=stream(10,b'\x00abcdefgh\x00ij')+b'padding'
        self.assertEqual(decode(data),(b'abcdefghij',16))
    def test_overlapping_reference_and_msb_flag_order(self):
        self.assertEqual(decode(stream(7,b'\x40A\x30\x00')),(b'A'*7,8))
    def test_big_endian_reference_distance(self):
        self.assertEqual(decode(stream(7,b'\x08ABCD\x00\x03'))[0],b'ABCDABC')
    def test_offset_and_empty(self):
        data=b'prefix'+stream(0,b'')
        self.assertEqual(decode(data,6),(b'',4))
    def test_bad_header_offset_and_limit(self):
        for data,offset,limit in ((b'bad',0,99),(stream(0,b''),-1,99),(stream(10,b''),0,9)):
            with self.assertRaises(ValueError):decode(data,offset,limit)
    def test_truncated_literals_and_references(self):
        for data in (stream(1,b''),stream(1,b'\x00'),stream(4,b'\x40A\x00')):
            with self.assertRaises(ValueError):decode(data)
    def test_reference_before_output_and_output_overrun(self):
        for data in (stream(3,b'\x80\x00\x00'),stream(2,b'\x40A\x00\x00')):
            with self.assertRaises(ValueError):decode(data)

if __name__=='__main__':unittest.main()
