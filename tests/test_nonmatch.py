"""NONMATCH functions: generated assembly, progress accounting and replacement on a match."""

from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import build
import common
import compiler_agbcc
import nonmatch
import objdiff_report
import progress_report


def segment(name, start, end, **extra):
    return {'name': name, 'start': start, 'end': end, 'kind': 'c', 'source': f'src/{name}.c',
            'input_section': f'.text.{name}', **extra}


class AssemblyTests(unittest.TestCase):
    def test_symbols_follow_the_current_build(self):
        by_name = {'gFrameObjects': 0x03002C30, 'Renamed': 0x08049420}
        by_address = {0x03002C30: ['gFrameObjects'], 0x08049420: ['Renamed']}
        self.assertEqual(nonmatch.resolve('gFrameObjects', by_name, by_address, False), 'gFrameObjects')
        self.assertEqual(nonmatch.resolve('sub_08049420', by_name, by_address, True), 'Renamed')
        self.assertEqual(nonmatch.resolve('D_03001384', by_name, by_address, False), '0x03001384')
        self.assertEqual(nonmatch.resolve('.L08048C9C', by_name, by_address, False), '.L08048C9C')
        with self.assertRaises(ValueError):
            nonmatch.resolve('sub_08001234', by_name, by_address, True)

    def test_include_body_drops_the_function_header(self):
        source = ('\t.syntax unified\n\t.thumb\n.text\n\t.align 2, 0\n\t.globl sub_08000100\n\t.thumb_func\n'
                  'sub_08000100:\n\tpush\t{lr}\n\tadd\tr0, sp, r0\n\tbl\tsub_08000200\n\tpop\t{r0}\n\tbx\tr0\n'
                  '.L08000110:\n\t.word\tD_03000000\n')
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / 'build' / 'm2c').mkdir(parents=True)
            (root / 'build' / 'm2c' / 'sub_08000100.s').write_text(source, encoding='utf-8')
            with patch.object(nonmatch, 'ROOT', root):
                text = nonmatch.assembly('sub_08000100', 0x100, 0x114, {'Helper': 0x08000200}, {0x08000200: ['Helper']})
        lines = [line.strip() for line in text.splitlines() if not line.startswith('@')]
        self.assertEqual(lines[0], '.syntax unified')
        self.assertEqual(lines[-1], '.syntax divided')
        self.assertNotIn('sub_08000100:', lines)
        self.assertIn('add\tr0, sp', lines)
        self.assertIn('bl\tHelper', lines)
        self.assertIn('.word\t0x03000000', lines)

    def test_compile_cache_sees_included_assembly(self):
        text = 'void f(void) __attribute__((naked)) { asm(".include " "\\"asm/non_matching/f.inc\\""); }'
        self.assertEqual(compiler_agbcc.ASM_INCLUDE.findall(text), ['asm/non_matching/f.inc'])


class AccountingTests(unittest.TestCase):
    segments = [
        segment('main', 0x0, 0x40),
        segment('sub_08000040', 0x40, 0x80, nonmatching=True),
        segment('table', 0x80, 0xA0, category='data'),
    ]

    def test_progress_counts_nonmatch_as_not_in_source(self):
        with patch.object(progress_report, 'rom_config', return_value={'size': 0xA0}):
            row = progress_report.measure(self.segments)
        self.assertEqual((row['code_end'], row['code_done'], row['functions']), (0x80, 0x40, 1))
        self.assertEqual(row['game_c'], 0x40)

    def test_objdiff_report_lists_nonmatch_as_unmatched(self):
        report = objdiff_report.build(self.segments)
        measures = report['measures']
        self.assertEqual((measures['total_code'], measures['matched_code']), ('128', '64'))
        self.assertEqual((measures['total_functions'], measures['matched_functions']), (2, 1))
        unit = next(unit for unit in report['units'] if unit['name'] == 'src/sub_08000040')
        self.assertFalse(unit['metadata']['complete'])
        self.assertEqual(unit['functions'][0]['fuzzy_match_percent'], 0.0)

    def test_linker_discards_constants_of_dead_attempts_only(self):
        entries = [dict(entry) for entry in self.segments]
        script = build.generate_linker(entries, 0x08000000)
        discard = next(line for line in script.splitlines() if '/DISCARD/' in line and '.rodata' in line)
        self.assertIn('sub_08000040', discard)
        self.assertNotIn('main', discard)
        self.assertLess(script.index(discard), script.index('.unexpected'))


class ReplacementTests(unittest.TestCase):
    def test_a_match_replaces_the_nonmatch_entry_and_its_files(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / 'src' / 'non_matching').mkdir(parents=True)
            (root / 'asm' / 'non_matching').mkdir(parents=True)
            c_file = root / 'src' / 'non_matching' / 'sub_08000040.c'
            include = root / 'asm' / 'non_matching' / 'sub_08000040.inc'
            c_file.write_text('', encoding='utf-8')
            include.write_text('', encoding='utf-8')
            entries = [segment('main', '0x000000', '0x000040'),
                       dict(segment('sub_08000040', '0x000040', '0x000080', nonmatching=True),
                            source='src/non_matching/sub_08000040.c')]
            with patch.object(common, 'ROOT', root):
                kept = common.replace_nonmatching(entries, 0x40, 0x80)
            self.assertEqual([entry['name'] for entry in kept], ['main'])
            self.assertFalse(c_file.exists() or include.exists())


if __name__ == '__main__':
    unittest.main()
