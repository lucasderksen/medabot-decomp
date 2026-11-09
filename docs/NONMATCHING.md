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

None: every function matches. The `NONMATCH` mechanism stays for future work.

## Fake-matching functions

These match only through a construct AGENTS.md accepts as a fake match. Each
carries a `/* FAKE MATCH: ... */` comment; `grep -rn "FAKE MATCH" src` lists
them.

| Function | File | Construct |
| --- | --- | --- |
| `sub_08001520` | `src/m2c_final_08001520_0.c` | `FORCE_REGISTER` pins: `depth` in r7 (shared with `width`), the depth sum in r0, the X scroll in r8 |
| `sub_080185E8` | `src/m2c_harvest_419.c` | `FORCE_REGISTER(u32 twice, r0)`: keeps `index * 2` in r0 |
| `sub_0804538C` | `src/m2c_final_0804538C_0.c` | Nested `do { } while (0)` wraps (nine around `width = dims & mask`, two around a no-op `height = (u16)height`, three around `column = 0`) and a no-op `height = (u16)height` in the inner loop: they set the global-alloc order column, height, width, object (r3, r5, r6, r7) |
| `sub_08045E6C` | `src/m2c_final_08045E6C_0.c` | `FORCE_REGISTER(u32 alt, r1)`: regmove would tie `mode & alt` to `alt` instead of reloading `mode` into it |
| `sub_080465B8` | `src/m2c_final_080465B8_0.c` | Two `do { } while (0)` wraps: around the command-search flag test (found/flag in r4/r5) and around the child0F call (work in r8, set in sb) |
| `sub_0804842C` | `src/m2c_final_0804842C_0.c` | Dead `if (k & 0x100) second \|= 1;` (its label keeps combine from folding `0xFF \| value` in the duplicated arm, so that arm cross-jumps away after advancing the reload rotation); `FORCE_REGISTER(.., r1)` on the 0x7F and 0xFF constants |
| `sub_080488E8` | `src/m2c_harvest_419.c` | `FORCE_REGISTER(s32 i, r4)`: global-alloc would give r4 to `power` |
| `sub_08048BE0` | `src/m2c_final_08048BE0_0.c` | `FORCE_REGISTER(u32 next, r0)` and `FORCE_REGISTER(u16 mask, r1) = 0xFFFF`: the u16 hard register makes reload emit the reference's `ldr r3,=0xFFFF; adds r1,r3,#0` |
| `sub_080513C8` | `src/m2c_final_080513C8_0.c` | two `skip = 0;` padding stores: a redundant one in the `value == 0` arm (own block for the gcse insertions) and a dead one before `goto store` in the `value == 1` arm (label survives until jump2, so `value`/`k` are reloaded) |
| `sub_08051CB8` | `src/m2c_final_08051CB8_0.c` | Nested `do { } while (0)` wraps on the `up` and `left` key statements and around the switch: loop-depth-weighted refs give global-alloc the reference order (direction r4, then left/up/down shift words r5/r6/r7) |
| `sub_08059960` | `src/m2c_final_08059960.c` | Dead padding locals (`NAV_PAD_*`) so cse's 1,000-insn flush lands in the fifth object block as in the reference; `FORCE_REGISTER(u16 none, r0) = 0` for the cleared shadow flags |
| `sub_08060708` | `src/m2c_harvest_420.c` | `FORCE_REGISTER(u8 one, r0) = 1`: a fresh 1, so the two arms cross-jump |
| `sub_08064EB4` | `src/m2c_final_08064EB4_0.c` | `FORCE_REGISTER(void *dest, r1) = (void *)0x06004000` for CpuSet: CSE cannot share the literal with `size + 0x06004000` |

## Other accepted workarounds

These reproduce the reference exactly and say so in a comment in the body.

| Function | File | Workaround |
| --- | --- | --- |
| `sub_08006F34`, `sub_08015390`, `sub_080155A8`, `sub_0801A6EC` | `src/m2c_lean_a_66.c` | Falls off the end like the reference |
| `sub_08037728` | `src/m2c_lean_f_5.c` | Falls off the end like the reference |
| `sub_080488E8` | `src/m2c_harvest_419.c` | Returns the caller's incoming r8 on one path, like the reference |
| `sub_0804842C` | `src/m2c_final_0804842C_0.c` | Falls off the end like the reference |
