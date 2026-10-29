# Late state callbacks and motion tables

`src/late_state_callback_data.c` reconstructs ten directories containing 604
function pointers (2,416 bytes). Their native roots are 083AECD8, 083AEEA0,
083AEF90, 083AF090, 083AF180, 083AF6B0, 083AF810, 083AF860, 083AF8A0 and
083AF8C0. Every target is an already matched Thumb function; relocations
preserve its Thumb bit. Existing address aliases remain valid.

`src/action_motion_data.c` reconstructs twenty arrays (952 bytes) interleaved
with these directories: selection weights, acceleration steps, four directional
paths and coordinate/motion offsets. Element widths follow the matched
consumers' declarations and loads. Signedness varies between existing views;
the source preserves the stored bit patterns without rewriting those views.
Names retain ROM addresses where the full semantics remain unknown.

Both sources use normal GCC data flags with no overrides. All thirty sections
match through their `build/more/*_production_spec.json` specifications. No game
function is newly counted. Eight bytes at 083AFA00..083AFA08 remain raw in the
former 3,380-byte region.

`src/late_selection_pointer.c` reconstructs the single pointer at
`083AFA08..083AFA0C`; its target remains raw. The `08039AC8` consumer uses
integer addressing for the signed pointer index and retains all 308 original
bytes. `tools/check_late_selection_pointer.py` runs 258 native fixtures on
indices -82..-3 and 0..48, reading neighboring callback and asset pointers.
The fixtures use the fixed-column path, stub three helpers, and check guarded
RAM and the ABI; indices -2 and -1 produce non-ROM pointers and are excluded.

`python tools/check_late_state_callbacks.py` checks every stored slot through
the original dispatcher: 604 cases and 3,148 callback invocations. The selected
callback bodies are intercepted; 08034E94/0803D424 return the fixture index;
0803EED8/0803E780/080195C0/08032F64 are no-ops returning zero. Render mode is
zero. Indexing, object loops, return values, stack and callee registers are
checked; callback effects and alternate rendering paths are outside the test.

`python tools/check_action_motion.py` executes 1,024 acceleration cases through
0803526C, spanning all 256 lookup entries, fractional-byte overflow, coordinate
wrap, landing and accumulator saturation. Another 136 cases execute 080366DC
across all four paths, including disabled objects and terminal phase 16. There
are no helper hooks in this check; full frame writes and callee preservation
are compared. Reports are `build/more/late_state_callback_cpu.json` and
`build/more/action_motion_cpu.json`.
