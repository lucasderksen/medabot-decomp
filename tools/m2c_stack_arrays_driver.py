"""Opt-in declarations for fixed arrays in a reviewed m2c stack context.

Pinned m2c names an addressed array element but may omit its parent local
declaration. Register that known root before the element is registered. Keep
the returned expression and upstream instruction/type analysis unchanged.
No array sizes are inferred here, and the downloaded m2c is never modified.
"""

import json
from pathlib import Path
import sys


def install_known_stack_arrays():
    """Install subprocess-local declaration bookkeeping; return undo, records."""
    downloaded = Path(__file__).resolve().parent / 'downloads' / 'm2c'
    sys.path.insert(0, str(downloaded))
    from m2c import translate
    from m2c.options import Formatter

    original = translate.StackInfo.get_stack_var
    records = []

    def get_stack_var(info, location, *, store):
        local = original(info, location, store=store)
        if (not isinstance(local, translate.LocalVar) or not local.path
                or len(local.path) < 3 or local.path[0] != 0
                or info.stack_pointer_type is None):
            return local
        stack = info.stack_pointer_type.get_pointer_target().get_struct_declaration()
        if stack is None:
            return local
        for field in stack.fields:
            if not field.known or not field.type.is_array() or local.path[1] != field.name:
                continue
            size = field.type.get_size_bytes()
            if not size or not field.offset <= local.value < field.offset + size:
                continue
            root = translate.LocalVar(field.offset, type=field.type, path=local.path[:2])
            info.add_local_var(root)
            item = {'field': field.name, 'offset': field.offset, 'bytes': size,
                    'declaration': root.toplevel_decl(Formatter())}
            if item not in records:
                records.append(item)
            break
        return local

    translate.StackInfo.get_stack_var = get_stack_var

    def undo():
        translate.StackInfo.get_stack_var = original

    return undo, records


def main():
    report = None
    if '--stack-array-report' in sys.argv:
        index = sys.argv.index('--stack-array-report')
        report = Path(sys.argv[index + 1])
        del sys.argv[index:index + 2]
    undo_stride = None
    if '--fix-pointer-strides' in sys.argv:
        sys.argv.remove('--fix-pointer-strides')
        from m2c_stride_driver import install_pointer_stride_rendering
        undo_stride = install_pointer_stride_rendering()
    undo, records = install_known_stack_arrays()
    try:
        from m2c.main import main as upstream_main
        upstream_main()
    finally:
        undo()
        if undo_stride:
            undo_stride()
        if report:
            report.write_text(json.dumps(records, indent=2) + '\n', encoding='utf-8')


if __name__ == '__main__':
    main()
