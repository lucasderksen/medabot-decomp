"""Preserve observed ARM word-argument positions in opt-in m2c drafts.

Unknown signatures may omit unused earlier registers or stack words. The C
formatter must retain those positions, rather than move a used R2 into R1.
This rendering-only hook leaves analysis and known prototypes unchanged. It
does not recover caller values or validate inferred stack arguments.
"""

from pathlib import Path
import json
import sys


def install_argument_slot_rendering():
    downloaded = Path(__file__).resolve().parent / 'downloads/m2c'
    sys.path.insert(0, str(downloaded))
    from m2c import translate, if_statements
    from m2c.types import Type
    from m2c.instruction import Register

    original = if_statements.get_function_text

    def render(info, options):
        stack = info.stack_info
        arguments = list(stack.arguments)
        signature = Type.ptr(info.symbol.type).get_function_pointer_signature()
        if (signature is None or signature.params_known or
                stack.replace_first_arg is not None or info.return_type.is_struct()):
            return original(info, options)
        slots = []
        for argument in arguments:
            location = argument.loc
            if (not (argument.type.is_reg() or argument.type.is_pointer()) or
                    (argument.type.get_size_bits() or 32) > 32):
                return original(info, options)
            if location.reg is not None:
                name = location.reg.register_name
                if name not in ('r0', 'r1', 'r2', 'r3'):
                    return original(info, options)
                slot = int(name[1:])
            elif location.offset is not None and location.offset >= 0 and location.offset % 4 == 0:
                slot = 4 + location.offset // 4
            else:
                return original(info, options)
            slots.append(slot)
        # Large apparent stack arguments often reflect unrecovered local arrays.
        if (not slots or max(slots) > 16 or len(set(slots)) != len(slots) or
                slots == list(range(len(slots)))):
            return original(info, options)
        mapping = dict(zip(slots, arguments))
        names = dict(stack.param_names)
        padded = []
        for index in range(max(slots) + 1):
            if index in mapping:
                padded.append(mapping[index])
                continue
            location = (translate.ArgLoc(None, index, Register(f'r{index}')) if index < 4 else
                        translate.ArgLoc((index - 4) * 4, None, None))
            stack.param_names[location] = f'_unused_arg{index}'
            padded.append(translate.PassedInArg(loc=location, stack_info=stack, type=Type.u32()))
        stack.arguments[:] = padded
        try:
            print('ARG_SLOT_RENDER_REPAIR ' + json.dumps({
                'function': stack.function.name, 'observed_slots': slots,
                'padded_parameters': len(padded),
            }), file=sys.stderr)
            return original(info, options)
        finally:
            stack.arguments[:] = arguments
            stack.param_names.clear()
            stack.param_names.update(names)

    if_statements.get_function_text = render

    def undo():
        if_statements.get_function_text = original

    return undo


def main():
    if '--fix-pointer-strides' in sys.argv:
        sys.argv.remove('--fix-pointer-strides')
        from m2c_stride_driver import install_pointer_stride_rendering
        install_pointer_stride_rendering()
    install_argument_slot_rendering()
    from m2c.main import main as upstream_main
    upstream_main()


if __name__ == '__main__':
    main()
