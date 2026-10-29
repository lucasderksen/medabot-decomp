"""Guard the optional source-signature hints against invented interfaces."""

from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from production_signatures import collect, definitions, used_declarations


def segment(name, source="src/sample.c", **extra):
    return dict(kind="c", source=source, input_section=".text." + name, **extra)


class ProductionSignatureTests(unittest.TestCase):
    def test_only_active_external_definitions_supply_hints(self):
        source = """extern s32 active(u8 value, const void *data) { return value; }
void unlinked(void) { }
static void local(void) { }
void data_region(void) { }
void declaration(void);
"""
        rows = collect([segment("active"), segment("local"),
                        segment("data_region", category="data"), segment("declaration")],
                       {"src/sample.c": source}, "")
        self.assertEqual([(r["name"], r["prototype"]) for r in rows],
                         [("active", "s32 active(u8, const void *);")])
        self.assertEqual(rows[0]["source"], "src/sample.c")

    def test_opaque_old_style_variadic_and_nested_shapes_are_rejected(self):
        source = """void old() { }
void opaque(struct Private *work) { }
u16 *typed_pointer(void) { }
void callback(void (*fn)(void)) { }
void variadic(u32 value, ...) { }
void array(u8 bytes[3]) { }
volatile u32 qualified(void) { }
void wrapper(void) {
 void nested(void) { }
 const char *text="void invented(void) { }";
}
/* void commented(void) { } */
"""
        self.assertEqual([r["name"] for r in definitions(source)], ["wrapper"])

    def test_headers_duplicates_and_known_abi_exclusion_take_priority(self):
        sources = {"src/a.c": "void known(void) {}\nvoid duplicate(void) {}\nvoid sub_08060D28(void) {}\nvoid eligible(void) {}",
                   "src/b.c": "void duplicate(void) {}"}
        segments = [segment(n, "src/a.c") for n in ("known", "duplicate", "sub_08060D28", "eligible")]
        segments.append(segment("duplicate", "src/b.c"))
        rows = collect(segments, sources, "s32 known(u32);")
        self.assertEqual([r["name"] for r in rows], ["eligible"])

    def test_conditional_source_requires_preprocessing_review(self):
        self.assertEqual(definitions("#if 0\nvoid inactive(void) {}\n#endif\nvoid active(void) {}"), [])

    def test_used_hint_declarations_keep_standalone_drafts_complete(self):
        rows = [{"name": n, "prototype": "void " + n + "(void);"}
                for n in ("entry", "used", "already", "unused", "callback", "use", "returned")]
        text = "extern void already(void);\nvoid entry(void) { used(); already(); set(callback);\n return returned();\n}\n/* unused(); */"
        self.assertEqual(used_declarations(text, rows, "entry"),
                         "extern void used(void);\nextern void callback(void);\nextern void returned(void);\n\n")

    def test_generate_preserves_hint_declarations_in_saved_and_compiled_text(self):
        import m2c_candidate as candidate
        hints = [{"name": "callee", "prototype": "void callee(u32);"}]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory)
            with patch.object(candidate, "OUTPUT", output), \
                 patch.object(candidate, "decode", return_value=({}, {}, {}, set())), \
                 patch.object(candidate, "render", return_value="assembly"), \
                 patch.object(candidate.subprocess, "run", return_value=subprocess.CompletedProcess(
                     [], 0, "void entry(void) { callee(1); }\n", "")):
                _, _, _, _, result = candidate.generate(b"", None, candidate.BASE,
                    candidate.BASE + 4, "entry", signature_hints=hints)
            expected = "extern void callee(u32);\n\nvoid entry(void) { callee(1); }\n"
            self.assertEqual(result.stdout, expected)
            self.assertEqual((output / "entry.c").read_text(), expected)


if __name__ == "__main__":
    unittest.main()
