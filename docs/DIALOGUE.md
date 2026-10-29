# Native dialogue and font data

The dialogue dispatcher at `0803FD28` reads a linear byte stream through the
16-bit position at work+0x0C. `tools/dialogue.py` decodes storage boundaries;
wrapping, input waits and portrait transitions can revisit a command at runtime.
The decoder holds glyph indices above 134 instead of assuming another format.

| Byte | Stored operands | Consumer |
| --- | --- | --- |
| 00..86 | none; glyph index | `08040038` |
| F7 | delay byte | `080407A4` |
| F8 | none; toggle font | `0803FD28` |
| F9 | replacement-buffer selector | `080402B4` |
| FA | delay byte | `0804070C` |
| FB | portrait side, character, frame | `0803FEB8` |
| FC | none; page/input wait | `080405D0` |
| FD | none; newline/wrap | `0804056C` |
| FE | none; advance position | `0803FEA8` |
| FF | terminal callback mode | `08040820`, `080408D0` |

FF within a portrait, timer or replacement operand is data. It does not end
the message. The native command macros are in `include/dialogue_commands.h`.

`src/dialogue_data.c` reconstructs 4,330 distinct decoded message starts,
416,029 payload bytes and 19,180 directory bytes. Six storage objects preserve
contiguous messages and shared suffixes. Every referenced suffix begins at an
instruction boundary; no instruction boundary overlaps an operand. The eighteen
leaf directories contain 4,763 non-null references, including eight entries
248..255 of `084144B4` that point back to that directory itself. These remain
self-pointers, without being interpreted as valid messages. The sixteen child
directories selected through `0847DF24` retain their native null sentinels.
The first 256-entry directory and 33-entry quantity directory have fixed bounds.

The four font objects in `src/text_glyphs.c` add 18,304 bytes. Both native
glyph banks contain 135 8x16 images, each sixteen little-endian 4-bpp row words.
Each metric bank has 256 width/auxiliary-byte pairs; `08040038` and `080402B4`
read the width at twice the character index. The second byte remains named
auxiliary because these consumers do not establish its meaning. The next text
object at `083B5208` is independently referenced at `083B5578`; the two glyph
bank ends, `084C1E24` and `084C7B64`, are independently referenced asset starts.

All 29 data sections match both scratch and actual production source. The 28
existing functions in `src/effect_work.c` still match after replacing incomplete
font declarations with the shared header. Reproduction artifacts are under
`build/more/`: `dialogue_survey.json`, `dialogue_data_audit.json`,
`text_glyphs_audit.json`, the `*_production_spec.json` files and
`effect_work_proof.log`. The source generators are `reconstruct_dialogue.py`
and `reconstruct_fonts.py` in that directory.

`tools/check_dialogue.py --inventory build/more/dialogue_survey.json --limit 64`
checks sixteen synthetic controls and 64 native messages against the original
Thumb dispatcher and handlers, including long messages and entries distributed
across the banks. BIOS copies, text-map drawing and sound are stubbed. Portrait
mode 2 skips transitions, delay FF avoids timer waits, A accepts pages and
inserted names contain one A. The check confirms instruction and terminal
positions under those states; it does not verify rendered pixels, devices or
every interactive playback path. Seven independent parser regressions cover
operand bytes, bounds, truncation, glyph limits, terminal storage and roundtrip.

## State-zero and menu directories

`src/dialogue_extra_data.c` adds 661 message starts in sixteen storage objects
(24,912 bytes), with sixteen native pointer directories (2,676 bytes). These
roots are passed to `0803FB3C` or `08047C24` by existing state-zero and menu
callbacks. All decoded starts and shared suffixes are instruction boundaries.
The 28-entry directory at `08485678` ends at the independently named
`gMainState3Callbacks` table (`084856E8`); the nineteen-entry `08486D78`
directory ends at the independently named asset root `08486DC4`. Their adjacent
function and asset pointers are not interpreted as dialogue.

`include/dialogue_messages.h` records the native directory bounds. The old
scalar declaration of `083CF530` is now a pointer array; its two mutable-pointer
declarations are made read-only. `08485F88` is likewise an array, with its old
scalar use expressed as element zero. All 31 functions in the four affected
source files still match in isolation. Native absolute aliases with other names
remain at their original addresses.

All 32 added data sections match scratch and production source. Independent
roundtrip/boundary checks cover all 661 starts, and the original Thumb check
passes sixteen synthetic plus 32 sampled native messages with the same explicit
stub/state limits described above. Evidence in `build/more/` uses the
`extra_messages`, `dialogue_extra`, and `extra_caller_*` prefixes. The extra
generator is `reconstruct_extra_messages.py`.

The original F9 replacement handler also fetches glyph FE (254) when its RAM
replacement string is empty. Font source addresses now go through integer bus
arithmetic before adding the 64-byte glyph offset, preserving that native read
outside the stored bank. No clamp or substituted glyph is introduced. All 28
effect/text functions remain exact. Twelve isolated original Thumb cases cover
both fonts and selectors 0..4/default, confirming the glyph source and terminal
position with BIOS copies/drawing/sound stubbed; the check does not inspect
copied pixels. Reproduction: `build/more/check_empty_font.py`,
`empty_font_cpu.json`, `effect_font_bus_production_spec.json`.

## Late-scene dialogue directory

`src/late_scene_dialogue_data.c` reconstructs `08486004..084869BC`: twelve
programs occupying 2,440 bytes, followed by twelve pointers. Original root
boundaries and terminal command operands are preserved; standard GCC data
settings match all 2,488 bytes through
`build/more/late_scene_dialogue_production_spec.json`.

`0806E3C4` selects a root using the halfword at work+0xC and calls `0803FB3C`.
A nonzero result sets work+4 to 5 and global phase `0300137C` to 2.
`tools/check_late_scene_selector.py` passes all twelve indices with completion
results 0, 1 and 255, intercepting only that dialogue call and verifying its
pointer. Guarded work memory, phase, preserved registers and SP are checked.

`python tools/check_dialogue.py --inventory build/more/late_scene_dialogue_inventory.json --limit 100 --output build/more/late_scene_dialogue_cpu.json`
passes all twelve native programs and sixteen synthetic command cases through
the original interpreter. This validates command boundaries and termination;
the check retains its documented graphics, BIOS and sound stubs, so it does not
validate rendering or hardware timing. Draft generation is reproducible with
`build/more/reconstruct_late_scene_dialogue.py`.

## Scene location descriptions

`src/scene_location_dialogue.c` reconstructs ten consecutive messages at
`08484D60..08484F95`, three zero alignment bytes and their ten-entry pointer
directory at `08484F98..08484FC0` (608 bytes in total). `08060A1C` selects
a directory entry using context byte `0x17` and passes it to `0803FB3C`.

`tools/check_scene_locations.py` runs 20 original selector fixtures covering
all entries and both dialogue results, with dialogue and update helpers stubbed;
it checks guarded RAM, calls, and preserved registers. It separately checks all
ten messages through the original interpreter and handlers, with BIOS copy,
drawing and sound stubbed. Interactive playback and rendering are not modeled.

## State-three callback directories

`src/state3_callback_tables.c` reconstructs four adjacent pointer tables at
`084856E8..08485764`, with 8, 5, 5 and 13 entries. Their consumers are
`08068440`, `08068888`, `080688E0` and `08068DD0`; the next bytes belong
to other data. `tools/check_state3_callbacks.py` checks all 31 dispatch
entries in 62 native fixtures with callbacks stubbed, including return and
counter behavior, the display-control bit, and preserved ABI. It does not
execute the callback bodies or establish normal-gameplay reachability.

## Main-two local message

`src/main2_local_data.c` reconstructs the 83-byte message at
`080AF8CD..080AF920` and six callback pointers at `080AF920..080AF938`.
Existing absolute aliases retain their addresses. `tools/check_main2_local_data.py`
checks the original stack copy, both dialogue results, all six callback
dispatches and an interpreter boundary pass; dialogue, drawing and callbacks
are stubbed where documented by the checker. Rendering is not checked.

The cancellation message at `080AFCA8..080AFCB7` is also in
`src/main2_local_data.c`. `tools/check_menu_cancel_dialogue.py` checks the
original cursor-six selection and an interpreter boundary pass; display and
dialogue helpers are stubbed.
