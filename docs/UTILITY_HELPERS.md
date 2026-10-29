# Utility helpers

The assigned interval is `0x08044094..0x08044CDC`, ending before the next entry. Caller targets, returns and literal pools establish twenty routines totaling 3,144 bytes. The first staged batch contains ten exact routines and 420 bytes, compiled with ordinary agbcc game settings and `-fprologue-bugfix`. Source and strict comparison specifications remain in `build/experiments/initialization/utility_helpers`.

| Entry | End | Bytes | Status |
| --- | --- | ---: | --- |
| 08044094 | 080440B4 | 32 | Exact C |
| 080440B4 | 080440D4 | 32 | Exact C |
| 080440D4 | 08044100 | 44 | Exact C |
| 08044100 | 08044118 | 24 | Exact C |
| 08044118 | 08044160 | 72 | Exact C |
| 08044160 | 080441A8 | 72 | Exact C |
| 080441A8 | 080441B8 | 16 | Exact C |
| 080441B8 | 0804422C | 116 | Exact C |
| 0804422C | 080442B4 | 136 | Exact C |
| 080442B4 | 080445F4 | 832 | Exact C |
| 080445F4 | 080446B4 | 192 | Exact C |
| 080446B4 | 080447EC | 312 | Candidate |
| 080447EC | 08044934 | 328 | Candidate |
| 08044934 | 08044A3C | 264 | Candidate |
| 08044A3C | 08044B28 | 236 | Candidate |
| 08044B28 | 08044B34 | 12 | Exact C |
| 08044B34 | 08044B58 | 36 | Exact C |
| 08044B58 | 08044BA8 | 80 | Exact C |
| 08044BA8 | 08044C38 | 144 | Exact C |
| 08044C38 | 08044CDC | 164 | Exact C |

sub_08044094 assigns main state 1, substate 1 and the word at 0300137C to 7. sub_080440B4 counts first bytes equal to three in nine eight-byte records beginning at 030017A0. sub_080440D4 returns one only when all 480 adjacent byte pairs beginning at 03004C40 agree. The latter accesses 960 bytes, agreeing with four 240-byte rows in equipment helpers.

sub_08044118 reads a rectangle of halfwords from a GBA screen block into contiguous caller memory, while sub_08044160 writes the inverse transfer. Both derive screen block from control bits 8..12, x displacement in halfwords and a 32-halfword row stride. sub_080441A8 Le-decompresses into EWRAM 02027000; sub_08044B28 forwards source and destination to LeDecompress.

sub_08044B34 first narrows the supplied value to a byte. A nonzero byte is returned directly; zero returns the byte table at 083B2AF0 indexed by save-work byte 0C5C relative to 030057E0. Its existing u32-to-u32 caller interface remains compatible. Those RAM/table names are provisional; table bounds and the index meaning are not proven.

sub_08044B58 sets bits C0 in RAM byte 03000BE0, initializes selected bytes of the first record at 030017A0, and sets the second byte of entries at offsets 0056, 0146, 0236 and 0326 in the paired-byte buffer. These offsets differ by 240. It does not use the unrelated gObjectParameterWork alias at 03000468.

The second staged batch reconstructs sub_0804422C and sub_080442B4, 968 additional exact bytes. The object helper indexes the halfword table at 083C6F78 using offset24 minus one as a 256-entry page, offset25 as an eight-entry row and offset27 modulo four as a two-entry pair. It adds the first entry to screenY modulo 256 and the second to screenX modulo 512, then increments offset27. A base-pointer local and an explicit u32 x-mask local reproduce the target's constant initialization schedule; table extent and original declarations remain unproven.

The directional selector accepts four signed coordinates, computes nonnegative x/y differences as floats, and returns cardinal codes 0, 8, 16 and 24, diagonal codes 4, 12, 20 and 28, or intermediate offsets within a quadrant. Each intermediate count rounds a ratio via `(larger + smaller*0.5f)/smaller`, converted to s32. For counts above four, `gFrameCounter & 3` selects four when nonzero and three when zero. Thus the target's overwrite of the count register with mask three is intentional observable behavior, reproduced by an explicit conditional three/four assignment. Both outer quadrant guards are independent if statements. The C and runtime relocations match all 832 bytes including literal pools.

Four setup functions provide 616 additional exact bytes. sub_080441B8 fills both 512-byte palette RAM banks with zero, clears twenty bytes at 03000490, sets its first byte to three, clears transfer selection bytes 41..43, and selects main state zero/substate three. Its two scoped fill locals reproduce separate stack slots and initialization timing.

sub_080445F4 clears 208 bytes at 02026000, 2,080 bytes at 020260D0 and 96 bytes at 020268F0. It writes mode two at 03000430, points 03002414 at EWRAM 02024000, and calls CpuFastSet with fill count 0426. It then points 03005308 at 020268F0, fills 0100 words beginning at context offset 0B84 with value 0200, clears bytes 1094/1095 and passes the observed buffers and ROM 083D1D78 to sub_08047414. The unusual first CpuFastSet count is preserved as encoded; this note describes its supplied count without claiming an exact BIOS-rounded endpoint.

sub_08044BA8 clears frame objects and twenty work bytes at 0300047C, stores the supplied byte at 0300047D and selects main state zero/substate five with word 0300137C=16. Four separate switch case bodies preserve the target's case tree; grouping cases one through three emitted a shorter range test. sub_08044C38 clears two twenty-byte work regions and chooses substates four, five or ten from its mode. Cases two/three assign different flags at 03000578. Numeric state meanings remain provisional.

RAM aliases at 0300047C and 03000490 overlap the previously established work buffer beginning at 03000440. They name observed pointer bases rather than proving separate C objects. Buffer/context fields outside these accesses remain neutral. sub_08047414 uses the existing canonical RecordDisplayWork/RenderWork interface from state0_display.h; the neutral byte views in the setup routine are explicitly converted at its call.

## Unmatched checkpoint

Sixteen functions totaling 2,004 bytes are exact. The four remaining definitions are isolated in `build/experiments/initialization/utility_helpers/candidate.c`, outside production. `verify.py` permits size mismatches for diagnosis only; delivery specifications require exact sizes and bytes.

The three wrappers at 446B4, 447EC and 44934 select a 1,040-byte buffer by slot and call the record-display compositors. Speed cases 0..3 map to 100, 200, 300 and 400; 447EC adds its final narrowed byte. A narrowed Boolean input maps zero to flag one and other values to flag two. Mode one adds bit four; mode two additionally resets 128 OAM records and clears context bytes 1094/1095. Coordinate inputs are zero-extended to sixteen bits at entry and sign-extended when passed onward. Exact source arity and parameter types remain provisional.

The closest 44934 variant is `variants/short_alias_0_008.c`: 264 bytes, 38 differing bytes after the corrected sweep. The bounded parameter/local sweep is recorded in `sweep_short.py` and `sweep_short_alias.log`. It uses ordinary casts, local variables and branches, without register pinning or instruction changes. The residual differences concern conversion scheduling and register allocation; no candidate is counted as reconstructed C.

44A3C chooses an identifier using a seven-column word table and a byte-index table, scans its selected string up to 255 characters, increments one of two slot timers, and advances the matching cursor after a successful renderer call. The reference checks the bound before loading the next string byte. An explicit initial-byte check plus a bounded do/while reproduces this loop shape, including repeated pointer-table loads, with ordinary nonvolatile accesses. The buffer base is two bytes after the cursor base at 020260CE. `variants/text_explicit_False_0.c` preserves those observations; it remains 240 bytes against 236 in the reference. Other candidates and compiler-option experiments remain under `variants`.

The renderer status register is only assigned on the cursor-below-length path, then tested unconditionally. The current candidate leaves that local uninitialized on the other path rather than inventing a zero initialization absent from the ROM. A valid caller precondition or a source-level explanation is still needed before claiming the routine is fully understood.

The 446B4 and 447EC wrappers have void epilogues: each pops its saved return address into R0 and branches through it. They do not establish a meaningful value return. The caller at 0800D6A8 passes zero and then one as the first argument of successive 446B4 calls; the second one comes from a nearby load also used for stack arguments. The first formal selects the data slot (`slot * 1040`) and is therefore not unused.
