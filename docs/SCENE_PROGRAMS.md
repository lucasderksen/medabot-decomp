# Scene programs, geometry and setup data

This batch reconstructs 16,204 bytes with the normal modern-GCC data profile:
14,860 bytes in `src/scene_program_data.c` and 1,344 bytes in
`src/scene_setup_data.c`. It adds no game-C functions. The existing consumers
retain their compiler flags and exact code bytes.

## Geometry and source directories

`080ABD7C..080AC604` contains 42 fixed 52-byte `SceneSource` records. Each has
a word-sized object count and three rows of four signed coordinates. Forty
records appear in the 48-pointer source bank at `083D2E70`; the other two
stored records retain the same physical layout. Thirty-two pointers at
`083D2F30` select variable-length views of that source bank. They are not
32 padded sixteen-entry arrays.

`08054014` reads all four entries on every axis, regardless of object count,
then scales and translates them. Scene command 1B reads the same count when
creating frame objects. The shared `SceneSource` layout is in
`include/scene_view.h`; its count remains `long`, matching the interpreter's
prior count view. A same-width `int` field retained size/layout but changed
the interpreter's register allocation. The shared long view matches both
consumers, including all 9,896 bytes of `0805424C`.

## Wordcode

`083D2FB0..083D5F70` contains 3,056 signed words forming 623 stored commands.
`include/scene_program_commands.h` expresses the command boundaries and keeps
every operand. Thirty-three root pointers at `083D5F70` select 25 distinct
starts, including the shared END-only program. CALL and scheduled-call operands
refer to 38 distinct stored command starts. Their source initializers produce
actual symbol relocations using target GCC's pointer-to-word initializer
extension; they are not unexplained integer addresses.

The native interpreter indexes words rather than bytes. SETUP (01) consumes
five words and yields; TICK (02) can wait without advancing. END (04) resets
the cursor and performs scene cleanup. CALL (22) saves the current program,
next cursor and actor before selecting its target. RETURN (23) restores them.
SCHEDULE (24) consumes five words, or seven when mode bits 8..15 equal 01.
The stored relative form uses the parent's Z-motion limit and a zero slot.
MOTION_X/Y/Z retain all sixteen setup payload words, including the final word
copied by `080497C0` even though the setup consumer does not use every field.

Many actor commands advance over their second word without reading it.
The selected actor is interpreter state established by CALL or a scheduled
call. Source macros retain these skipped operands. The six-bit scene selector
does not establish a 64-entry physical source/root directory; no bounds clamp
was added to the consumers.

## Adjacent setup tables

The complete `083D2A30..083D2E70` prefix is reconstructed. It includes object
factors, four direction-remap rows, sixteen eight-byte setup rows, graphics
selectors, twelve four-byte transition records, 192 map-selector categories,
destination records, and three 176-byte per-object priority/flag/class tables.
Three zero bytes align the source bank. `SceneTransitionChoice` names the four
byte fields read by `0804842C`; its body remains assembly.

The directory at `083D5FF4..083D60F4` stores 17 initialized callbacks and 47
NULL slots. The NULL slots are preserved storage, not callable menu states.
`src/unreferenced_scene_text.c` reconstructs three encoded labels following the
directory, ending at their FF markers (33 bytes). Their consumer and the three
following zero bytes are not established; the zero bytes remain raw. The
sections match under standard GCC data flags, with no runtime behavior claimed.

## Validation

All 25 data sections and all five functions in the two consolidated consumer
sources match in isolated production compilation. `tools/scene_programs.py`
rejects truncated commands and roots/call targets inside operands; six unit
tests cover those checks, negative operands and variable-width scheduling.

`tools/check_scene_programs.py` executes original Thumb code for:

- 1,869 individual command cases: every stored command with actors 0, 1 and 7.
- 432 scalar/pointer state checks, plus all motion payload copies and call
  cursor/stack/target transitions.
- 144 geometry cases: every stored source-pointer slot with three sets of
  scales, comparing the complete scene-view buffer.
- 256 setup-row/frame-selector combinations, 16 graphics lookups, 384 map
  selector cases and all 17 initialized callback slots.

Command cases route a second dispatch to the native epilogue so only one
command runs. Engine/render helpers are explicit no-op hooks. Real soft-float
conversions and the 49714/497C0 memory helpers execute. Geometry cases stub
projection/drawing helpers while retaining native coordinate arithmetic.
Setup cases use the real row-copy helper; callback bodies are intercepted.
Preserved registers and stack are checked on returned command/geometry/row
cases. This does not claim complete scene flow, hardware timing or rendering.

```text
python tools/check_scene_programs.py --output build/more/scene_programs_cpu.json
python tools/match.py build/more/scene_programs_production_spec.json --output-dir build/more/scene_programs_data_final
python tools/match.py build/more/scene_setup_production_spec.json --output-dir build/more/scene_setup_production_check
```
