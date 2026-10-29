"""Memory-width candidate rewrites preserve surrounding declarations and code."""

from pathlib import Path
import sys
import unittest
from unittest.mock import patch
import tempfile
import os

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from rewrite_drafts import (captured_key_identity, compiler_profiles, fix_scaled_unknown,
                            read_key_low_byte, share_full_width_zero, share_zero_at_first_store,
                            sink_pointer_initialization, variants, MAX_VARIANTS, context_fingerprint, rewrite_context, variant_key, _top_level_integer_members)


class MemoryWidthRewriteTests(unittest.TestCase):
    def test_key_read_keeps_declarations_writes_and_addresses(self):
        source = '''extern u16 gNewKeys;
void candidate(void) {
    gNewKeys = 0;
    gRepeatedKeys |= 2;
    use(&gHeldKeys);
    if (gNewKeys & 1) use(gRepeatedKeys);
}
'''
        result = read_key_low_byte(source, 'candidate')
        self.assertIn('extern u16 gNewKeys;', result)
        self.assertIn('gNewKeys = 0;', result)
        self.assertIn('gRepeatedKeys |= 2;', result)
        self.assertIn('use(&gHeldKeys);', result)
        self.assertIn('if ((*(u8 *)&gNewKeys) & 1)', result)
        self.assertIn('use((*(u8 *)&gRepeatedKeys));', result)
        self.assertIsNone(read_key_low_byte(result, 'candidate'))

    def test_nested_shift_argument_uses_byte_offset(self):
        source = '''extern M2C_UNK D_0300059A;
void candidate(void) {
    use((work[M2C_FIELD(base, u8 *, 3)] << 8) + &D_0300059A, 2);
}
'''
        result = fix_scaled_unknown(source, 'candidate')
        self.assertIn('<< 8) + (u8 *)&D_0300059A, 2)', result)
        self.assertIsNone(fix_scaled_unknown(result, 'candidate'))

    def test_hexadecimal_asset_offset_is_not_scaled_by_four(self):
        source = 'extern M2C_UNK D_0850F3F8;\nvoid candidate(void) {\n    use(&D_0850F3F8 + 0xFFFFFEA0);\n}\n'
        result = fix_scaled_unknown(source, 'candidate')
        self.assertIn('(u8 *)&D_0850F3F8 + 0xFFFFFEA0', result)
        self.assertIsNone(fix_scaled_unknown(result, 'candidate'))

    def test_shift_rewrite_respects_symbol_boundaries(self):
        source = 'extern M2C_UNK D_0300059A;\nvoid candidate(void) {\n    use((slot << 8) + &D_0300059AB);\n}\n'
        self.assertIsNone(fix_scaled_unknown(source, 'candidate'))



class LearnedRewriteTests(unittest.TestCase):
    def test_key_identity_all_byte_values_and_unsigned_boundaries(self):
        for key in list(range(65536)) + [0x80000000, 0xFFFFFFFF, 0xFFFFFFFE]:
            for mask in (1, 4):
                self.assertEqual((key & mask) & key, key & mask)

    def test_verified_mask_four_preserves_snapshot_and_hexadecimal_mask(self):
        source = "void candidate(void) {\n    u32 flags;\n    flags = *(u8 *)&gNewKeys;\n    if (0x04U & flags) use();\n}\n"
        result = captured_key_identity(source, 'candidate')
        self.assertIn('((flags & 4u) & flags)', result)
        self.assertEqual(result.count('*(u8 *)&gNewKeys'), 1)
        self.assertIsNone(captured_key_identity(result, 'candidate'))

    def test_mask_four_direct_reads_stay_independent_and_other_masks_stay_bounded(self):
        source = "void candidate(void) {\n    helper(gNewKeys & 4, 4 & gHeldKeys);\n}\n"
        result = captured_key_identity(source, 'candidate')
        self.assertIn('rewriteKeys = gNewKeys', result)
        self.assertIn('rewriteKeys1 = gHeldKeys', result)
        self.assertEqual(result.count('gNewKeys'), 1)
        self.assertEqual(result.count('gHeldKeys'), 1)
        self.assertIsNone(captured_key_identity(result, 'candidate'))
        self.assertIsNone(captured_key_identity(source.replace('& 4', '& 2').replace('4 &', '2 &'), 'candidate'))

    def test_captured_key_is_ordinary_local_and_idempotent(self):
        source = "void candidate(void) {\n    u32 keys;\n    keys = *(volatile u8 *)&gNewKeys;\n    if (keys & 1) use(keys);\n}\n"
        result = captured_key_identity(source, 'candidate')
        self.assertIn('((keys & 1u) & keys)', result)
        self.assertEqual(result.count('*(volatile u8 *)&gNewKeys'), 1)
        self.assertIsNone(captured_key_identity(result, 'candidate'))

    def test_direct_key_capture_preserves_each_read_and_its_branch(self):
        source = "void candidate(void) {\n    if (enabled) {\n        if (1 & gRepeatedKeys) use();\n    }\n    if (gRepeatedKeys & 1) again();\n}\n"
        result = captured_key_identity(source, 'candidate')
        self.assertEqual(result.count('gRepeatedKeys'), 2)
        self.assertIn('if (enabled) {\n        if (((rewriteKeys = gRepeatedKeys)', result)
        self.assertIn('u32 rewriteKeys;', result)
        self.assertIsNone(captured_key_identity(result, 'candidate'))

    def test_multiple_arguments_have_independent_key_capture_locals(self):
        source = "void candidate(void) {\n    helper(gNewKeys & 1, gHeldKeys & 1);\n}\n"
        result = captured_key_identity(source, 'candidate')
        self.assertIn('u32 rewriteKeys;', result)
        self.assertIn('u32 rewriteKeys1;', result)
        self.assertIn('rewriteKeys = gNewKeys', result)
        self.assertIn('rewriteKeys1 = gHeldKeys', result)
        self.assertEqual(result.count('gNewKeys'), 1)
        self.assertEqual(result.count('gHeldKeys'), 1)
        self.assertIsNone(captured_key_identity(result, 'candidate'))

    def test_byte_capture_does_not_repeat_or_widen_input_read(self):
        source = "void candidate(void) {\n    if (1 & (*(u8 *)&gNewKeys)) use();\n}\n"
        result = captured_key_identity(source, 'candidate')
        self.assertEqual(result.count('(*(u8 *)&gNewKeys)'), 1)
        self.assertIn('rewriteKeys = (*(u8 *)&gNewKeys)', result)

    def test_key_rule_refuses_volatile_local_or_shadowed_local(self):
        source = "void candidate(void) {\n    volatile u32 keys;\n    if (keys & 1) use();\n}\n"
        self.assertIsNone(captured_key_identity(source, 'candidate'))
        source = "void candidate(void) {\n    u32 keys;\n    {\n        u32 keys;\n        if (keys & 1) use();\n    }\n}\n"
        self.assertIsNone(captured_key_identity(source, 'candidate'))

    def test_new_rules_do_not_edit_other_functions_comments_or_strings(self):
        source = "void other(void) {\n    if (gNewKeys & 1) use();\n}\nvoid candidate(void) {\n    /* gNewKeys & 1; */\n    say(\"gNewKeys & 1\");\n    if (gNewKeys & 1) use();\n}\n"
        result = captured_key_identity(source, 'candidate')
        self.assertTrue(result.startswith(source.split('void candidate', 1)[0]))
        self.assertIn('/* gNewKeys & 1; */', result)
        self.assertIn('say("gNewKeys & 1");', result)
        self.assertEqual(result.count('rewriteKeys = gNewKeys'), 1)

    def test_inline_comments_in_matched_expressions_are_preserved(self):
        source = "void candidate(void) {\n    if (gNewKeys /* snapshot */ & 1) use();\n}\n"
        self.assertIsNone(captured_key_identity(source, 'candidate'))
        source = "u32 candidate(void) {\n    M2C_FIELD(work, /* byte */ u8 *, 1) = 0;\n    M2C_FIELD(work, u16 *, 2) = 0;\n    return 0;\n}\n"
        result = share_full_width_zero(source, 'candidate')
        self.assertIn('M2C_FIELD(work, /* byte */ u8 *, 1) = 0;', result)

    def test_shared_zero_preserves_scalar_store_sites_and_returns(self):
        source = "s32 candidate(void) {\n    M2C_FIELD(work, u8 *, 1) = 0;\n    M2C_FIELD(work, u16 *, 2) = 0;\n    return 0;\n}\n"
        result = share_full_width_zero(source, 'candidate')
        self.assertIn('u32 rewriteZero = 0;', result)
        self.assertIn('M2C_FIELD(work, u8 *, 1) = rewriteZero;', result)
        self.assertIn('M2C_FIELD(work, u16 *, 2) = rewriteZero;', result)
        self.assertIn('return rewriteZero;', result)
        self.assertEqual(result.count('M2C_FIELD('), source.count('M2C_FIELD('))
        self.assertIsNone(share_full_width_zero(result, 'candidate'))

    def test_frame_type_parser_refuses_multiline_nested_fields(self):
        body = "\n    u16 angle;\n    union {\n        s32 nested;\n        struct {\n            u16 low;\n        } parts;\n    } position;\n    u8 *pointer;\n    u8 active;\n"
        self.assertEqual(_top_level_integer_members(body), {'angle', 'active'})

    def test_shared_zero_uses_established_frame_scalar_fields(self):
        source = "u32 candidate(void) {\n    struct FrameObject *object;\n    object->angle = 0;\n    gFrameObjects[3].unknown2C[1] = 0;\n    return 0;\n}\n"
        result = share_full_width_zero(source, 'candidate')
        self.assertIn('object->angle = rewriteZero;', result)
        self.assertIn('gFrameObjects[3].unknown2C[1] = rewriteZero;', result)
        union = source.replace('object->angle', 'object->positionX')
        result = share_full_width_zero(union, 'candidate')
        self.assertIn('object->positionX = 0;', result)

    def test_first_store_initializes_after_address_without_hoisting(self):
        source = "u32 candidate(void) {\n    u8 *work;\n    work = input;\n    *work = 0;\n    return 0;\n}\n"
        result = share_zero_at_first_store(source, 'candidate')
        self.assertIn('u32 rewriteZero;', result)
        self.assertIn('work = input;\n    *work = (rewriteZero = 0);', result)
        self.assertIn('return rewriteZero;', result)
        self.assertIsNone(share_zero_at_first_store(result, 'candidate'))

    def test_first_store_dominance_guard(self):
        source = "u32 candidate(void) {\n    if (enabled) {\n        M2C_FIELD(work, u8 *, 1) = 0;\n    }\n    return 0;\n}\n"
        self.assertIsNone(share_zero_at_first_store(source, 'candidate'))
        self.assertIsNotNone(share_full_width_zero(source, 'candidate'))

    def test_shared_zero_refuses_pointer_store_and_pointer_return(self):
        source = "u8 *candidate(void) {\n    u8 *pointer;\n    pointer = 0;\n    return 0;\n}\n"
        self.assertIsNone(share_full_width_zero(source, 'candidate'))
        source = "void candidate(void) {\n    object->unknown = 0;\n    other->unknown = 0;\n}\n"
        self.assertIsNone(share_full_width_zero(source, 'candidate'))

    def test_shared_zero_refuses_shadowed_pointer_local(self):
        source = "u32 candidate(void) {\n    u32 value;\n    {\n        u8 *value;\n        value = 0;\n    }\n    return 0;\n}\n"
        self.assertIsNone(share_full_width_zero(source, 'candidate'))

    def test_shared_zero_handles_name_collision_and_volatile_store_width(self):
        source = "u32 candidate(void) {\n    u32 rewriteZero;\n    *(volatile u16 *)0x04000000 = 0;\n    return 0;\n}\n"
        result = share_full_width_zero(source, 'candidate')
        self.assertIn('u32 rewriteZero1 = 0;', result)
        self.assertIn('*(volatile u16 *)0x04000000 = rewriteZero1;', result)

    def test_sink_pointer_initialization_only_adjacent_literal_store(self):
        source = "void candidate(void) {\n    u8 *destination;\n    destination = &object->commandDelay;\n    *destination = 0;\n}\n"
        result = sink_pointer_initialization(source, 'candidate')
        self.assertIn('*(destination = &object->commandDelay) = 0;', result)
        self.assertIsNone(sink_pointer_initialization(result, 'candidate'))
        self.assertIsNone(sink_pointer_initialization(source.replace('*destination = 0;', '*destination = *input;'), 'candidate'))
        self.assertIsNone(sink_pointer_initialization(source.replace('*destination = 0;', 'helper();\n    *destination = 0;'), 'candidate'))

    def test_pointer_sink_combines_with_shared_zero_but_refuses_volatile_value(self):
        source = "u32 candidate(void) {\n    u8 *destination;\n    destination = &object->commandDelay;\n    *destination = 0;\n    return 0;\n}\n"
        shared = share_full_width_zero(source, 'candidate')
        result = sink_pointer_initialization(shared, 'candidate')
        self.assertIn('*(destination = &object->commandDelay) = rewriteZero;', result)
        volatile = shared.replace('u32 rewriteZero = 0;', 'volatile u32 rewriteZero = 0;')
        self.assertIsNone(sink_pointer_initialization(volatile, 'candidate'))

    def test_learned_profiles_are_bounded_and_keep_expensive_passes(self):
        profiles = compiler_profiles(['-O1', '-fprologue-bugfix'], 'captured_key_identity')
        self.assertEqual(len(profiles), 4)
        self.assertIn(['-O2', '-fprologue-bugfix', '-fno-force-mem'], profiles)
        self.assertIn(['-O2', '-fprologue-bugfix', '-fno-force-mem', '-fno-cse-skip-blocks'], profiles)
        self.assertFalse(any('-fno-expensive-optimizations' in p for p in profiles))
        self.assertEqual(len(compiler_profiles(['-fprologue-bugfix'], 'original_profile_control')), 3)

    def test_extra_profiles_are_targeted_to_key_rules_or_explicit_opt_in(self):
        best = ['-O1', '-fprologue-bugfix']
        for label in ['share_full_width_zero', 'sink_pointer_initialization', 'hoist_member_array+share_zero_at_first_store']:
            self.assertEqual(compiler_profiles(best, label), [best, ['-fprologue-bugfix']])
            self.assertEqual(len(compiler_profiles(best, label, all_profiles=True)), 4)
        self.assertEqual(len(compiler_profiles(best, 'read_key_low_byte+captured_key_identity')), 4)
        self.assertEqual(len(compiler_profiles(best, 'original_profile_control')), 4)

    def test_learned_rule_has_reserved_variant_slot(self):
        source = """extern M2C_UNK D_0300059A;
void candidate(u8 arg0) {
    u8 var_r0;
    u32 keys;
    keys = gNewKeys;
    var_r0 = gState0TransferWork.bytes[4];
    use(((arg0 << 8) + gSetupBuffer_03000590));
    use((arg0 << 8) + &D_0300059A);
    use(M2C_FIELD(&gWork, u8 *, 1));
    use(gOther[0]);
    use(gOther + 4);
    if (keys & 1) use();
    M2C_FIELD(work, u8 *, 1) = 0;
    M2C_FIELD(work, u16 *, 2) = 0;
}
"""
        results = variants(source, 'candidate')
        self.assertLessEqual(len(results), MAX_VARIANTS)
        self.assertTrue(any(label == 'captured_key_identity' for label, _ in results))
        self.assertTrue(any(label == 'share_full_width_zero' for label, _ in results))
        self.assertEqual(len({text for _, text in results}), len(results))

    def test_key_rule_refuses_precedence_sensitive_partial_expression(self):
        for expression in ['gNewKeys & 1 << 2', 'gNewKeys & 1 + 2',
                           '2 + gNewKeys & 1', '!gNewKeys & 1', '1 & gNewKeys + 2',
                           'gNewKeys & 1 == 0', 'other == gNewKeys & 1']:
            source = 'void candidate(void) {\n    if (' + expression + ') use();\n}\n'
            self.assertIsNone(captured_key_identity(source, 'candidate'), expression)

    def test_failed_variant_context_invalidates_each_input(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            paths = ['include/layout.h', 'tools/downloads/m2c/m2c_macros.h',
                     'tools/compiler_agbcc.py', 'config/symbols.json', 'build/medabots.elf',
                     'tools/downloads/agbcc/' + ('agbcc.exe' if os.name == 'nt' else 'agbcc')]
            for relative in paths:
                path = root / relative
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(b'initial')
            baseline = context_fingerprint(root)
            self.assertEqual(baseline, context_fingerprint(root))
            for relative in paths:
                path = root / relative
                path.write_bytes(b'changed')
                self.assertNotEqual(baseline, context_fingerprint(root), relative)
                path.write_bytes(b'initial')
            (root / 'include/new.h').write_bytes(b'new declaration')
            self.assertNotEqual(baseline, context_fingerprint(root))

    def test_variant_generation_stops_after_quotas_and_keeps_atomic_rules(self):
        import rewrite_drafts as module
        calls = []
        def transform(label):
            def apply(text, name):
                calls.append(label)
                return text + ' ' + label
            apply.__name__ = label
            return apply
        old = [transform('old' + str(i)) for i in range(10)]
        learned = [transform('learned' + str(i)) for i in range(2)]
        with patch.object(module, 'TRANSFORMS', old + learned), patch.object(module, 'NEW_TRANSFORMS', set(learned)):
            results = module.variants('source', 'candidate')
        self.assertEqual(len(results), MAX_VARIANTS)
        self.assertLess(len(calls), 100)  # exhaustive triples alone would need660 calls
        labels = {label for label, _ in results}
        self.assertIn('learned0', labels)
        self.assertIn('learned1', labels)
        calls.clear()
        with patch.object(module, 'NEW_TRANSFORMS', set(learned)):
            legacy = module.variants('source', 'candidate', old)
        self.assertEqual(len(legacy), MAX_VARIANTS)
        self.assertTrue(all('learned' not in label for label, _ in legacy))
        with patch.object(module, 'TRANSFORMS', learned), patch.object(module, 'NEW_TRANSFORMS', set(learned)):
            few_old = module.variants('source', 'candidate')
        self.assertEqual(len(few_old), 3)  # both atomic rules and their combination

    def test_context_is_hashed_once_per_batch_process(self):
        rewrite_context.cache_clear()
        with patch('rewrite_drafts.context_fingerprint', return_value='context') as fingerprint:
            self.assertEqual(rewrite_context(), 'context')
            self.assertEqual(rewrite_context(), 'context')
            fingerprint.assert_called_once_with()
        rewrite_context.cache_clear()

    def test_failed_variant_key_does_not_reuse_old_cache(self):
        first = variant_key('source', ['-O2'], 'context A')
        self.assertTrue(first.startswith('v2:'))
        self.assertNotEqual(first, variant_key('source', ['-O2'], 'context B'))
        self.assertNotEqual(first, variant_key('source', ['-O1'], 'context A'))
        self.assertNotEqual(first, variant_key('changed', ['-O2'], 'context A'))

if __name__ == '__main__':
    unittest.main()
