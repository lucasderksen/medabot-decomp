# Action and scene data

`src/action_scene_data.c` reconstructs the complete **35,076-byte** interval
`083C6A04..083CF308` in thirty objects. Compiler: ordinary GCC with the project's
default data profile. The native command widths and shared graphic-piece layout
are in `action_scene_commands.h` and `action_scene_data.h`.

| ROM range | Stored format |
| --- | --- |
| `083C6A04..083C6CA8` | 676 byte-script bytes, 588 physical command records |
| `083C6CA8..083C6EB8` | 132 byte-script pointers, 93 distinct roots |
| `083C6EB8..083C6F48` | Byte parameter lengths, including the stored zero tail |
| `083C6F48..083C6F68` | Four FE-terminated labels, 29 bytes plus three zero alignment bytes |
| `083C6F68..083C6F78` | Four label pointers |
| `083C6F78..083CAD78` | 31 motion groups: 32 directions, four signed (Y, X) pairs per direction |
| `083CAD78..083CADF4` | 124 pose-variant selectors used by `08044A3C` |
| `083CADF4..083CE164` | 13,168 halfword-script bytes, 1,958 physical command records |
| `083CE164..083CE374` | 132 halfword-script pointers, 112 distinct roots |
| `083CE374..083CE410` | Halfword parameter lengths, including the stored zero tail |
| `083CE410..083CE600` | 67 graphic pieces and 114 two-byte zero terminals |
| `083CE600..083CE810` | 132 graphic-list pointers, 113 distinct roots |
| `083CE810..083CEDF4` | 37 variable-length tile-animation scripts, 1,508 bytes |
| `083CEDF4..083CEE88` | 37 tile-animation pointers |
| `083CEE88..083CF308` | Three 128-byte and twelve 64-byte selection lookup tables |

All byte/halfword directory roots fall on command boundaries in the decoded
physical banks. Byte opcode 02 has one parameter and 03 has four; the halfword
commands have zero through eight parameters. Labels above 7F occupy command
positions and are skipped by the byte dispatcher `08033840`. Opcode 01 sends
that dispatcher to its completion state through `080338DC`. Reader checks
walk stored positions through the first 01; they do not claim to execute each
action handler or prove complete game control flow. The parameter-table sizes
are physical spans up to the following object, not recovered original C bounds.

The motion reader `0804422C` selects
`(group - 1) * 256 + direction * 8 + (frame & 3) * 2`, reads Y then X, masks
positions to eight/nine bits, and increments the byte frame counter. The native
table remains an exact integer table; no host trigonometry is substituted.
`08044A3C` separately uses the following byte selector in its seven-variant pose
lookup. Those selectors are not motion deltas or duration thresholds.

Graphic lists use `(u16 units, u16 asset)` records, where units count 32-byte
tiles; a terminal contains only the zero units halfword. The flat word bank
preserves the short terminals and the native palette helper's unconditional
following asset read. The shared `ActionGraphicPiece` type replaces two private
copies of this observed layout. All 67 active pieces select already reconstructed
composite assets, so this batch adds no compressed-payload credit.

Tile animations begin with base/width halfwords, followed by duration/frame
pairs. FD plays a sound, FE branches to twice its halfword operand, and FF stops
with a single halfword. Eight-bit cursor/timer narrowing and immediate processing
of subsequent commands are preserved. The two original readers target different
VRAM layouts. Source macros preserve their short terminals and loop endings.

`tools/check_action_scene.py` compares the original Thumb against independent
ROM-backed models: 2,517 byte positions, 2,912 halfword positions, 7,954 motion
cases, 132 graphic loaders, 218 palette requests, 37,888 animation ticks and
7,680 selection cases. Complete affected work buffers, saved registers and SP
are checked. Decode, BIOS copy and sound calls are recorded and stubbed; the
selection-update helper is stubbed to control the indexed byte. Motion and
script readers execute without stubs. Rendering/audio and RNG quality are
outside the check.

All thirty source sections and all 81 functions in the twelve isolated caller
specifications match with their existing compiler flags. No game-C/function
credit is added. Reproduction: `build/more/action_scene*_spec.json`,
`action_*_spec.json`, `action_scene_audit.json`, `action_scene_cpu.json`;
full gate `checkpoint_action_scene.log`.

## Pose-group selection words

`src/pose_group_data.c` reconstructs the 20-byte `MultiSioSync010316`
identification and padding at `0807E8D8`, followed by 47 rows of seven
32-bit pose-group values at `0807E8EC..0807EE10`. The following address
is the independently reconstructed template bank. `08044A3C` indexes these
words with `group * 7` plus a byte from the existing pose-variant selectors.

`tools/check_pose_group.py` executes the original selector and duration count
loop for all 329 physical entries. It stubs the interpolation helper and
checks its arguments, the guarded work buffer, return, and preserved registers.
It does not establish that every group is reachable in normal gameplay.
