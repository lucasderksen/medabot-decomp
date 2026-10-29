# agbcc source idioms that reproduced the reference

The lean-run idioms were verified during 17-18 October 2026; later entries
record additional reproducible compiler behavior. Use them as first guesses
for near-misses.

## Complete and incomplete array redeclarations

With the project's agbcc `-fprologue-bugfix` profile, declaring a scalar array
with a bound and then redeclaring it without one can crash at `stor-layout.c:203`
when indexing it. This minimal byte example reproduces it; unsigned halfwords
do too:

```c
extern const unsigned char data[144];
extern const unsigned char data[];
unsigned int test(unsigned int i) { return data[i]; }
```

Either declaration alone compiles, as does the reverse order. Consolidate the
declaration in its owning header and remove stale unsized declarations rather
than changing compiler flags or the function body. This fixed the action
parameter readers and motion table consumer while retaining their exact bytes.
Eight fresh compile probes are recorded in
`build/more/array_redeclarations/results.json`.

## Local aggregate initializers

A `memset(row, 0, 0x10)` call followed by element stores, where some rows of
the same array are cleared and others are stored element by element
(zeros included), is gcc's `store_constructor` for a brace initializer with
non-constant elements: each mostly-zero row is cleared with a memset libcall,
the others get one store per element in order. Write the initializer, not the
explicit calls; repeated non-constant elements (`table[x]` twice) are shared
by cse, so loads appear where first used. sub_08066B4C (three rotation
matrices) went from 19 rows with an unacceptable hack to an exact match:

```c
s32 rx[4][4] = {
    { 0x100, 0, 0, 0 },
    { 0, sine[x + 0x40], sine[x], 0 },
    { 0, -sine[x], sine[x + 0x40], 0 },
    { 0, 0, 0, 0x100 },
};
```

## Flag profiles

- Run `tools/try_flags.py` on any near-miss before more rewriting: three parked 7-17-row functions matched outright under profiles other files already use (sub_08030780 `-fno-cse-follow-jumps -fno-cse-skip-blocks`, sub_0805AE4C `-fno-regmove`, sub_0805B0D8 `-fno-gcse`).

## Addresses and bases

- Base loaded before the index shift (`ldr rB,=gFrameObjects; lsls r0,rI,#6`):
  `u32 root = (u32)gFrameObjects; object = (struct FrameObject *)(root + (index << 6));`
  (sub_0806E074, sub_0806B1FC, sub_080706A4; older sub_0806E038, sub_08070648).
  When the reference reloads the base literal for each later access, give each
  access its own block-scoped `u32 root` (sub_0807190C, sub_080719B8).
- Symbol + offset kept as `ldr base; adds #off` instead of one folded literal:
  access a real struct field, not `((u8 *)&g)[off]` or a pointer cast
  (gCounter6ED08_03001800 views in lean_a/lean_b sources).
- `&gPointer` held in a callee-saved register from function entry (`ldr r5,=gX` before the first compare), then fresh literal loads after the first call: use `T **rootp = &gX;` and `(*rootp)->` up to the first call in each branch, then `gX->` (sub_08074288).
- agbcc aligns every struct to 4 bytes, including nested ones. Records at an
  offset that is not a multiple of 4 must be arrays (`u8 rec[][8]`) or the
  enclosing struct must start earlier (sub_080668D4).
- A struct view of an existing global may be declared with an assembler label:
  `extern struct View gView[] asm("gFrameObjects");` (lean_b).

## Loops

- A label loop with a block and `if (mask) goto loop` can keep the counter in
  a high register and spill the long-lived parameter, where `do/while` chooses
  the opposite lifetimes. This matched `sub_08074D50`; the same form also
  matches `sub_08074A8C`. Both dispatchers take full-word arguments; m2c's
  inferred narrow parameters introduced extra truncations.
- The reference reloads constants each iteration and keeps a separate counter,
  with no strength reduction: write the loop as a label plus `goto`
  (sub_08071804, sub_08074A04).
- Direct indexing such as `gX[G.f + i].field` keeps constant addresses hoisted.
  Temporaries such as `row`/`obj` stopped the hoisting (lean_b: sub_0802D5BC,
  sub_0802B184).
- Explicit offset variables plus a goto loop reproduce reference givs
  (sub_08062C98 shape).
- A reference loop counting down to zero (`subs rK,#1; cmp rK,#0; bge`)
  whose counter is unused in the body is often a count-up source loop that
  gcc reversed: `for (k = 0; k < 16; k++)` matched where `k = 15..0` placed
  the counter initialisation differently (sub_0805BE0C, near-miss sub_0805BD44).
- Indexing (`buffer[i]`) instead of a walking pointer lets the strength-reduced
  pointer be created after the hoisted constants (sub_0805BF14 shape,
  sub_0804B1B0 shape).
- Empty-body `for (; i <= j && v[i] <= v[left]; i++);` scans reproduced the
  three byte/halfword quicksorts (sub_08049EE8, sub_08049FD0, sub_0804A0F0).

## Expressions and stores

- An OR whose byte and constant occupy the opposite two registers can be
  written as `dst = ~(~old & ~mask)`. agbcc folds it back to an OR with different
  operand allocation: `sub_08074A04` matches all 116 bytes using this form for
  `flags | 0x5F`, where direct OR forms left two register differences.
- `x / 2` and `< 0x41` instead of `x >> 1` and `<= 0x40` on a u8 loaded twice
  (sub_08067870).
- `ldr r0,=0xFFFF; orrs r0,rOld; strh` comes from a plain `field = -1;` through
  a struct field while the old value is live (sub_0806E074).
- Reference `ldrb rB,[G+0x60]; subs rB,#k; adds rB,rI` (row = base - k + index) came from `G.base60 + (index - k)`; `G.base60 - k + index` reassociates to `index - k` first (lean_b: sub_080388A4, sub_08038AC0, sub_08038700).
- A table offset built from a constant just stored (`movs rK,#0x48; strb rK,[W]; lsls rK,#2`) came from storing the index and reading it back: `W.bytes[0x84] = 0x48; f(gState0NextCommands_083B6100[W.bytes[0x84]])` (lean_b: sub_0802E4C8, sub_0802EC4C).
- `if (1 & global)` keeps the constant in a register; `mode & global` does not
  (lean_b: sub_0803DEF0).
- Tails that m2c shows as "choose an offset in each branch, store at the join"
  were full separate stores per branch, merged by cross-jumping (lean_a/lean_b:
  sub_0801EEE4, sub_0803C044, sub_08036120). The same holds for a pointer chosen in
  each arm and dereferenced at the join (lean_b: sub_080395E8, sub_080396D4, sub_08039AC8).
- Separate `call; return` in every branch rather than one call after the join
  (lean_b: sub_08038E9C).
- A narrow (u8) parameter that is spilled shows as `str r1,[sp]` plus a later
  `ldrb [sp]`, with no lsl/lsr at entry.
- `ldr rH,=0xFFFFF000; adds rL,rH,#0; ands` (constant in a callee-saved register, then copied) came from a sign-extended mask on an s16 store, `field = (a * b) & ~0xFFF;`, sometimes chained (`*out = field = ...`) (sub_080732F0, sub_0807334C, sub_080733BC). An `0xFFFFF000` literal or an s32 temporary does not reproduce it.
- A two-case switch compiled as a signed tree (`cmp #1; beq; cmp #1; bgt default; cmp #0; bne default`) had an extra empty case, e.g. `case 2: break;` (sub_080722B0). Without it gcc emits `cmp #0; beq; cmp #1; bne`.
- A local initialized array compiles to `memcpy` from the ROM constant; call
  `memcpy(local, gConstant, n)` explicitly (sub_08071804).
- `table[(index << 2) + (index << 1) + k]` keeps the reference
  `lsls #2; lsls #1; adds` for index*6; `index * 6` or `index * 4 + index * 2`
  folds to `((x << 1) + x) << 1` (sub_0805B188).
- Calls the reference repeats (`__divsi3`/`__modsi3` recomputed instead of
  CSE'd) are explicit library calls in the source, not `/` and `%`
  (sub_0805A3A4 shape).
- Values the reference loads into r3-r5 before a call and then moves to r0-r2
  were assigned to locals first (`x = first[i]; ...; call(x, y, z)`)
  (sub_08053B04).
- `p = c ? 13 : 12` emitted as `movs r3,#13; cmp; bne; movs r3,#12` comes from
  `c == 0 ? 12 : 13` written after the call (sub_08058070).
- A `do { ... } while (0);` around the tail changed pseudo priorities and fixed
  a two-register swap (sub_08050358); worth one try for persistent swaps.
  It also works around inner statements and as an if body (`if (c) do { ... } while (0);`):
  lean_b sub_08038BC0, sub_08041164, sub_0804126C, sub_08033184. Brute-forcing every
  brace-balanced statement range is cheap (one compile per range) and found most of these:
  `python tools/try_wraps.py <name> <draft.c> -fprologue-bugfix 10`; for declaration order and
  integer types use `python tools/try_decls.py <name> <draft.c> -fprologue-bugfix`.
- `digits[k] = rest / 1000;` with the `/` operator (libcall `__udivsi3`) evaluates the stack
  array address before the call (`mov r6, sp; bl; strb r0,[r6]`); an explicit
  `__udivsi3`/`sub_0807CEC8(...)` call or a temporary computes it after the call (sub_08041164).
- A constant used once at the end, held in an initialized local declared at entry (`void *palette = (void *)0x05000000; ... CpuFastSet(buf, palette, 0x80);`, `IntrFunc callback = Fn; ... gCallback = callback;`), fixed call-argument load order and loop register allocation (lean_b: sub_0803F684, sub_0803F788, sub_0803F890; first found by tools/permute.py).
- A global read twice with a reloaded literal although nothing clobbers it can
  be a second asm-label alias of the same symbol (near-miss sub_0805B984).

- A returned `struct TileCoordinates` split as `strh r0; asrs r0,#16; strh` (signed high half) came from
  `union { struct TileCoordinates tile; s32 packed; } c; c.tile = sub_08042BC0(...);` then
  `x = c.packed; y = c.packed >> 16;` (lean_a: sub_080222A8, sub_08022648, sub_08022A04, sub_08022E14).
- A spilled loop value whose stack slot sits after the hoisted invariants is
  a strength-reduced giv: write `x + i * 16` in the body instead of a
  separate `x += 16` (sub_08059734).
- A named temporary for one intermediate (`u8 value = obj->field - 1;` before
  the store, `later = gLaterBuffer;` before `table[later[0]]`) fixed hoisted or
  argument temp register swaps (sub_0804B1B0, sub_08052284; both found by
  tools/permute.py).
- Tilemap cell addresses were pointer arithmetic,
  `(u16 *)((block << 11) + 0x06000000) + x + (y << 5)`, not byte sums; the
  evaluation order also fixed the allocation of the coordinate registers
  (sub_08059F58).
- A switch tree rooted at an unexpected case had extra cases that share the
  break label: `case 0: case 0x40: break;` moved the root to 0x40
  (sub_08049A6C).
- Constants the reference rebuilds after a branch join (`movs r5,#0xd` at
  entry, `lsls r1,r5,#12` later; `movs r1,#0x1e; lsls #11`) were locals set
  once at entry (`palette = 0xD; block = 0x1E;`) and used as `palette << 12`,
  `block << 11` (sub_0805A988, sub_0805A3A4, sub_0805A444).
- `block << 11` kept apart from `x * 2 + 0x06000000` came from
  `(vu16 *)(block << 11) + (x + 0x03000000) + ((y + 1) << 5)`; byte sums fold
  both constants and `(y + 1)` into one literal (sub_0805A444).
- A local updated with `ldr/str [sp]` and addressed as `mov rX, sp` was a
  one-element array (`union Entry entry[1]; entry->...`); plain or
  address-taken locals were purged back to registers. A 16-bit bitfield clear
  (`entry->clear.low = 0`) gave the word `ldr; ands 0xFFFF0000; str`
  (sub_0805ABCC).
- `x--; if (x != 0)` on a u8 field gave `lsls #24` tests where `if (--x)` used
  an `ands` with a hoisted 0xFF (sub_0804E134).
- A pointer copy before a loop (`adds r4, r1, #0`) followed by `adds r4, #8`
  was an indexed walk `entry[i * 8]` with `i++` (a strength-reduced giv), not
  `entry += 8`; `u8 map = work.map; entry = table[map];` gave the index load
  before the table literal (sub_08052E88).

- Command words read as `ldrb; lsls #26` (count) and `ldrb [p,#1]; lsrs #7` (flag) were
  bitfields of a byte struct (`struct LaterCmd { u8 count:6; u8 b6:2; u8 b8:7; u8 flag:1; ... }`);
  the bitfield view fixed an address/index register swap that no byte-cast form fixed
  (lean_b: sub_080460B0). Two asm-label aliases of one table give duplicate literal-pool
  words (`"*name"` and `name` are different symbol strings); declare one alias and reach
  the other type through a cast of it, `((const u32 (*)[4])gLaterCmdF610)[i]`.

## Setup records and frame objects (lean_a round 3)

- `gSetupBuffer_03000590` holds 256-byte records; m2c's `ldr base; adds #off`
  per field means a record-struct view (`extern struct V gV[] asm("gSetupBuffer_03000590")`),
  not byte indexing. Offsets 0x48/0x60/0x78/0x90 are four 0x18-byte part records
  (`name[13]` at +0, byte +0x10, `data11[6]` at +0x11, id +0x17); `parts[k]` as a nested
  struct array reproduced the reference givs (sub_08014F90, sub_0801D5A8).
- `(i << 8) + base` added before `+ j`: write `row = buf + (i << 8); row[j]`, not
  `buf[(i << 8) + j]` or a 2D array (sub_08004AF8).
- m2c `D_0300xxxx` bases with offsets like `0xFFFFF1C0` are one symbol at several
  offsets (gcc CSE of symbol+const): here `&gFrameObjects[n]` (sub_0801D738).
- `(k << 8) + root + 0x1664` (big folded constant after the base) came from
  `((struct FrameObject *)((k << 8) + root))[0x59].field` with block-scoped
  `u32 root = (u32)gFrameObjects` (sub_0801D9DC); `gFrameObjects[0x59 + k * 4]` gives
  `(k << 8) + 0x1640 + base`.
- `a == 3 && b == 3` on adjacent bytes compiles to one word compare; the reference's
  two byte compares came from nested `if (a == 3) if (b == 3)` (sub_08004AF8).
- An `adds` of literal `0xFFFF8000` before a u16 store came from
  `+ (u16)(x + 0x8000)`; `- 0x8000` and `+ 0xFFFF8000` emit `0x8000` (sub_08004AF8).
- A loop whose body starts with `if (!x) break;` is rotated by gcc (entry jump to a
  bottom copy of the test). The reference's top-of-loop exit test came from `return`
  or `goto label_after_loop` instead of `break` (sub_08018D0C, sub_08018DF4, near-miss sub_0801A33C).
- `x = call(); part = x & 0xFFFF; x >>= 16;` (one variable reused) kept the reference's
  result register; separate `part`/`full` temporaries did not (sub_08015C40).
- A call argument computed as `x + 1` with the counter bumped afterwards (`f(x + 1); x++;`)
  reproduced `adds r4, r7, #1 ... adds r7, r4, #0` around calls (sub_08015C40, near-miss sub_08017734).
- Masks the reference keeps in high registers (`mov sl, r5` for 0x1F) were locals
  (`redMask = 0x1F`), written mask-first (`redMask & *src`) (near-miss sub_0800147C).
- A per-iteration index the reference adds before the scaled term (`(b + i) * 4 + (k + 0x5A)`
  kept as `adds #0x5a` before the add) needed a narrowing cast: `(u8)((0x7F & k) + 0x5A)` (sub_080277DC).
- A register-allocation-only near-miss resolved by reusing a variable for an unrelated value
  (`(xAddress = row) << 6`, found by tools/permute.py) (CopyTilemap).
- tools/m2c_integrate.py only handles `sub_XXXXXXXX` drafts; a named function (CopyTilemap) was
  integrated by hand: own source file, segment entry, absolute symbol removed.
- `++x & 4` on a u16 field adds a `0xFFFF` mask; `x++;` as its own statement, then
  `if (x & 4)`, tests the loaded register directly (sub_08024C94).
- `0x20 & (u8)gRepeatedKeys` gives the reference `ldrb` of the key word (sub_0800AE54).
- `-fno-expensive-optimizations` can match but emits a `.rodata` constant pool that
  accept_draft rejects; rewrite the source instead (sub_08024C94).

- `gEncounterFrameSlots` reads the reference repeats after an outgoing-argument store or with no call in between came from a non-const view, `extern u8 gEncounterFrameSlotsView[3][3] asm("gEncounterFrameSlots");`; the const header declaration lets gcc CSE them (lean_b: sub_08069B38, sub_08069BFC, sub_0806B01C, sub_0806ADB0, sub_0806AAA4).
- Reference `subs rK,rC,#k; subs rK,rI3,rK` (`i*3 - (c - k)`) came from `i * 3 + k - c`; writing `i * 3 - (c - k)` folds to `(i*3 + k) - c` (same functions).
- `gFrameObjects` literal loaded before the slot-table literal came from repeating the full `gFrameObjects[slots[i][c]].field` expression in each test instead of a `struct FrameObject *` temporary (sub_0806A748, sub_0806B01C).
- An index `i + 1` used in the body of `for (i = 0; i <= 15; i++)` reproduced the reference `adds r1,#1; ... adds r6,r1,#0` copy pair around calls; `next = i + 1` or `++i` forms did not (sub_08067C04).

- A DMA fill source the reference stores through the same register it later writes to DMA3SAD came from `volatile s32 fill; fill = 0;` before the DMA block; a plain local recomputes the large sp offset (sub_08069910).
- A spilled value tested twice (`7 & t`, then `t & 0x20` with `ands` into the loaded register) came from assigning a local inside the first test, `if (!(7 & (t = obj.unknown1A)))` (sub_0806CFEC).

## Known blockers

- A non-void function that falls off the end and returns its argument in r0
  is rejected by the strict return-type check (lean_a: sub_0801A6EC,
  sub_08015390).
- Draft symbols such as `D_030018F8`, `gTransferByte_03001860` or
  `gUnknown_030018D2` inside 0x03001800..0x030019FF are `gCounter6ED08_03001800`
  fields: write `gCounter6ED08_03001800.flagsF8` (include/battle_work.h). The
  struct field changes register allocation even where the literal is the same
  (lean_b: sub_0802B258, sub_0802A824). Likewise `gUnknown_083B62xx` command
  pointers are `gState0NextCommands_083B6100[n]`.
- A second counter the reference increments before the loop counter (`adds r5,#1; adds r4,#1`,
  initialised after the hoisted invariants) was an expression of the counter, `f(i + 2)` or
  `f(i * 2 + 4)`, reduced to a giv; a separate `x++` variable changed hoisting (lean_a:
  sub_0800B174, sub_08017EA8).
- Draft symbols inside 0x03000440..0x03000579 (`gUnknown_030004C4`, `D_03000555`) are
  `gState0TypedWork.bytes[off]`; the union access changed hoisting and temp registers
  (lean_a: sub_08017734, sub_08017EA8).
- A switch whose cases share one body compiles to a compare chain; the
  reference's jump table needs each case written with its own (identical)
  statements, merged later by cross-jumping (lean_b: sub_080378F0).
  Likewise `x == 0 || x == 1` becomes `x <= 1`; the reference's two compares
  came from `if (x == 0) goto both; if (x == 1) { both: ... }`
  (lean_b: sub_08033B7C, sub_08033D30).

## Link/menu handlers (lean_c round 4)

- `movs rK,#0; cmp; bne; movs rK,#4` then `adds base,#0xa; adds rK,base` came from the store-flag index `gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1]`, not an explicit 0/4 offset (sub_08066280, sub_08063FB0).
- `ldrb` of the 16-bit `gRepeatedKeys` in key tests came from `0x40 & (u8)gRepeatedKeys` (sub_08066280, sub_08061338).
- An `adds rX,rY,#0` copy right after a load (root base copied to a callee-saved register, or a byte compared through a copy) came from re-reading the same field/global instead of a cached local, e.g. `gFrameObjects[i].unknown1A` in each test, `ctx->cursor05 != 0 ? ctx->cursor05 - 1 : 4` (sub_0806B248, sub_08066280).

- A comparison temp assigned inside the condition, `(value >> 8) == (low = value & 0xFF)`, moved the
  `movs #0xFF` after the shift (found by tools/permute.py, sub_0800FDD8).
- A pointer computed from a base loaded first (`ldr rB,=gX` before the index math, then `adds rI,rB`)
  also applies to non-frame bases: block-scoped `u32 root = (u32)gSetupBuffer_03000590;` (sub_080173B4) and
  `(... + 0x18 + root)` for gInventoryRecords (sub_0800AD58).
- Values from a table passed later as call arguments stayed in low registers only as `u32` locals;
  `u8 x = table[i]` moved them to high registers (sub_080183A4).
- A field read twice instead of a `u8 flags` local avoided the in-place `ands` on the dying register
  (`movs r0,#0x40; ands r0,r1` in the reference) (near-miss sub_0800A1E4, 13 -> 9 rows).
- A constant reused in a later compare as `lsls/lsrs #16` of the OR operand register came from a `u16` comparison temp (`u16 mask = w0 & 0xC000; if (mask == 0x4000 ...)`) (sub_08063254).
- `(u8)(field += 8) > 0x40` kept one hoisted `movs rK,#0xFF` used by a later `ands` test (sub_0806CB28).

## Switch trees and pointer pseudos (lean_a round 5, near-miss evidence)

- A three-case switch on 1/2/3 whose tree is rooted at 1 (`cmp #1; beq; cmp #1; ble default; cmp #2 ...`)
  had a `case 0:` sharing the default body (`case 0: default:`); without it gcc roots the tree at 2
  (sub_08001520 table selector, 3 rows fixed).
- `doubleBits = (0x20 & flags) ? 0x300 : 0x100;` gave the reference "and, store 0x100, branch, store 0x300"
  order on a spilled local; an if-statement stored first (sub_08001520).
- Spill slots are assigned in pseudo (declaration) order: declaring the spilled locals first, in reference
  slot order, reproduced the whole sp+0x210..0x22C layout (sub_08001520).
- `order[count].field = ...; count++;` (giv) put the pointer init after hoisted constants; an explicit
  `entry++` pointer did not (sub_08001520).
- A walking source pointer the reference keeps in a fresh register (here `ip`) while the parameter is
  copied elsewhere was a separate local `src = source + 6`, not `source += 6`; reusing one `s32 n` for
  the packed word, the length and the copy counter fixed the remaining pressure (LeDecompressVram,
  300 -> 21 rows; LeDecompressBytes 34 -> 33 rows).


## Selecting the function for local searches

The wrapper/declaration tools use the selected definition's balanced outer
body, through c_source.function_body_lines. The former last-opening-brace
heuristic searched the final nested block in Allman-style LeDecompressBytes,
and could select a later function. Formatting alone must not narrow the
search scope. Comments and string/character literals do not delimit C blocks.

A do/while(0) scope around a single literal store can affect agbcc register
allocation even when the store has no declarations: wrapping the first of
three case-3 byte stores solves LeDecompressBytes (264 bytes, only
-fprologue-bugfix). The byte copy and pointer increments remain sequenced.


## Fixed-length reads across encoded labels

Some label callers use a fixed byte count even when FE ends a label sooner
(08011F50 copies18 bytes; 08011FA0 copies11). Individual C string objects
would make reads into the next string undefined. A contiguous text-and-root
aggregate with roots initialized from a character view of the entire object
preserves those original reads, including a final label's overlap into pointer
data. Keep the native encoded bytes and terminator; do not infer ASCII or
truncate the copy. encoded_labels.h records three independently bounded banks.


An explicit blank local assigned zero before the character test in each loop
iteration can put its hoisted zero before a hoisted font-base literal. Merely
wrapping the else-store or changing declaration order did not fix that order.
This resolves the final two rows in080674BC (104 bytes, only
-fprologue-bugfix). Integer byte-cursor updates avoid before-string pointer
arithmetic, and font indices are expressed within the full mapped VRAM span.

## Large-function experiments (lean_c round 5, near-miss evidence only)

None of these produced a full match; they are row reductions measured with
tools/try_draft.py and small agbcc probes, recorded so the next attempt starts
from them. Drafts: build/lc4/ in the lean_c worktree.

- Script-interpreter program counters: `S.pc += 2; ... script[S.pc]; S.pc++; ...`
  makes CSE fold every later index to `old + k` (`adds rX, rOld, #3`). The
  reference's single incrementing register (`adds rK, #2; str; ... adds rK, #1; str`)
  came from two statements `S.pc++; S.pc++;` followed by `S.pc++; x = script[S.pc];`
  per operand (statement order: the store of pc precedes the field address).
  `x = script[++S.pc]` computes the destination address first (sub_0805424C).
- agbcc -O2 uses type-based aliasing: an `int` field store forces later `int`
  fields of another struct to be reloaded, a `long` field store does not
  (probe: `struct A { long x; }` vs `struct S { int pc; }`). Which reloads the
  reference performs therefore constrains the declared field types; in
  sub_0805424C the savedPc/depth/savedActor arrays behave as one type and
  pc/actor/when/target/pending as another. A `u8` store still reloads every
  scalar, and the reference does not reload pc after the actor `objects[]`
  byte stores there, which remains unexplained.
- A function-scope index variable reused as the actor index in many switch cases
  got the reference's single callee-saved register (r7); block-local copies were
  spilled or given scratch registers (sub_0805424C, 3500 -> 2000 rows).
- Eight repeated frame-object blocks: a `static inline` helper taking the object
  index, offsets, frame and parameter reproduced the shared constant register
  (`movs rK, #1; mov sl, rK`) and block shape (sub_08059960, 755 -> 475 rows).
- An object index assigned in both arms of a switch (`objIndex = count + 0x31`
  in the case and in `default:`) is not a giv; a block-local `obj = count + 0x31`
  became a strength-reduced `&gFrameObjects[0x31]` pointer spilled to the stack
  (sub_080513C8, frame size then matched, 378 -> 297 rows).

## Record display and scroll handlers (lean_a round 7)

- A table base the reference loads late (`ldr r6,=gRecordDisplayData; adds r0,r0,r6` right
  before the store) while the parameter registers look as if one more value were live came
  from an initialized local at entry, `u32 data = (u32)gRecordDisplayData;`, used once as
  `(u8 *)(index * 0x410 + data)`; with no free callee-saved register the local gets no hard
  register and reload rematerializes the constant at the use. Together with a late
  `s16 h; ... h = height;` before the store this matched sub_08044934 (u8/u16 parameters in
  the header). In the 12-parameter siblings sub_080446B4/sub_080447EC the same source makes
  the whole prologue match but the local finds `sl` free and is loaded at entry.
- `(delta + 0x188) - value` (reference `adds r0,r4,r3; subs r4,r0,r1`) came from
  `delta + (0x188 - value)`; `delta + 0x188 - value` folds into the compare's CSE'd
  `value - 0x188`, and `delta - value + 0x188` subtracts first. Likewise
  `delta + (value - 0x168)` gives `(delta - 0x168) + value` (sub_0803C33C/sub_0803C0CC, near-miss).
- A u16 sum zero-extended in place (`lsls r2,r2,#16; lsrs r2,r2,#16`) followed by `lsrs r3,r2,#8`
  needed an `s32 full = seed;` copy and `u8 high = full >> 8`; with u32 temps combine folds the
  extension into `lsls #16; lsrs #24`. A `u16 shifted = low << 8;` temp placed before `high`
  reproduced the reference order (sub_080424B8, 10 -> 2 rows).
- A fresh literal for a pointer the reference reuses after a loop (`ldr r2,=gFrameObjects` inside
  the loop while addresses use the hoisted base) is not reproduced by `root = (u32)gFrameObjects`
  (CSE copies the hoisted register). An asm-label alias gives identical code but a second
  literal-pool word (sub_08022B40, near-miss at 2 rows).
  Solved (lean_a round 8): every in-loop address uses a separate base local set in the for-init
  (`for (i = 0, base = (u32)gFrameObjects; ...)`, `((0x21 + i) << 6) + base`), so the loop block
  holds no symbol load for CSE to reuse and `root = (u32)gFrameObjects` gets its own `ldr`. The
  literal comes after the `lsls/lsrs #24` compare extension only when the incremented byte goes
  through temporaries first: `u32 count = p->c + 1; p->c = count; u8 count8 = count; root = ...;
  if (count8 > 0x5A) { if (count & 1) ...`. Byte reads of the base after the loop stay as
  `*(u8 *)(root + 0x849)`; a struct index folds the offset into `movs; lsls`.

## Lean_a round 8 near-miss evidence

- sub_0803C33C / sub_0803C0CC (60 -> 26 / 59 -> 24 rows): `u8 shift` (not s8) removes the
  `lsls/asrs` before `delta >> shift`. Three different object pointers fix most rotation: the
  entry object, a separate `other` re-taken in branch 1 after the call, and a third in branch 2
  (branch 2's pre-call `delta = object->screenX` still reads the entry object). A separate
  `value1` for branch 1 and `delta + (value - 0x168)` in branch 2 helped. With the 0x188 compare
  constant in r3, reload turns the later 0x1FF load into `adds r3, #0x77` and the cross-jump
  point matches the reference. Remaining: branch-1 `other`/`value1` take r1/r2 where the
  reference has r2/r1. try_decls and try_wraps found nothing more. Drafts: build/la8/c33c_c.c and
  c0cc_c.c in the lean_a worktree.
- sub_08030780 (8 -> 7 rows): `u16 *word = &gState0TypedWork.widths.word86;` after the busy
  read gives the reference base copy (`adds r2, r0, #0`); the reference still adds 0x86 at the
  use.
- sub_080424B8 stays at 2 rows. `u32 low = full & 0xFF` gives the reference `movs #0xff; ands`,
  but `high ^ low` then overwrites the dying `low` instead of copying `high`. About 200 type and
  expression variants did not change this.
## Late-range batch (lean_b round 7)

All verified by a full byte match except where marked as a near-miss.

- Palette fades `dest[i] = f(src[i])` (the sub_08068CC8 form, destination
  written with the source read inline): the sibling sub_08068A84 matched with
  the same C once the source pointer was read through a pointer to the global,
  `u16 **source = &gUnknown_0300002C; ... (*source)[i]` (found by
  tools/permute.py). sub_08072080 did not move (7 rows).
- A sum the reference keeps in r0 and copies (`adds r0, r5, r0; adds r1, r0, #0;
  subs r1, #0x24`) came from a function-scope `s32 key` shared by two switch
  cases plus a separate `s32 sum`: `sum = note + (s8)t; key = sum - 0x24;`
  (sub_08072910). Block-local `key` coalesced the two.
- `lsls rX, rT, #24` hoisted before a compare, then `lsrs #26` / `lsrs #25` in
  each arm came from `(u8)(field >> 2)` and `(u8)(field >> 1)` on u8 fields;
  `field / 4` or `field >> 2` gives a plain `lsrs`. `a - (b - 20)` is folded to
  `(a - b) + 20` unless both terms are locals: `s32 a = ...; s32 d = ... - 0x14;
  f(a - d)` (sub_08066D8C).
- Fields read into `s16` locals let combine sink each sign-extending load into
  its use (interleaved with the multiplies); `s32 px = p->x` keeps the three
  loads grouped before the products (sub_08066D8C).
- `b += (a - b) / 16` evaluates `&b` first; `b = (a - b) / 16 + b` gives the
  reference order (load a's address first, reload b with `ldrh` before the add)
  (sub_08066D8C).
- A u8 argument masked with a hoisted `0xFF` register (`mov rK, sb; ands`) came
  from an explicit `& 0xFF` with the callee declared `u32`; a `u8` prototype
  gives `lsls/lsrs` pairs. Likewise `(++c & 0xFF) == 0` on a u16 field needs
  `c = f + 1; f = c; if ((c & 0xFF) == 0)` with `u16 c` to keep the `ands` with
  a reused 0xFF register (sub_08066D8C).
- `t = D; t = 0x7800 - t;` loads `D` straight into `t`'s register
  (`ldrh r2, [r0]; subs r2, r7, r2`); `v = x * 15; v *= 8; v = t - v;` reproduced
  the multiply temporaries, and a do-while(0) around the two stores (try_wraps)
  finished sub_0806D4A4.
- Byte records copied from a struct offset that is not a multiple of four
  (`gCounter6ED08_03001800 + 0x8F`, four bytes per record): a row view
  `((u8 (*)[4])&g.pad8C[3])[i][k]` keeps `base + 0x8F + (i << 2)` per access,
  where `pad8C[i * 4 + 3 + k]` became one strength-reduced pointer. A record
  pointer loaded and then advanced in place (`ldr r6, [r0]; adds r6, #4`) is
  `p = table[n]; p += 4;`, not `p = table[n] + 4;` (sub_08068F50).
- Four tilemap stores whose literal register survives (`ldr r1, =0x06000286;
  adds r3, r0, r1; ... adds r1, #2`) came from one reused `u16 *cell` variable
  (`cell = (u16 *)(block + 0x06000286); *cell = tile; cell = ...`); direct
  `*(u16 *)(block + K) = v` stores overwrite the literal register and reload
  each constant (near-miss sub_08067D00, 23 -> 17 rows).
- A switch rooted at case 1 (`cmp #1; beq; cmp #1; bgt; b default`) again came
  from an explicit `case 0: default: break;` (near-miss sub_0806C3A0).
- tools/permute.py cannot parse `asm("symbol")` declarations. For the permuter
  run, replace each view with a macro, e.g.
  `#define gView (*(struct View **)&gMainContextPointer_03006F74)`; this kept the
  same code for four of five drafts (sub_08067F64 changed, 108 -> 118 rows).
- A value chosen per switch case and stored by each case (`movs r3, #0xb; cmp;
  bgt; movs r3, #0xa; ...; strh r3`) needed a block-local variable in every case
  (`case 0: { s32 frame = 0xB; if (t <= 7) frame = 0xA; obj.f = frame; break; }`);
  one function-scope `frame` swapped the base and value registers
  (sub_0806CEDC, 20 -> 0 rows, starting from lean_c's plain `gFrameObjects[n]`
  draft; struct-pointer or `u32 root` views fold the offsets into a 0x800
  anchor instead of the reference's per-field literals).
- An if/else-if chain on `3 & byte` (`cmp #1; bne; ...; cmp #2; bne`) is not a
  switch: a switch statement reorders the tests (sub_0806BFEC).
- A tail shared by two branches and placed after the second one (the first
  branch jumps into the middle of the second's tail, the code after the if/else
  stays after the else block) came from writing the whole tail in both branches
  (`if (sound) play(sound); refresh();`) and letting cross-jumping merge it. A
  `goto` into the second branch makes jump.c move the else block to the end
  instead. Paths that skip part of the tail were `goto label;` to a label inside
  each copy, not `sound = 0` (sub_08065208, 77 -> 3 rows).
- `x - (a - 0x10)` and `x + (a - 0x10)` are reassociated by fold (the sum gets
  CSE'd with `x - 0x10` elsewhere and costs a register); an `(s16)` cast on the
  inner difference keeps the reference order (near-miss sub_0806D138).
- `map[i] = table[(*frame + i) & 0xFF]; map[i] = (map[i] & 3) + 0xF1FC;` (two
  statements through the destination) reproduced the reference loop registers
  in sub_08068460/sub_08068684, where one combined expression gave a different
  allocation (permuter, 65 -> 39 rows; both functions share this case).
- Register copies the reference makes after a call (`adds r3, r6, #0` of the
  loop index, the root base reused from r4) came from explicit copies,
  `s32 k = index; u32 base = root;`, used by the later access
  `((struct FrameObject *)((k << 6) + base))->value32++` inside a do-while(0)
  (sub_08071804, goto loop + block-scoped root; last step found by
  tools/permute.py).
## Later display builders (lean_c round 6, near-miss evidence)

Row reductions measured with tools/try_draft.py on sub_080460B0 (1,288 B, now 6
rows), sub_080465B8 (1,192 B) and sub_08046D1C (1,256 B); drafts in docs/drafts/.

- Type-based aliasing decides whether a pointer loaded from a struct is reused
  after a store. A store through a field of a struct that contains `u8` members
  (alias set with a char child) conflicts with every load, so the reference
  reloaded `work->render` after each affine store; writing the same store as
  `((u16 *)work->render->unknownF8C)[k]` (alias set of `u16`) let CSE keep
  `render` in a register and cost a spill slot. A view struct with a real
  `u16 affine[]` field reproduced the frame (sub_080465B8, 0x50 -> 0x4C).
- `0x160 + 0x140` style adds kept unfolded (`movs r3,#0x160; movs r2,#0x140;
  adds`) came from a `u16 base = 0x160;` local; the reference's placement of the
  constant (rebuilt per call instead of held in sl) needed the assignment between
  the template struct copies (found by tools/permute.py, sub_080460B0).
- An `asrs rX, rK, #16` at the call with `rK = 0x320000` built earlier came from
  an `s16 priority = 0x32;` local passed to an int parameter (sub_080460B0).
- A local fill word placed below an address-taken `u16` parameter: `volatile u32
  fill` (the non-volatile local landed above it).
- Scalars whose address is taken get their frame slot at the first `&`; arrays
  at their declaration. Declaring `u32 list[32]` inside the block that uses it put
  the earlier `&tileBase` scalar at sp+0x10 below it (sub_08046D1C).
- `(flags & ~2) | 4 | 8` folds to one `orrs #0xC`; the reference's two `orrs`
  came from `f = extra->flags; f &= ~2; f |= 4; f |= 8; extra->flags = f;`.
- Command-table loops `for (k = 0; table[i][k] & 0x3F; k++)` with element
  indices let loop.c eliminate the biv into a `k * 4` giv (`movs r1,#4; add r8,r1`)
  and hoist the table base into sb before `k = 0`; byte-offset loops
  (`k += 4`) built different givs. Byte arithmetic `(const u8 *)T + k * 4 + i * 16`
  gave the reference operand order `adds rI, rK, rRow`; `&T[i][k]` gave
  `adds rI, rRow, rK`.
- Recursive callers that sign-extend narrow arguments (`asrs` before the
  recursive call) mean the definition takes full-width parameters narrowed into
  `u8`/`s16`/`u16` locals; this compiles exactly like a K&R definition and keeps
  tools that parse ANSI definitions working (sub_080465B8).
- A frame-relative struct the reference re-addresses after a call (`mov r1, sp; movs r2, #0x1a;
  ldrsh r0, [r1, r2]` for `matrix.pb` after `ObjAffineSet(&input, &matrix, ...)`) while ours
  reused the call's `&matrix` register: an `s16` temporary in a later store of the same struct
  (`affine[++k] = (pd = matrix.pd);`, found by tools/permute.py) stopped the CSE (sub_080465B8).
- A byte loaded late from an address register (`ldrb r4, [r4]` after the other call
  arguments) moved earlier, with the address in a scratch register, when read through
  `u32 b2 = *addr;` before the call; this still reduced sub_080460B0 from 8 to 6 rows, so
  the temporary is not the whole explanation.

## Division libcalls and constant arguments (lean_b round 8)

- `sub_0807CD2C`, `sub_0807CDF8`, `sub_0807CEC8` and `sub_0807CF40` are
  `__divsi3`, `__modsi3`, `__udivsi3` and `__umodsi3`. Drafts call them as
  functions; the `/` and `%` operators instead emit const libcalls
  (`call_insn/u`), which neither clobber memory for CSE/GCSE nor force
  argument evaluation order. `step % div == 0` and `table[step / div]` on the
  globals themselves matched sub_08068BC4 directly (global read once and kept
  across the four libcalls, divisor reread after each volatile DMA store),
  where explicit calls needed temporaries and still loaded the arguments in the
  wrong order. Use explicit calls only when the reference recomputes after
  memory could change (sub_0805A3A4 shape).
- A quotient truncated in a compare but used raw in the store (`lsls/lsrs` into a
  new register while the libcall result stays live) came from writing the
  division twice as an operator: `if ((u8)(L / 10u) * b + b > 100) s = 100; else
  s = b + (L / 10u) * b;`. The const libcall is CSE'd, the truncation is not
  (sub_08041D70; a `u8 t` temporary merges both sums instead).
- A constant base the reference keeps in a caller-saved register across a loop
  and reloads only at one join (`ldr r2, =gFrameObjects` after the `next:`
  label) is a variable with two definitions, which GCSE cprop cannot replace:
  `root = gFrameObjects;` before the loop and `root = <alias of
  gFrameObjects>;` at the join (sub_0806C3A0, 136 -> 4 rows).
- The same `%` form fixed the swap-loop shape of sub_08068460/sub_08068684
  (`for` loop, `j = rand[(frame + i) & 0xFF] % (16 - i) + i`); an explicit
  call there costs 12 bytes. Because the libcall does not kill memory, GCSE PRE
  can hoist every repeated literal (array base, `&gFrameCounter`) to the start
  of the case; which of them then gets a high register decides the remaining rows.
- A constant argument the reference builds in its own callee-saved register
  (`movs r6, #4; str r6, [sp]`, while every other call reuses `r4 = 4`) came
  from a variable assigned twice in one block: `do { ...; i = 4; f(..., i);
  i = 0; } while (0);` before the `for (i = 0; ...)` loop (sub_08069CC0, found
  by tools/try_wraps.py). Without the second assignment CSE replaces `i` with
  the shared constant register.
- Operator forms also matched sub_0806BB64 (`rand[(frame + i) & 0xFF] % 3u` and
  `% 7u`: the hoisted `&gFrameCounter`/table registers come back once the call
  is a const libcall; per-case `lanes[i] = lanes[i - 1] != 0 ? lanes[i - 1] - 1 : 1`
  ternaries give the reference's dest-address-first order and double byte load)
  and sub_0806D138 (`table[k * 4] / obj.commandOffset`, 99 -> 45 rows at once).
- A frame-object base the reference copies before a test (`adds r1, r5, #0`) and
  then uses for one store at a join came from `objs = gFrameObjects;` assigned in
  both branches and `objs[0x20].field = frame;` after them; the copy also stops
  jump threading of a repeated `0x10 & t` test and cross-jumping with another
  store tail. Values picked by `(t & 8) ? 8 : 7` set the constant after the
  `ands` (sub_0806D138).
- Three-loop pointer walkers (`stm r6!`, `ldm r7!`, `stm r4!`) whose registers are
  shared between loops were the same C variables reused: loop 1 walks `next`, loop 2
  uses `src`/`next`/`dst`, loop 3 walks `dst` again (sub_080668D4; separate `p`
  walkers swapped r4/r6).
## Main2 setup handlers (lean_a round 9)

- A symbol base the reference reloads per use (`ldr rX,=0x02023002` in each block, or a
  sort-table literal kept inside a loop) while another base is hoisted came from a
  constant-integer pointer, `((u8 *)0x02023000)[((u8 *)0x02023000)[0x78] + 2]`; the
  symbol form `gObjectSortBytes[...]` is CSE'd/hoisted (sub_08061CE0 full match; near-miss
  sub_08062614, where the same change moved the hoisted pair to {records, halfword table}).
- A constant pointer the reference hoists into a callee-saved register before a loop
  (`movs r6,#0x81; lsls r6,#0x12`) was a pointer variable set in the for-init,
  `for (i = 0, records = (struct R *)0x02040000; ...)`; a plain constant expression in the
  body is rematerialized per iteration (near-miss sub_08062614, 28 -> 10 rows).
- `do { i = 0; next = frame + 2; base = 0x0600D800; dest = 0x1C0; } while (0);` before a
  goto loop fixed the r7/r8 roles of base and next (sub_08062C98 full match, found by
  tools/try_wraps.py plus a statement-order sweep inside the wrap).
- `movs r5,#1` at entry with `lsls r7,r5,#14` repeated on several edges before a VRAM
  address (`0x06000000 + 0x4000`) came from `u32 block = 1;` at entry and
  `(block << 14) + 0x06000000` uses (near-miss sub_08060708, 25 -> 8 rows); same family as
  the `palette = 0xD; block = 0x1E;` entry locals above.
- An OR constant loaded as literal `0xFFFFC000` and copied (`ldr r3,=0xFFFFC000; adds r0,r3,#0;
  orrs`) before `lsls #16` came from `s16 tile = (s16)(x) | (s16)0xC000;`; `| 0xC000`,
  `| -0x4000` and `| ~0x3FFF` fold to a positive 0xC000 (near-miss sub_08060BE4).
- The `u8 c % 26` / `c / 26` operators pick `__umodsi3`/`__udivsi3` but drop the
  `lsls/lsrs #24` after each call that the reference keeps (gcc knows the result range);
  sub_0805E334's reference truncates both results, so there the libcalls are explicit
  `u8` calls (near-miss).
- A tilemap literal the reference keeps in a callee-saved register and advances with
  `adds r6,#0x40` for a later cell (`0x060000C6` then `0x06000106`) came from a `u32 cell`
  variable used as `offset + cell`, then `cell += 0x40;`. Assigning `cell = 0x060000C6`
  before the enclosing if (after the preceding frame-object loop) fixed the function-wide
  register roles, but CSE then folds `cell + 0x40` into a fresh literal (near-miss
  sub_0805E478, 10 -> 4 rows; tools/permute.py first found `halfword36 = (cell = ...)`).
- A u16 field cached in a callee-saved register, compared through `lsls/lsrs #16` and
  incremented into a scratch register (`adds r0, r6, #1; strh r0`) came from re-reading the
  field in every expression, `if ((u16)obj.unknown1A < 0x78)` and
  `obj.unknown1A = obj.unknown1A + 1`, with no local (sub_0805FF1C, found by tools/permute.py
  from a two-row draft; `/ 0x78` operators replace the explicit __divsi3 calls).
## Record display and sine-wave handlers (lean_b round 9)

- A stack parameter the reference loads at function entry (`ldr r3, [sp, #0x38]` before
  the first branch, used only in one late arm) was modified in the source: `y -= dy;`
  and then `y << 8` at the call. An unmodified stack parameter keeps its memory
  equivalence and is loaded at the use (sub_08046A60, 98 -> 41 rows; `x -= dx` likewise
  for the second coordinate, 37 -> 23).
- `ldr r2,[cmd]; lsls r2,#26` kept once, then `lsrs r0,r2,#24` for each table index and
  `lsrs r2,r2,#26` for the selector: three index expressions that CSE does not recognise
  as equal but combine folds to the same shift. `c >> 26`, `(u8)(c >> 26)` and
  `(c >> 26) & 0x3F` are all CSE'd; `(s32)c >> 26 & 0x3F` and `(s32)(c >> 1) >> 25` are
  not (sub_08046A60; source form of the original unknown).
- The `struct LaterCmd` bitfield loop of sub_080460B0 (`for (k = 0; T[i][k].count; k++)
  if (!T[i][k].flag) ...`, no outer `if`) also matched both command loops of
  sub_08046A60 where byte-offset loops (`k += 4`) left `adds r4, r5, r1` operand-order rows.
- `ldr r0,=gPtr; ldr r1,[r0]; <slot*48>; adds r0, r0, r1` (base loaded before the index)
  came from repeating the full `((struct X *)gPtr)[slot].field` expression in each
  statement; an `extra` pointer local loads the base after the index (sub_08046A60).
- A stack parameter loaded into a low register at entry *and* copied to a frame slot
  (`ldr r7, [sp, #0xf4]; str r7, [sp, #0x9c]`) is two variables: the parameter (r7) and
  a local copy (`u32 index = slot;`, spilled). When r7 is later overwritten by a field
  load (`ldr r7, [r0, #0x28]`), the source reassigned the parameter itself
  (`slot = extra[index].slot;`) and kept using the copy for indexing (sub_08046D1C,
  132 -> 72 rows; the sub_080460B0/sub_08046A60 `struct LaterCmd` loops without
  `if`/`do`-wrappers then matched exactly).
- Explicit `sub_0807CD2C(x, divisor)` calls replaced by `x / divisor` with a local
  `divisor = 0x400` (expanded before constant propagation, so it stays a `__divsi3`
  libcall with the divisor in a callee-saved register): the const libcall lets GCSE keep
  `gSineTable` and `&gMainContextPointer_03006F74` in sb/sl, inserted as copies right
  after their first use (`mov sl, r4; mov sb, r2` before the first compare). With the
  explicit calls the literals are reloaded per block (sub_0805B614, 159 -> 31 rows).
- A store whose object address the reference computes before the call (`adds r4, r5,
  #0xc0` in both arms, `strh r0, [r4, #4]` at the join) came from a per-arm pointer,
  `{ struct FrameObject *p = &objects[3]; p->screenY = center + f(...); }`, used only for
  objects 3..7; objects 1..2 (offsets below 0x80) were plain `objects[n].screenY` stores.
  The same pointer took the last callee-saved register and pushed `done` to the stack
  as in the reference (sub_0805B614).
- Values the reference computes into consecutive stack words from one register
  (`str r0,[sp]; adds r1,r0,r2; str r1,[sp,#4]` ...) with literals rotating through r2/r3
  were a local array `s32 angles[8]`; scalars got registers (sub_0805B614).

## Large-function near-miss evidence (lean_e, 20 October)

Row reductions measured with tools/try_draft.py; drafts in docs/drafts/.

- A constant the reference rebuilds for a second compare (`movs r0,#0xa8; lsls #1`
  for 0x150 after `movs r0,#0x80; lsls #1` for 0x100) where ours derived it from the
  first (`adds r0,#0x50`) came from two separate `if` statements with duplicated bodies
  instead of `a > 0x100 || b > 0x150`; cross-jumping merges the bodies again
  (sub_08001520, one row). The `adds rK,#delta` form looks like reload's move2add rewrite, which
  needs the same hard register to hold the previous constant; if so it is a register
  allocation symptom: sub_08061F00's reposition stores (0x204/0x2C4/0x304 in
  r5/r4/r5 in the reference, r4/r4 in ours) show the same pattern.
- A table at a constant address read as `[rB,#4]`, `[rB,#0xc]`, `[rB,#0x14]` from one
  `movs rB,#0x81; lsls #0x12` base, with `adds rB,#4` before a variable index, came from
  an array inside a struct: `#define RECORDS (((struct T *)0x02040000)->r)`,
  `RECORDS[k].value`. A plain `((struct R *)0x02040000)[k].value`, a const pointer or a
  pointer-to-array cast folds every element into its own literal (sub_08061F00,
  288 -> 242 rows).
- `value / 10` and `value % 10` as operators on an `s32` local (loaded from a byte) gave
  the reference `__divsi3`/`__modsi3` with no result truncation; a `u8` local gives
  `__udivsi3` plus `lsls/lsrs`. Writing the libcall inside the store expression,
  `(ctx->base + value % 10 * 2) | 0x7000`, loaded the context pointer before the call as
  in the reference; a separate `digit = ...;` statement loads it after (sub_080639C4,
  110 -> 84 rows). The reference also computes each tilemap address before that call:
  that is the plain store `*(u16 *)(addr) = (... value / 10 ...) | 0x7000;` (gcc expands
  the destination address first). A `map = addr; *map = ...;` temporary gave the same
  instruction order but a different register allocation for the whole branch, frame
  and saved registers (79 -> 25 rows).
- `if (x == 0) ...; x--;` on a struct byte, with the shared `sub(2); goto out;` tail
  written in both the up and down branches, gave the reference single `strb` through the
  cached context pointer (cross-jumped); a `u8 row` local adds `lsls/lsrs` and a pointer
  reload (sub_08061F00).
- A context pointer loaded once per loop iteration and reused after an if/else for
  `ctx->total += add` came from `ctx = gCtx;` at the top of the loop body (sub_08061F00).
- In sub_08001520 the reference's two OAM givs (`&gOamShadow[k]` in r8 and `k * 8` in a
  stack slot) and its 0x238 frame appear when the attr0/attr1 stores go through a
  block-scoped `struct OamEntry *shadow = gOamShadow;` declared at the top of the inner
  loop body (`shadow[oamIndex].attr0 = ...`): loop.c hoists the symbol load and reduces
  the address giv. The rest of the function then allocates differently (312 rows
  against 271), so this is not yet in the draft.
- A reference `ldr rK, =0xFFFC; adds r0, rK, #0; ldrh r2, [..]; adds r0, r0, r2` (the
  16-bit constant reloaded into the result register before the other operand is loaded)
  comes from the constant written inline, `obj->x = 0xFFFC + anchor->x + i * 8;`.
  A `u16 adj = -4; ... adj + anchor->x` local is propagated by CSE into a pseudo and
  gives `ldrh; ldr; adds` instead (sub_0801A33C/sub_0801A418, 16 -> 2 rows). The last 2
  rows there were the loop-preheader order of the `i * 8` giv init: an `s32 flags =
  0xC224;` local set before the loop and stored as `obj->flags = flags` fixed it
  (found by the permuter).
- Loops whose first statement is `if (text[i] == 0xFE) break;` get that test copied to
  the loop entry and bottom (jump.c exit-test duplication); `return` instead of `break`
  (when nothing follows the loop) keeps the single test at the loop top as in
  sub_0801A33C and sub_080368C4.
- `(s16)x` sign extensions that the reference repeats inside a loop (or keeps although
  the result is masked with `& 0x1FF`) survive when the sum is a separate statement:
  `{ s32 t = (s16)x; t += table[k]; f->screenX = t & 0x1FF; }` (sub_08036C20 matched with
  `D[k = path * 2] + (s16)x`).
- When the reference loop keeps two pointer givs for one object (`&obj` and `&obj + 0x23`,
  both including `gFrameObjects`), every store is written as
  `gFrameObjects[first + i].field = ...`; a `f = &gFrameObjects[first + i]` pointer gives one
  giv and recomputes `f + 0x23` (sub_080368C4/sub_080369C8, 48 -> 0 rows with the
  inline-constant fix above).
- Hoisted loop constants that the reference sets *after* the strength-reduced pointer
  inits (sub_0806F9D8, `0x7C00` after `&pal[0]`/`buf`) come from explicit `src`/`dst`
  pointers and mask locals all initialised in the for-init, in the reference order
  (`for (i = 0, red = 0x1F, green = 0x3E0, src = pal, dst = buf, blue = 0x7C00; ...)`);
  loop.c puts its own movables and giv inits before the loop, after any user init.
- Under `-fno-regmove`, `*(vu16 *)REG &= 0xFFEF` ties the result to the loaded value
  (`ldrh r0; ldr r1,=C; ands r0,r1`). The reference form `ldrh r1; ldr r0,=C; ands r0,r1`
  came from `{ s32 v = *REG; s32 m = 0xFFEF; m &= v; *REG = m; }` (sub_0806F9D8).
- A two-case `switch` whose dispatch is `cmp #1; beq; cmp #1; bgt; b default; cmp #2;
  beq; b default` has a third case label sharing the default body (`case 0: default:`);
  without it agbcc emits `cmp #1; beq; cmp #2; beq` with the default inline
  (sub_0804FE9C, 60 -> 29 rows).
- `ldr r0, =gState0NextCommands_083B6100; ldr r0, [r0, #k]` before the `lsls/lsrs #24` of
  the u8 index argument came from declaring the table without the second const,
  `extern const u8 *gState0NextCommands_083B6100[];`; `const u8 *const ...[]` loads it
  after the truncation (sub_08036784).
- A `do { ... } while (0)` spanning several switch cases (used for register allocation)
  reverses the block order of the cases inside it; write those cases in reverse source
  order to get the reference order back (sub_08019B40: cases 1B, 1D, 1C).
- `f->flags = flags; f->tableSelector = 0;` where the reference sets the zero after the
  copy of the high-register `flags` (`mov r7, sl; strh r7; movs r0, #0`) came from
  `*(u16 *)f = flags;` (sub_08036FF8, -fno-gcse).
- A flags value the reference keeps in a register and masks later
  (`orrs r2, r0; strh r2; ... ldr r0, =0xEFFF; ands r2, r0; strh r2`) came from
  `obj->flags = (...) | 0xC004; ... obj->flags &= 0xEFFF;` (CSE reuses the stored value
  across the other field stores); a `flags` local copies the 0xEFFF constant instead
  (near-miss sub_08019D9C).

## Reload-register rotation (lean_b round 10)

- agbcc allocates reload registers round-robin (`reload1.c`, `allocate_reload_reg`:
  `last_spill_reg` is reset per function and advanced after every reload). When the
  only residue is the low register used to move a constant or value into a high
  register or an invalid immediate (`movs r0,#0x1f; mov ip,r0`, `mov r2, r8; adds`,
  `movs r2,#0xc4; lsls r2,#0x16; adds`) and the reference's choices look like ours
  shifted by one step, the source has one reload more or fewer somewhere earlier,
  usually invisible in the output. `agbcc -dg` on the draft's `candidate.i` writes
  `candidate.i.greg`; reload insns there carry the highest UIDs, so the reload sequence
  can be compared with the reference's register choices.
- sub_0805BF14 matched by replacing `if (level > 0xF) level -= 0x10; else level = 0;`
  with `level = level > 0xF ? level - 0x10 : 0;` (identical instructions, one reload
  fewer); every other form left the three loop-invariant constants loaded through
  r2/r6/r0 instead of r0/r2/r6.
- sub_0805A6C8 (sibling of sub_0805A988) had the same one-step offset in row 1; the
  missing reload was the tile-map base: writing the first row's address like the second,
  `dst = (vu16 *)(block << 11) + (x + 0x03000000) + (y << 5)` with `block = 0x16`,
  makes combine fold `0x0600B000` into the add (a reload) where the `0x0600B000 + x`
  form kept it in a pseudo. Diagnosed by comparing `-dc` combine dumps of a u16-`x`
  variant (which matched apart from the narrowing) with the u8 draft.
- The one-step offset remains in the drafts for sub_0804FE9C and sub_0805B984.
- A dead variable reused for a later value (`u = (float)gSceneView.wordA0 / d;
  *outX = v * u; *outY = w * u;`, sub_08053C7C) kept the soft-float scale in the
  register the reference uses; a separate `k` spilled `outX` and `z`.
- A switch tree `cmp #1; beq; cmp #1; bgt; b default; cmp #2; beq` came from an extra
  `case 0:` sharing the default body (sub_0804FE9C draft).
- gcse PRE turns repeated literal-pool loads of a symbol address into one long-lived
  pseudo inserted at the dominating block (e.g. a switch case entry); when two such
  symbols compete for one high register, global-alloc keeps the one with the better
  refs/live-length ratio and the other is rematerialised as fresh `ldr =sym` at each use.
  If the reference keeps the other symbol in the register, address the losing table
  through its raw address in one place (`p = (u16 *)0x03000008; p[i] ...` for
  gTransferOffsets): a CONST_INT is not a pool load, so gcse no longer PREs it, and the
  minipool still shares the literal (sub_08068684, sub_08068460: gFrameCounter in sl).
- Spilled loop counters such as `k = 0x28` (+1 per iteration) and `obj = &base[0x28]`
  (+0x40) that the reference initialises *after* the base literal load are
  strength-reduction givs, not user variables: write `i + 0x28` / `gFrameObjects[0x28 + i]`
  and let loop.c create them; explicit `obj`/`k` loop variables put the base load after
  their inits (sub_0806C3A0). Passing `j = i + 0x28` (a dead store into a local) to the
  calls gave the reference's sl/stack priority between the givs.
- loop.c hoists constant loads out of a loop only while
  `threshold * savings * lifetime >= insn_count`; an extra RTL insn in the body can stop
  a constant from being hoisted. In sub_0805EA44's final loop
  `{ s16 sx = x; obj.screenX = sx; }` (same final code) stopped the palette constant 13
  from being hoisted, so r7 is no longer pushed (54 -> 45 rows).
- cse1 replaces a QImode constant store (`ctx->byte = 1`) by the low part of any wider
  register known to hold that constant in the same extended basic block (e.g. a
  `u32 block = 1` local), so the arm no longer cross-jumps with its `= 0` twin
  (sub_08060708, RTL dump).
- `mov r8, r0; mov r1, r8; cmp r1, #imm` right after a field load (the compare reads
  the high register again instead of the just-loaded r0) came from comparing the field
  directly and incrementing it in place (`if (!(work->index2E <= 0x27)) return 1; ...
  work->index2E++;`), with no `u8 count = work->index2E;` local: the local copy lets
  regmove/reload inherit r0 for the compare (sub_0806FDA4, found by tools/permute.py).
  (sub_08019D9C).
- A byte loaded into one register and copied for the test (`ldrb r5, [r0]; adds r1, r5, #0;
  movs r0, #0x80; ands r0, r1`) came from `offset = byte; b = offset; if (0x80 & b)
  offset = (u16)(b - 0x100);` with `u8 b` (a `u32 b` loads into the test register instead;
  sub_08019D9C).
- A slot record reached through a local pointer (`slot = base + index * 8; slot->f`) that
  the reference instead hoists into several registers (`rec+0x64` in sb, `rec+0x65` in r5,
  `rec+0x67` in sl, a second copy of `rec`, `rec+0x66` spilled) came from indexing the
  global view every time (`((struct View *)&gWork)->recs[index].f`): loop-invariant motion
  hoists each field address. The resulting pressure also spills a constant loop flag,
  which reload rematerialises at the latch as `movs r0, #1; cmp r0, #0; bne` (from
  `running = 1; do { ... } while (running);`; sub_0801BFB4).
- `adds r1, r1, r5; adds r0, r6, #0; adds r0, #0xb0; adds r1, r1, r0; ldrb; adds #1; strb`
  (the index register accumulates the address) came from `slot += off; { u32 q = (u32)root
  + 0xB0; slot += q; (*(u8 *)slot)++; }`; `root[0xB0 + off + slot]++` forms put the sum in
  the other register (sub_08018900).
- The scroll handlers sub_0803C0CC and sub_0803C33C (pointer in r2, value in r1, then
  `adds r1, r2, #0; adds r1, #0x29` before the final store) matched only when one `u32`
  scratch variable holds both the first branch's `(u16)value30` and, in the last scroll
  branch, the frame index (`temp = gState0TypedWork.bytes[0x12F];
  gFrameObjects[temp].screenX = ...`); a fresh index variable leaves 26 rows (found by the
  permuter on sub_0803C33C, then applied unchanged to sub_0803C0CC).
- Reload registers for constants (`movs rN,#0xB0; lsls rN,#2` before an add) are picked
  round-robin over the function's spill registers, starting after the last one used, and
  skipping registers live at that insn. One extra or missing reload earlier in insn order
  shifts every later choice by one register. Code that cross-jumping later merges
  still counts. sub_08061F00 went from 45 rows to a match when each `byte05` branch got its own
  `else { [11].flags &= 0xBFFF; [12].flags &= 0xBFFF; }`: the reference has a single
  copy, but the deleted first copy's reloads explain the reference's register sequence.
  A reference branch that jumps into the middle of another block's statement is the
  usual sign of this.
- The same holds for switch cases: sub_0804FE9C matched when `case 0: finished = 1; break;`
  was written as its own body before `case 1` (with a separate `default:` copy at the end)
  instead of `case 0: default:`. The early copy's reload shifts the rotation by one, then
  cross-jumping merges it with the default and drops the `cmp #0` test.
- A global base copied into a call-saved register at the end of the first test block
  (`adds r4, r1, #0` before the `cmp`) and used by both branches and the common tail is
  gcse PRE: it fires only when the expression is not recomputed in a join block. sub_08028130
  matched with the common tail statement (`counterAA++`) written in each branch; cross-jumping
  merges the two copies (and the preceding `movs r2,#0xff; bl`) again.
- An `offset + K` address whose constant is reloaded into a far register
  (`ldr r5,=0x06000246` after `ldr r5,[sp,#..]`) can be a local holding K that is set
  early, before calls, so global alloc spills it and reload rematerialises the
  REG_EQUIV constant at its use (sub_080639C4: `cell2 = 0x06000246;` before the medal
  calls).
- To make the ior result share the constant's register (`movs r2,#0xC0; lsls r2,#23;
  orrs r2,r0`), shift first into a temp, then `t = 0x60000000; t |= shifted; t >>= 16;`.
  The one-expression form ties the result to the shifted operand (sub_080639C4).
- sub_0804B2B0 (844 B) matched once the call arguments `gContinuedWork_030057E0.halfC4A >> 3`
  were written `halfC4A / 8` (u16 field): the unsigned division expands later than the
  shift, so the argument value no longer took a high register (ip/sb/r8 copies before the
  calls disappeared, 35 -> 0 rows). Worth one try wherever a shifted field argument is
  routed through a high register.
- sub_0804B008 matched with a real `struct` view of gContinuedWork_030057E0 (named fields
  at 0x7FE, 0xC28, 0xC48..0xC57, 0xC5C, 0xCBA) where a `u8 *work` local or byte-array
  indexing kept the base in a low register: the struct form leaves the base in r8, all uses
  reload it into r5, and the two compared bytes are spilled to the stack as in the
  reference (67 -> 0 rows).
- Constant folding into a struct-array base (`buf - 1` folded into `sym + 0x80F`, or the
  `- 1` moved onto another addend) is blocked by building the index in two statements,
  `s32 idx = y * w - 1; idx += x; result = *(idx + work.buffer810);` (sub_080524C8, 52 -> 0).
- `rec->x == work.cellX && rec->y == work.cellY` on adjacent byte fields is merged by fold
  into one halfword compare; the reference compares bytewise, which needs the second test
  grouped with the third, `a == b && (c == d && e)`, or nested ifs (sub_08052400, with a real
  struct view of gContinuedWork whose records start at +0x5DC; 68 -> 0).
- Frame-pointer functions with VLAs (`add r7, sp, #0x10`, `sub sp, #8` per array): the order
  of spilled-variable frame slots follows declaration order, so scalars the reference keeps
  below the VLA pointers must be declared before the arrays. A loop bound written
  `(s32)sizeof(names)` stays an unfolded `cmp #5; blt` with an entry test, as in the
  reference; a literal 5 becomes `cmp #4; ble` (sub_0805AED0 draft).
- A switch over {1, 2, 3..4} whose tree is rooted at the 3..4 range (`cmp #4; bgt default;
  cmp #3; bge`) has a fourth case node: balance_case_nodes splits three nodes at the middle
  one but four (with one range) at the third. A far value sharing the default body
  (`case 0xFF: default:`) adds the node without triggering a jump table (sub_0804FD10 draft).

## Lean_a round 10

- `ldr rB,=sym; adds rB,#4; ldrb rI,[...]; adds rB,rB,rI` (constant offset added to the symbol before the
  variable index) came from an array field of a struct view, `gPostDispatchBytes.bytes[frame]` with
  `struct { u32 word; u8 bytes[8]; }` over `gPostDispatchWord_03002B70`; `sym[4 + frame]` adds the
  index to 4 first and `(sym + 4)[frame]` folds to one literal (sub_0803E680).
- A `movs r0,#0; cmp; bne; movs r0,#1; cmp r0,#0; beq` flag computed after a call came from a
  `static inline` helper returning 0/1 used in `if (count > 0x1F || Helper())`; a local flag gets a
  callee-saved register and is zeroed before the call (sub_080438C4). m2c_integrate.py rejects top-level
  helpers, so such a function is integrated by hand (own file, segment entry, symbols.json entry removed).
- Loop invariants hoisted by loop.c (a global field address kept in r8 across a float call) only appear
  for a real `for` loop; the m2c `goto` loop recomputed them per iteration. A pointer copy the reference
  places among the hoisted invariants (`adds r5,r1,#0` after other literal loads) was
  `dst = buffer + i * 8;` at the top of the body, not `dst = buffer` before the loop (sub_08043960).
- Fresh offset literals (`ldr r1,=0xC29` instead of `subs r1,#4` from a previous offset) came from
  separate early `return 0;` tests instead of one `&&` chain (sub_080438C4).
- A failure block after a label that addresses `gCounter6ED08_03001800` through the entry register
  (`adds r1,r4,#0; adds r1,#0xaa; movs r0,#0x2d`), with every success branch ending in its own
  `ldrb; adds #1; b join` and only the final `strb r0,[r1]` shared, came from a pointer local
  `struct BattleWork *w = &gCounter6ED08_03001800;` (assigned after a `struct View *setup = gView;`
  local, which fixed the literal order) plus `w->counterAA++; return;` per branch and
  `fail: w->counterAA = 0x2D;`. Direct global accesses reload the literal after the label and the
  success tails merge into one block (sub_0801C524).

## Reload-held constants (lean_c round 7)

- `ldr r6,=K; ...; adds r6,#d` where the second address constant K+d appears as an
  add to a callee-saved register is reload_cse_move2add on two *reloads*, not a source
  `cell += d`. The constants were long-lived `u32` locals set once before an enclosing
  `if` (REG_EQUIV constants that global-alloc leaves unallocated, so reload
  rematerializes each into the next reload register). Which tilemap cells get such a
  local decides the reload rotation: sub_0805E478 matched with locals for the 2nd, 3rd
  and 4th cells (`0x060000C6`, `0x06000104`, `0x06000106`) and an inline 1st cell.
- A redundant `lsls #16; lsrs #16` of a halfword already loaded with `ldrh`, before
  `cmp` with a literal and a `strh` of the same register, came from re-reading the
  field in the condition and storing the *constant*: `else if (w.f == 0xFE0F)
  w.out = 0xFE0F;` (cse replaces the constant by the compared value). A local
  `v = w` or `u16`/`u32` temporaries drop the zero-extension (sub_08066460).
- Leaf if/else whose second arm used the next-higher scratch registers (`ldr r1,[r0]` for
  the pointer, `ldrb r2`, result in r3) matched once the arm's temporary was a
  function-scope `s32 field` assigned in both arms (`field = *data & 7; field++;
  *data = field | (*data & 0xF8);`), while the first arm keeps its block-local `u8 value`
  for the `(u8)(x + 1) << 4` truncation (sub_08053280, 10 -> 0 rows; found from a
  tools/permute.py hint).
- Same lever with two call arms: `u32 object` declared at function scope and assigned in
  both `if`/`else if` arms (`object = twice + base;` with block-local `twice`/`base`)
  gave the reference's separate object register and pointer temp, the cross-jumped
  `step++`/`column++` tail and all DMA registers, with no do/while wraps (sub_0806FF2C,
  26 -> 0 rows). Block-local `object` in each arm, or one combined expression, does not.
- Inner tile-copy loop the reference runs as a reversed countdown (`cmp width,#0; beq`,
  then `subs rN,#1; cmp rN,#0; bne`, with `palette << 12` recomputed per row) appeared
  when the index sum was written `map[((row + y) << 5) + col + x]` instead of
  `... + x + col`; the value order `src[...] + (palette << 12) + tile` then matched
  (sub_0806FBB8, 46 -> 0 rows; draft by lean_b). The `+ x + col` form keeps an up-counting
  `cmp col, width` loop and spills `row + 1`.
- Fixed-point position update `(0xFF & pos) | hi` whose reference result shares the
  0xFF constant's register (`adds r6, r2, #0; ands r6, r3; orrs r6, r1`) and computes
  the shifted sum first matched with a separate `hi = ((pos >> 8) + sine) << 8;`
  statement before `px = (0xFF & pos) | hi;`; together with `struct FrameObject *base =
  gFrameObjects; obj = &base[index];` (index in r8, base in sb) this closed
  sub_0806B2F4 (55 -> 0 rows).
## Lean_a round 11

- Frame-object loops whose stores use a strength-reduced object pointer (`adds r4,r2,#0x840` init,
  `adds r4,#0x40`) while reads add a separate large constant (`(b+i)<<8; movs #0xba; lsls #5; adds;
  adds r0,r0,r2`) came from plain `gFrameObjects[index]` / `gFrameObjects[(b + i) * 4 + 0x5D]` with a
  block-local `u32 index = i + 0x21;` at the top of the if body; `root` locals produced extra copies
  (sub_08029A14). For a 2-D group the index order mattered: `gFrameObjects[j + 0x30 + i * 4]`
  matched where `i * 4 + 0x30 + j` hoisted the giv init differently (sub_0802D198).
- A retry loop that exits from its body (`for (k = 0; k <= 3; k++) { r = f(); if (!r) goto next; ...
  if (!g) goto next; ... } next:;`) kept the reference's top-of-loop layout; `break` rotated the loop
  (sub_08029B84, sub_08029FE0).
- A record field byte the reference reaches as `lsls #8; adds base; adds #0xdd` (base before the field
  offset) came from a struct view indexed by record, `gSetupView[frame].byteDD`; byte indexing
  `buf[(frame << 8) + 0xDD]` adds the offset first (sub_08014B34).
- A 12-byte roster indexed by counter (`gCounter + 7 + i * 12`, walked as a giv from a copy of the
  base) is a struct view of gCounter6ED08_03001800 with `members[i].id` (sub_080120C8).
- A field pointer taken once inside the matched branch, `u8 *slot = &records[i].byte3; cell = slot[sel];
  slot[sel] = ...`, kept the reference's per-iteration `i * 8` next to the record giv; indexing
  `(&records[i].byte3)[sel]` twice folded `sel` into a strength-reduced giv (sub_080421B4).
- Indexing an array through a pointer cast, `((struct R *)gArray)[j + 1]`, distributes the `+ 1` into
  the base (`adds rB, #8` before adding `j * 8`); an array-typed view keeps `(j + 1) * 8`. A flat u8
  array view `gBytes[i * 2 + 1]` keeps `(i * 2 + 1) + base` where `gPairs[i][1]` hoists `base + 1`
  (near-misses sub_080423A0, sub_08042318).
- Loop-invariant hoisting order follows the order the invariants appear in the body.
  sub_08062614 hoists the `gObjectHalfwordBytes` literal before the `0x02040000` records
  base (table r6, records r5). It matched with a block-local records pointer in the loop
  body plus an explicit slot pointer for the read-modify-write:
  `{ u8 *slot; struct R *records = (struct R *)0x02040000; slot = &table[records[i].id * 2 + ...]; *slot += amount[i]; }`.
  `table[...] += ...` or a for-init `records` kept the opposite order. No agbcc flag
  (all -f/-fno- options, singly and in pairs, and old_agbcc) changed any of the 2-3 row
  near-misses sub_08067974, sub_08067D00, sub_0805DEC8, sub_08065208, sub_08060708 (lean_c r9).
## Variable scope and pseudo sharing (lean_e, 21 October)

- Repeated if/else-chain branches that each build `&gFrameObjects[arg0 * 3 + 0x47]` matched only with
  block-scoped locals per branch (`struct FrameObject *objects = gFrameObjects; u32 slot = ...;
  struct FrameObject *object = &objects[slot];`) or with no locals at all; one function-scope `slot`
  and `object` shared by all branches gives one pseudo and the wrong callee-saved registers (116 rows,
  sub_08019720).
- The opposite case: two switch cases with identical copy loops allocated differently until their
  `n`/`from` loop variables were function-scope variables shared by both cases (21 rows -> match,
  LeDecompressVram 0x08000B14). Try moving per-case declarations to function scope when only one of
  several identical blocks mismatches.
- Address sums the reference accumulates in the first operand's register
  (`lsrs r1,r1,#8; ands r1,r0; lsls r1,r1,#0xb; adds r1,r1,r0 ...`) came from compound statements on
  one variable (`screen = control >> 8; screen &= 0x1F; screen <<= 11; screen += xAddress;
  screen += y << 6; base = screen + 0x1000;`), and `out = (u16 *)base + (row << 5)` rather than a
  byte-address cast fixed the loop-invariant register order (sub_0803F1C8).
- A stack argument the reference loads after the first statement (`ldr r6,[sp,#0x28]` after the
  global store) was a parameter copied to a local there (`source = data;`).
- Repeated computed-address stores (`dst = BG-map address; ctx = gMainContextPointer; *dst = ...`) matched only
  with `dst`/`ctx` declared in a fresh block per store; reusing one function-scope `dst`/`ctx` gave 120 rows
  of register differences at the exact size (sub_08067F64).
- One variable reused for a call result, a product and a final total (`value = sub_08044E64(...); ...
  value = dims[0] * dims[1]; ... value = columns * (rows * value);`) reproduces the reference keeping all
  three in the same callee-saved register (sub_0804545C, 38 -> 10 rows).
- The opposite of scope splitting, variable *reuse*, fixed two near-misses where the reference does not
  reuse a constant it already holds (lean_c r10). sub_0805DEC8: the first call's result and the fill byte
  are one variable, `value = sub_08074FA4(4); if (value) return value; ... name[i] = value = 0xFE;`
  (the result lands in r1, and the store-chained `0xFE` comes after the loop base load).
  sub_08067974: the `0x1F` mask is loaded through the later `s8 row` variable, `low = timer; row = 0x1F;
  low &= row; ... row = timer / 32 + 0x10; row &= 0x1F;`. Reassigning `row` kills the equivalence, so
  the second mask is a fresh `movs #0x1F` (try_decls then picked `s8`).
- sub_08064A80 (lean_c r10): one variable for two roles in disjoint branches matched; `bits` is the
  shift amount in one branch (`bits = (word >> 8) & 3; ... << (bits * 8); 1 << bits`) and the
  shifted word in the other; a separate `shift` local left 9-29 rows. The packed store was two
  statements, `out = bits & 0xFF; out |= (i << 8) | 0xF400;` (a single expression reassociates the
  OR constant to the middle).

## Field stores and dead zeros (lean_b round 11)

- agbcc expands every struct field store as `field = (field & 0) | value`; the `0` is a pseudo that
  CSE shares with later stores and combine folds away, leaving `(use)` insns. A dead
  `movs r6, #0` in a callee-saved register next to a flags OR (`adds r0,r2,#0; movs r6,#0;
  adds r2,r0,#0; orrs r2,r1`) is that zero kept alive by two such uses. It came from plain
  compound assignments, `gFrameObjects[0x21].flags |= 0x220; ... if (c) gFrameObjects[0x21].flags |= 0x1000;`;
  m2c's `temp = 0x220 | flags; flags = temp; ... temp | 0x1000` form gives identical code minus the
  zero (sub_08027F84, sub_0802410C).
- sub_0801C774 matched from lean_a's 42-row draft by the same change: `field = (x << 10) | 0xC204;`
  stored directly and `field |= 0x1000;` later (no `flags` local, no `(s16)` cast).
- CSE follows at most PATHLENGTH (10) taken/around jumps per extended block. A constant register the
  reference reuses only in the first few arms of a long if-chain (`mov r1, r8` for 2 in the first two
  arms, fresh `movs #2` later) came from early exits written as separate
  `if (c) { counterAA++; return; }` blocks (each jump around one becomes a path entry; cross-jumping
  merges the copies); `goto fail` to one shared label adds no entries (sub_0801F4AC, 18 -> 0 rows).
- sub_0800147C (16-colour BlendPalettes sibling, lean_e 21 Oct): an `and` whose colour input dies was
  tied to the colour by regmove (`ands r2,r7; adds r0,r2,#0`); the reference's mask copy
  (`adds r0,r7,#0; ands r0,r2`) came from statement form where the and's destination is set again by
  the next statement (`component = blueMask & sourceColor; component *= sourceWeight;`), which stops
  regmove's forward pass (fixup_match_1 breaks when dst is set before it dies). The add then needs a
  fresh target to keep `weighted + product` order: `component = (weightedBlue + component) >> 5;`
  (`x = w + x;` is swapped to `x + w` by expand_binop).
- sub_0805EA44 (name-entry keyboard, lean_e 21 Oct, no flags): a second `screenY = 0x8C` store the
  reference materialises again in a scratch register (`movs r1,#0x8c`) instead of reusing the first
  HImode constant came from storing through an existing function-scope `s32` that is dead there
  (`gFrameObjects[1].screenY = blank = 0x8C;`, `blank` being the later default-name flag): the SImode
  set is not CSE'd with the HImode constant. A fresh variable is CSE'd away; `i`/`x` reuse also stops the
  CSE but their other live ranges move the register.
- Same function: `ldr rB,=gFrameObjects` before the first context load came from a chained assignment,
  `gFrameObjects[0].screenX = x0 = ENTRY->column0D * 8 + 20;` (expand_assignment expands the
  left-hand address before the right-hand side); `s32 x0 = ...; gFrameObjects[0].screenX = x0;` loads
  the base at the store.
- Same function: a loop counter that must share a callee-saved pseudo with a later signed counter but
  compares unsigned (`cmp #0xf; bhi`) was the signed function-scope `i` with
  `i < sizeof(ENTRY->name58)` (sizeof makes the comparison unsigned); a separate `u32 k` swapped two
  registers.

## Lean_f (final push, 21 October)

- global-alloc sorts pseudos by `floor_log2(refs) * refs / live_length` and breaks ties by
  pseudo number. Two parameters swapped between r7 and r8 (u8 `amount` in r7, the derived
  key in r8 in the reference) came from reusing the parameter for the key, `kind &= 0x3F;`:
  the key's live range then starts at the prologue copy, so `amount` outranks it
  (sub_08042318, sub_080422B8). A fresh `u8 key = kind & 0x3F` local always won r7.
- regmove skips a two-address fix-up when the source is a "remote constant"
  (`reg_is_remote_constant_p`): set once, the setter not in the insn's LOG_LINKS, and *any*
  REG_EQUAL note on the setter. That is why the u8-`low` draft of sub_080424B8 kept the
  reference's `adds r0, r3, #0; eors r0, r1` (the lsl/lsr zero-extension carries a REG_EQUAL),
  while `u32 low = full & 0xFF` tied the xor to `low`. The full match used a `u32 mask = 0xFF`
  local inside a u16 store, `seed = ((full & mask) << 8) | ((high = full >> 8) ^ (full & mask))`:
  fold narrows the and to HImode, the widened and gets a REG_EQUAL, and the mask stays an SImode
  register that regmove can tie (`movs r1, #0xff; ands r1, r2`). A plain `0xFF` constant in the
  narrowed and becomes a `(subreg:SI (reg:HI))` that neither regmove nor local-alloc ties.
- A table index used as `T[k = n * 2]` then `T[k + 1]` and incremented in place
  (`adds r2, #1` on the dying k) needs a block-local `k` in every case/branch; one
  function-scope `k` set in several blocks is global and `k + 1` gets a new register
  (sub_080366DC switch cases, sub_08038428 if/else).
- Bubble sorts whose swap temporaries sit in r4-r6 while the record pointers take r2/r3
  (sub_080423A0, sub_0804242C): the swap was written twice, `if (a.key < b.key) { swap }
  else if (a.key == b.key && a.tie < b.tie) { swap }`, with the temporaries at function
  scope. Each temporary is then set in two blocks (global, allocated after the pointers);
  cross-jumping merges the copies and leaves the second copy's `key = a.key` reload in front
  of the shared tail. A single `||` condition makes them block-local and local-alloc gives
  them r2-r4. Same functions: `for (count--; count != 0; count--)` on the u8 parameter (the
  reference keeps count and the loop bound in one register, ip), and a constant-address view
  `OBJECT_SORT_ENTRIES` (include/object_helpers.h) so the base literal is reloaded per inner
  iteration.
- A second address giv for one record field (`adds r4, r1, #1` init after the hoisted
  invariants, `strb r5, [r4]`, while other accesses use `[r1, #1]`) came from a row-0 flat
  index in that one store, `gObjectCountPairs[0][i * 2 + 1] = amount;`, with every other
  access written `gObjectCountPairs[i][k]` (sub_080422B8). User pointer walkers, `(u8 *)`
  casts and `*(pairs[i] + 1)` all fold the giv into `[r1, #1]` or lose strength reduction.
- `movs r6, #2; adds r6, #3` (a constant built in two steps) is reload rematerialising a
  REG_EQUIV local: `row = 2` set once and used as `row + 3`, `row + 6`, `row + 9`. A value the
  reference computes in each arm and copies at the join (`mov r8, r4` after the if/else) came
  from writing the expression (`x + 4`) inline in every call; gcse inserts the copy
  (sub_080364A8, 564 B).
- A function that never writes r0, returns through `pop {r1}` and keeps all locals out of r0
  falls off the end of a non-void function (the incoming r0 is live to the return); the
  strict return-type rule blocks it (sub_08037728).
## Search loops and PRE (lean_g, 21 October)

- Parameters the reference keeps in stack slots and reloads at every use (`str r0,[sp]` at entry,
  `ldr r0,[sp]` before each access, no `-O0` frame) are `volatile` parameters (sub_0804361C,
  sub_080436AC; existing header prototypes without the qualifier stay compatible).
- A loop constant the reference rebuilds each iteration (`movs r0,#0x80; ands` in the body) while
  a `while` loop let loop.c hoist it came from a goto loop (`if (index != 0) { ... previous: index--;
  ...; if (index != 0) goto previous; }`): no loop notes, no loop.c hoisting. The reference's
  `ldr r2,=base; adds r3,r2,#0` (base hoisted twice) came from a block-local `records = gInventoryRecords`
  used for the first test and the global for the second (sub_0804361C).
- `a != b` on two bytes loaded the first byte only after the second address; `(s32)a - b != 0` loads
  `a` before computing the address of `b` (sub_080436AC). Returning through a shared `found: return
  column;` label after the forward loop placed the backward branch's return block after the literal
  pool as in the reference.
- gcse PRE hoists `y + height` (and `row + 1`) of an outer loop to the block before the inner loop's
  entry test (`PRE/HOIST: end of bb 1` in a `-dG` dump). An expression stays at the bottom when one of
  its operands is set in that bottom block before it: a per-row copy `u16 py = y; ... object->y = py;
  ... y = py + height;` (sub_0804538C draft). Quick check: compile a stand-alone copy with
  `agbcc -O2 -mthumb-interwork -fprologue-bugfix -dG` and grep `PRE/HOIST`.
- A sign extension the reference keeps before a 9-bit bitfield store (`lsls/asrs #16; ands ip`) needs
  `s32 sx; sx = (s16)x; object->x = sx;`; `object->x = (s16)x` (and an `s16 sx`) is folded away by the
  bitfield narrowing.
- `*tileBase = call(...) + *tileBase` is narrowed to a HImode add whose result is tied to the loaded
  halfword; `{ u32 sum = call(...) + *tileBase; *tileBase = sum; }` gives the reference
  `adds r0, r0, r1` with the return register as destination (sub_08045E6C draft).
## Lean_h (21 October)

- A pointer the reference keeps in a caller-saved register with `str r3,[sp]` before a call and
  `ldr r3,[sp]` after it (caller-saves) was allocated last: global alloc tries the preferred LO_REGS
  without call-clobbered regs, then caller-saves in LO_REGS (profitable when refs > 4 * calls), only
  then high registers. sub_0805E334 got that order once the *other* pointer's store was written in
  both arms (`*bottom++ = value;` in then and else, cross-jumped back into one tail), which raised
  its priority above `top`.
- `code = *name; if ((value = code) != 0)` kept the reference's separate compare copy
  (`ldrb r5; adds r0,r5,#0; cmp r0,#0`) and the else-arm store of `value`; `value = code;` as a
  statement lets cse replace `value` by `code` (sub_0805E334).
- Global-alloc priority is `floor_log2(refs) * refs / live_length`, and flow weights every ref by
  its loop depth. A `do { } while (0)` around just one use raises that pseudo's priority; this decided
  which hoisted constant got r8/ip/sb in sub_0805BD44 and sub_08060BE4 (near-misses). Pass 0 of
  find_reg only takes registers already used (ip is often among them), so the first-allocated
  high-register pseudo gets ip, the next ones r8, sb, sl.
- regmove's backward pass ties `dst = src & mask` to the load of `src` only when `src` is a plain
  SImode REG that dies there and its setter is reachable without crossing a label, jump or loop note;
  otherwise it copies the other operand into `dst` first (`mov r2, ip; ands r2, r0`).
- cse only forgets equivalences at CODE_LABELs (and, in cse1 only, at NOTE_INSN_LOOP_END):
  a `do { } while (0)` after a constant assignment stops cse1 substituting it later, but cse2 ignores
  loop notes, so only a real label helps there (sub_08060708 near-miss: `byte18 = 1` keeps reusing
  `block = 1`'s register).
- A loop the reference runs as `test; body; i++; if (i <= 3) goto top` with the context pointer
  hoisted out was `for (i = 0; i <= 3; i++) { if (count <= i) goto done; call(); } done:`; the
  `goto` loop form gave cse2 a skip-block path across the loop so a later gcse re-load of the
  pointer was CSE'd away (sub_080619B0, 22 -> 15 rows).
## Lean_a round 13

- A register copy the reference places on one exit edge only (`adds r4,r5,#0; b second` in its own block,
  ours hoisted before the branch) is a GCSE PRE copy inserted at the end of the edge's source block. The
  block survives until GCSE only if it holds an insn: a dead store before the `goto` (`if (x != 1) { found = 1;
  goto second; }`; flow deletes the store later) reproduced it (sub_0800A1E4).
- `table[idx]` with a constant pointer argument: a symbol (`D_02020000`) is PRE-hoisted into a callee-saved
  register before an earlier loop; `(u16 *)0x02020000` is not a pool load and stays at the call (sub_080185E8).
- A loop counter giv `slot = i + 4` that the reference strength-reduces (init after the hoisted constants,
  `lsls rS,#6` per iteration) appears only when no other `4 + i` is computed: reading the counter bytes as
  `pad3D[4 + i]` makes CSE share that index and the giv is "not worth while"; an array field view starting
  at the byte (`cells41[i]`) plus `gFrameObjects[i + 4].field` per store and `call(i + 4)` matched
  (sub_0800712C). Read `-dL` (`giv of insn N not worth while`) to see such decisions.

## Allocation debug compiler and priorities (lean_c, 21 October)

**Debug agbcc** (`tools/agbcc_debug.patch`). It patches local-alloc.c, reload1.c and
combine.c and prints to stderr only when `AGBDBG` is set; the assembly output is
byte-identical to the production compiler. Build (Git Bash, MinGW gcc first in PATH or
cc1 fails silently with exit 1):

    cp -r tools/downloads/agbcc/source/gcc <scratch>/gcc && cd <scratch>/gcc
    patch -p1 -d .. < <repo>/tools/agbcc_debug.patch     # or apply per file
    export PATH="/c/ProgramData/mingw64/mingw64/bin:$PATH"
    make normal CC=gcc -j12                               # gives agbcc.exe
    AGBDBG=1 ./agbcc.exe -O2 -mthumb-interwork -ffunction-sections -w -fprologue-bugfix \
        build/m2c/<name>/match/candidate.i -o /tmp/x.s 2> dbg.txt

Output lines: `LOCAL block b` + one line per quantity in allocation order
(`ord`, `qty`, chosen hard reg, priority, suggestions, calls crossed, refs, birth,
death, member pseudos); `RELOAD insn N rK -> hr R (idx, prev) spills: ...` for every
allocate_reload_reg pick (the round-robin index); `EMIT insn N rK reg R ...` for every
reload of an insn, including ones that reuse a dying register (no round-robin step);
`COMBINE i3 i2 i1: <pattern>` for every successful combination. Add `-dl`/`-dg` for
the pseudo numbers. lean_d's tools/agbcc_reload_debug.patch (if present) only covers
the reload picks; this one is a superset.

**local-alloc order** (single-block pseudos): quantities with a hard-register
suggestion first, then by
`pri = floor_log2(refs) * refs * size / (death - birth) * 10000` (birth/death are
2*insn index in the block), ties by quantity number (order of birth). Each quantity
takes the lowest free register over its life. A one-insn constant temp scores exactly
10000 (2 refs over 2), so a long value chain with pri < 10000 loses r0 to it. Ties
join the output of an insn to its first dying input (op1, then op2 if commutative);
a pseudo that is not local (set/used in several blocks or dies twice) cannot be tied.
Inlining a subexpression instead of using a temp local (or the reverse) changes
refs/life of the chain and often flips a register pair (sub_08064C6C matched this way).
Global-alloc uses `floor_log2(refs) * refs / live_length`, and REG_EQUIV constant
pseudos get their live length doubled.

**Reload rotation**: allocate_reload_reg starts after `last_spill_reg` in the
spill_regs list (usually r0,r1,r3). A reload that reuses a dying input register does
not advance it, so the same asm can come from RTL with a different rotation.

**CSE and loop notes**: NOTE_INSN_LOOP_END ends CSE1's extended basic block, so a
`do { ... } while (0)` wrap stops CSE1 from sharing a constant across it, but CSE2
(rerun after loop) ignores loop notes and still shares it (sub_08064EB4's 0x06004000).
With expensive optimizations combine runs one more simplify pass on the substituted
source, which swaps `(ior (subreg a) (subreg b))` operands: under the default profile
`x.f = c | x.f` ends constant-first (output tied to the constant), under
`-fno-expensive-optimizations` flags-first.

## Reload rotation, priorities and dead stores (lean_d, 21 October)

- A redundant initialisation, `s32 i = 0;` followed by `for (i = 0; ...)`, changed global allocation and
  loop hoisting enough to reach the reference size (sub_0804FD10: `W + 0x12` hoisted into sl, `mode`
  spilled; 79 -> 24 rows). Worth one try when a counter's register or a hoisted base is wrong.
- Global priority is `floor_log2(refs) * refs / live_length` with refs weighted by loop depth. Identical
  switch-case bodies written separately (`case 0xFF: done++; break; default: done++; break;`) are merged
  later by cross-jumping but their refs still count, which moved `done` ahead of an i*8 giv
  (sub_0804FD10, 24 -> 15). Do/while(0) wraps add weight the same way; when a variable needs many more
  refs than a couple of wraps give (sub_080488E8 needs 8 nested wraps), the source shape is different.
- Local-alloc uses the same formula per block, and a one-insn constant (2 refs, life 2) scores exactly
  10000, so a long tied chain that needs r0 before such constants must reach refs*log2/life >= 1. A
  wrap around a statement that also loads a constant doubles that constant too (40000, it takes r0
  first); wrap only the chain's first set instead, e.g. `do { bgcnt = REG_BG0CNT; } while (0);
  block = ((bgcnt >> 8) & 0x1F) << 11;` (sub_08067D00: chain 11 -> 12 refs over 34 beats the 0x1F
  and VRAM-offset constants; the 0x04000008 address dies where the chain is born, so its weight is
  harmless). Check with the AGBDBG local-alloc dump (tools/agbcc_debug.patch).
- Loop strength reduction reduces giv families in reverse scan order of each family's
  representative insn (`-dL`: "giv at N reduced to reg M"). When two families start at the same
  address, the first reduced one owns the init and the second becomes a copy with one ref less,
  which decides who wins the last callee-saved register. sub_0802D8D0: moving
  `dst = &gFrameObjects[i + 0x24]` below the first two stores (used for `dst->screenX`) put the
  flags/screenX family after the case-arm family, as in the reference.
- A parameter the reference loads and zero-extends but never uses came from a defaulting store that
  dies only after flow: `if (frames3 == 0) frames3 = 1;` next to the two used frame counts
  (sub_080497E0). The extension insn survives because flow saw the compare use it.
- `obj = &gFrameObjects[i]` assigned after a `continue` test (not at the loop top) makes gcse PRE put the
  symbol load inside the loop (at the end of the first block that anticipates it) instead of hoisting
  it, giving the reference `base + i*64` offset givs (sub_08052784 draft, 100 -> 41 rows).

### Reload-debug agbcc

`tools/agbcc_reload_debug.patch` adds one `fprintf` to `allocate_reload_reg` (reload1.c): with
`AGBCC_RELOAD_DEBUG=1` the compiler prints `ALLOC insn=<uid> reload=<n> reg=<hard reg> n_spills=<n>`
for every round-robin reload-register choice. Generated code is byte-identical to the normal agbcc.

Build (about a minute):

    cp -r tools/downloads/agbcc/source/gcc build/dbgcc/gcc
    cd build/dbgcc && patch -p1 --binary < ../../tools/agbcc_reload_debug.patch
    # then from PowerShell (MinGW cc1 failed silently inside the Bash tool sandbox):
    cd build\dbgcc\gcc; $env:PATH = "C:\Program Files\Git\usr\bin;" + $env:PATH
    Remove-Item *.o; make normal

Use it on a draft's preprocessed file after `tools/try_draft.py`:

    AGBCC_RELOAD_DEBUG=1 build/dbgcc/gcc/agbcc.exe -O2 -mthumb-interwork -ffunction-sections \
        -fprologue-bugfix build/m2c/<name>/match/candidate.i -o out.s 2> reloads.txt

Add `-dg` to map the insn UIDs to RTL (`out.i.greg`... written next to the input). Only rotation choices
are printed; inherited reloads and output-register reuse (`adds rD, rS, #0` copies for tied operands)
do not advance `last_spill_reg`. Comparing the printed sequence with the registers the reference uses
for constant reloads shows where one reload is missing or extra (sub_0804FE9C: the reference is one
step ahead from the case-1 `0x31000000` reload on).
- Reload-rotation residue in two flag set/clear blocks (`if (a && b) set; else clear;`) disappeared when each
  was written as `if (!a) clear; else if (b) set; else clear;`: the duplicated clear arm is cross-jumped
  away, but its reloads advance the round-robin first (sub_0805B984, 6 -> 0 rows).
- Under `-fprologue-bugfix -fno-expensive-optimizations` (an existing profile) expand no longer forces
  large constant operands into pseudos outside loops, so `size + 0x06004000` keeps its own literal instead
  of being CSE'd with an earlier `vram + 0x4000` register; this is the profile when the reference reloads a
  literal that an earlier register already holds (sub_08060DD4 near-miss, 64 -> 7 rows).
- sub_08060DD4 matched under that profile once (a) symbol operands were written as constant addresses
  (otherwise `-fno-expensive-optimizations` emits a `.rodata` pool of `.LC` words that accept_draft
  rejects), (b) the CpuSet mask was a variable assigned between the shift and the call
  (`half = size >> 1; mask = 0x1FFFFF; CpuSet(.., half & mask)`), reused by the second CpuSet, and (c)
  `chars = 0x4000; chars += vram;` instead of `vram + 0x4000`: global alloc gives a copy preference for
  `(set A (plus B const))`, which tied the sum to vram's r8; the two-statement form has none.
- Header-field products and arguments (sub_0804545C; same 0x58-0x92 sequence in sub_08045120):
  the reference recomputes the rows argument from the cached `d << 20` and passes the columns argument
  through `adds r5, r0, #0` (a reload_cse copy: the arguments are recomputed shifts and r0 still holds
  the columns value). Source: one `t` for rows and columns, `x = value * t; t = cols; value = x * (u16)t;`
  (the no-op `(u16)` cast is what gave `t` r0 and `x` r1 in global alloc), `x = d << 26; x >>= 30;`
  for the shape (no separate shift temp, so `x` prefers only r1), then `t = descriptor;` and the
  argument shifts written on `t` (which kills the CSE equivalences).
- A loop-invariant header word whose spill slot order and store position differ (sub_08045120 draft):
  reading it through a block-local `const u32 *h = header;` around the loops reorders the gcse PRE
  pseudos, so the slots follow the reference (`row + 1` below the header word).
- sub_08045120 matched once the two PRE pseudos (`row + 1` and the loop-invariant header word) were
  created in the reference order: gcse's pre_delete walks the expression hash table bucket by bucket,
  so the order depends on the hashed register numbers modulo the table size. Reading the header in
  the loops through a pointer local assigned just before the `if (palette)` block
  (`layout = header; ... *layout << 20 ...`) put the header copy's insertion before the entry compare
  and its slot above `row + 1`, as in the reference. Use `-dG` and the `PRE: redundant insn` order to
  check. The OAM pointer is the parameter itself (a local copy moves its entry copy later), and the
  placement byte fields go through a view struct with `u8 y` so the y read is `ldrb`.

- A constant addend that fold must not reassociate into the address (reference computes
  `i8 + 1` as its own add before `+ state * 4`) can be a block-local `s32 first = 1;`
  declared in the case block: fold sees a variable, cse substitutes the constant in RTL
  (sub_0804FD10; function-scope locals stay in a register across the loop).

### Global-alloc order and doubled live lengths (lean_h, 26 October)

- `-dg` prints the sorted allocno list (`Register N, refs = R, live_length = L`); global
  priority is `floor_log2(R) * R * 10000 / L`, and each allocno then takes the lowest free
  register (pass 0 only reuses registers already used and not preferred by a conflicting
  lower-priority allocno). Three loop-long values in r5/r6/r7 therefore come out in exactly
  their priority order.
- `update_equiv_regs` (local-alloc.c) doubles `REG_LIVE_LENGTH` of any pseudo whose *first*
  set carries a REG_EQUAL constant, even when the pseudo is set again later: loop counters
  (`i = 0`) and strength-reduced pointer givs (`dest = &array[0]`) get twice their flow live
  length and drop far down the order; a loop-invariant product (`inv * 31`) does not.
- Refs are recounted by `recompute_reg_usage` with loop depth 1 outside and 2 inside a loop
  (+1 per enclosing do/while(0)); a wrap around a loop init (`do { i = 0; } while (0);`)
  adds one ref but also changes the order loop.c hoists invariants.
- A debug print after `find_reg` in `global_alloc` (allocno order, hard reg, refs, length)
  plus one in `update_equiv_regs` at the doubling were enough to explain sub_08072080; same
  build recipe as the debug agbcc above.
- regmove ties `x = mode & bit` to the dying `bit` even with `-fno-regmove` (local-alloc then
  ties it); a `u8 bit = (*p & 0x8000) != 0;` operand changes the extraction to
  `lsrs #15; ands #1` and the surrounding priorities (sub_08045E6C, 20 -> 16 rows).

## Native traversal across adjacent ROM objects

When the reference walks beyond a recovered data object's extent, preserve the
bus address calculation before converting back to a pointer. For example,
`angles = (s16 *)((u32)angles + ((u32)stride << 1));` preserves the 32-bit
address/stride wrap without claiming a larger `s16` array or changing native
reads. Keep null tests in their original order relative to address adjustments.
At `08047428`, the caller requests 64 channels from 49-track pose planes, so
the final fourteen iterations read adjacent native ROM. This change leaves all
328 bytes exact with only `-fprologue-bugfix`. Signed byte coordinates multiplied
by 256 likewise emit the original shifts while keeping negative C operands
defined. Original Thumb checks cover 843 native-ROM cases, all 64 output records,
guards and preserved registers; BIOS Div is modeled. Evidence is
`build/more/pose_bus_production_spec.json` and `pose_bus_cpu.json`.

Font fetches use the same rule. An empty F9 insertion starts with FE, and the
native `080402B4` path still requests glyph 254 despite the stored 135-glyph
bank. Form `(const void *)((u32)bank + (u32)character * 64)` before the BIOS
copy. All 28 effect/text functions retain their bytes; twelve original Thumb
cases verify the glyph254 source address for both fonts and every replacement
selector, including the default selector. BIOS copy contents and rendered
pixels are outside that check. Evidence: `build/more/empty_font_cpu.json` and
`effect_font_bus_production_spec.json`.


### Repeated byte reads in a short-circuit comparison

A nonzero check followed by a byte comparison may retain a second load of the
same address. In `08018EE0`, making the *first* read volatile preserves the
reference's three-load order; making only the later read volatile schedules
the comparison operands in reverse order. Assigning the comparison result to
a named local also affects agbcc register allocation. The accepted source is
`src/equipment_status_scan.c`; the native read trace is covered by
`tools/check_equipment_scan.py`. Use this only when the reference actually
performs the repeated read, and verify complete bytes and read order.
### Preserve inline helpers in permutation seeds

The upstream permuter stripper replaces other function bodies with declarations,
including `static inline` helpers. That changes generated code before searching:
the 512-byte `0803BE44` seed's `Wrap9` helper became a call, giving base score
9120 instead of 75. `tools/permute.py` now restores inline helper definitions
after stripping. A macro substitution is not equivalent for agbcc code generation
(this example grew to 548 bytes). Confirm the base score before trusting a run;
scores are search metrics, and exact bytes still require `tools/match.py`.


## Constant addresses, loop.c hoisting and local-alloc equivalences (lean_e, 26 October)

- A symbol address is a pool load `(mem/u (symbol_ref .LCn))` by gcse time and is PRE-hoisted to the
  earliest block; a constant address `(T *)0x080AFB80` is a `const_int` that gcse never touches and
  loop.c may hoist instead. When the reference hoists a table base *after* the loop.c-hoisted
  constants (`mov sb,r4; mov r8,r3; ldr r0,=table; mov sl,r0`), write the table as a constant address
  (sub_08060BE4); when it rebuilds a table base inside a loop and the symbol form gives a hoisted
  register, a constant-address pointer assigned in the loop body matched (sub_080619B0:
  `table = (const u8 *)0x084838E4; part = &table[...]`, which also fixed a reload-rotation offset).
- loop.c moves a constant only if `threshold * savings * lifetime >= insn_count`
  (threshold = 2 * 13 = 26 for a call-free thumb loop, minus 3 per insn already moved; `-dL` prints
  `life`/`savings`). Lifetime is measured in luids, and every non-line-number note (loop notes,
  deleted insns, block notes) has a luid: a bare `{ }` block between a constant pointer's assignment
  and its use lengthened it from 3 to 4 and got it hoisted in the reference order (sub_08060BE4).
- Global-alloc refs are weighted by loop depth, and a `do { } while (0)` counts as a loop: a use
  inside a wrap counts 2. This decided a hoisted constant (refs 4 vs 3) against a parameter.
- local-alloc's update_equiv_regs moves a constant pseudo that is set once and used once next to its
  use, even into another basic block, unless the use is inside a loop (depth > 0). A
  `do { work->data = ...; } while (0)` around the only use kept `work = (T *)0x02026000;` before the
  compare in a caller-saved register as in the reference (sub_08044A3C).
- Two rotation steps of reload registers missing before a loop came from constants the reference
  materialises by reload (unallocated equivalence pseudos) where ours were ordinary insns; the
  constant-address pointer above restored them. Operand order of a three-register add follows the
  source: `(struct R *)(i * 8 + (u32)records)` gave `adds r4, r5, r2` instead of `adds r4, r2, r5`.

## Lean_d (26 October)

- Reload rotation: a duplicated arm placed *before* the arm that needs a different
  reload register can supply the missing round-robin step even when cross-jumping later
  deletes it. sub_08065208's `[11]` flag block matched as
  `if (!(a)) clear; else if (b) set; else clear;` (clear/set/clear): the first clear is
  cross-jumped into the second, but its 0x2C0 reload (r1, with r0 live) runs before the
  set arm's, so the set arm's 0x2C0 reload takes r3 as in the reference. The
  set-first and clear-clear-set orders leave the one-step offset. Check with the
  reload-debug compiler (`RELOAD insn ...` lines) which pick is missing and where a
  forced pick (only one free spill register) would supply it.
- `x = (x + byte) & 0x1FF` on a u16 field: the store narrows the whole expression to
  HImode, so the position is a lazy HImode MEM (address, then `byte`, then the load,
  as in the reference) but the mask becomes an HImode constant (`ldr r1,=0x1FF;
  adds r6,r1,#0`). Passing the sum through `static inline u16 Wrap(u16 v) { return
  v & 0x1FF; }` keeps the narrow sum and evaluation order while the body's AND (and
  its CSE-shared mask register) is SImode with a direct `ldr r7,=0x1FF`; the
  parameter's zero extension is deleted by combine. The helpers' return type also
  matters: returning `u16` instead of `u32` from the tail wraps changed global
  priorities (live length) enough to swap two callee-saved registers
  (sub_0803BE44; the permuter found the return-type change).
- Global-allocation priorities use live lengths computed by flow, before combine, so
  insns combine deletes later (here the u16 helper's zero extensions) still lengthen
  every pseudo live across them; plain inline copies are usually gone by then (CSE).
  Compare `Register N, refs = .., live_length`
  in the `-dg` dump to see which pseudo must move ahead.
- A `(off = i * 8 + 1)` assignment expression inside an index keeps `i*8+1` as an
  opaque temporary computed after the other index terms (fold cannot reassociate the
  constant into the address). Distinct never-read `offN` variables match
  sub_0804FD10 byte for byte, but they are dead stores; the comma form `(o = .., o)`
  is hoisted by fold, and statement temps / inline helpers break the `i*8` giv.
- sub_08073810 (145 -> 0 rows): the call-argument temporaries of each switch case must
  be block-local (`{ const struct SoundSampleHeader *sample; s32 note; ... }` per case)
  rather than function-level variables shared by the cases. Block-local pseudos go
  through local-alloc with hard-register suggestions (r2/r3 for the call), which pushes
  the case's other temporaries into r4/r5 and leaves the parameter in r6 as in the
  reference. Also: `envelope = (level * half40) & ~0xFFF` stored through an `s16` local
  (HImode narrowing) gives the reference's `adds r3,r1,#0; muls r3,r0,r3` and
  `ldr r4,=0xFFFFF000; adds r1,r4,#0`; `switch (field)` directly (no u16 copy); and
  `cleared = 0xBF; cleared &= status; field = cleared;` ties the AND output to the
  constant register (`movs r0,#0xbf; ands r0,r2`), which no operand order of
  `0xBF & status` does.

## Lean_b (26 October, round 2)

- **A reused pointer variable stops local-alloc tying an address to a dying base.**
  In `p = (u16 *)(row + C1); *p = 0; p = (u16 *)(row + C2); *p = 0; ...` every address
  is the same user pseudo, set several times, so `combine_regs` refuses to tie it to
  the row base where that base dies (`reg_qty[sreg] >= -1`). Each address then stays
  in one register (`adds r2,r0,r4; strh r3,[r2]` ×3) and the dying base keeps its
  register. Separate `*(u16 *)(row + C) = 0` statements give `adds r0,r0,r2` on the
  last store. Used for sub_0805AED0. There, a single `do { } while (0)` around the
  last two stores of the second row sets local priorities (loop-depth-weighted refs)
  and stops CSE1 from sharing the 0x0600F030/0x0600F032 literals.
- **A user variable as the first step of an OR chain prevents a tie.** In
  `keys = a << 3; keys = keys | b | c;` the first shift is set into a non-local
  user pseudo, so the `lsrs` feeding it is not tied (`lsrs r0,r7; lsls r1,r0,#3`
  instead of `lsrs r1,r5; lsls r1,r1,#3`). Used for sub_08051CB8.
- **The cse 1,000-insn hash flush is visible in long straight-line functions**
  (sub_08059960). After the flush, gcse turns the first reload of a cached address
  into a register copy (`adds r7, r6, #0`), and later blocks get new constant
  registers. If the reference shows that copy in an earlier block than ours, its
  source expanded to more RTL per statement than ours.
