# Object display and part data

This batch reconstructs 22,608 bytes in fifteen GCC data sections using the
normal data profile. No new game function is counted.

`src/object_display_data.c` covers `083B2994..083B4E08` (9,332 bytes):

* Three callback directories contain 14, 6 and 2 function pointers, used by
  08041674, 08041CA4 and 08041CD4. Function addresses use relocations.
* The 256-byte scripted random sequence at 083B29EC is indexed after the
  byte-sized index increments, including wrap from 255 to zero (080424B8).
* Four coordinate-frame values and sixteen scene selector values follow.
* 4,272 text-background tilemap entries at 083B2B00 preserve tile index,
  flip bits and palette fields. The 106-entry directory at 083B4C60 has 105
  distinct roots into this bank. Rectangles are caller-defined; adjacent
  roots do not establish a universal width or height.

`src/part_metadata_data.c` covers `083B83FC..083BA1FC` (7,680 bytes).
There are 120 records, each with four 16-byte part slots copied by 08042B58.
The partial semantic layout is in `include/part_metadata_data.h`. Unknown
fields retain offset-based names; rank and score-factor accesses are recorded
from 0805B0D8, and slot-three byte01 also feeds the biased value in 08068F50.
The old byte-view symbol remains valid, preserving consumers' address arithmetic.

`src/part_dialogue_data.c` covers three message banks and their directories
(5,596 bytes): `083B7588..083B7E54`, `083B8310..083B83FC`, and
`083BDA30..083BE654`. The 121 stored messages decode with the existing native
dialogue parser; all directory targets land on command boundaries. Terminal
operands and the single alignment bytes remain exact. Sources use dialogue
macros for controls and glyph bytes for text.

Validation:

* All fifteen sections match with production-source specifications under
  `build/more/` (`object_display`, `part_metadata`, `part_dialogue`).
* `python tools/check_object_display_data.py` passes 88 callback cases,
  256 scripted-random cases, 80 selector cases, 318 tilemap fixtures and all
  480 part-slot copies. It verifies native results, write guards, preserved
  registers and stack restoration. Only selected callback bodies are hooked;
  tilemap, random, lookup and copy routines execute natively. Tilemap fixtures
  exercise entire physical spans, without claiming gameplay dimensions.
* `python tools/check_dialogue.py --inventory build/more/part_dialogue_inventory.json
  --limit 242 --output build/more/part_dialogue_cpu.json` passes sixteen
  synthetic cases and every one of the 121 native messages. Its established
  BIOS, drawing and sound stubs remain; this is command advancement under
  controlled state, not a full rendering or interactive-playback check.

The remaining region `083B7E54..083B8054` mixes six-byte records, triplets,
short lists and a pointer directory. It is not one flat triplet table and
remains raw until each boundary and consumer is established.

## Inventory selections and cursor coordinates

`083B7E54..083B8054` is reconstructed in `src/inventory_selection_data.c`:
52 six-byte records, 30 three-index lists, two zero alignment bytes, six counted
cursor tables, and their six-pointer directory. The six-byte record layout and
two-byte cursor header/point layouts are in `include/inventory_selection_data.h`.
Record bytes 1 and 5 select dialogue directories in `08008CA0`; other unknown
fields keep neutral names. The original byte aliases remain available to callers.

`08015668` copies three indices, then one selected six-byte record. `0800FF50`
reads the cursor count and initializes object 6; `0800FFF4` updates its coordinates.
Both convert tile coordinates to pixels by multiplying by eight. Cursor tables
have 5, 6, 2, 7, 8 and 8 positions; the count header includes a reserved zero byte.
Explicit byte alignment preserves the tables at addresses ending in 2 and A.

`python tools/check_inventory_selection.py` passes 270 native copy cases and
72 cursor cases, covering all list slots at three setup offsets and every cursor
position through both consumers. Only the follow-up display (`08015564`) and
animation setup (`08040B90`) are intercepted; the copy helper runs natively.
Guarded RAM, callee-saved registers and SP are checked. Standard GCC data profile;
`build/more/inventory_selection_production_spec.json` stages all 512 bytes through
`tools/match.py`. No gameplay C function is claimed by this reconstruction.

## Equipment animation tables

`083C4238..083C47C3` supplies eleven tile widths followed by eleven 128-byte
frame sequences. `08043FEC` increments an eight-bit counter and advances a
seven-bit sequence index when the counter exceeds two. Frame 255 restarts the
sequence at index zero. It copies `width * 32` bytes from
`02027000 + width * frame * 32` to `06008020` using a word-mode BIOS transfer.
The width/frame arrays use explicit byte alignment because the latter starts at
an odd ROM address; fixed bounds are recorded in `include/equipment_helpers.h`.

`tools/check_equipment_animation.py` passes 7,040 native cases (11 animations,
128 physical positions, counters 0, 1, 2, 254, 255), including 1,578 restart
paths. Frame selection and the one-byte copy helper run natively; only BIOS
CpuSet is modeled. Work memory, guarded tile transfers, preserved registers and
SP are checked. Tests cover stored positions without asserting their gameplay
reachability or hardware timing. All 1,419 bytes match with standard GCC data
settings via `build/more/equipment_animation_production_spec.json`.

## Equipment menu text, lookup and placement data

`083C47C3..083C4E24` contains alignment, six menu labels and their pointers,
128 further labels and their pointers, a 7-by-11 byte lookup with three padding
bytes, and seventeen four-byte placement records. Text banks stay contiguous:
`08015F24` copies twelve bytes, and other callers copy fourteen, so copying may
cross the FE terminator into the next label. FE marks the end for these label
consumers; these are not dialogue-interpreter programs.

`080191E4` indexes the lookup by `(setup[bank].byte91 - 100) * 11 + column`.
The placement layout is in `include/equipment_menu_data.h`: `08019D9C`
sign-extends xOffset but uses yAdd as an unsigned byte, then adds palette and
optional mirror settings. Values F4 in yAdd therefore remain 244, not -12.

`tools/check_equipment_menu.py` passes 134 fixed-width label copies (including
six native selector calls), 462 lookup cases and 612 placement cases. Copy and
placement logic execute natively; text display, the lookup's downstream consumer
and an orientation query are intercepted explicitly. Guarded memory, preserved
registers and SP are checked. All 1,633 bytes match with the standard GCC data
profile using `build/more/equipment_menu_production_spec.json`.

## Action palette banks

`src/action_palette_data.c` reconstructs 63 physical sixteen-color RGB555 slots:
`0850FBF8..0850FEF8`, `0850FF18..0850FF98`, and `085100D8..08510538`.
All 2,016 bytes match using the standard GCC data profile and
`build/more/action_palette_production_spec.json`.

Transfers can span two slots. `08025858` selects overlapping 64-byte ranges
starting at `0850FE98` or `0850FEB8`. The 64-byte transfer from `0850FED8`
continues into the existing `object_asset_palette_0850fef8` section; preserving
that neighboring section and the full transfer is required. The slot at
`0850FF78` is transferred by DMA3 in `08010DAC`.

`python tools/check_action_palettes.py` runs 146 fixtures through 60 original
loaders, covering all 2,016 reconstructed bytes and 69 distinct transfers.
CpuFastSet palette copies and the DMA3 register-triggered copy are modeled;
other external callees return zero. The checker verifies guarded palette RAM,
transfer arguments, preserved registers and SP. It does not validate other
helper effects, rendering, audio or hardware timing.

## Early action palettes and preserved high bits

`src/early_action_palette_data.c` reconstructs 1,952 bytes at
`0850F298..0850F5D8` and `0850F5F8..0850FA58` as sixteen-halfword palette
slots. Some stored colors have bit 15 set; those bits are preserved exactly.
Native consumers establish the palette interpretation: `0805CDAC` copies
512 bytes from `0850F298` into the palette shadow at `0202F800`, while
`08013B8C` copies 256 bytes from `0850F498` into palette RAM at `05000200`.
`0801A788`, phase 8, selects hardware or shadow destinations for its palettes.
The unreferenced 32-byte gap `0850F5D8..0850F5F8` remains raw.

`python tools/check_early_palettes.py` passes 168 fixtures across 21 original
loaders and covers every reconstructed byte. Fixtures exercise four palette
choices, both position orientations, and both hardware/shadow destinations of
`0801A788`. CpuFastSet copies and fills are modeled in guarded palette and
shadow buffers; other helpers return zero. Preserved registers and SP are
checked. Other helper effects, rendering, audio and timing are outside scope.
Standard GCC data settings match both sections through
`build/more/early_action_palette_production_spec.json`.

## Fallback map graphics

`080AC72C..080ACAEC` contains six 160-byte records, each a sixteen-halfword
palette followed by four 32-byte tiles. The shared layout and bounds are in
`include/fallback_map_assets.h`. `0804830C` uses word DMA to copy palettes to
`0202FA00`; `0804B2B0` uses halfword DMA to copy tiles to `06009080` onward.
Both select records in order 0, 1, 2, 3, 0, 0, 0, 4, 5.

All current map table entries are nonnull. `tools/check_fallback_map_assets.py`
therefore explicitly substitutes one null table entry in each fixture; the
loader instructions and asset bytes remain original. Four fixtures cover both
loaders at map indices 0 and 191, all 960 bytes, guarded destination buffers,
callee-saved registers and SP. DMA copies are modeled and other external
helpers return zero. These checks establish fallback transfer layout, not
reachability in the shipped game, rendering or hardware timing. Standard GCC
data settings stage-match via `build/more/fallback_map_production_spec.json`.

## Inventory page tiles

`084C4330..084C4830` stores five rows of eight 32-byte tiles. Native selector
`0800B0F8` reads page byte `0300047F` and copies tile `[row][page]` for each
of five rows to consecutive VRAM slots beginning at `06007A00`.
`tools/check_inventory_page_tiles.py` passes all eight physical page values,
verifying forty source/destination pairs and all 1,280 bytes. Only CpuFastSet
is modeled; the selector executes natively, with guarded VRAM, preserved
registers and SP checked. This does not validate rendering or timing.
Standard GCC data settings match through
`build/more/inventory_page_tiles_production_spec.json`.

## Late background tile bank

`087BAD60..087BB060` holds nine 64-byte 8-bit tiles and 96 palette halfwords;
`087BB7E0..087BBA60` holds twenty 32-byte map rows. Every map entry selects a
tile in the nine-tile bank. Three preceding zero alignment bytes are preserved.
Native `0806D7A0` copies the assets to `06008000`, `05000000`, and `06007800`
and writes BG2 control `6F8A`, selecting character base 2 and screen base 15.
`tools/check_late_background.py` checks all 1,408 asset bytes, five DMA transfers,
guarded VRAM/palette memory, BG controls and ABI. DMA is modeled and external
calls (including decompression) are stubbed, so rendering and timing are not
validated. Standard GCC settings match all 1,411 bytes with alignment through
`build/more/late_background_production_spec.json`.

## Equipment status scan

`08018EE0` scans four 24-byte entries at `030005DC + bank * 256`. It returns
the first one-based index whose byte 13 is nonzero and differs from byte 0,
or zero if none qualifies. The initial volatile read preserves the original
separate zero-check and comparison loads. `tools/check_equipment_scan.py`
passes 1,536 cases across six banks without stubs, checking exact byte-read
order, return values, untouched input RAM and ABI. All 44 bytes match strict
agbcc with `-fprologue-bugfix` via `build/more/equipment_status_scan_spec.json`.

## Object and scene callback and selection tables

`083AFAEC..083AFE88` contains 80 object callbacks, 12 scroll-shift bytes,
32 signed vertical steps, 96 scene callbacks, 32 random-choice bytes,
sixteen six-byte choice rows, and sixteen starting-bank choices. Original
callback addresses are preserved, including still-copied `0803BE44`.
The data reconstruction claims no C implementation for that callback.

`tools/check_object_scene_tables.py` passes 1,148 fixtures: all 80 object
selectors through 39 object slots, 96 scene selectors, 96 vertical-step cases,
64 random choices, 32 choice-row copies, 12 scroll-shift cases and 768
starting-bank/side/part/active-mask cases. These execute the original dispatch,
selection and motion bodies and the indirect-call trampoline, checking all
924 table bytes, guarded IWRAM and ABI. Callback bodies are intercepted;
randomness and a fixed +8 X movement are supplied by fixtures; other external
helpers return zero. Callback effects, rendering and timing are not validated.
Standard GCC settings match through
`build/more/object_scene_tables_production_spec.json`.

## Bridge segment layouts

`08485AEC..08485B4C` contains eight layouts of three four-byte segments:
start X, start Y, end X, end Y. `include/bridge_segments.h` records the layout.
Native `0806FF2C` advances a column across each segment, positions the sloping
end objects, writes tile D2 along the span, and advances after end X.
`tools/check_bridge_segments.py` passes 8,192 fixtures covering all eight layouts,
steps 0..3 and every byte-valued column. It verifies all 96 table bytes are read,
full guarded IWRAM/VRAM, callback arguments, return values and preserved ABI.
Object initialization is stubbed; single-halfword DMA is modeled. Rendering
and timing are outside the check. Standard GCC stage-matches through
`build/more/bridge_segments_production_spec.json`.

## Late scene callback banks and bridge labels

`src/late_scene_tables.c` reconstructs eight callback banks at `084857D0`,
`084858FC`, `08485964`, `084859BC`, `084859D8`, `08485A08`, `08485B68`, and
`08485BD8`: 101 pointers total. It also reconstructs eight variable-length
bridge labels at `08485A80..08485ACB`, one alignment byte, and their eight
pointers at `08485ACC..08485AEC`. Token 14 hexadecimal ends a label; token 15
emits a blank tile. Other tokens select tile `9064 + token`. The terminator
blinks between zero and tile 9078 according to phase bit 3, on even phases.
The pool layout is recorded in `include/bridge_labels.h`.

`tools/check_late_scene_tables.py` passes 1,257 native fixtures: all selectors,
20 command-processing frame slots with success/failure/cleared-command returns,
scroll-helper enable combinations, every label token, and parity/blink phases.
It covers 511 bytes of native ROM reads plus the verified zero alignment byte.
Callback bodies are stubbed with fixture results and the label DMA is modeled;
full guarded IWRAM/VRAM, call arguments, return values and ABI are checked.
Callback effects, rendering and timing are outside this check. Standard GCC
stage-matches all 512 bytes via `build/more/late_scene_tables_production_spec.json`.
The callback alias for still-raw `08072080` does not claim C coverage.

## Scene animation records

`084857FC..084858FC` holds 32 eight-byte records: u16 frame, s16 duration,
u8 next record, and three zero padding bytes. The shared format is declared in
`include/scene_animation.h`. Native `0806B4C8` visits 20 objects; nonzero record
indices advance when the old byte timer reaches the duration, resetting the
timer and loading the next frame. Record zero is the inactive sentinel.
`0806B530` initializes states 1..5 from records 1, 3, 7, 11 and 15.

`tools/check_scene_frame_animation.py` passes 8,592 native fixtures without stubs:
every index and byte timer across all 20 object slots, plus 400 initialization
cases. Full guarded IWRAM and ABI are checked. Native reads cover all 155 active
payload bytes. The 96 zero padding bytes and five inactive-record payload bytes
are preserved structurally and stage-matched, not claimed as native read coverage.
Standard GCC matches all 256 bytes through
`build/more/scene_animation_production_spec.json`.

## Timed frame dispatch and arc offsets

`src/late_frame_dispatch_tables.c` reconstructs 164 bytes: 64 signed arc offsets
at `08485924`, eight callbacks and intervals at `08485994..084859BC`, five
callbacks and intervals plus three alignment bytes at `08485B4C..08485B68`,
and eight callbacks at `08485BB8..08485BD8`.

`tools/check_late_frame_dispatch_tables.py` passes 16,248 fixtures through
`0806DE0C`, `08070550` and `0807178C`, with the original signed remainder helper.
It covers all 97 table bytes, all object slots, timer wrap and interval boundaries,
and callback returns 0, 1, 255 and 2. Callback and reset bodies are stubbed;
call order/arguments, full guarded IWRAM and preserved ABI are checked.
The three zero alignment bytes are checked separately.
`tools/check_late_scene_arc.py` passes 1,035 fixtures through original `0806CF7C`
without stubs: all 64 offsets, high timer bits, five command values and three
Y boundaries across eight objects, with full guarded IWRAM and ABI checks.
Standard GCC stage-matches through
`build/more/late_frame_dispatch_tables_production_spec.json`.

## Encounter frame intervals

`src/encounter_frame_intervals.c` reconstructs the 77-byte `[11][7]` interval
matrix at `08485783..084857D0`. Original `0806AA10` indexes it by encounter
variant and the active participant state's speed class. It increments a signed
32-bit timer and advances the selected frame object's 16-bit phase when the
interval is reached, then clears the timer. Inactive participant states skip it.
`tools/check_encounter_frame_intervals.py` passes 5,390 native fixtures with no
stubs, covering every byte, three active/two inactive states, signed timer
boundaries (including hardware wrap), phase wrap, guarded IWRAM and ABI.
Standard GCC emits the exact 77 bytes; the production spec is
`build/more/encounter_frame_intervals_production_spec.json`.

## Encounter sine phase offsets

`src/encounter_phase_offsets.c` reconstructs 22 bytes at `0848576D..08485783`
as two participants by eleven encounter variants. Original `0806A860` adds the
selected byte to the participant phase, masks to eight bits, and indexes the
signed sine table at `083D6A2C`. The resulting timer threshold is
`((sine >> 5) & 7) + 6`. `tools/check_encounter_phase_offsets.py` passes
22,528 native fixtures without stubs: every offset and phase, three active
states and one inactive state, firing/nonfiring timers, full guarded IWRAM
and ABI. Fixture setup excludes animation reset and global recovery branches;
the checker does not claim to validate those paths. Standard GCC emits all
22 bytes exactly using `build/more/encounter_phase_offsets_production_spec.json`.

## Late scene asset pairs and key-wait script

`src/late_scene_assets.c` reconstructs 108 bytes: five two-entry asset pointer
banks at `08485A58..08485A80`, two sixteen-color RGB555 background palettes at
`087C951C..087C955C`, and `FF 02` plus two zero alignment bytes at `08485BB4`.
The latter is an inline script, not a pointer. `FF` invokes the end handler;
mode 2 waits for either low key bit before advancing the script state.
Pointers reference the existing typed LZ77 streams and object palette banks.

`tools/check_late_scene_assets.py` passes 66 native fixtures. Original
`0806ED08` and `0806F0E0` load the first pointer entries; the harness models
DMA, checks palette destinations and decompressor arguments, and stubs other
called bodies. Second pointer entries are structurally preserved references,
not runtime exercised; the second background palette is verified structurally
as sixteen RGB555 values. Original `0803FD28` and `08040820` execute together
for all sixteen low key combinations and four script states including wrap,
with sound stubbed and full guarded IWRAM/ABI checked. Native reads cover
20 pointer bytes and two script bytes; padding is checked separately. Standard
GCC stage-matches every byte with `build/more/late_scene_assets_production_spec.json`.

## Full scene palette banks

`src/large_scene_palettes.c` reconstructs twelve 512-byte RGB555 banks (sixteen
rows of sixteen colors each) and nineteen preceding zero alignment bytes,
6,163 bytes total. Bases are `0878C088`, `0878DC74`, `0878F5E8`, `0879461C`,
`08796790`, `08797910`, `0879AD8C`, `0879BC34`, `0879D890`, `087CDCE0`,
`087D1E74`, and `087D5758`. Every color's high bit is clear.

`tools/check_large_scene_palettes.py` executes thirteen original integrated
scene routines and verifies fourteen complete transfers covering all 6,144
palette bytes. BIOS fast copies and DMA are modeled; other called helpers
return zero. Fixtures initialize scene/context memory to zero and check the
palette source, 512-byte size, palette-RAM/shadow destination, transferred
bytes, and preserved ABI. These checks do not establish full scene behavior
or all branches. The similar bank at `087A56EC` has no verified consumer
and remains raw. Production placement and standard GCC matches are recorded
in `build/more/large_scene_palettes_production_spec.json`.

## Palette words with set high bits

`src/scene_palette_high_bits.c` reconstructs four complete 512-byte hardware
palette banks at `087915F4`, `08799F20`, `087BEE04`, and `087C1BB4`, plus nine
zero alignment bytes (2,057 total). Original halfwords are preserved including
set bit 15; no color normalization is applied.
`tools/check_scene_palette_high_bits.py` executes original `0805F19C`,
`08061CE0`, `0806ED08`, and `0806EEA8`, confirming all four complete transfers
to palette RAM or its shadow buffer. BIOS fast copies/DMA are modeled,
other helper calls return zero, and fixtures initialize scene/context memory
to zero. Transfer addresses, 512-byte sizes, output bytes and ABI are checked;
full scene behavior and unvisited branches are outside this check. All four
banks and padding stage-match under standard GCC; production spec:
`build/more/scene_palette_high_bits_production_spec.json`.

## Smaller scene palette transfers

`src/small_scene_palettes.c` reconstructs 992 palette bytes plus nine preceding
zero alignment bytes. Native transfer spans are `08792E9C` (224 bytes),
`0879F6CC` (320), `087A25A4` (96), `087B4CE4` (64), `087B6710` (160),
and 32 bytes each at `087C643C`, `087C67C4`, `087C9A0C`, `087C9EE8`.
At the last group, only the observed palette spans are included; remaining
bytes in larger gaps stay raw.
`tools/check_small_scene_palettes.py` verifies nine transfers from nine
original consumers. It checks exact source-specific lengths, palette-RAM
or palette-shadow destinations, copied bytes and ABI. BIOS fast copies/DMA
are modeled and other helpers return zero; zero-filled scene/context fixtures
do not establish full scene behavior or all branches. Standard GCC emits
all 1,001 bytes exactly; spec: `build/more/small_scene_palettes_production_spec.json`.

## Palette spans from setup routines

`src/scene_palette_extensions.c` reconstructs 704 palette bytes plus three
zero alignment bytes. Spans are 32 bytes at `080AF938`, 32 at `080AF960`,
64 at `080AFA78`, 32 each at `084E43D8` and `084E43F8`, and the full 512-byte
bank at `087A56EC`. The latter's direct literal lies in still-unmatched
`08067D00`; searching only integrated consumers had missed it.
`tools/check_scene_palette_extensions.py` executes four original setup
routines (`0805CDAC`, `0805D860`, `0805FD10`, `08067D00`) and verifies seven
complete transfers. The harness checks source-specific sizes, palette/shadow
destinations, copied bytes and ABI, models BIOS fast copies/DMA, and stubs
other helpers. It does not verify full scene behavior. All 707 bytes
stage-match under standard GCC; spec:
`build/more/scene_palette_extensions_production_spec.json`.

## Additional native palette spans

`src/scene_palette_tails.c` reconstructs 864 palette bytes and six preceding
zero alignment bytes. Spans: `087A1540` (288 bytes), `087C5E50` (416), and
32 bytes each at `087C645C`, `087C67E4`, `087C9F08`, `087F312C`, `087F39CC`.
Original words retain their high bits. Larger surrounding gaps are not included.
`tools/check_scene_palette_tails.py` executes seven original consumers,
verifying seven complete transfers to palette RAM or palette shadow, with
source-specific sizes, copied bytes and ABI checked. BIOS fast copies/DMA
are modeled and other helpers return zero; full scene effects and unvisited
branches are outside this check. All 870 bytes stage-match under standard
GCC using `build/more/scene_palette_tails_production_spec.json`.

## Random lookup, audio waves and scene limits

`src/random_wave_limits.c` reconstructs 332 bytes: three signed32-bit spawn
tick limits (80,64,32) at `080B00AC`, four16-byte wave-RAM patterns at
`080B0820`, and a256-byte random lookup at `083F7D80`. Each wave contains
32 packed4-bit samples; the random table is preserved verbatim, not assumed
to be a permutation. Standard GCC matches all three sections exactly.

`tools/check_random_wave_tables.py` checks11,520 native `08049780` cases:
all lookup indices, five step/wrap cases, nine nonzero narrowed ranges, full
guarded IWRAM and ABI. Its original Mod wrapper executes with BIOS division
modeled. Another32 cases execute `08073A48` across all four waves and eight
control-register values; BIOS CpuSet is modeled, exact call/IO/guarded RAM/ABI
checked. `tools/check_scene_spawn_limits.py` checks4,320 native `0806C694`
initial-phase cases (ticks0..79, three limits, eight first-free slots or all
occupied, both directions), with sound stubbed and full guarded IWRAM/ABI
checked. Reset/transition branches are outside this check. Production spec:
`build/more/random_wave_limits_production_spec.json`.

## Command setup and restoration tables

`src/command_setup_tables.c` reconstructs320 bytes:112 tilemap halfwords
at `085FBA78`,16 tile-strip halfwords at `085FBBC0`, and16-color object
palettes at `085FBBE0` and `085FBDFC`. The32-byte gap at `085FBB58` remains
raw; its consumer has not been verified.
`tools/check_command_setup_tables.py` passes162 native fixtures through
`0805718C` and `080576E0`, covering all81 combinations of four three-way
selectors per routine. It models memory clear/DMA and stubs other graphics
helpers, checking exact transfer traces, the complete setup buffer, palette
RAM output during setup, palette-shadow output during restoration, and ABI.
Other scene state is outside this model. Standard GCC emits all320 bytes
exactly; spec: `build/more/command_setup_tables_production_spec.json`.

## Inventory appearance and kind records

`src/inventory_appearance_assets.c` reconstructs the 600-byte directory at
`083AC614`: 30 categories by five variants referencing 81 existing native LE
streams. `src/inventory_kind_metadata.c` reconstructs 30 sixteen-byte records
at `083B62D8` (480 bytes); their layout is in `include/inventory_kind_data.h`.
Unknown fields are named for their observed destination byte, without assuming
gameplay meaning. Both sources match under the standard GCC profile.

`tools/check_inventory_appearance_assets.py` passes 9,000 native fixtures
through `08009750`, covering every category, variant, inventory slot, and
owned/empty state. Decompression and empty-slot drawing are stubbed; exact
call arguments, guarded IWRAM and ABI are checked.
`tools/check_inventory_kind_metadata.py` passes 11,160 native fixtures through
`08041D70`: all kinds, first-free/full states, and 12 boundary levels. The
byte copy, rank selector and division runtime execute natively; only the
level supplier is stubbed. It checks complete guarded IWRAM, return values,
call counts and ABI. All 1,080 table bytes are read by these fixtures.

## Main/frame dispatch and scroll controls

`src/dispatch_scroll_data.c` reconstructs 428 bytes under standard GCC:
22 eight-byte scroll-control records at `083C3C84`, ten main-state callbacks
at `083D2104`, and 53 nonzero frame callbacks at `083D212C`. Every callback
points to an existing source function. The following 44 zero bytes at
`083D2200` remain raw; their membership in the frame table is unconfirmed.

`tools/check_dispatch_scroll.py` passes 44 native copy fixtures through
`080121A8` and `0803E870`, executing the actual byte-copy helper and checking
complete guarded IWRAM and ABI. Another 63 fixtures execute `0804763C` and
`0804A220`, including the native call trampoline, with callbacks and subsequent
frame helpers stubbed. They verify every dispatch target, helper trace and ABI;
frame flags/context are zero, so other branches and callback effects are outside
this check. All 428 table bytes are read.

## Action setup and selection tables

`src/action_aux_data.c` reconstructs 527 bytes under standard GCC: 27 eight-byte
base-stat rows at `083AD380`, 32 four-byte priority records at `083AD470`, six
count/kind/x/y sprite records at `083AD502`, six phase choices at `083AD51A`,
32 signed motion bytes at `083AD533`, 32 selection choices at `083AD553`, six
selection remaps at `083AD573`, seven setup remaps at `083AD579`, and callback
directories of 4/5/10 entries at `083AD580`, `083AD590`, and `083AD5A4`.
The sprite layout is in `include/action_aux_data.h`. All 30 inventory kinds
select only the first 27 base-stat rows; the following 24 bytes remain raw.

`tools/check_action_aux.py` passes 6,148 native fixtures through ten original
consumers and reads every reconstructed byte. It executes byte-copy and
indirect-call helpers, stubbing only the random source, sprite-clear helper,
and dispatched callbacks. It checks full guarded IWRAM, exact helper calls,
returns where meaningful, and preserved-register/stack ABI. Cases cover all
30 kinds at eight levels and three setup slots; all selection starts, seven
exclusions, five active-slot masks and three remap conditions; every callback;
and motion offsets 0..32/255, delays 0/1/255 and signed-coordinate boundaries.
Stubbed helper effects are outside the model.

## Terrain help dialogue

`src/terrain_help_data.c` reconstructs `083BE958..083BEAC8` (368 bytes):
seven complete native messages, three zero alignment bytes, and their seven-entry
pointer directory at `083BEAAC`. Text retains native glyph codes with readable
comments; FA/FF commands use the existing dialogue macros. Standard GCC matches
all nine sections. `tools/check_terrain_help.py` verifies 28 native selection
fixtures through `0800E350`, including all pointers, both completion results and
kind values 3/255. Update/index/dialogue-entry helpers are stubbed for that
check; exact calls, full guarded IWRAM and ABI are checked. Separately it runs
all seven messages through the original `0803FD28` interpreter and handlers
using `check_dialogue.py`, verifying command and terminal boundaries with BIOS
copy, drawing and sound stubbed. Rendering is outside scope. The existing
dialogue checker additionally passes its 16 synthetic control fixtures.

## State-zero sprite palette banks

`src/state0_sprite_palette_banks.c` reconstructs `084E4418..084E4678`
as nineteen sixteen-halfword palettes (608 bytes), retaining every stored bit.
The standard GCC profile stage-matches the complete bank via
`build/root_continue/state0_sprite_palette_banks_spec.json`.
Existing fixed-address aliases continue to identify individual palettes.

`tools/check_state0_palette_banks.py` passes 128 native fixtures through
sixteen existing loaders, covering all nineteen palettes and 21 distinct
source/destination transfer tuples. Four phase values and two flag/slot values
exercise palette RAM and shadow destinations. CpuFastSet and DMA copy/fill
are modeled; other callees return zero. Complete guarded palette/shadow
buffers and preserved registers/SP are checked. Rendering, external helper
effects, audio and hardware timing are outside this check.

## Common scene palettes

`src/common_scene_palettes.c` reconstructs eight sixteen-color banks at
`084C7F34..084C8034` (256 bytes). Existing absolute aliases retain their
addresses, including seven individual banks used by multiple loaders. The
preceding two bytes remain outside the reconstructed object.

`tools/check_scene_common_palettes.py` executes 72 native fixtures through
nine loaders and covers every stored byte. CpuFastSet and DMA copies/fills
are modeled; other callees return zero. Palette and shadow buffers are guarded
and preserved registers and SP are checked. Rendering, other helper effects,
audio and hardware timing are outside the check.

## Menu setup palettes

`src/menu_setup_palettes.c` reconstructs 96 bytes at `080AFB20` and 448
bytes at `087883F4`. Original, still-unmatched `08060708` transfers them to
OBJ and BG palette RAM respectively; the surrounding bytes remain separate.
`tools/check_menu_setup_palettes.py` checks both transfers and guarded palette
RAM for eight native setup fixtures. CpuFastSet copies are modeled and other
helpers are stubbed, so rendering and their side effects are outside scope.

## Main-two callback directories

`src/main2_callback_tables.c` reconstructs seven callback tables at `080AFB98`,
`080AFBE4`, `080AFC18`, `080AFC48`, `080AFC58`, `080AFC88` and `080AFCC0`
(59 pointers, 236 bytes). Existing absolute aliases retain their addresses.
`tools/check_main2_callback_tables.py` executes all 59 dispatches with original
copy and indirect-call code, stubbing callback bodies and checking preserved ABI.
Normal-gameplay reachability and callback effects are outside the check.

## Background scroll and palette data

`src/scroll_callback_tables.c` reconstructs two seven-entry callback tables
at `080B0020..080B0058`; `tools/check_scroll_callbacks.py` exercises both
dispatchers with all callbacks stubbed, including scroll wrapping and ABI.
`src/late_background_palette.c` reconstructs six 16-color banks at
`087C5FF0..087C60B0`. `tools/check_late_background_palette.py` covers the
192-byte palette transfer in eight native loader fixtures, with DMA/BIOS
modeled and other helpers stubbed. Existing absolute aliases remain.

## Frame motion offsets

`src/frame_motion_offsets.c` reconstructs 64 signed vertical offsets at
`080B00C8..080B0108`. The existing `080706A4` routine masks its index to six
bits and adds or subtracts the selected offset according to object parity.
`tools/check_frame_motion_offsets.py` checks 6,144 native cases covering every
entry, both directions, index wrapping, byte increment wrapping, guarded IWRAM,
and the preserved-register ABI. It does not establish gameplay reachability.

`src/frame_animation_steps.c` reconstructs the four-frame sequence and the
eight- and twelve-entry movement timing tables at `080B0108..080B0120`.
`tools/check_frame_animation_steps.py` covers every table entry in 208 native
fixtures, checking animation masks, both movement directions, guarded IWRAM,
and ABI. The animation timer is stubbed and movement transition helper paths
are suppressed, so their effects and gameplay reachability are not covered.

`src/equipment_scene_palettes.c` reconstructs two sixteen-color object palette
banks at `087C647C..087C64BC`. The native `08069530` equipment-scene loader
transfers them and two preceding banks to palette RAM. Four fixtures in
`tools/check_equipment_scene_palettes.py` verify all four DMA sources,
destinations, guarded palette RAM and ABI; DMA is modeled and other helpers
are stubbed, so graphics decompression and scene effects are outside scope.

`src/late_scene_script.c` reconstructs the nine bytes copied at `080B0120` by
`080722B0`, including four wait/sound command pairs and the final `FF` byte.
`tools/check_late_scene_script.py` checks 30 native fixtures at bounded command
positions, with DMA fill modeled and helper calls stubbed. It verifies command
transitions, sound arguments, guarded memory and ABI, but does not establish
behavior for arbitrary out-of-range script positions or full scene effects.

`src/scene_blend_steps.c` reconstructs two eight-byte arrays at
`080B00B8..080B00C8`, copied separately onto the stack by `0806CB28`.
`tools/check_scene_blend_steps.py` checks the eight in-bounds blend steps and
guarded registers and memory. The original routine can also read past those
stack arrays for later timer values; those paths are excluded and no larger
array is claimed.

`src/main2_animation_data.c` reconstructs two twelve-halfword frame tables,
thirteen signed vertical steps, an eight-byte frame sequence and one object
palette at `080AFABA..080AFB20` (101 bytes, excluding the byte at `080AFADF`).
`tools/check_main2_animation_data.py` covers every animation entry in 1,072
native cases; one scene helper is stubbed. `tools/check_main2_object_palette.py`
checks four native setup fixtures and guarded palette memory with CpuFastSet
modeled and other helpers stubbed. Full scene behavior is outside these checks.

`src/scene_bounded_lookups.c` reconstructs three signed choice identifiers at
`080AFCBD..080AFCC0` and six record-search slot indices at
`083ABDFC..083ABE14`. `tools/check_scene_bounded_lookups.py` checks all entries
and the search's early-exit and missing-result paths in 13 native fixtures;
the called scene and record helpers are stubbed.

`src/affine_identity.c` reconstructs the four-halfword object affine matrix
initializers at `080ABD5C..080ABD6C`. `tools/check_affine_identity.py` checks
16 native wrapper fixtures and the copied matrix, with ObjAffineSet and record
helpers stubbed. Three partial fixtures stop the still-unmatched recursive
renderer immediately after it copies the second matrix. The checks verify
initialization and output placement rather than BIOS calculations or complete
recursive rendering.

`src/roster_selection_data.c` reconstructs three text coordinate pairs and
16 random-start choices at `083AD06A..083AD080`.
`tools/check_roster_selection_data.py` covers every entry in 66 native
fixtures, stubbing text rendering, the random generator and selection helper.

`src/scene_object_layout_data.c` reconstructs four frame values at
`083AE060..083AE064` and four coordinate records at `083AFACC..083AFADC`.
`tools/check_scene_object_layout_data.py` checks five native fixtures,
including both horizontal orientations; scene helpers are stubbed. The four
stored record padding bytes are preserved and byte-matched but not read by
the tested consumer.

`src/scene_sound_choices.c` reconstructs four frame choices at
`083AD520..083AD524` and three sound choices at `083AD530..083AD533`.
Both consumers accept an unchecked byte index. `0801677C` now forms the ROM
address as an integer, matching its original 64 bytes while retaining adjacent
reads; `08018A54` already did so. `tools/check_scene_sound_choices.py` checks
all 256 index values for each native consumer, including reads outside the
named tables. Sound playback is stubbed.

`src/scene_selection_coordinates.c` reconstructs six coordinate pairs at
`083AD524..083AD530`. Four existing consumers now form their ROM addresses as
integers, preserving the original instructions and unchecked adjacent reads;
the other three consumers already used integer address arithmetic.
`tools/check_scene_selection_coordinates.py` checks 84 native fixtures through
the four changed consumers, covering all six pairs, selected adjacent reads,
both movement directions, guarded IWRAM and ABI. Scene helpers are stubbed;
arbitrary gameplay states and helper effects are outside the check.

`src/action_selection_tables.c` reconstructs three six-byte angle and selection
tables at `083AD4F0..083AD502`. Existing consumers `08016154` and `08016288`
now form unchecked ROM addresses as integers and retain their exact original
instructions; `08015F90` and `08016080` already did so.
`tools/check_action_selection_tables.py` checks 2,048 native fixtures through
the two rewritten functions, including all byte indices, three object indices,
both directions and adjacent-ROM reads. Coordinate and scene helpers are
stubbed; complete gameplay and helper effects are outside the check.

`src/main2_menu_selection_data.c` reconstructs three name-menu column mappings,
52 music choices and 118 effect choices at `080AF9C8..080AFA76` (173 bytes;
the intervening byte at `080AF9CB` remains separate). Two existing consumers
now use integer ROM addresses for unchecked indices and still match their
original instructions. `tools/check_main2_menu_selection.py` executes 893
native fixtures, covering every entry and selected adjacent-ROM reads. The
keyboard fixtures stop immediately after the table read; menu helpers are
stubbed, so full rendering and audio are outside the check.

`src/record_display_pairs.c` reconstructs eight coordinate pairs at
`080AFBB4..080AFBC4`. Consumer `08062B48` now uses integer ROM addresses for
its unchecked indices while retaining its 164 original instruction bytes.
`tools/check_record_display_pairs.py` checks 64 native fixtures covering all
pairs, selected adjacent reads, helper arguments, guarded RAM and ABI; the
renderer is stubbed.

`src/main2_script_maps.c` reconstructs two dialogue maps at
`080AFC80..080AFC88` and a six-entry cursor map at `080AFCB7..080AFCBD`.
Two existing consumers use integer ROM addresses for their unchecked lookups
and retain their original instructions. `tools/check_main2_script_maps.py`
checks 517 native fixtures across every entry, selected adjacent reads and the
special cursor path; script and display helpers are stubbed. It does not verify
the contents or effects of the referenced scripts.

`src/credits_scroll_columns.c` reconstructs three credits scroll column values
at `080B000E..080B0011`; the following three bytes remain separate.
The existing credits routine `08067974` now forms an integer address for its
unchecked line-count lookup and still matches all original instructions.
`tools/check_credits_scroll_columns.py` checks all 256 byte indices in each
original lookup, including adjacent ROM reads. Fixtures stop immediately
after the reads and do not cover complete credits rendering.

`src/record_selection_map.c` reconstructs the four-byte record-selection map
at `083D262C..083D2630`. The existing `0804BE50` consumer now uses an integer
ROM address for its unchecked byte index, preserving all 116 function bytes.
`tools/check_record_selection_map.py` checks all 256 index values,
including reads into the following callback table, with the record helper
stubbed and guarded RAM and ABI checked.

`src/scene_loading_palettes.c` reconstructs five sixteen-color banks at
`08488540..084885E0` (160 bytes), retaining all stored high bits.
`tools/check_scene_loading_palettes.py` executes eight native loader fixtures
covering all five banks and the already reconstructed bank at `080AFBC4`.
CpuFastSet is modeled and other helpers are stubbed; guarded palette and
shadow memory and the ABI are checked, while rendering and other helper
effects are outside scope.

`src/late_scene_palette_9f28.c` reconstructs one sixteen-color bank at
`087C9F28..087C9F48`. `tools/check_late_scene_palette_9f28.py` verifies eight
native `0806EEA8` loader fixtures with DMA modeled and other helpers stubbed,
including guarded palette and shadow buffers and preserved ABI. Rendering and
other helper effects are outside scope.

`src/interface_palette_banks.c` reconstructs the sixteen-color banks at
`08488520..08488540` and `084885E0..08488600`, preserving their high bits.
`tools/check_interface_palette_banks.py` executes the native `0803F3A8` and
`080075AC` loaders with CpuFastSet modeled and other helpers stubbed. It checks
the complete guarded palette buffer and ABI; rendering and helper effects are
outside scope.

`src/action_phase_limits.c` reconstructs the three timing limits at
`083AE950..083AE953`; the following padding byte remains raw. The `0802BE44`
consumer uses integer ROM addressing and still matches all 168 bytes, including
the phase-zero read from `083AE94F`. `tools/check_action_phase_limits.py`
checks 32 native fixtures with sound stubbed, guarded RAM and the ABI checked.

`src/main2_frame_tables.c` reconstructs four-frame choices at
`080AF958..080AF960` and `080AF980..080AF988`; both consumers mask their
indices to 0..3. `src/state0_map_row_positions.c` reconstructs three coordinate
pairs at `083AD064..083AD06A`. Its `08012024` consumer uses integer ROM
addressing for the unchecked row count and still matches all 116 function
bytes. `tools/check_frame_and_map_row_tables.py` runs 1,024 native frame
fixtures and all 256 row-count fixtures, including neighboring ROM reads; the
two row helpers are stubbed, and guarded RAM and ABI are checked.

`src/action_movement_sequence.c` reconstructs eight angle/duration pairs and
their terminating byte at `083AEB08..083AEB19`; trailing padding remains raw.
The `0802DE1C` consumer's integer ROM addressing preserves its 252 bytes and
unchecked indexing. `tools/check_action_movement_sequence.py` exercises all
256 indices with and without mirroring, including sentinel and adjacent-ROM
reads, with three helpers stubbed and guarded RAM and the ABI checked. The
early-return and active-delay paths are outside these fixtures.
