"""Opt-in rendering correction for pinned m2c typed-pointer byte additions.

The evaluator uses byte offsets for analysis. Keep that AST intact and only
render marked raw pointer arithmetic in C element units when its final
pointee size is known and divides the immediate. Variable byte offsets use
unsigned address arithmetic rather than C element scaling. Other expressions retain
upstream behavior; bounds, non-divisible immediates and inferred ABIs still
require review. The downloaded m2c checkout is never modified.
"""

from dataclasses import replace
from pathlib import Path
import sys
from weakref import WeakSet


def install_pointer_stride_rendering():
    """Install subprocess-local hooks; return an undo function for tests."""
    downloaded = Path(__file__).resolve().parent / 'downloads' / 'm2c'
    sys.path.insert(0, str(downloaded))
    from m2c import evaluate, translate

    marked = WeakSet()
    original_add = evaluate.add_imm
    original_normalize = translate.BinaryOp.normalize_for_formatting
    original_intptr = translate.BinaryOp.intptr
    original_add_real = evaluate.handle_add_real
    original_assignment = translate.format_assignment
    dynamic = WeakSet()

    def add_imm(output_reg, source, imm, args):
        result = original_add(output_reg, source, imm, args)
        right = translate.early_unwrap_ints(result.right) if isinstance(result, translate.BinaryOp) else None
        if (isinstance(imm, translate.Literal)
                and isinstance(result, translate.BinaryOp) and result.op == '+'
                and translate.early_unwrap_ints(result.left) is translate.early_unwrap_ints(source)
                and isinstance(right, translate.Literal)
                and right.value == imm.value):
            marked.add(result)
        elif (isinstance(result, translate.BinaryOp) and result.op == '+'
              and translate.early_unwrap_ints(result.left) is translate.early_unwrap_ints(source)
              and not isinstance(translate.early_unwrap_ints(imm), translate.Literal)):
            dynamic.add(result)
        return result

    def intptr(left, op, right):
        # ARM LDM/STM writeback and SUB bypass add_imm. Their intptr
        # literals are still byte offsets, even when pointer types emerge
        # only after the evaluator has linked stack values and loop phis.
        result = original_intptr(left, op, right)
        literal = translate.early_unwrap_ints(right)
        if op in ('+', '-') and isinstance(literal, translate.Literal):
            marked.add(result)
        elif op in ('+', '-'):
            dynamic.add(result)
        return result

    def add_real(left, right, args):
        # A recognized array/field access is already expressed in element
        # units. Only the remaining raw register-add expression is in bytes.
        result = original_add_real(left, right, args)
        if isinstance(result, translate.BinaryOp):
            dynamic.add(result)
        return result

    def normalize(expr):
        if expr in marked:
            left = translate.late_unwrap(expr.left)
            right = translate.late_unwrap(expr.right)
            target = left.type.get_pointer_target() if left.type.is_pointer_or_array() else None
            size = target.get_size_bytes() if target else None
            if size and size > 1 and isinstance(right, translate.Literal) and right.value % size == 0:
                rendered = replace(expr, right=replace(right, value=right.value // size))
                return original_normalize(rendered)
        if expr in dynamic:
            left = translate.late_unwrap(expr.left)
            right = translate.late_unwrap(expr.right)
            targets = [operand.type.get_pointer_target() for operand in (left, right)
                       if operand.type.is_pointer_or_array()]
            result_target = expr.type.get_pointer_target() if expr.type.is_pointer() else None
            # m2c's unknown pointee has no analysis size, but valid-syntax C
            # declares it as four-byte M2C_UNK. A raw byte address must not
            # inherit that accidental element scaling. Restrict this case to
            # a proven byte-pointer result; unknown/wider results stay as-is.
            unknown_byte = (result_target is not None and result_target.get_size_bytes() == 1
                            and any(target is not None and target.get_size_bytes() is None
                                    for target in targets))
            if unknown_byte or any(target and (target.get_size_bytes() or 0) > 1 for target in targets):
                from m2c.types import Type
                word = Type.uintptr()
                address = translate.BinaryOp(
                    translate.Cast(left, word, silent=False), expr.op,
                    translate.Cast(right, word, silent=False), word)
                return translate.Cast(address, expr.type, silent=False)
        return original_normalize(expr)

    def assignment(dest, source, fmt):
        raw = translate.late_unwrap(source)
        if isinstance(raw, translate.BinaryOp) and raw in dynamic:
            rendered = normalize(raw)
            if isinstance(rendered, translate.Cast):
                # Upstream compound-assignment formatting expects the
                # normalizer to return a BinaryOp. A pointer += byteOffset
                # would also reintroduce element scaling, so keep the full
                # casted assignment instead.
                return original_assignment(dest, rendered, fmt)
        return original_assignment(dest, source, fmt)

    evaluate.add_imm = add_imm
    translate.BinaryOp.intptr = staticmethod(intptr)
    evaluate.handle_add_real = add_real
    translate.BinaryOp.normalize_for_formatting = normalize
    translate.format_assignment = assignment

    def undo():
        evaluate.add_imm = original_add
        translate.BinaryOp.intptr = staticmethod(original_intptr)
        evaluate.handle_add_real = original_add_real
        translate.format_assignment = original_assignment
        translate.BinaryOp.normalize_for_formatting = original_normalize

    return undo


def main():
    install_pointer_stride_rendering()
    from m2c.main import main as upstream_main
    upstream_main()


if __name__ == '__main__':
    main()
