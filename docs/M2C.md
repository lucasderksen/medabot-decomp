# m2c drafts

For a register-only near-match in a loop, reconstruct an actual structured
`do`, `while` or `for` loop before expanding the compiler-profile search.
At `0806E7EC..0806E90C`, replacing the m2c inner label/backward-goto with a
structured loop preserves the exact iterations and changes the compiler's
allocation of the row base and tile bias from IP/R8 to the reference R8/IP.
All twelve tested structured inner/outer forms match the same288-byte function;
they represent one accepted function. The cleaned production implementation is
`src/m2c_harvest_390.c`, only `-fprologue-bugfix`. Check the complete CFG and
counter bounds before making this rewrite; a byte score is not a semantic proof.

[m2c](https://github.com/matt-kempster/m2c) turns agbcc-style Thumb assembly
into C. `tools/m2c_candidate.py` feeds it one function from the reference ROM and
can compile the result through the real agbcc profile and `tools/match.py`.
m2c output is a **draft**: it uses `M2C_FIELD` casts, placeholder `D_XXXXXXXX`
and `sub_XXXXXXXX` names and guessed types. Accepted source still follows the
ordinary-C policy, compiles without `-w`, and passes the full `tools/build.py`
comparison.

Production builds always preprocess each normal-agbcc source. They may reuse
an object only when the complete preprocessed bytes, source identity, compiler
flags, compiler/assembler contents and adapter contents are unchanged, and both
the object and generated assembly still match their recorded hashes. Changed
headers and damaged/missing cache artifacts force compilation. The other
compiler profiles are rebuilt. Isolated matching and strict acceptance always
compile afresh. Every full build still assembles the raw ROM and symbol stubs,
links all sections and compares all 8 MiB before publishing artifacts; no match
verdict is cached.

## Setup

```powershell
python tools/bootstrap.py --m2c
```

This checks out m2c commit `708d2d2cb2698f091a92492b328f73b24209f72d` into
the ignored `tools/downloads/m2c/`. m2c is pure Python; no other dependency is
needed. `build/medabots.elf` must exist (run `python tools/build.py` once),
because calls and literal-pool addresses are named from its symbols.

## Use

```powershell
python tools/m2c_candidate.py 0x0801D5A8                 # draft C on stdout
python tools/m2c_candidate.py 0x0801D5A8 --match         # also compile and compare
python tools/m2c_candidate.py 0x0801D5A8 --end 0x0801D61C --cflags "-fprologue-bugfix -fno-regmove"
```

- **Bounds.** The function is decoded by following control flow from the entry,
  so literal pools and agbcc switch tables (`cmp`/`bhi`/`ldr`/`mov pc`) become
  data. Without `--end` the end is the last decoded instruction, pool word or
  table entry. The tool prints the bounds; verify them like any other boundary
  claim. A missing switch table stops the tool instead of guessing.
- **Context.** All `include/*.h` headers are preprocessed into
  `build/m2c/context.c` and passed to m2c, so known prototypes, structures and
  globals are used. `--no-context` disables this.
- **Optional source signatures.** `--production-context` supplements those
  headers with conservative primitive signatures from C definitions selected
  by active `.text.NAME` manifest entries. It accepts integer/void types and
  void pointers, excludes private types, static/conditional/duplicate
  definitions, variadics and unspecified parameter lists, and preserves every
  existing header name. The snapshot is saved in
  `build/m2c/context_production_signatures.json`; only declarations used by a
  generated draft are copied into that draft for standalone compilation.
  This option also works with `--evaluate` and `--harvest`, and leaves the
  default context unchanged. These are provisional source hints, not a fresh
  ROM ABI audit: inspect the actual caller/callee registers before accepting
  a new function. The unresolved `sub_08060D28` interface is explicitly
  excluded. At checkpoint `49fd28e`, 979 eligible signatures supplement the
  headers. A fresh `08025A18` smoke draft retains the real
  `extern u32 sub_08036E54(u32);` and compiles under production `-Werror`
  without extra sections; it still mismatches, so this is a context/compile
  validation, not a measured improvement in match rate.
- **Optional pointer strides.** `--fix-pointer-strides` uses the local
  `tools/m2c_stride_driver.py` wrapper without modifying the pinned download.
  For raw typed-pointer arithmetic emitted by m2c's byte-offset evaluator,
  it renders a divisible literal offset in C element units: a halfword
  cursor plus two bytes becomes `cursor += 1`, and a 64-byte frame cursor
  plus 64 bytes becomes `cursor += 1`. The byte-offset analysis tree stays
  intact; already resolved array/field accesses are not scaled again.
  It also covers ARM load/store-multiple writeback, explicit subtraction,
  and raw immediates whose pointer type is inferred later. For example,
  a word load with four-byte writeback becomes `cursor += 1`.
  Raw variable offsets (including commuted addition and subtraction) use
  unsigned word-address arithmetic before conversion back to the inferred
  pointer type. This preserves machine byte offsets rather than multiplying
  them by the C pointee size. In-place variable updates stay full casted
  assignments, so compound pointer += cannot reintroduce element scaling.
  Recognized array indices and struct fields remain unchanged. Integer/byte
  additions, unknown sizes and non-divisible immediate offsets retain
  upstream behavior and still need manual review. This option also works
  with `--evaluate` and `--harvest`, independently of `--production-context`.
  Default generation stays unchanged. Synthetic Thumb loops verify both
  strides, load/store writeback, subtraction, field access and scalar
  increments, variable byte offsets, commuted operands, subtraction,
  in-place updates and late type inference without changing the analysis AST.
  A real `53B04` float-pointer control also verifies its two
  stack-held cursor writebacks and subtraction. Fresh ROM probes at `07480`,
  `00E94` and `0147C` remain mismatches. This reduces a demonstrated manual
  correction, without a measured increase in automatic exact matches.
- **Compile check.** `--match` writes `build/m2c/<name>/candidate.c` and
  `spec.json` and runs `tools/match.py`. The draft is compiled with `-w` (m2c's
  loose casts would otherwise fail `-Werror`; warnings do not change code) and
  renamed `m2c_<name>` after the headers so a guessed signature cannot clash
  with an existing prototype. Placeholder names are defined at their encoded
  addresses. The default profile is `-fprologue-bugfix`, which 1,310 of the
  1,591 accepted agbcc segments use.
- Other unrecognized options are passed to m2c (for example `--stack-structs`).

Outputs: `build/m2c/<name>.s` (m2c input), `build/m2c/<name>.c` (draft),
`build/m2c/<name>/` (compile check).

## Measured on accepted functions

`--evaluate N` runs m2c on N random accepted single-function agbcc segments,
compiling each with the flags its accepted source uses, and writes
`build/m2c/evaluation.json`. Result on 6 October 2026, 200 functions (seed 3),
after placeholder `sub_` callees were declared as Thumb functions (see below):

| Accepted size | Functions | Compiled | Correct size | Exact without edits |
| --- | ---: | ---: | ---: | ---: |
| < 40 bytes | 63 | 63 | 52 | 44 (70%) |
| 40–99 bytes | 77 | 75 | 46 | 31 (40%) |
| 100–249 bytes | 44 | 43 | 18 | 4 (9%) |
| ≥ 250 bytes | 16 | 13 | 1 | 0 |
| **All** | **200** | **194** | **117** | **79 (40%)** |

An earlier run measured 16%. Its harness defined placeholder callees as plain
addresses, so the linker treated every call to a not-yet-decompiled function as
ARM interworking and inserted a `bx pc` veneer. Production integration was
never affected: it always declared those symbols as Thumb functions.

So m2c alone finishes most small functions; for larger ones it supplies
control flow, call arguments and field offsets to start from. The byte
similarity printed by `--match` compares bytes at equal offsets: it ranks drafts
roughly but drops sharply after the first size difference.

## Harvest of copied code

`--harvest` lists likely entries inside copied intervals below the end of the
code region (gap starts, `BL` targets and odd Thumb pointers anywhere in the
ROM), decodes each within its gap, and tries m2c with `-fprologue-bugfix`, then
default flags. Exact candidates are recorded in `build/m2c/harvest.json` with
their spec; they are staged results for root review, not accepted source.
Pointer-derived entries include false positives; the decoder and compile check
reject most of them, but every staged boundary still needs review.

### First harvest (6 October 2026)

2,578 entries were tried (218 gap starts, 671 `BL` targets, 1,689 odd
pointers) in the 341,376 copied bytes below `0x0807E858`. 127 drafts were exact
without edits (4,962 bytes), all with `-fprologue-bugfix`.

`tools/m2c_integrate.py` then rewrote 125 of them (4,776 bytes) as production
C in `src/m2c_harvest_0.c` and `src/m2c_harvest_1.c`, and the complete ROM
still matches byte for byte:

- `D_XXXXXXXX` placeholders became `gUnknown_XXXXXXXX` (30 new
  `config/symbols.json` addresses); absolute entries for functions now defined
  in C were removed.
- `M2C_FIELD(expr, type *, offset)` was expanded to the plain cast it denotes;
  `M2C_UNK` became `s32`.
- Functions with conflicting declarations go to separate files.
- Skipped: `0x0802FBF2`, whose decoded start includes a `0000` padding halfword
  (the function probably starts at `0x0802FBF4`), and `0x0803D6AC`, for
  which m2c emitted its own anonymous structure.
- Not attempted: the three primary ranges assigned on 6 October
  (`0801D5A8..0801DAEC`, `0805F488..0805F9C8`, `080352EC..0803536C`).

Boundaries were checked in bulk: entries follow a previous function's literal
pool, `bx`/`pop {pc}` tail or padding, and are followed by the next function's
prologue or code. Names (`sub_XXXXXXXX`, `gUnknown_XXXXXXXX`) and parameter
types are m2c's guesses; renaming and moving these functions into subsystem
files is ordinary follow-up work and does not change bytes.

### Corrected harvest (6 October 2026)

After the Thumb-placeholder fix, a third harvest (2,421 entries) found 238
exact drafts (15,436 bytes); 235 were integrated (15,128 bytes) into
`src/m2c_harvest_8.c` to `_11.c`. Three were skipped because m2c emitted its own
structure. Every integration lands new gap starts, so rerunning the harvest
after an integration can find functions that nothing else references.

To repeat after more context exists (new headers improve m2c's types):

```powershell
python tools/m2c_candidate.py --harvest
python tools/m2c_integrate.py --exclude START-END ...   # assigned ranges
python tools/checkpoint.py "Integrate m2c harvest" --push
```

`m2c_integrate.py` only adds: each run writes new `src/m2c_harvest_<n>.c`
files for exact functions not yet in source and leaves earlier ones alone. If
the build then fails, discard that run's changes with
`git checkout config` and by deleting the new file, then rerun with
`--drop START` for the offending function.

## Instruction-level diff

`tools/match.py` reports differing bytes; `tools/asm_diff.py` shows why:

```powershell
python tools/match.py spec.json --output-dir build/experiments/foo
python tools/asm_diff.py spec.json --output-dir build/experiments/foo
```

It aligns the reference and candidate Thumb disassembly of every mismatched
section side by side. Literal-pool loads are shown as their loaded value
(`ldr r1, =0x04000204`) and branches relative to the section start, so a
size change does not make the rest of the function look different. Markers: `|`
differs, `r` differs only in registers, `<`/`>` only on one side. It replaces
the GUI objdiff for this project: agents can read it, and it needs no exported
target objects.

## Reviewed Thumb long branches

Some large agbcc functions use four-byte Thumb BL encodings as unconditional
jumps within the current function. Default decoding retains every BL as a
call: an internal destination or missing prologue does not prove a jump.
After inspecting every affected site and destination, a single-function
experiment can explicitly select reviewed destinations:

```powershell
python tools/m2c_candidate.py 0x0805424C --end 0x080568F4 --fix-pointer-strides --long-branch-target 0x08054280 --long-branch-target 0x0805678C --long-branch-target 0x0805678E --long-branch-target 0x08056796 --long-branch-target 0x080567F0 --long-branch-target 0x080567FE
```

Prove that these transfers continue the current stack frame, return through
the entry-saved LR rather than the BL fallthrough, and do not consume the
BL-generated link value. Genuine local callable helpers must stay calls.
Hints require explicit bounds, even in-function targets and reachable BL
sites; automatic harvest/evaluation does not accept them.

The generator preserves each decoded instruction's original four bytes/size
and follows selected transfers without inventing a fallthrough. It writes
semantic `b` instructions only to `build/m2c/<name>.m2c.s`, used by m2c.
That input is not an assembly matching reference. The normal `<name>.s`
retains its original BL instructions and remains the match/permuter reference.
`<name>.branch_hints.json` records bounds, targets, affected sites and ROM bytes.
The usual strict compile, ABI/bounds review, no-extra-section check and full
ROM comparison still apply to any resulting C.

For `5424C..568F4`, root independently repeats the six-destination, 34-site
analysis: each destination has only the shared `568D8` exit, following stack
restore at `568CA` and entry-saved LR pop at `568D6`; no decoded instruction
reads live LR after the prologue. The corrected input removes 102 false
fallthrough instructions and reduces raw m2c errors from 27 to five. Those
remaining errors concern real branch-merged stack arguments of `497E0`.
This function is still an unmatched draft and receives no progress credit.
Address `55534` is a literal pool word containing `03006D30`, referenced by
the LDR at `55524`, and cannot be credited as a separate function.

## Register-based stack allocation

`--fix-register-stack` is another optional, single-function input correction.
The pinned m2c recognizes an immediate stack allocation but misses a prologue
that loads a negative constant into a register and then adds it to SP. That
can turn actual local slots into supposed caller arguments.

```powershell
python tools/m2c_candidate.py 0x08001520 --end 0x08001CAC --fix-register-stack --fix-pointer-strides --no-switches
```

The resolver tracks only exact literal loads, immediate/register moves and
literal left shifts within one straight-line block. It discards known values
at calls, branches, joins, gaps and unknown writes to the relevant register.
Only a non-flag-setting `add sp, rN` with an exactly known nonzero, word-aligned
delta receives an immediate view. The canonical `<name>.s` and original
instruction size/bytes remain unchanged. The separate `<name>.m2c.s` supplies
the corrected analysis to m2c; `<name>.stack_adjustments.json` records each
site, register, signed delta and original bytes. It composes with reviewed
long-branch hints and remains disabled in normal/automatic generation.

For `01520`, ROM `152C` adds R4 loaded from literal `FFFFFDC8`, allocating
568 local bytes; `1C90` restores 568 via `8E << 2`. Together with 32 bytes of
saved registers, m2c now recognizes its actual 600-byte frame and recovers
`void sub_08001520(void)` instead of thirteen supposed caller parameters.
With `--no-switches`, missing-stack-argument errors disappear. A template
still infers only one order entry where the ROM uses an array; pointer tables,
operand widths and a saved-register expression remain unresolved. The C is
still an unmatched draft, and this improvement receives no progress credit.
Older independent renderer candidates and semantic checks remain in
`build/experiments/compiler_input`; their matching status is unchanged.

## Declarations from reviewed stack arrays

Pinned m2c can name a known stack array element such as `widths[0]` without
declaring the root array. For a manually reviewed `_m2c_stack_NAME` context,
opt in to declaration recovery:

```powershell
python tools/m2c_candidate.py 0x080697B4 --end 0x08069910 --production-context --context build/reviewed_stack_context.c --declare-stack-arrays --fix-pointer-strides
```

The additional context must contain the actual stack struct, including verified
array sizes and saved-register space. `--declare-stack-arrays` registers only
explicitly known fixed positive-size array fields that m2c actually addresses.
It preserves the original returned expressions and instruction/type analysis.
`build/m2c/<name>.stack_arrays.json` records the recovered declarations, offsets
and byte sizes. No bounds or allocation sizes are inferred. Unknown, zero-length
and out-of-bounds fields remain unchanged; bulk generation is rejected.

This option works independently of `--fix-pointer-strides`. Both can be used
together; normal generation retains upstream behavior. The subprocess-local
wrapper never edits the downloaded m2c. Array-root recovery does not fix raw
`sp` cursors, aggregate copies, missing hardware reads or inferred helper ABIs.
Review the complete draft and use the usual byte/production-Werror/section gates.

The reviewed `697B4` layout recovers its actual eight-byte width/height arrays
and two eight-halfword arrays. Its original canonical reference remains intact;
other draft repairs are still required, so this improvement receives no function
progress credit. Evidence is `build/continued_697B4_typed_stack/cli_audit_46.json`.

## Permuter

[decomp-permuter-agbcc](https://github.com/WhenGryphonsFly/decomp-permuter-agbcc)
randomly rewrites a draft (temporaries, statement order, casts) and keeps
variants closer to the reference. `tools/permute.py` runs it on m2c drafts:

```powershell
python tools/bootstrap.py --permuter
python tools/permute.py sub_080191A4 --cflags="-fprologue-bugfix -fno-regmove" --seconds 300
python tools/permute.py --batch build/m2c/near_misses.json --jobs 12 --seconds 600
```

- The target object is the m2c input assembly (`build/m2c/<name>.s`)
  assembled; every variant is compiled with the real agbcc wrapper.
- On Windows the permuter's own multiprocessing does not work and it expects
  an executable `compile.sh` and `cpp`; `tools/permute.py` patches those three
  points at import time and runs one single-threaded permuter per function,
  several functions in parallel.
- A score of 0 is **re-verified** with `tools/match.py` byte comparison. Only
  then is the draft replaced and the function recorded in
  `build/permuter/solved.json`, which `tools/m2c_integrate.py` reads alongside
  the harvest.
- Use `--cflags=...` (with `=`) when the flags start with `-`.
- Temporary files stay on the project drive. Each run points `TEMP`/`TMP` at
  `build/permuter/<name>/run-*/tmp` and deletes it afterwards. Each invocation
  has a fresh run directory containing its seed, target, flags, log and saved
  outputs; its JSON result includes that directory. Older results are preserved
  and cannot supply the new run's score or source. The compile hook also
  removes the `.i`/`.s` intermediates of every variant; the permuter itself only
  deletes its `.c` and `.o`. Before this fix, hours of batch runs filled `C:`
  with leftover intermediates in `%TEMP%`.
- Plain source is automatically randomized by the upstream parser. Normal
  logs suppress trial compiler output, and `best_score: null` means no variant
  was saved; it does not mean no alternatives were compiled. The unbuffered
  log retains the base score even when the bounded process is stopped.

`python tools/m2c_candidate.py --near-misses` writes `build/m2c/near_misses.json`: harvest drafts with the correct size,
classified by `asm_diff` markers; the batch takes those differing only in
registers or in at most three instruction rows. Typical fix found: hoisting a
global's address into a temporary so agbcc loads it before an index shift.
- Variants are searched with `-w`, but production uses `-Werror`.
  `solved.json` records `compiles_with_werror`; a `false` entry needs a small
  cleanup after integration. The first batch had one: a `const u8 * const`
  local assigned after declaration, fixed by dropping the second `const`
  (bytes unchanged).

### First permuter batch (6 October 2026)

37 near-misses (registers only, or at most three differing instruction rows),
10 minutes each: 13 reached score 0 and were byte-verified, then integrated
(428 bytes, `src/m2c_harvest_5.c` to `_7.c`). Most of the rest were not real
functions: misaligned pointer entries or epilogue fragments
(`pop {r0}; bx r0` without a prologue). The harvest now rejects both.

Permutation setup normalizes a simple literal-word alias only when one
undefined seed name resolves to the identical full address. Ambiguous aliases,
Thumb state bits, odd data addresses and relocation expressions remain intact.
It also aligns the target's function section name with the seed's. The entire
normalized target is relinked at its original ROM address and byte-compared
before searching; original decoded assembly is retained. This removes a
demonstrated name-only score penalty. `normalization.json` records address
rewrites and verified interval size. Seed compilation with `-w` is only for
symbol extraction: score-zero C still needs strict comparison and semantic
review, including arithmetic and pointer bounds.

## Fixing drafts by hand and by rule

### Constant outgoing stack arguments across branches

For a reviewed single function whose known callee has missing stack arguments
at a control-flow join, try:

```powershell
python tools/m2c_candidate.py 0x0805EA44 --end 0x0805EFD4 --name sub_0805EA44_stack_review --production-context --recover-stack-constants --fix-pointer-strides
```

`--recover-stack-constants` uses a subprocess-local wrapper around pinned m2c.
It tracks aligned full-word literal stores separately from m2c's block-local
call arguments. A slot survives a join only when every direct predecessor has
already been translated and supplies the identical value. Only missing slots
required by a known nonvariadic integer/pointer prototype are inserted; unused
slots are not imported as `extra?` arguments. Calls, SP changes, unknown writes,
partial overwrites and elided register-save stores invalidate relevant evidence.
Untranslated loop predecessors are not assumed to agree. No path predicates,
signatures, local array lengths or saved-register inputs are inferred.

The default generator and bulk harvest are unchanged. Bulk modes reject this
option. It composes with pointer-stride rendering and reviewed stack-array
declarations; `<name>.stack_joins.json` records the function, join, parents,
callee, slot and recovered value. Downloaded m2c files remain unchanged.

The actual `0805EA44..0805EFD4` control recovers only SP4=13, SP8=1 and SP12=0
at node73 from parents50/72. SP0 is nonliteral on one predecessor and retains
its explicit `M2C_ERROR`. This reduces draft errors; it is not an accepted C
function or additional progress. Fifteen regression tests cover real Thumb
branches, conflicting/missing inputs, calls, partial/indirect writes, loop
backedges, unknown/variadic/float/64-bit/aggregate signatures, existing argument
precedence, excess slots, SP/store invalidation, pass reset and hook restoration.

`tools/try_draft.py <name> [file]` swaps a hand-written function into
`build/m2c/<name>/candidate.c`, compiles it and prints only the differing
instruction rows; `tools/accept_draft.py <name>` re-verifies the bytes,
requires a clean `-Werror` compile and queues the function in
`build/m2c/manual_solved.json` for `tools/m2c_integrate.py`.

Recurring fixes found this way are automated in `tools/rewrite_drafts.py`,
which applies combinations of up to three transforms to every unfinished draft
and keeps byte-exact results (see its docstring for the list). What the hand
fixes showed about this codebase's original source:

`sink_phi_store` keeps each branch's original value assignment before moving
the following store into that branch. This preserves narrowing conversions,
volatile accesses, sequence points and later uses of the value. It is limited
to the named function and exhaustive simple branches with an immediate store;
intervening statements and labels are held. The earlier rule dropped the
assignment, which was unsafe when a later field store still used the value.
The revised rule has a reserved learned-variant slot. A fresh `16554` ROM
control changes88bytes/13rows to92bytes/exact under only-fprologue-bugfix and
passes production-Werror/noextra-section checks. That function was already
integrated, so the tool control receives no new progress credit. Ten regressions
cover conversions, live later values, side effects, scope and held patterns.

- **Globals go through locals.** Work areas and tables are almost always
  loaded into a local pointer first (`work = gUnknown_030057E0;`,
  `base = gRecords; record = &base[i];`, `buffer = gSetupBuffer; p = buffer + 0x40;`).
  agbcc then loads the address before the index arithmetic, and keeps a
  constant offset as a run-time add instead of folding it into the literal.
  m2c writes the folded form; this is the most frequent source of mismatches.
- **Full-width parameters and counters.** Narrow `u8`/`s16` parameters and
  locals make agbcc insert extensions that the original (int-typed) code lacks.
- **Stores in each branch.** `if (c) g = A; else g = B;` rather than a merged
  temporary.
- **Casts, not shift pairs**, for sign/zero extension.

On 7 October the transforms fixed 16 of 115 known failures in the evaluation
set (accepted functions), and roughly 60 harvest drafts.

The later speed pass adds a ranked remaining-target queue,
reusable matching sessions and bounded learned variants. Use
`python tools/target_queue.py --families --min-bytes 250 --limit 30` to choose
manual work, and `python tools/rewrite_drafts.py --learned-only --variant-limit
13 --jobs 2 --limit 16` for a small rule trial. Historical queue scores do not
replace fresh matching. The new rules, guarded profile sweep, cache keys and
measured results are in [SPEED_REWRITES.md](SPEED_REWRITES.md).


### Retaining ARM argument positions

`python tools/m2c_candidate.py ADDRESS --fix-argument-slots --match` opts into
rendering unused earlier word parameters for an unknown signature. For example,
assembly using R0 and R2 could otherwise become a two-parameter C function,
placing the second value in R1. The new driver retains an unsigned unused
parameter in slot1. A real agbcc control emits the original ADD R0,R0,R2;
the uncorrected draft emitted ADD R0,R0,R1.

This hook changes only function rendering and restores the analysis argument
list and names afterward, including on formatter failure. Known prototypes,
methods, aggregate returns, multiword parameters and apparent stack slots above
16 are unchanged. Inferred stack arguments and caller values still require a
ROM ABI review. The feature currently supports single-function generation and
can combine with --fix-pointer-strides; stack-array/join drivers remain separate.
The unchanged assembly and actual repairs are recorded in NAME.argument_slots.json.
Eight regression tests cover register and stack gaps, unchanged signatures,
large/multiword holds, restoration and the real compiler instruction encoding.

### Reusing a pointer across separate phases

When instruction differences are only register allocation, compare pointer
lifetimes as well as expressions and loop syntax. The73094 dispatcher uses
one byte cursor first for a circular list and then for a captured work root.
Two separate m2c locals emit a different saved-register list; reusing the
cursor, together with the reference branch layout, gives a strict480-byte
match under-fprologue-bugfix -fno-gcse. This is ordinary local reuse: preserve
the actual value at every use, child-call side effects, all live-root reloads
and whole-object pointer bounds. Do not add artificial state or register pins.

### Check every return path after a zero search score

A permuter score0 can still be invalid C. The15390 search moved its incoming-word
return before the default label, making type>7 fall off a non-void function.
That result is rejected even though the compiler happens to emit the reference
bytes. Preserve the ROM's explicit default return behavior and do not invent a
narrower input domain. The ordinary-Werror build only rejects enabled warnings;
it does not replace return-path, sequencing, bounds and ABI review. A lookup-only
PERM_RANDOMIZE region can keep switch/return statements outside the search.

`accept_draft.py` now also runs the modern cross-compiler with
`-S -std=gnu89 -Werror=return-type` on the strict agbcc preprocessed input,
before copying the draft or recording acceptance. Its assembly is diagnostic
only; production flags, matching objects and ROM output still use agbcc.
agbcc rejects `-Wreturn-type`, and a modern `-fsyntax-only` pass misses this
particular error, so neither is a substitute for this compilation check.
The actual rejected15390 preprocessed input fails the check; the defined DMA
draft passes. Two regression tests cover the misplaced/default return paths.

### Check MMIO reads and inferred argument slots against the entry

An unused-looking memory read can be an actual device operation. At0806FDA4,
the ROM reads DMA3CNT after writing its enable/count word; the no-context m2c
draft drops that read and uses unknown-object pointer arithmetic with the wrong
stride. A typed volatile three-word DMA view and explicit control read recover
the observed device sequence. Keep ordinary work RAM nonvolatile. The raw
signature also invents unused earlier words through incomingR3, while the entry
only consumes low-byteR0 and four direct callers pass0/40. Conversely48CF0
really loads callerSP+8 (word slot6), and three callers explicitly populate
all three stack words. Rendering a gap is a hypothesis, not ABI evidence.
Neither example has yet established a new C match.

### Four-byte structure returns use a hidden destination with agbcc

`TileCoordinates` is four bytes, but the production compiler returns it through
a hidden destination in R0. At caller0801B004, R0 is SP+0xC before42CA0;
the six logical arguments occupy R1/R2/R3 and SP+0/4/8. The caller then reads
the packed result from SP+0xC. The pinned m2c ARM ABI currently adds a hidden
destination only for structures larger than four bytes. Its raw coordinate
calls consequently have shifted arguments and an extra apparent parameter.
Do not change the real helper prototypes to accommodate those drafts.

Private `build/to80/sret_batch269.py` tests an analysis-only context declaring
the two known helpers as void functions with an explicit destination. It then
restores canonical C structure-return assignments into four-byte unions of
`TileCoordinates` and `s32`. Only named, word-aligned stack destinations with
the expected argument count are transformed. All13 affected unowned callers
compile after this repair;78 comparisons under draft `-w` profiles produce
zero exact matches. This is a draft-generation workaround, not an accepted
function or a general ABI fix. Stack layout, cursor bounds and clean no-w
compilation still need review. The rejected untyped_aggregate37 alignment
case remains rejected. Details and setup failures are in the numeric notebook.

### Unknown globals can still scale byte addresses by four

An inferred pointee without a known size is printed as four-byte `M2C_UNK`.
At16080, the ROM adds a byte index to083AD4F0 and reads one byte; the old draft
prints `*(index + &D_083AD4F0)`, which makes C scale the index by four. The
opt-in stride driver now also handles a marked raw dynamic address when its
result is a proven byte pointer and an operand has an unknown pointee size.
It emits unsigned word address arithmetic followed by the byte-pointer cast.
The analysis AST, default driver, known arrays and unknown wider results stay
unchanged. This does not guess an unknown structure's layout or repair bounds.

Two regression tests include a synthetic Thumb lookup passed through actual
m2c and agbcc: the original C emits LSL#2, while the fixed draft emits a byte
load without that scale. Unknown halfword/word results are unchanged. The
private276 survey repairs64 drafts and compiles49 plus10 profile comparisons;
none is exact. Clean data declarations, bounds/alignment and ABI review remain
mandatory before acceptance. In particular639C4's rejected alignment draft is
excluded from this survey and remains rejected.



### A scoped single-iteration store can affect register allocation

At333E4, a canonical80-byte counter draft differs by an R4/R5 allocation swap.
The bounded permutation search changes only its final status store to
`do { root[0x51] = 1; } while (0);`. This ordinary C block preserves the
condition and side effects and recovers all80 original bytes. Integer address
traversal avoids a post-loop pointer beyond the six setup records. Strict
acceptance and an8192-case CPU/state model verify the cleaned result; details
and limits are in the numeric notebook. This is an observed compiler source
shape, not permission to wrap declarations or control-flow statements blindly.
The general survey retains its failed parse/compile hypotheses and still
rejects exact functions with extra data sections.


Audio follow-up (16 October): keep08074A04 output-40-1 from private search636
excluded: the score improvement overwrites a live metadata pointer with a
flags byte and subsequently dereferences it.635/636 also retain an obsolete
s32 return declaration for7455C; actual entry/epilogue establishvoid(void*,s32).
Reset7455C's final record+4C store is a halfword.74978 takesstruct Link74978*.
Strict corrected controls634/638..642 have no exact candidate. Generic
627/629/631 function-exacts with extra.rodata remain excluded; no scoring,
compiler, linker or acceptance guard was weakened.


Frame gate/counter0803B900 is now164-byte exact in m2c_harvest_404.c, with
only-fprologue-bugfix and no extra sections. Native647 preserves ordinary
unsigned value/address lifetimes and original branch sharing; fresh m2c646
was still negative. Clean648/acceptance650/production652 agree. Integer
cursors retain all256 byte indices without out-of-range FrameObject pointer
arithmetic or an invented array extent. Model656 passes38144 independent
state cases, all non-stack IWRAM, preserved registers and bounded returns.
Comparison643 has no eligible result;636's score40 pointer overwrite remains
rejected. Full evidence and coverage are in the numeric notebook.

Two frame functions are now reviewed in `m2c_harvest_405.c`: 080280D4 / 92 bytes
and 0802976C / 128 bytes, both with only `-fprologue-bugfix`. The latter uses
real command helpers and an observed const ROM pointer word; the former keeps
a genuine zero comparison that resolves the last two ADD register differences.
Strict acceptance 678 and independent production comparison 680 pass without
extra sections. State models cover 66,048 and 14,976 cases with explicit sound
and BIOS limits. Fresh m2c drafts still mismatch. The private lifting studies
are experiments, not semantic approval; reads across caller-saved kills must
pass the corrected flow check 665.

Windows compiler routing is also needed when multiprocessing imports the
runner as `__mp_main__`: the parent has already rewritten argv, removing
`--run-permuter`. Regression tests cover this import and the ordinary compile
fast path. This changes worker execution only, not compiler flags, strict
matching or acceptance. Private four-process search714 exercises it; scores
still require fresh strict comparison and semantic review.

Tile-map adjust0805BAA0 now has reviewed108-byte C in harvest406: a genuine
u16 entry snapshot resolves the last load/copy register swap, while preserving
unsigned shifts, existing three-argument ABI and original hardware bus cursor.
Clean do/while source and production731 are strict exact with only
-fprologue-bugfix. Independent model727 checks1419 calls/1453056 halfword
updates; detailed domains and VRAM/mirroring limits are in the lift notebook.

New integer-cursor source for0801AE70 is68-byte exact without extra sections
in harvest407. Direct adjacent CMP operands remove unnecessary comparison
snapshots; original condition consumers remain valid. Cleanup743/3 retains the
matching loop branches. Model745 exhausts timer/phase pairs for frames120..127.
The final unused integer advance forms no out-of-range pointer. Older drafts
with extra rodata remain rejected; no acceptance or section guard changed.

Sound guard08073274 is68-byte exact in harvest408 with only-fprologue-bugfix.
Removing comparison scratch requires proving no surviving reads; typed cleanup
uses the existing SoundDispatchWork73094 root slot and reloads it after the
callback. Depth+730 stays inside the observed734-byte allocation. Model757
checks196608 initial/callback-depth cases with explicit effects and limits.
Actual production761 emits only the expected function section.

Mapped record setup08014EE8 is92-byte exact in harvest410, using the genuine
scalar alias from the accepted14F44 pattern. Real41D3C/3F63C model785 passes
16640 caller-domain cases. gIntrTable is converted to an integer address before
mapped offsets, never indexed as a31-record array. Numeric and symbolic base
forms have different allocation; retain the strict-exact symbolic form791.
Acceptance792 and production794 emit only the expected function section.
Turn selection0803713C is244-byte exact in harvest411 with only
-fprologue-bugfix. A genuinely read local scalar alias plus propagation of a
dead F8-address temporary resolves the final copy-register mismatch. Independent
model804 passes262144 cases with real selection/dispatch helpers and explicit
predicate-result models. Actual production813 has no extra sections; the caller's
unused-return hint is corrected to void(void). See the lift notebook for the
BF/BE oracle correction, bounds, ABI and remaining model limits.



### Shared callback prototypes and parser-only packing

Keep full callback prototypes in shared headers. At an outgoing-call join,
m2c can lose stack arguments written before the branch: 08073810 omitted two
arguments until the reviewed eight-argument PCM prototypes were supplied.
The typed draft then reports M2C_ERROR for those two words. Check each incoming
ROM path and its outgoing stack stores; never infer a shorter interface from
that draft. The PCM callbacks themselves match with the shared prototypes.

Keep packing-dependent sizeof assertions beside the data definitions. The
permuter strips __attribute__ for its parser context, which makes unrelated
packed-record size assertions fail before search begins. The production data
source retains those checks; normal matching and score-zero verification use
the real headers and compiler.
