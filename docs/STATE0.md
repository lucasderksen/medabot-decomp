# Secondary callbacks under main state zero

These routines are reconstructed from the supported Metabee Europe revision 0
dump. They compile as ordinary C with the default pinned agbcc settings.
Their address-based names remain provisional. Screen identity and the meaning
of the larger shared RAM object have not yet been established.

`sub_08002534` dispatches the main-state-zero table at `083AC2C8` using the
word `gMainSubstate` at `03002B8C`. Two additional dispatchers, `08002554` and
`080027BC`, use the separate word at `0300137C` to index tables at `083AC3C8`
and `083AC404`. A fourth dispatcher at `08003374` uses the same word with the
table at `083AC454`. Five adjacent tables now match typed C data in
`src/state0_callback_tables.c`:

| Start | End, exclusive | Pointer count | Boundary evidence |
| --- | --- | ---: | --- |
| `083AC2C8` | `083AC3C8` | 64 | Next table referenced by dispatcher `08002554` |
| `083AC3C8` | `083AC404` | 15 | Next table referenced by dispatcher `080027BC` |
| `083AC404` | `083AC454` | 20 | Next table referenced by dispatcher `08003374` |
| `083AC454` | `083AC4A0` | 19 | Next table referenced by dispatcher `080039E0` |
| `083AC4A0` | `083AC5A0` | 64 | Next position table referenced by helpers `08004EF8` and `080056A4` |

The counts describe reconstructed source intervals bounded by independently
referenced starts; they do not recover the original source declarations. The
state-zero table has eleven initial non-dummy callbacks, dummy slots 11..62,
and `0800B890` in slot 63. Nested tables also contain deliberate dummy entries.
All pointers retain their Thumb-state bit through typed function symbols.

## Matching intervals

| Start | End, exclusive | Observed behavior |
| --- | --- | --- |
| `080025B4` | `080026A4` | Low-byte keypad handling, BG1 scroll, callback transitions |
| `080026A4` | `080026E0` | Calls `0803F51C`; byte return equal to 1 sets callback index 1 |
| `080026E0` | `08002730` | Writes ten byte codes into `03002B74..03002B7D`, then polls `0803FB3C` |
| `08002730` | `0800275C` | Polls a pointer-table entry, starts another operation, advances callback |
| `0800275C` | `0800277C` | Waits for `08041674`, calls `0803FB0C`, advances callback |
| `0800277C` | `080027BC` | Chooses one of two pointer entries from the high nibble at shared offset `28` |
| `080027DC` | `080028AC` | Sets display/BG0 control, expands six Le streams, transfers two palettes with DMA3 |
| `080028AC` | `08002A2C` | Loads rows in four staggered phases, then initializes a selection object |
| `08002A2C` | `08002AF8` | Four-position selection cursor; repeat Up/Down, new B/A |
| `08002AF8` | `08002C34` | Reverses the staggered row transition and finishes with `08044094` |
| `08002C34` | `08002D48` | Prepares the selected row and an odd transition count, then advances callback |
| `08002D48` | `08002DF4` | Shrinks the selected row, snapshots palettes and advances when byte counter reaches zero |
| `08002DF4` | `08002EC4` | Two palette-related calls and two changing row widths; advances at counter 19 |
| `08002EC4` | `08002F70` | Four-way switch chooses main/substate changes or `0804765C(1)` |
| `08002F70` | `08003018` | Restores display/palette work for three selections and resets transition bytes |
| `08003018` | `08003104` | Reverse width transition, installs dummy callback and prepares odd row count |
| `08003104` | `08003300` | Restores other rows, selection object and callback index 2 |
| `08003300` | `08003374` | Loads cursor tiles/palette and initializes frame object zero |

The adjacent block lives in `src/state0_submenu.c` and also matches through
`080039E0`. It uses the supported `-fprologue-bugfix` option: the branched leaf
at `080039BC` requires omission of the otherwise emitted LR save/restore, while
all other matching functions in that translation unit retain their bytes.
The reconstruction's file boundaries and compiler options do not establish the
original translation units.

| Start | End, exclusive | Observed behavior |
| --- | --- | --- |
| `08003374` | `08003394` | Dispatches the 19-pointer table |
| `08003394` | `080034A4` | Loads three tilemaps, a palette, and a row; resets transition counter |
| `080034A4` | `08003504` | Updates BG3 scrolling and a nine-step transition, then creates cursor |
| `08003504` | `08003620` | Three-position selection and independent new B/A branches |
| `08003620` | `08003654` | Starts the reverse transition and snapshots palettes |
| `08003654` | `080036A8` | Nine-step reverse transition |
| `080036A8` | `080036C8` | Returns to main substate 1, callback 16 |
| `080036C8` | `080036F4` | Polls two routines and advances on nonzero return |
| `080036F4` | `08003784` | Copies VRAM work to EWRAM, then chooses main substates 3/4/5 |
| `08003784` | `080038CC` | Restores tilemaps, palette and saved VRAM work, starts another operation |
| `080038CC` | `080038F0` | Waits for completion and recreates cursor |
| `080038F0` | `08003904` | Sets callback index 2 |
| `08003904` | `0800393C` | Chooses one of three Le streams by byte `8F` |
| `0800393C` | `080039BC` | Initializes cursor using three-position coordinates |
| `080039BC` | `080039E0` | On odd frame-counter values, decrements BG3 X and increments Y |

End addresses include literal pools and alignment. The complete image comparison
is required after integration; isolated candidate matches alone are insufficient.

The next two sources, `src/state0_entry.c` and `src/state0_link.c`, match the
complete interval `080039E0..08004AF8` with default agbcc settings. The dispatcher
at `080039E0` first calls the shared display/serial guard. In render mode 2 it
fills the first 1,024 bytes of the render work's OAM array with `0x200` before
dispatching the reconstructed pointer table at `083AC4A0`.

| Start | End, exclusive | Observed behavior |
| --- | --- | --- |
| `08003A38` | `08003D4C` | Three-stage graphics/palette/object setup using byte `139` |
| `08003D4C` | `08003DE0` | Nine-step display transition and byte `56` reset |
| `08003DE0` | `08003E54` | Per-frame work, then low-byte B/A/Start handling after two guards |
| `08003E54` | `08003EE0` | Starts and polls a display effect in two callbacks |
| `08003EE0` | `08003F28` | Clears render mode and selects main substate 2, callback 16 |
| `08003F28` | `08003FE8` | Palette snapshot and nine-step reverse transition |
| `08003FE8` | `0800406C` | Starts an operation and polls a pointer-table entry |
| `0800406C` | `080043A8` | Loads graphics/maps/palettes, clears frame objects and initializes fourteen helpers |
| `080043A8` | `0800442C` | Nine-step display transition and byte `56` set |
| `0800442C` | `080044F8` | Seven guards precede B, shoulder-button toggle and choice handling |
| `080044F8` | `080045C4` | Chooses snapshot or effect, then advances a nine-step transition |
| `080045C4` | `080045DC` | Two helper calls and callback index reset |
| `080045DC` | `08004644` | Starts and polls a display effect in two callbacks |
| `08004644` | `08004764` | Five-way selection initializes a 20-byte subobject and chooses substates 4/5 |
| `08004764` | `080047EC` | Resets a halfword timer, waits beyond 60, then chooses the next callback |
| `080047EC` | `08004840` | Display transition across counter values 0 through 32 |
| `08004840` | `08004874` | Clears render mode and selects substate 7, callback 0 |
| `08004874` | `080048D8` | Waits beyond 60, starts an effect, then polls it |
| `080048D8` | `080049C8` | Prepares three records and selects main state 3, substate 4, callback 5 |
| `080049C8` | `08004A18` | Starts an operation and polls table entry 11 |
| `08004A18` | `08004A40` | Three setup calls and callback increment |
| `08004A40` | `08004A78` | Waits for a guard, then clears outgoing serial halfword and timer |
| `08004A78` | `08004AF8` | Waits for timer 24, clears byte/halfword transfer work and advances |
| `08004C58` | `08004CA4` | Timer 16, resets four transfer counters and advances |
| `08004CA4` | `08004DB4` | Exchanges two checksum words and compares reversed pairs; failure selects callback 50 |
| `08004DB4` | `08004DF0` | Clears outgoing word, snapshots palettes and resets transition counter |
| `08004DF0` | `08004E40` | Blends BG/OBJ palette banks over counters 0 through 32 |
| `08004E40` | `08004E74` | Clears render mode and selects substate 7, callback 0 |
| `08004E74` | `08004E98` | Increments BG3 X/Y on odd frame counters |
| `08004E98` | `08004EF8` | Initializes four frame objects with staggered phase bytes |
| `08004FD0` | `08005000` | Invokes a record helper for each active one of nine eight-byte records |
| `0800522C` | `0800529C` | Loads selected/default graphics and configures a 2×2 tilemap rectangle |

The transfer loop at `08004AF8..08004C58` and two nine-record text helpers
at `08005000..08005118` remain copied intervals. Their experimental C is not
included in the matching source totals. The checksum callback reads the opposite serial participant's
second received halfword and strips its high ready flag before storing values.

`include/state0_work.h` supplies partial RAM views for the halfword timer at
shared offsets `5C` and `86`, transfer work at `03001800`, outgoing serial work
at `03005010`, and eight-byte records at `030017A0`. These alias existing RAM
symbols. The declared array bounds cover observed accesses; they are not claims
about original object sizes. Four-byte transfer records use a packed declaration
to retain the observed first-record offset `8F` with the historical compiler's
structure alignment rules. Callback and field names remain provisional.

## Record and inventory helpers

The matching helpers in `src/state0_helpers.c`, `src/state0_record_display.c`,
`src/state0_inventory_display.c` and `src/state0_inventory_control.c` use
`-fprologue-bugfix`. Two orbit functions rotate a four-object marker around a
selected record, derive scale/priority from its Y coordinate, and advance or
reverse a six-bit phase. The nine-record selection handles repeat direction
buttons independently; when several are set, the last direction condition
chooses the navigation row. Select starts or completes a record swap.

| Start | End, exclusive | Observed behavior |
| --- | --- | --- |
| `08004EF8` | `08004FD0` | Forward marker orbit and depth-dependent scale/priority |
| `08005118` | `0800522C` | Selected record name and type text |
| `0800529C` | `08005588` | Initialize, refresh and update selected-record preview |
| `08005588` | `080056A4` | Nine-record navigation and reverse-marker setup |
| `080056A4` | `08005798` | Reverse marker orbit |
| `08005798` | `08005948` | Marker blinking and Select-driven record swapping |
| `08005948` | `080059D0` | Two conditional object/preview helpers |
| `080059D0` | `08005AD0` | Prepare inventory index and four selected parts, update usage flags |
| `08005AD0` | `08006238` | Twelve helpers for name/type graphics, four part texts and property displays |
| `08006238` | `080063B4` | Five paired highlight tile patterns |
| `080063B4` | `0800656C` | Leg property, part setup, two cursor objects and blinking |
| `0800656C` | `08006824` | Initialize, refresh and update the current inventory preview |
| `08006824` | `08006980` | Five-row highlight blinking and repeat Up/Down selection |
| `08006980` | `08006C64` | Repeat Left/Right inventory or part selection and dependent display refresh |
| `08006C64` | `08006E08` | Start-driven part cycling with category and inventory predicates |
| `08006E08` | `08006F34` | Part decrement, preview validation and conditional object update |
| `08006FB0` | `0800712C` | Commit selected parts to a record and count owned, unused inventory |
| `0800725C` | `08007440` | Transfer-slot undo, acceptance, validation and confirmation |
| `0800750C` | `08007584` | Conditional text clear and three-record count update |
| `08007584` | `08007A04` | Guarded inventory dispatch, display setup, input and fade transitions |

`include/state0_inventory.h` records a partial 64-byte inventory stride at
`03000BE0`; a name view aliases its base plus ten bytes. Calls distinguish valid
indices `0..29` from sentinel `30`, and part indices `0..119` from missing parts.
The four part-property functions pass their part category to `08042B58`, copy
sixteen metadata bytes, compare two bytes, and choose a tile pattern. Those
observations do not establish all field names or the complete inventory layout.
The preparation callback preserves subtraction before storing the mapped index.

`080068EC` reads repeat direction flags first as bytes and later as a word.
The latter is retained through a small bitfield view over the key address;
only bits 6 and 7 affect the result. Four selection callbacks use explicit labels
for the shared unchanged/changed paths to reproduce original branch placement.
They contain ordinary C and no instruction patches.

Five byte tables at `083AC5A0..083AC603` now reproduce marker positions,
priorities, text positions and four nine-byte navigation rows. A four-pointer
array at `083AC604..083AC614` points into those rows. The one-byte gap stays
copied; explicit one-byte array alignment retains the observed layout.

The 480-entry table at `083BBB4C..083BC2CC` is reproduced as typed pointers
into the part-text region beginning at `083BA838`. Calls index it as
`part * 4 + category`, with part indices `0..119` and four categories. The
text encoding itself remains copied and has not been fully recovered.

Transfer acceptance examines three selected-slot bytes at `03001841`.
It rejects duplicate low-nibble record indices and requires the selected
eight-byte record's first byte to equal three. Filled slots retain the selected
index plus sixteen. Undo clears the last filled slot first. The exact duplicate
checker and object-blinking routines remain copied, as does the earlier
three-record transfer loop. `08006F34` also remains experimental: its no-input
path leaves the incoming return register unchanged, so no zero return has been
invented for that path.

The following inventory dispatcher calls the contiguous 112-entry table at
`083AC86C..083ACA2C`. All entries are odd Thumb pointers; the following word is
non-pointer data. Its input callback gives B precedence over A, and A validates
the owned bit of a selected 64-byte inventory record. Display setup preserves
the original ordered VRAM/palette writes and uses the existing Le decoder.

The two orbit callers now use the coordinate helper's four-byte aggregate
return through a union view. This preserves the original APCS hidden return
buffer and remains byte-identical. Three explicit arguments are retained at
calls to `080432A0`, including an unused final zero; two read arguments do not
establish the original declared arity.

## Memory widths and transitions

The shared object starts at `03000440`. The reconstruction uses a byte array
because a complete structure and the boundaries of subobjects are still unknown.
The callbacks access bytes `0E`, `28`, `84`, `85`, `88`, and `8E`, and pass the
address of offset `9E` to other routines. These offsets do not establish the
original C types or gameplay names.

`080025B4` reads only the low byte of the held/new-key halfwords. In order:

1. Held Up/Down increment/decrement BG1 Y; Left/Right increment/decrement X.
2. New B toggles shared byte `88`.
3. New A clears byte `0E`, increments the callback index, and toggles byte `85`.
4. New B independently sets `gMainSubstate = 1` and clears the callback index.
5. New Start calls `0803FAA0(0, 0, 0)` and adds 2 to the index.
6. New Select makes the same call and adds 3.

Those are independent conditions, so simultaneous buttons preserve all operations
in that order. Moving them into an exclusive chain would change behavior.

`08002A2C` first calls `08040BD8` with entry zero of the table at `083B6100`.
Repeat Up/Down independently update byte `8E` modulo four and write
`(selection << 4) + 8` to `gFrameObjects[0].screenY`. Each branch calls
`08074DE0(2)`. New B resets byte `84` and selects callback 3 after four calls;
otherwise new A calls `08074DE0(4)` and selects callback 6. Here B takes
precedence over A. These call patterns suggest a menu, but the exact screen and
audio call names remain unverified.

The inventory dispatcher block now has thirty matching callbacks through
`08008650`. Category changes wrap modulo four, and the later detail input gives
A precedence over B, L, R and Start. Its page-zero script selects a pointer
from `083B83DC` using inventory byte `24 + selectedRecord*64 + work[46]`;
the other page uses entry fifteen of `083B5578`. Later confirmation and value-edit
callbacks now extend through `080093F8`, apart from the script-selection interval
`08008CA0..080090D0`, which remains copied. Page, category and display names remain
provisional until the screens are traced in context.

All twenty-six shared inventory-view functions at `080093F8..0800A000` now
match C. They divide thirty records into five pages of six rows. Up and Down are
independent checks before their combined refresh test; Left and Right follow the
same pattern for pages. Simultaneous opposing inputs therefore preserve both
updates. Record ownership uses bit 80, while bit 40 gates a nine-record part
lookup. Select marks a record with bit 80 of work byte 3E, then swaps two complete
64-byte records on the next selection. The mark blinks only on the corresponding
page and odd frames. These are observed operations, not fully established screen
or gameplay labels.

Eight following detail helpers now match at `0800A000..0800A854`, apart from
the copied selection scan `0800A1E4..0800A2B4`. They use record bytes 4, 6 and 7
for text and tile lookups, and enable the pair of cursor objects only when work
byte 41 exceeds one. The three-row panel has thresholds 9, 29 and 59; the first
row refreshes all three part identifiers, while the later rows consume the
identifiers already in work bytes EE..F0. Each valid row copies six metadata
bytes into work 10E..113 before displaying text and a tile. The selected-row
panel repeats the three-identifier copy for its own threshold and displays
metadata bytes 10F and 110 as text and a two-column number. Other selector
values follow the third-row case exactly.

Thirteen helpers at `0800A854..0800AFF8` now match, with five intervening
selection and tile-loop gaps retained from the dump. Their row navigation wraps
among three entries and preserves separate Up and Down checks. The preview
helpers pass the selected record's four part identifiers to the shared layout
code; invalid selections clear the render-work count. Three following animation
and refresh functions also match: five 32-byte chunks come from the selected
animation page, the page counter advances after 180 ticks on odd ticks, and eight
pages reset the timer. Numeric and bar drawing candidates remain isolated.

Seven confirmation and guarded-value helpers at `0800B4EC..0800B814` match,
with the preceding transfer copy still isolated. Holding Start while repeating L
increments the owned record's byte 5 unless it equals 100, then refreshes its
metadata and display; repeating R under the same guard subtracts 100 from the
word at record offset 2 when that word exceeds 99. Both paths preserve their
original byte/halfword reads. The confirmation object starts with scale 64 on
both axes, blinks for 30 calls, then shrinks by 8 per call before its tile region
is cleared. The four-entry callback table at `083ACA4C` ends at the independently
referenced table `083ACA5C`; its last entry is the dummy interrupt callback.

All thirty-two following functions at `0800B814..0800D9DC` now match, including
the medal, part, item, face, image and sound pages. Dispatch slot 63 of the
main state-zero table reaches a menu whose eleven labels include Process,
Medal, Parts, Tinpet, Item, Face, Mdlpic, Battle, Sound and Motion. This suggests
a debug menu; forced RAM entry now renders those labels in mGBA, but its
normal gameplay entry conditions have not been traced. The
menu saves and clears 4 KiB of frame objects through DMA3 and restores that
snapshot on exit. Category Left/Right inputs wrap through eleven values. B takes
precedence over A, while text blinking uses bit 2 of the canonical frame counter.
The Process page edits three byte values and can assign them to main state,
substate and callback index after restoring the object snapshot. B clears its
display objects and returns to the category selector. Its three labels render
as User, Func-no and S-func; encoded glyph 43 is a hyphen. Category seven renders
Rnd-tk. The local experiment at `build/experiments/force_debug_menu.py` boots
the new-game menu, changes main/substate/callback to 0/63/0, and captures the
resulting category and Process pages. These are overlays on the prior menu;
this experiment establishes labels and dispatch behavior, not a gameplay entry
sequence. Screens and the trace remain under `build/experiments/debug-menu-forced/`.

The Tinpet page toggles its selected byte on either repeated Left or Right,
then calls the copied creation helper only when the existing count is zero. The
Rnd-tk page toggles equipment-work byte C2C. The battle page edits the selected
byte, clears C2E/C2F, sets C2D, copies the selected value into C2A, and changes
substate to 6 on A. B takes precedence. The motion page initializes index 39,
loads two previews, fills the render OAM region through DMA3, and navigates
122 indices with repeated Start/Select. A advances to playback; B returns to
the category selector. The playback callback updates both previews and backs
up two callback slots on B. All these control paths retain the reference bytes.

The Medal, Parts and Item pages each expose Get/Lost/All operations. Their
navigation limits are 29, 119 and 62 respectively; the Item activation guard
also accepts value 63. Preserve that distinction rather than changing the guard
to match the navigation limit. The Face page selects FaceNo/Look values through
175/8 and loads two tilemaps. Mdlpic uses those same labels, limits 29/4, and an
object preview; the adjacent unused No/Lv labels and their two pointers are
reconstructed in `src/state0_debug_labels.c`. Sound selects
Se/Bgm values through 127/53 and starts or stops the observed audio helpers.
Twenty exact label/pointer intervals add 228 bytes of typed data. The No/Lv
records have no known menu reference; their stored pointers establish the two
record starts.

The following dispatcher at `0800D9DC` and twenty-five of its callbacks now
match in `src/state0_next.c`, totaling 3,236 bytes. The eighty-entry table at
`083ACCD4..083ACE14` is independently bounded by its next reference and adds
320 bytes of typed data. The dispatcher suppresses work while the display guard
is active and clears render objects with BIOS CpuFastSet when render mode is two.
The initializer configures four backgrounds, loads the observed assets, clears
8 KiB of frame objects and advances the callback. Palette transitions use a
byte counter through eight, with weights advancing in steps of four. The
selection callback preserves mutually exclusive Up/Down navigation and A versus
B/Start priorities. Exit cases restore different main/substate/callback values,
and cases two and three clear both palette banks with separate stack fill words.
Screen naming and normal gameplay entry remain untraced. Four callbacks are
still copied: `0800E020`, `0800E350`, `0800E78C` and `0800EA98`. The table's
shared dummy entries already point to matching C. Candidate
sources for the two small mismatches remain isolated under `build/experiments/`.

The row transitions increment the byte at offset `84`; subtraction-range checks
explicitly truncate to eight bits. The load transition advances its callback
after the incremented counter exceeds 18. Pointer-table indices and fixed VRAM
addresses are retained exactly, while asset interpretation remains research.

Eight following selection/cursor helpers now match in
`src/state0_next_helpers.c`, replacing 892 copied bytes. They use pinned agbcc
with `-fprologue-bugfix`; the complete 8 MiB ROM hash was verified after
integration.

| Function | End, exclusive | Observed behavior |
| --- | --- | --- |
| `0800EBFC` | `0800EC20` | Increment both BG3 scroll halfwords on odd frames |
| `0800EC20` | `0800EC44` | Split selection byte `3D` into quotient `3F` and remainder `40` by four |
| `0800EEE4` | `0800EF58` | Initialize frame objects 1 and 2 at x=76/140, y=24 |
| `0800EF58` | `0800EFB0` | Blink those objects using frame-counter bit 3 |
| `0800EFB0` | `0800EFFC` | Initialize object 3 at x=80, y=48 + 16 times selected row |
| `0800EFFC` | `0800F08C` | Independently apply repeated Up/Down, wrap through four rows and refresh selection |
| `0800F08C` | `0800F148` | Independently apply repeated Left/Right, wrap through 30 pages and redraw |
| `0800F148` | `0800F218` | Independently apply newly pressed L/R, wrap through four groups and redraw |

For `0800EC20`, ordinary C division/remainder expressions `/ 4` and `% 4`
produce the original second byte load after the quotient store. Replacing them
with `>> 2` and `& 3` lets this compiler reuse the earlier load, emitting 32
instead of the required 36 bytes. No volatile access or instruction patch is
needed. At `0800F148`, a two-byte field view of `gNewKeys` retains the observed
base address plus high-byte offset; array indexing hoists the offset into the
literal instead. These are observed compiler-shape constraints, not proof of
the original source spelling. Three display helpers at `0800EC44`, `0800ED10`
and `0800EDA0` remain copied pending separate reconstruction.

Five further functions replace 756 copied bytes, also with
`-fprologue-bugfix`. `src/state0_part_display.c` recovers
`0800EE34..0800EEE4` (176 bytes): four rows test each part's first count byte,
call the copied status helper, draw one of the two observed tiles, or clear
the unowned row. A shared `part = page * 4` value serves both address
calculation and the later helper call; deferring it to the call changed
register allocation despite producing the same section length.

`src/state0_preview.c` recovers `0800F300..0800F440` (320 bytes). The selected
group determines the copied preview helper's placement and final flags.
The function then fills 256 render-object words with 512 and clears the two
render counters. Assigning the display data pointer before obtaining the
work pointer preserves the original load/literal order. The preceding
`0800F218..0800F300` remains copied; its candidate emits 224 rather than
232 bytes.

`src/state0_part_names.c` contains three exact functions:
`0800F6CC..0800F6E4` (24 bytes), `0800F6E4..0800F77C` (152 bytes), and
`0800F77C..0800F7D0` (84 bytes). The first subtracts 100 from selection
identifiers at least 100. The second selects one of two name-pointer tables;
the third selects the table indexed by work byte `EE`. Both drawing helpers
copy 14 text bytes to the work buffer at `9E` and retain the observed word
argument slots of the glyph helper. The name-table labels are provisional;
their complete bounds and assets remain copied.

For `0800F6CC`, a conditional expression and a signed result local assigned in
both branches each reproduce all 24 bytes. An equivalent early-return form
has the same size but different instructions. These variants are preserved
as `build/experiments/state0_identifier_conditional.c/.json` and
`state0_identifier_signed_result.c/.json`. They constrain matching source
shape without establishing the original source spelling.

The continued batch adds `0800F440..0800F60C` (460 bytes) and
`0800F60C..0800F6CC` (192 bytes) to `src/state0_preview.c`. The first checks
the selected part before drawing, except for the observed bypass groups.
A byte-sized selected-value local before constructing the group pointer
reproduces instruction order. The second initializes preview work; obtaining
the render-object pointer before the work pointer preserves load/literal order.
The return/pool at `F5FC..F60C` proves these are separate functions.

Three additions to `src/state0_part_names.c` match 264 bytes:
`0800F7D0..0800F844`, `0800F844..0800F8A0` and `0800F8A0..0800F8D8`.
They draw tile entries or selected part text using the existing table at
`083BBB4C`. Computing the first tile entry before the BG1 control read, and
loading the text-table pointer before the work pointer, preserves source
lifetimes needed by the pinned compiler. Word/halfword tile-entry locals both
match, so these findings do not establish original local types. All five use
`-fprologue-bugfix` and passed the complete-ROM comparison.

Two further complete routines replace 904 bytes using the same extra flag.
`src/state0_part_labels.c` covers `0800F8D8..0800FA7C`: explicit group branches
draw four, five or six label rows. `src/state0_part_values.c` covers
`0800FA7C..0800FC60`, drawing the corresponding numeric values. Passing
literal `0x53C4` to each glyph call preserves its load after the BG1 MMIO
read; a cached constant local produces a same-size but different routine.
The following count helper `0800FC60..0800FCF0` now matches 144 bytes in
`src/state0_part_count.c`. The scan preserves mode bypass, status testing and
the queried eight-byte record comparison. Separate setup/loop scopes and
`(u8)(value >> 8) != (value & 0xFF)` match; casting both sides to byte changes
four instruction bytes despite the same size. The result is narrowed to a
halfword inside a word local. Two equivalent exact sources are preserved,
so this constrains compiler shape without identifying original spelling.

Two marker helpers at `0800FCF0..0800FD74` and `0800FD74..0800FDD8` replace
232 bytes. They initialize two objects and blink them when count exceeds one.
The word at `0800FD70` is the first function's last literal; the next prologue
starts at `FD74`. Cursor initialization and coordinate update at
`0800FF50..0800FFF4` and `0800FFF4..08010040` replace another 240 bytes.
The latter requires coordinate word locals before forming destinations through
a byte view of canonical object-six X/Y fields. Canonical header declarations
replace inline caller prototypes and pass the full-ROM comparison.

The intervening navigation `0800FDD8..0800FF50` remains copied: ordinary and
complete shared-label models emit 352/376 and 348/376 bytes. Preserve these
failed shapes before exploring different pointer lifetimes.

The next object-four row initializer at `08010040..080100BC` matches 124
bytes. It sets x=168, y=56+16 times work byte `4A`, both scales to64 and
the observed flag/frame/palette/priority values. Its zero stores are at object
offsets `1C`, `29`, and `27`; the latter two retain unknown member names.
The initial offset guesses were rejected by strict comparison. Three-row
navigation at `080100BC..0801013C` matches 128 bytes, preserving independent
Up/Down tests, wrap through0..2, sound call and object Y refresh. Both use
`-fprologue-bugfix`; the twenty-fourth full build checks their canonical
declarations in all existing callers.

The following row dispatcher, blink, shrink, rectangle-clear and two BG/work
callbacks replace 400 bytes in `state0_row_actions.c`, `state0_row_blink.c`
and `state0_row_shrink.c`. Their bounded intervals and independent pointer
references are recorded in `root_continued/row_action_references.json`; matching
caller `0800EB34` independently reaches `0801013C`. Object-four unknown byte
`29` is the dispatch phase and byte `27` is the thirty-step blink counter.
Shrink decreases the byte scales by eight and hides the object at X scale zero.
The four-entry callback table `083ACE14..083ACE24` is sixteen bytes of typed
data in `state0_row_data.c`, bounded by the independently referenced next table.
The shared header declares the four-entry array; its former absolute alias is
removed. Function/data counts remain separate.

Three mosaic callbacks at `08010328..080103A4` replace another 124 bytes in
`state0_mosaic.c`: increase/decrease byte counter `84` by two, write the actual
volatile hardware halfword at `0400004C`, and advance callback at the endpoints.
Canonical work-field expressions preserve literals and reloads. The following
cycle `080103A4..080103F4` stays copied; seven ordinary models, including the
three narrow-local ideas, emit 76/80 bytes. Preserve those
failed models before trying
new evidence-supported forms.

Map setup, mirrored row drawing and palette clearing at `080103F4..0801058C`
replace 408 bytes in three source files. They use canonical scroll/work fields,
the matching LeDecompress routine, actual volatile DMA/hardware accesses, and
two CpuFastSet fills with distinct stack source words. The first palette-clear
probe named CpuSet and differed at both calls; it was rejected as the wrong
callee. Pointer slots `083ACE3C/40/44`, complete returns and pools independently
establish the intervals. Copied image/palette payloads remain outside source
coverage. Header declarations and all three compiled sections pass the full-ROM
build.

The intervening map dispatcher at `08010264..080102C0` also matches all92 bytes
in `state0_map_dispatch.c`. Canonical render mode at03000430 selects the actual
fixed-source DMA fill into RenderWork's object array, followed by dispatch through
the copied pointer table at083ACE24. Its extent remains unknown, so that table
stays an unbounded alias outside typed-data totals. The existing matching callback
table references this entry, and its private prototype is replaced by the shared
state-zero header. The complete-ROM build checks the dispatcher and its caller.

The following graphics setup at1058C..10794 replaces520 bytes, preserving
five decompress calls, tilemap setup, eight palette DMA transfers and a
fixed-source clear of the observed frame-object region. An explicit shared
palette-source word followed by subtracting0x160 reproduces the reference
lifetimes; separate constants emit516/520. Copied payloads remain outside
source-data counts. The92-byte fade at10794 matches direct canonical byte
indexing; five pointer/snapshot/scaled-local models failed before comparison
with the earlier matching034A4 access pattern. Four waits at107F0..108FC add
268 bytes, preserving message selection, byte input and distinct confirmation/
cancellation control flow. Pointer slots083ACE48..083ACE5C independently
identify all six entries. The copied message-table extent remains unknown.

Seven callbacks108FC..10AC8 add460 bytes, independently identified by slots
083ACE60..083ACE78. All seven first source probes match. The code preserves
SnapshotPalettes, signed selection/result flow including the high-nibble case,
message lookup indices20/21, full rectangle clearing and object hiding, and
the nine observed word arguments of copied497E0. Actual42318 narrows two word
slots internally; shared declarations replace old private declarations in
other state-zero callers and the entire ROM passes build43. Message tables
remain copied aliases with no claimed extent. Exact report is
`build/experiments/root_continued/map_second_first/results.json`; root's next
complete callback begins10AC8.

Six further callbacks10AC8..10C50 replace392 bytes; every first probe matches.
They preserve the slower fade and interrupt reset, the20-byte state-buffer
clear, equality-capped halfword counters and conditional sound selection,
callback112 branch, selected message and low-byte A/B acceptance, and text
completion. The actual table slots083ACE7C/CEB0/CEE8/CEF4/CEF8/CEFC are offsets
from the already matching10264 dispatcher's unbounded083ACE24 table; a new
table start or full extent is not inferred. Copied1BF64 consumes a halfword
counter pointer and word limit narrowed internally, with defined word result
unused by this caller. New message lookup083C3B04 remains copied and unbounded.
Root report `map_third_first` and full build46 verify source/shared declarations.
Build47 adds the next three callbacks10C50..10DAC /348 bytes. Independent
083ACE24 table slotsCF00/CF04/CF08 establish each complete entry.10C50
preserves its two branch paths and transfer-state writes.10CE8's first
equal-size model failed register/load order; the ordered source reads the
message before forming the destination buffer and keeps the selected pointer
alive across the first copy.10D58's first source used index171; the actual
byte offsetD6<<1 is428, so the corrected pointer index is107. Failed first
sources/reports are preserved; `map_fourth_ordered` strictly matches all three.
Copied message-table aliases083C6744/083C6F68 remain unbounded.

Build48 adds10DAC..10F08 /348 bytes in three callbacks. Decompress payloads
084D923C/084D9350 and palette payloads0850FF78/084E4538 stay copied. The
source preserves actual DMA writes and the control read, plus canonical
object1/2 flags, positions, frames, palettes and priority. No new private
offset layout is required: every first typed source matches. The condition
helper36AC4 consumes full word arguments1/0;12468 consumes globals without
arguments. Shared declarations and `map_fifth_first` pass the full build.
Independent existing-table slotsCF0C/CF10/CF14 prove the entries without
claiming the table's full extent.

Build50 adds six callbacks10F08..11078 /368 bytes. Direct low-byte key tests
match10F08; cached locals/mask comparison leave two register bytes. Buffer,
base and offset locals reproduce the16C halfword formatter source after a
direct-field model folded its literal and emitted56/60. Failed sources remain
saved. Other first probes match, including indices118/109 and endpoints96/64.
Copied12584/127DC initialize arguments from globals. Existing-table slots
CF18..CF2C prove the entries; `map_sixth_final` and full build50 are exact.

Build51 adds six callbacks11078..11268 /496 bytes. Existing-table slots
CF30/CF34/CF38/CF40/CF44/CF48 establish the entries without a complete table
extent claim. Index/stride snapshots before forming field pointers restore
the132/180-byte models' allocation. Word-unsigned identifier decrement before
lookup retains subtract-before-scale; promoted-byte expressions instead
yield pointer-minus-four. Matching types are not recovered declarations.
The four shorter first probes match. Copy lengths11/17, destination+20,
indices119/120 and endpoints71/75/67 are preserved. Shared unbounded083B74B8
declarations replace compatible private declarations; every caller passes
build51. `map_seventh_unsigned` is exact.

Build52 adds five callbacks /332 bytes at11268,112C4,112F0,11490 and114E0.
Existing-table slotsCF50/CF54/CF58/CF64/CF84 and repeated pointers establish
the entries. All first compiled sources match.11268 resets selection3 and
advances its callback for active entries;11490 directly tests the selection
without12098/43CD4, selecting callback78 or resetting to91. SnapshotPalettes,
the capped fade and final sound8 retain exact behavior. `map_eighth_first`
and the full-ROM build are exact.

Build54 adds five entries /784 bytes at11344,11500,115B4,115E8 and11644,
proven by slotsCF5C/CF90/CFA4/CFA8/CFAC.11344's copied values must be loaded
before destination pointers form; its state root precedes result decrement.
The first348-byte and equal-size instruction-order failures are preserved.
Other first models match. DMA fill/read order and selected record copies are
exact. Root map_ninth_final passes the full build.

Build55 adds five callbacks11A58..11BB8 /352 bytes, proven by slotsCFBC/CFC0/
CFE4/CFE8/CFF4. First models match. Restore11764/756 passes56 from slotCFB8;
the text-buffer-root integer address model preserves state byte030004C4 after
the two text copies, correcting the first760-byte model. Saved graphics,
decompression and DMA remain in their exact order; payloads stay copied.
Selector116C4/160 passes57 from slotCFB0. Separate cases with complete source
tails retain observed lifetimes before the compiler merges their assembly.
Grouped/shared-tail, width, case-order and declaration-order failures remain
saved. Root reports map_tenth_exact, map_restore_buffer and map_switch_final
are strict and the entire ROM passes. Five callbacks11BB8..11DB0 /504 pass58;
slotsCFF8/D000/D008/D00C/D010 prove their entries. Literal zero usage corrects
the11BB8 stack-store ordering, and a byte-pointer-plus-offset model restores
11C88 root allocation. Copied122F4 retains its full input word;421B4 narrows
both word inputs internally;440B4 takes no arguments. These interfaces and
the03000590 buffer alias are shared. Root map_eleventh_pointer and full build58
are exact. Four helpers11DB0..11F50 /416 pass59 from the verified10540 call
chain. DMA fill/control-read, two-byte equipment copy, weighted selection and
four independent random draws per each of three records are preserved. The
initial256-byte body has reversed count/offset registers; snapshots plus
count-first/offset-second initialization and a do-loop restore all256 bytes.
11F20 retains four full-word arguments/results and unsigned39/69/89 tests.
The copied table/pointer aliases have unknown extents. Root map_records_ordered
and the entire cartridge match. Five11F50..120C8 /376 pass60 from actual
recovered callers. Source-before-destination pointers fix the two text copies.
The three dynamic loops take a count snapshot before the guard, then declare
the saved work pointer inside the guarded block; this preserves the expected
load/branch/move order and actual fresh count reloads. Earlier size/load-order
failures remain saved. New copied label/coordinate aliases have unknown extent;
root map_text_objects_scoped and full build60 are exact. Three indicators
1214C/92,121A8/36 and121CC/36 pass61 from recovered callers. First models
match; copied121F0 retains a signed word result for the caller's signed random
threshold comparison, and12234 a word success result.120C8/132 remains140
(duplicated tail136);121F0/68 remains88 (early-return76);12234/192 emits188;
122F4/172 emits180 (integer-slot176). Compiler diagnostics fail and add no
coverage. Their complete hypotheses remain frozen. Three part-window helpers
123A0/200,12468/80 and124B8/204 pass full build62 after exact matching and
recovered-caller review.123A0 and124B8 retain their four independent drawing
cases and full-word44934 slots;12468 retains byte-narrow scale updates and
direction changes at64/128. The first stage lacked a copied44934 link symbol;
repairing that symbol yields all484 bytes without source changes. Root
continues score helpers12584..127DC. Six score components /440 pass build63:
12584/48,125B4/84,12608/68,126EC/112,1275C/32 and1277C/96. They preserve
unsigned average division, active-byte scans and halfword accumulation.
Split pointer roles fix folded address literals for reset/count without new
aliases.1264C/160 remains a failed average-comparison model with an extra
saved buffer lifetime; scoped/reloaded variants164/168 are preserved failures.
The first subset probe's omitted-definition linker failure was repaired before
freezing the strict six-function delivery. No failed model adds coverage.

Two map phase callbacks12970/88 and129C8/88 pass full build64. The accepted
main-state table slot083AC2E4 calls12970; its copied phase table083AD080
contains129C8 and following12A20. The real clear uses CpuFastSet at7CCC0,
and the indirect C callback uses the existing CallViaR0 trampoline7CCF0.
Initial CpuSet/ordinary-helper hypotheses failed and remain saved. Shared
callback declarations preserve existing link-state callers. The phase table
remains copied and unbounded; it adds no recovered-data claim.12A20/288
and127DC/404 remain failed staged models.

Ten further callbacks12B40..12F00 /960 pass full build65, established by
phase-table slots2..9 and11/12; slot10 remains the existing dummy. Split base
roles restore the fade counter and repeated selection pointer, with ordinary
source and no RAM qualifier changes.12C64 preserves A/B priority, signed setup
conditions, byte-normalized unsigned remainder and both background clears.
Its only two normal-model differences are cancel-mask register bytes;
-fno-regmove reproduces all308 bytes, while source-control/mask/bitfield and
no-expensive probes fail. Actual accepted flags are preserved in the manifest.
Four wait callbacks retain byte wrap and20/16/10 tests, fresh selection reads
and canonical drawing slots. Shared interfaces and all prior callers pass the
full cartridge comparison; copied phase-table data adds no recovered extent.

Six following callbacks12F00..13288 /904 pass full build66 from phase-table
slots13/14 and16..19. Ordinary switch cases restore12F00/248, preserving two
separate work scopes without forced registers.12FF8/68 and three detail
callbacks1303C/156,130D8/140,13228/96 match default game flags. Input13164's
byte-normalized word cancel result plus-fno-regmove matches196; either change
alone still fails. A/B priority, work counter wrap, clear destinations and
palette transfers follow the actual ROM. Unknown palette extents remain copied.
Frozen root reports continued_map_phase_selection, continued_map_phase_details
and continued_map_phase_detail_input reproduce each complete interval; shared
word ABI declarations and all8MiB pass after integration. Root continues at
13288; no failed12A20/127DC/1264C model gains coverage.

Six callbacks13288..13614 /908 pass full build67 from slots21,24..27 and29.
The two timed callbacks preserve a byte counter increment by2 and halfword
timer normalization before16; a counter snapshot before the saved zero value
restores their exact instruction order.133B8's separate base/counter roles
match128, while13438's explicit work/selection plus-fno-regmove matches208.
Default source/declaration-order probes remain208 failures.13330/136 and
13508/96 match directly. Palette4518 has unknown extent and remains copied.
Root continues complete effect/text callbacks beginning13614.

Six13614..13824 effects/text callbacks /528 pass full build69. Phase slots40..42
and32..34/48..50 independently prove their entries.13650's separate table root,
buffer root and selected record pointer restore96 bytes; pointer/partial-field
forms alone retain wrong load order. Record byte6 access is observed, with no
complete record type or pointer-table extent asserted. The five other helpers
match their source models, including existing SnapshotPalettes, five actual
CpuFastSet copies and canonical dummy interrupt callback. A missing buffer
declaration was repaired before comparison; failed setup logs are preserved.
The copied message table remains unbounded. Root continues13824 and following.

Setup13824/88 and restore1387C/504 pass full build70. State-byte snapshot before
the retained work base, and clear pointer before saved zero, restore the latter
from500 to504 exact after an intermediate six-byte ordering failure. Existing
render-work and copied helper interfaces are canonicalized. The original types
and copied asset extents remain unknown.

Return callbacks13A74/112 and13AE4/168 pass full build71. The first requires
separate base/counter and brightness roles; the second requires a word-mask
accumulator and real zero assignment in the first outgoing last argument.
Direct OR and narrowed mask probes fail despite equal168-byte size. No failed
model is counted. Complete fade13DE4/76 passes build72; preceding13B8C/600
remains copied with three differing bytes in its last record-byte/index access,
preserved in map_secondary_setup_roles and the subsequent selected-value/view
probes. Root continues complete13E30 and13FA8 callbacks.
