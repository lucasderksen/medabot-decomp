# Frame-object helpers

Eleven routines in ROM `0x08040B90..0x080415BC` are reconstructed as ordinary
C in `src/frame_objects.c`. Default pinned normal agbcc settings reproduce
all **2,080 bytes**, including literal pools, the command jump table, and
zero-fill alignment. Names are address-based; original symbols are unknown.

| Routine | ROM interval | Bytes | Observed operation |
| --- | --- | ---: | --- |
| `sub_08040B90` | `40B90..40BD8` | 72 | Initialize command state and preview a frame |
| `sub_08040BD8` | `40BD8..40CD0` | 248 | Process three-byte frame commands |
| `sub_08040CD0` | `40CD0..40D0C` | 60 | Clear successive 64-byte records |
| `sub_08040D0C` | `40D0C..40D44` | 56 | Clear flags bit `8000` in a range |
| `sub_08040D44` | `40D44..40D78` | 52 | Set flags bit `8000` in a range |
| `sub_08040D78` | `40D78..40DB8` | 64 | Find a record with zero flags |
| `sub_08040DB8` | `40DB8..40EE4` | 300 | Align and place an encoded byte string |
| `sub_08040EE4` | `40EE4..41020` | 316 | Place a byte string with coordinate offsets |
| `sub_08041020` | `41020..41164` | 324 | Place bytes using the observed 85FF frame offset |
| `sub_08041370` | `41370..41490` | 288 | Format decimal digits or a fixed marker |
| `sub_08041490` | `41490..415BC` | 300 | Format digits with a caller-provided base |

The helpers use the same 128 records at `0x03002C30` as the renderer.
`include/frame.h` now exposes bytes `20`, `21`, and `22` as `commandDelay`,
`commandOffset`, and `commandStopped`. These descriptive names reflect
observed accesses and preserve the established 64-byte stride. The first
two bytes at `1E` and the eight bytes at `23` remain unknown.

The initializer clears all three command-state bytes. It scans three-byte
commands with an eight-bit temporary offset until the first byte is at most
`FA`, then previews that command's next two bytes as `frameAndGroup` in
high-byte/low-byte order. It does not execute skipped control commands,
copy the temporary offset to the record, or start the delay. Thus subsequent
processing still begins at command offset zero. No terminator check is added
to this initializer; the observed caller data supplies an ordinary command.

The command processor returns immediately when `commandStopped == FF`.
Otherwise a nonzero delay is decremented and execution returns. With a zero
delay it reads a command at `commands[commandOffset]` and dispatches:

| First byte | Behavior |
| --- | --- |
| `00..FA` | Store that byte as delay, set `frameAndGroup` from the next two bytes in high-byte/low-byte order, advance the offset by three, then repeat |
| `FB` | Clear flags bit `4000` in **record zero**, load the following byte as delay, advance the selected record's offset by three, and return |
| `FC` | Set flags bit `4000` in **record zero**, advance the selected record's offset by three, then repeat |
| `FD` | Call `sub_08074DE0` with the following byte, advance by three, then repeat |
| `FE` | Set the byte offset to three times the following byte, then repeat |
| `FF` | Set the selected record's stopped byte to `FF` and return |

The record-zero flag updates are present in the original instructions even
when the selected index differs from zero. They are preserved without
assuming an intended correction. The third byte of control commands is not
read here. Offset updates truncate to eight bits. Ordinary commands repeat
within the same call: after a nonzero delay is stored, the next iteration
decrements it and returns. A zero-delay command advances immediately to the
next command. The exact target retains a constant repeat variable and loop
test; ordinary C reproduces that compiler behavior.

The range helpers take eight-bit start/count arguments. The clear routine
uses `CpuFastSet` in fill mode for 16 words per record. Setting/clearing
`8000` preserves all other flags. These three routines do not clamp the
range; established callers include `(0,128)`, `(10,7)`, and `(40,87)`.

The search helper examines `start+i` for an eight-bit loop counter `i`.
It stops when that sum equals 128, returns the first index whose complete
flags halfword is zero, and otherwise returns the original start index.
The fallback is indistinguishable from successfully finding the start
record. It tests equality with 128, not a general bounds comparison.
A common-exit label preserves the original branch layout; a plain `break`
caused legacy loop rotation and emitted four extra bytes.

The two matching formatters extract six decimal positions into a byte array.
They test the **low byte** of `value/100000`. When it is nonzero, they emit
the fixed byte sequence `05 12 12 0F 12 FE`. Otherwise they suppress leading
zero positions, always emit the last position, and terminate with `FE`.
`sub_08041370` adds `35` to each emitted digit. `sub_08041490` adds its
32-bit `base` argument instead, with each result stored as a byte. These are
encoded byte strings; no ASCII interpretation is imposed.

The leading-quotient test is not a general numeric bounds check: sufficiently
large inputs can have a leading quotient whose low byte wraps to zero.
The second remainder update subtracts `(value/10000)*10000` using the
original input rather than the current remainder. This exactly reflects the
original call operands and preserves their unsigned arithmetic. For ordinary
inputs below 100000 that distinction has no effect. A volatile local remainder
models the observed repeated word loads/stores and division calls; it is a
matching source reconstruction, not evidence of the original declaration.

The two five-position formatters in `41164..41370` remain isolated candidates. They insert byte `40` and still require an exact compiler match. The three byte-layout helpers in `40DB8..41164` are integrated as described below.

The initial matching record is
`build/experiments/compiler_input/frame_objects_goto/results.json`.
The final named-field source was independently checked with
`tools/match.py`; its spec uses the five intervals above and sections
`.text.sub_08040BD8`, `.text.sub_08040CD0`, `.text.sub_08040D0C`,
`.text.sub_08040D44`, and `.text.sub_08040D78`. No extra compiler flags,
inline assembly, register declarations, or emitted-byte patches are used.

A final integrated glyph helper at `0x08040EE4..0x08041020` now matches all316 bytes using default normal agbcc. It sums first metric bytes at `083B4E08`, applies the observed center/edge alignment against `boxWidth*8`, then populates successive frame records for nonzero character bytes while every byte advances the horizontal position by its metric. Coordinates first become `x*8+xOffset` and `y*8+yOffset`. Nonzero entries receive flags `(flags<<10)|(s16)0xC004`, screen coordinates, palette, zero selector, the observed priority expression, and character-minus-one frame/group. FE terminates the string. The two pointer IVs derive from one zero-based word-sized loop index, which makes the legacy compiler reproduce its preheader order. Interface: `void sub_08040EE4(const u8*,u8,s32,s32,u8,u8,u8,u16,s32,s32)`. Delivery `build/experiments/compiler_input/frame_glyph_offset_ready.c/.h/.json` is integrated with complete-ROM confirmation; the adjacent two glyph builders are now also strictly matched and delivered below.

The adjacent basic builder `40DB8..40EE4` (300 bytes) and group builder `41020..41164` (324 bytes) also match with the same shared-index reconstruction and default normal agbcc. Both multiply x/y by 8 without offsets. The group builder takes the first eight arguments of the offset-builder interface; the basic builder retains the word-sized slots described below. The basic builder stores character-minus-one. The group builder stores character plus the observed ROM literal `0x85FF`; the older provisional `0x1FFF` reconstruction was incorrect and is superseded. The group builder naturally emits the reference stack halfword-zero initialization and later byte reload for selector0, despite using an ordinary unqualified assignment; earlier volatile-view diagnostics are unnecessary and provide no qualifier evidence. Delivery `build/experiments/compiler_input/frame_glyph_remaining_ready.c/.h/.json` contains these two exact functions. Both are integrated with complete-ROM confirmation, using the corrected basic-builder word interface below. The three glyph deliveries total 940 bytes.

Integration identified a caller ABI detail for the basic builder: narrow formal arguments changed the register lifetime at `0800B938`, despite producing exact helper bytes. Its canonical interface therefore retains word-sized start/width/palette/alignment/flags slots: `void sub_08040DB8(const u8*,u32,s32,s32,u32,u32,u32,u32)`. Immediate `u8` locals for the first four and a `u16` flags local reproduce every basic-builder byte while preserving the broad caller interface. Casting the word parameters back into themselves gives292bytes and fails. The corrected exact delivery `frame_glyph_basic_word_ready.c/.h/.json` is integrated and the complete ROM matches; it supersedes the narrow basic-builder declaration in the earlier staged header.


## Native frame-command payload bank

The118-entry root at083B6100 points to118 distinct streams in
083B55D4..083B6100 (2860 bytes). Native macros in frame_command_data.h retain
all step, sound and jump choices. A terminal FE reads two bytes, despite the
three-byte sequential stride. FF reads only its opcode; unused following
bytes, including a nonzero byte, remain explicit. The pointer root remains
copied data; this batch credits only the2860 payload bytes.

The bounded tools/frame_commands.py model follows the byte cursor, preview
scan, delays, record-zero flags, stop and sound-request behavior. It rejects
truncated reads, out-of-span targets and cycles that cannot yield. Seven
synthetic tests cover these cases. tools/check_frame_commands.py compared all
118 original streams against08040B90/08040BD8 for256 calls each, plus a
synthetic flag/sound/jump case. Frame-object neighbors stayed unchanged.
Sound dispatch08074DE0 is stubbed to record IDs; audio is not simulated.
Reproduce with python tools/check_frame_commands.py; local report
build/resume/frame_command_cpu.json records hashes and per-stream results.
The CPU helper can omit a timed watchdog while retaining a positive instruction
cap; two independent tests verify successful return and bounded infinite-loop
termination. The checker uses a20000-instruction cap per call.
