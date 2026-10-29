"""The objdiff-format report counts source segments as matched and code gaps as unmatched."""

from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import objdiff_report


def segment(name, start, end, source, **extra):
    return {'name': name, 'start': start, 'end': end, 'kind': extra.pop('kind', 'c'), 'source': source, **extra}


class ObjdiffReportTests(unittest.TestCase):
    def setUp(self):
        self.report = objdiff_report.build([
            segment('header', 0x0, 0xC0, 'asm/header.s', kind='asm'),
            segment('main', 0xC0, 0x100, 'src/main.c', input_section='.text.Main'),
            segment('table', 0x100, 0x110, 'src/main.c', category='data', input_section='.rodata.gTable'),
            segment('libgcc_udivsi3', 0x120, 0x140, 'asm/libgcc/udivsi3.s', kind='asm', input_section='.libgcc_udivsi3'),
            segment('tail', 0x140, 0x200, 'src/tail.c', category='data', input_section='.rodata.gTail'),
        ])

    def test_gap_before_last_code_is_one_unmatched_function(self):
        measures = self.report['measures']
        self.assertEqual((measures['total_code'], measures['matched_code']), ('112', '96'))
        self.assertEqual((measures['total_data'], measures['matched_data']), ('400', '400'))
        self.assertEqual((measures['total_functions'], measures['matched_functions']), (3, 2))
        incbin = next(unit for unit in self.report['units'] if unit['name'] == 'incbin')
        self.assertEqual(incbin['functions'][0]['name'], 'sub_08000110')
        self.assertFalse(incbin['metadata']['complete'])

    def test_units_follow_sources_and_categories(self):
        units = {unit['name']: unit for unit in self.report['units']}
        self.assertEqual(units['src/main']['functions'][0]['name'], 'Main')
        self.assertEqual(units['src/main']['metadata']['source_path'], 'src/main.c')
        self.assertEqual(units['asm/libgcc/udivsi3']['metadata']['progress_categories'], ['runtime'])
        categories = {category['id']: category['measures'] for category in self.report['categories']}
        self.assertEqual(categories['game']['total_functions'], 2)
        self.assertEqual(categories['runtime']['matched_code_percent'], 100.0)


if __name__ == '__main__':
    unittest.main()
