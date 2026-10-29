# Nonmatching functions and matching workarounds

This is a matching decompilation: every function is rewritten until agbcc
produces the original bytes. Functions that do not match yet are kept as
`NONMATCH` functions (`include/global.h`), as in the Minish Cap and Sonic
Advance 2 decompilations:

```c
NONMATCH("asm/non_matching/sub_08048BE0.inc", void sub_08048BE0(void))
{
    /* closest C attempt */
}
END_NONMATCH
```

The build assembles the original code from `asm/non_matching/<name>.inc` in
the function's place, so the ROM stays byte-identical. The C body is compiled
as dead code (it stays type-checked; its constants are discarded at link
time) and `-DNON_MATCHING` compiles it instead. Progress counts these
functions as unmatched. The `.inc` files come from `tools/nonmatch.py`, which
resolves every symbol against the last matching build.

To work on one: `python tools/m2c_candidate.py 0x<address> --match` sets up
`build/m2c/<name>/`, `python tools/try_draft.py <name> src/non_matching/<name>.c`
compiles the current attempt as it is and prints the differing rows, and once
it matches, `tools/accept_draft.py` plus
`tools/m2c_integrate.py` replace the NONMATCH entry, its C file and its
assembly. Detailed notes from earlier attempts are in
[drafts/README.md](drafts/README.md).

## Nonmatching functions

Rows are the differing instruction rows from `tools/asm_diff.py`.

| Function | File | Flags | Size, best attempt | Problem |
| --- | --- | --- | --- | --- |
| `sub_08001520` | [sub_08001520.c](../src/non_matching/sub_08001520.c) | `-fprologue-bugfix` | 1,932 B; 1,908 B, 195 rows | OAM builder: the reference strength-reduces two OAM pointers (sp+0x234 and r8, both `+= 8` per part); depth in r7 (ours r4) |
| `sub_08020B4C` | [sub_08020B4C.c](../src/non_matching/sub_08020B4C.c) | `-fprologue-bugfix` | 416 B; 416 B, 38 rows | The `pos154[0]` address loses its high register; local-alloc gives sl/sb to CSE'd byte-address pseudos |
| `sub_0804538C` | [sub_0804538C.c](../src/non_matching/sub_0804538C.c) | `-fprologue-bugfix` | 208 B; 196 B, 59 rows | gcse PRE hoists `y + height` to the outer loop; the reference only hoists `row + 1` and reloads 0xFFFFFE00 per iteration |
| `sub_08045E6C` | [sub_08045E6C.c](../src/non_matching/sub_08045E6C.c) | `-fprologue-bugfix` | 456 B; 452 B, 45 rows | Index arithmetic one register lower than the reference; `visible = 0` store merge |
| `sub_080465B8` | [sub_080465B8.c](../src/non_matching/sub_080465B8.c) | `-fprologue-bugfix` | 1,192 B; 1,192 B, 49 rows | Register allocation in the visible block (&matrix/k/0x1095 in r5/r3/r6, reference r6/r5/r3) |
| `sub_0804842C` | [sub_0804842C.c](../src/non_matching/sub_0804842C.c) | `-fprologue-bugfix` | 600 B; 600 B, 82 rows | The reference keeps r6 as a reload register for the 0xC30 constant in several cases |
| `sub_08048BE0` | [sub_08048BE0.c](../src/non_matching/sub_08048BE0.c) | `-fprologue-bugfix` | 200 B; 200 B, 6 rows | Constant copy `ldr r3,=0xFFFF; adds r1,r3,#0`: cse folds the constant straight into r1 |
| `sub_080513C8` | [sub_080513C8.c](../src/non_matching/sub_080513C8.c) | `-fprologue-bugfix` | 1,064 B; 1,064 B, 238 rows | Unsigned `bhi` instead of signed range checks; the value==0 arm keeps its own load |
| `sub_08051CB8` | [sub_08051CB8.c](../src/non_matching/sub_08051CB8.c) | `-fprologue-bugfix -fno-regmove` | 384 B; 384 B, 7 rows | Register swap: direction r8 and work base r7 (reference r4 and r8); global-alloc priority |
| `sub_08052784` | [sub_08052784.c](../src/non_matching/sub_08052784.c) | `-fprologue-bugfix` | 372 B; 364 B, 38 rows | Loop counters i and k allocated the other way round |
| `sub_08059960` | [sub_08059960.c](../src/non_matching/sub_08059960.c) | `-O1 -fprologue-bugfix` | 1,264 B; 1,264 B, 187 rows | cse's 1,000-insn hash flush lands in block 8; the reference's source expands to more RTL per object, so it lands in block 5 |
| `sub_08064EB4` | [sub_08064EB4.c](../src/non_matching/sub_08064EB4.c) | `-fprologue-bugfix -fno-expensive-optimizations` | 448 B; 448 B, 2 rows | `movs r5, #0` is emitted after the `orrs` instead of before it; empty `asm("")` barriers do not move it |
| `sub_080697B4` | [sub_080697B4.c](../src/non_matching/sub_080697B4.c) | `-fprologue-bugfix` | 348 B; 348 B, 61 rows | Stack tables and indexed DMA reads; permuter got no closer |
| `sub_08072080` | [sub_08072080.c](../src/non_matching/sub_08072080.c) | `-fprologue-bugfix` | 264 B; 264 B, 7 rows | Global-alloc order: the reference allocates the destination pointer before `inv * 31` |

## Fake-matching functions

These match only through a construct AGENTS.md accepts as a fake match. Each
carries a `/* FAKE MATCH: ... */` comment; `grep -rn "FAKE MATCH" src` lists
them.

| Function | File | Construct |
| --- | --- | --- |
| `sub_080185E8` | `src/m2c_harvest_419.c` | `FORCE_REGISTER(u32 twice, r0)`: keeps `index * 2` in r0 |
| `sub_080488E8` | `src/m2c_harvest_419.c` | `FORCE_REGISTER(s32 i, r4)`: global-alloc would give r4 to `power` |
| `sub_08060708` | `src/m2c_harvest_420.c` | `FORCE_REGISTER(u8 one, r0) = 1`: a fresh 1, so the two arms cross-jump |

## Other accepted workarounds

These reproduce the reference exactly and say so in a comment in the body.

| Function | File | Workaround |
| --- | --- | --- |
| `sub_08006F34`, `sub_08015390`, `sub_080155A8`, `sub_0801A6EC` | `src/m2c_lean_a_66.c` | Falls off the end like the reference |
| `sub_08037728` | `src/m2c_lean_f_5.c` | Falls off the end like the reference |
| `sub_080488E8` | `src/m2c_harvest_419.c` | Returns the caller's incoming r8 on one path, like the reference |
