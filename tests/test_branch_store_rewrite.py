"""Branch-store candidates retain live values and C conversion/side effects."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from rewrite_drafts import sink_phi_store, variants


class BranchStoreRewriteTests(unittest.TestCase):
    def source(self, following='    frame->scaleX = value;\n'):
        return '''void candidate(void) {
    u8 value;
    if (frame->commandStopped & 4) {
        value = 0x60;
    } else {
        value = 0x40;
    }
    frame->scaleY = value;
''' + following + '}\n'

    def test_live_value_remains_assigned_for_second_store(self):
        result=sink_phi_store(self.source(), 'candidate')
        self.assertIn('value = 0x60;\n        frame->scaleY = value;', result)
        self.assertIn('value = 0x40;\n        frame->scaleY = value;', result)
        self.assertIn('    frame->scaleX = value;', result)
        self.assertIsNone(sink_phi_store(result, 'candidate'))

    def test_narrow_conversion_is_retained_before_wider_store(self):
        source=self.source('    return_value(value);\n').replace('0x60','0x100').replace('frame->scaleY','wordResult')
        result=sink_phi_store(source,'candidate')
        self.assertEqual(result.count('wordResult = value;'), 2)
        self.assertIn('value = 0x100;', result)
        self.assertNotIn('wordResult = 0x100;', result)

    def test_volatile_local_assignment_and_read_are_retained(self):
        source=self.source().replace('u8 value;', 'volatile u8 value;')
        result=sink_phi_store(source,'candidate')
        self.assertIn('volatile u8 value;', result)
        self.assertEqual(result.count('value = 0x'),2)
        self.assertEqual(result.count('frame->scaleY = value;'),2)

    def test_calls_stay_sequenced_as_two_statements_per_path(self):
        source=self.source().replace('0x60','next_a()').replace('0x40','next_b()').replace('frame->scaleY','*next_target()')
        result=sink_phi_store(source,'candidate')
        self.assertIn('value = next_a();\n        *next_target() = value;',result)
        self.assertIn('value = next_b();\n        *next_target() = value;',result)
        self.assertEqual(result.count('next_a()'),1)
        self.assertEqual(result.count('next_b()'),1)

    def test_exhaustive_else_if_chain_preserves_all_assignments(self):
        source=self.source().replace('    } else {','    } else if (other) {\n        value = 0x50;\n    } else {')
        result=sink_phi_store(source,'candidate')
        self.assertEqual(result.count('frame->scaleY = value;'),3)
        self.assertIn('value = 0x50;',result)

    def test_incomplete_chain_and_intervening_statements_are_held(self):
        partial='void candidate(void) {\n    if (c) {\n        value = 1;\n    }\n    output = value;\n}\n'
        self.assertIsNone(sink_phi_store(partial,'candidate'))
        self.assertIsNone(sink_phi_store(self.source().replace('    frame->scaleY','    helper();\n    frame->scaleY'),'candidate'))
        self.assertIsNone(sink_phi_store(self.source().replace('    frame->scaleY','join:\n    frame->scaleY'),'candidate'))

    def test_other_functions_comments_strings_and_missing_name_are_held(self):
        other=self.source().replace('candidate','other')
        source=other+self.source().replace('    u8 value;','    u8 value;\n    say("value = 1;");\n    /* if (ignored) { value = 1; } */')
        result=sink_phi_store(source,'candidate')
        self.assertTrue(result.startswith(other))
        self.assertIn('say("value = 1;");',result)
        self.assertIn('/* if (ignored) { value = 1; } */',result)
        self.assertIsNone(sink_phi_store(other,'candidate'))

    def test_nonmatching_target_and_partial_branch_are_held(self):
        self.assertIsNone(sink_phi_store(self.source().replace('frame->scaleY = value','frame->scaleY = value + 1'),'candidate'))
        self.assertIsNone(sink_phi_store(self.source().replace('        value = 0x60;','        helper();\n        value = 0x60;'),'candidate'))

    def test_multiple_independent_chains_remain_live(self):
        source=self.source().replace('    frame->scaleX = value;',self.source('').split('    u8 value;\n',1)[1].rsplit('}',1)[0]+'    frame->scaleX = value;')
        result=sink_phi_store(source,'candidate')
        self.assertEqual(result.count('value = 0x60;'),2)
        self.assertEqual(result.count('frame->scaleY = value;'),4)

    def test_rule_has_reserved_learned_variant(self):
        choices=variants(self.source(),'candidate')
        self.assertTrue(any(label=='sink_phi_store' for label,_ in choices[:12]))


if __name__=='__main__':
    unittest.main()
