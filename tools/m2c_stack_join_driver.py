"""Opt-in recovery of agreed constant outgoing-stack words at ARM CFG joins.

Keep m2c's ordinary stack argument state local to each basic block. Separately
track full literal word stores and intersect completed predecessor states. Only
inject missing slots required by a known, nonvariadic scalar/pointer prototype.
Calls, SP changes and unclassified writes invalidate the tracked values. This
does not infer signatures, local array sizes, path predicates or loop fixed points.
The downloaded m2c is never edited; hooks are confined to this subprocess.
"""
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools/downloads/m2c'))


def install_constant_stack_joins():
    """Install conservative bookkeeping and return an undo callback and report."""
    from m2c import translate as t
    originals = {name: getattr(t, name) for name in
                 ('translate_all_blocks', 'translate_block', 'evaluate_instruction')}
    methods = {name: getattr(t.NodeState, name) for name in
               ('store_memory', 'make_function_call', 'push_subroutine_arg')}
    completed = {}
    current = {}
    store_seen = set()
    records = []

    def words(state):
        return current.setdefault(id(state.node), {})

    def all_blocks(*args, **kwargs):
        completed.clear()
        current.clear()
        store_seen.clear()
        return originals['translate_all_blocks'](*args, **kwargs)

    def block(state, options):
        parents = state.node.parents
        inherited = {}
        if parents and all(id(parent) in completed for parent in parents):
            rows = [completed[id(parent)] for parent in parents]
            inherited = {offset: value for offset, value in rows[0].items()
                         if all(row.get(offset) == value for row in rows[1:])}
        current[id(state.node)] = inherited
        result = originals['translate_block'](state, options)
        completed[id(state.node)] = dict(words(state))
        return result

    def instruction(ref, state):
        instr = ref.instruction
        node_id = id(state.node)
        store_seen.discard(node_id)
        if (t.Register('sp') in instr.outputs + instr.clobbers
                or instr.mnemonic in ('push', 'pop')
                or (instr.is_store and instr.mnemonic not in ('str', 'strb', 'strh'))):
            words(state).clear()
        try:
            return originals['evaluate_instruction'](ref, state)
        finally:
            if instr.is_store and node_id not in store_seen:
                # Upstream may elide a register-save store; still a machine write.
                words(state).clear()

    def store(state, stmt, reg):
        store_seen.add(id(state.node))
        known = words(state)
        if isinstance(stmt.dest, t.SubroutineArg):
            offset = stmt.dest.value
            mnemonic = state.regs.current_instr_ref().instruction.mnemonic
            width = {'str': 4, 'strh': 2, 'strb': 1}.get(mnemonic)
            if width is None:
                known.clear()
            else:
                for previous in list(known):
                    if previous < offset + width and offset < previous + 4:
                        del known[previous]
                expr = t.early_unwrap(stmt.source)
                if (mnemonic == 'str' and offset >= 0 and offset % 4 == 0
                        and isinstance(expr, t.Literal)
                        and -0x80000000 <= expr.value <= 0xFFFFFFFF
                        and not expr.type.is_likely_float()):
                    known[offset] = expr.value
        else:
            # An indirect write may alias this outgoing stack frame.
            known.clear()
        return methods['store_memory'](state, stmt, reg)

    def call(state, target, outputs):
        arch = state.stack_info.global_info.arch
        signature = t.as_function_ptr(target).type.get_function_pointer_signature()
        def scalar(type_):
            return ((type_.is_int() or type_.is_pointer())
                    and type_.get_size_bytes() in (1, 2, 4))
        if (arch.arch == t.Target.ArchEnum.ARM and arch.home_space_size == 0
                and signature is not None and signature.params_known
                and not signature.is_variadic
                and (signature.return_type.is_void() or scalar(signature.return_type))
                and all(scalar(param.type) for param in signature.params)):
            abi = arch.function_abi(signature, {}, for_call=True)
            for slot in abi.arg_slots:
                offset = slot.loc.offset
                if (slot.loc.reg is None and offset in words(state)
                        and offset not in state.subroutine_args):
                    value = words(state)[offset]
                    state.subroutine_args[offset] = t.Literal(value)
                    item = {'function': state.stack_info.function.name,
                            'node': state.node.name(),
                            'parents': [parent.name() for parent in state.node.parents],
                            'callee': target.format(t.Formatter()),
                            'offset': offset, 'value': value}
                    if item not in records:
                        records.append(item)
        try:
            return methods['make_function_call'](state, target, outputs)
        finally:
            words(state).clear()

    def push(state, source):
        words(state).clear()
        return methods['push_subroutine_arg'](state, source)

    t.translate_all_blocks = all_blocks
    t.translate_block = block
    t.evaluate_instruction = instruction
    t.NodeState.store_memory = store
    t.NodeState.make_function_call = call
    t.NodeState.push_subroutine_arg = push

    def undo():
        for name, original in originals.items():
            setattr(t, name, original)
        for name, original in methods.items():
            setattr(t.NodeState, name, original)
    return undo, records


def main():
    report = None
    if '--stack-join-report' in sys.argv:
        index = sys.argv.index('--stack-join-report')
        report = Path(sys.argv[index + 1])
        del sys.argv[index:index + 2]
    undo_stride = None
    undo_arrays = None
    array_records = []
    array_report = None
    if '--stack-array-report' in sys.argv:
        index = sys.argv.index('--stack-array-report')
        array_report = Path(sys.argv[index + 1])
        del sys.argv[index:index + 2]
    if '--declare-stack-arrays' in sys.argv:
        sys.argv.remove('--declare-stack-arrays')
        from m2c_stack_arrays_driver import install_known_stack_arrays
        undo_arrays, array_records = install_known_stack_arrays()
    if '--fix-pointer-strides' in sys.argv:
        sys.argv.remove('--fix-pointer-strides')
        sys.path.insert(0, str(ROOT / 'tools'))
        from m2c_stride_driver import install_pointer_stride_rendering
        undo_stride = install_pointer_stride_rendering()
    undo, records = install_constant_stack_joins()
    try:
        from m2c.main import main as upstream_main
        upstream_main()
    finally:
        undo()
        if undo_stride:
            undo_stride()
        if undo_arrays:
            undo_arrays()
        if report:
            report.write_text(json.dumps(records, indent=2) + '\n', encoding='utf-8')
        if array_report:
            array_report.write_text(json.dumps(array_records, indent=2) + '\n', encoding='utf-8')


if __name__ == '__main__':
    main()
