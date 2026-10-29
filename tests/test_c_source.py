"""Whole-function extraction survives real draft formatting and literal braces."""

from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from c_source import function_body_lines, function_definition
from clone_transfer import function_text
from permute import extract_function


class DefinitionExtractionTests(unittest.TestCase):
    def test_search_scope_uses_outer_body_and_ignores_following_functions(self):
        source = ('void previous(void) {}\nvoid selected(void)\n{\n'
                  '    int count;\n    if (count)\n    {\n'
                  '        use(count);\n    }\n}\n'
                  'void next(void)\n{\n}\n')
        self.assertEqual(function_body_lines(source, 'selected'), (2, 8))

    def test_body_line_search_ignores_braces_in_signature_comments(self):
        source = 'void selected(/* { */ void) /* { */\n{\n    done();\n}\n'
        self.assertEqual(function_body_lines(source, 'selected'), (1, 3))

    def test_unindented_nested_block_does_not_truncate_the_function(self):
        definition = 'void selected(void) {\n{\n    first();\n}\n    last();\n}'
        source = 'void selected(void);\n' + definition + '\nvoid next(void) { other(); }\n'
        self.assertEqual(function_definition(source, 'selected'), definition)
        self.assertEqual(extract_function(source, 'selected'), definition)

    def test_comments_and_literals_cannot_close_the_function(self):
        definition = '''void selected(void)
{
    const char *message = "} \\" {";
    char closing = '}'; /* } */
    // } selected() {
    last();
}'''
        self.assertEqual(function_definition(definition, 'selected'), definition)
        self.assertEqual(extract_function(definition, 'selected'), definition.replace('void selected(void)\n{', 'void selected(void) {'))

    def test_missing_and_unclosed_definitions_are_rejected(self):
        for source in ('void selected(void);', 'void selected(void) {\n{\n}\n'):
            with self.assertRaises(ValueError):
                function_definition(source, 'selected')

    def test_clone_keeps_the_complete_body_and_private_type(self):
        definition = 'void selected(void) {\n{\n    first();\n}\n    last();\n}'
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'seed.c'
            path.write_text('struct View { u8 byte; };\nextern void first(void);\n' + definition + '\nvoid next(void) { other(); }\n')
            result = function_text(path, 'selected')
        self.assertIn('struct View { u8 byte; };', result)
        self.assertIn(definition, result)
        self.assertNotIn('void next', result)


if __name__ == '__main__':
    unittest.main()
