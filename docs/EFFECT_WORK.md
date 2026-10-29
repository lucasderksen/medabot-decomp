# Display effect work

The assigned interval `0x0803FB0C..0x08040B50` contains 28 routines. Boundaries follow returns, literal pools, callback targets, and calls within the interval. Address names are retained because the same work structure serves several script and display paths.

`src/effect_work.c` contains only verified definitions. `build/experiments/initialization/effect_work/candidate.c` preserves the remaining reconstruction candidates. The isolated `spec.json` uses agbcc with `-fprologue-bugfix`, including explicit zero section padding from the compiler adapter. Strict verification compares the complete function interval, including literal pools and padding.

## Verified initial group

| Routine | Range | Bytes | Observed behavior |
| --- | --- | ---: | --- |
| sub_0803FB0C | 3FB0C..3FB3C | 48 | Sets stage 4, clears script position and layout/wait fields. |
| sub_0803FB3C | 3FB3C..3FB6C | 48 | Stores script pointer, calls stage callback, returns whether stage exceeds 7. |
| sub_0803FB6C | 3FB6C..3FB94 | 40 | Snapshots palettes and starts the fade when byte 0 is zero; otherwise selects stage 2. |
| sub_0803FB94 | 3FB94..3FBDC | 72 | Blends selected BG/OBJ palette banks toward color 0x1B2 with twice the counter; advances after counter 8. |
| sub_0803FEA8 | 3FEA8..3FEB8 | 16 | Advances script position by one. |
| sub_080408D0 | 408D0..408F4 | 36 | Dispatches on the byte after the current script byte. |
| sub_080408F4 | 408F4..40914 | 32 | Dispatches through table 0x083B2954 using work byte 0x1B. |
| sub_08040914 | 40914..40934 | 32 | Dispatches through table 0x083B296C using work byte 0x1B. |
| sub_08040934 | 40934..40954 | 32 | Dispatches through table 0x083B2984 using work byte 0x1B. |
| sub_08040954 | 40954..40974 | 32 | Dispatches through table 0x083B2988 using work byte 0x1B. |
| sub_08040974 | 40974..40994 | 32 | Dispatches through table 0x083B2990 using work byte 0x1B. |
| sub_08040A00 | 40A00..40A40 | 64 | For mode 1, clears a 30 by 6 rectangle at (0,13) and advances substage by two; otherwise by one. |
| sub_08040AF0 | 40AF0..40B0C | 28 | Advances substage by one when byte 0 is zero, otherwise by two. |
| sub_08040B0C | 40B0C..40B50 | 68 | Applies the decreasing blend counter to BG/OBJ mask 0x1FFF; advances substage when zero. |

The first delivery was 580 bytes of matching game C. A second group brings the verified total to 1,364 bytes across 20 routines:

| Routine | Range | Bytes | Observed behavior |
| --- | --- | ---: | --- |
| sub_0803FBDC | 3FBDC..3FC20 | 68 | Selects stage 4 for mode 1; otherwise advances stage, resets transition and enables/configures BG0. |
| sub_0803FC20 | 3FC20..3FCC8 | 168 | Loads successive BG0 graphics/maps for transition steps 0 through 2, then advances stage. |
| sub_0803FCC8 | 3FCC8..3FD28 | 96 | Clears 52 tile records in VRAM, copies a 26 by 4 tile rectangle and enters the script handler. |
| sub_0804056C | 4056C..405D0 | 100 | Flushes a partial text tile; clears horizontal layout fields and advances to line 1 or wrap step 2. |
| sub_08040820 | 40820..408D0 | 176 | Flushes a partial tile; advances stage immediately for script modes 1/4 or on repeated A/B for modes 0/2/3. |
| sub_08040A40 | 40A40..40AF0 | 176 | Reverses the BG0 transition sequence, clears the text rectangle, then advances substage. |

The third group brings the verified total to 2,172 bytes across 23 routines:

| Routine | Range | Bytes | Observed behavior |
| --- | --- | ---: | --- |
| sub_0803FD28 | 3FD28..3FEA8 | 384 | Runs byte-script commands until work byte 0x13 becomes nonzero. |
| sub_080405D0 | 405D0..4070C | 316 | Flushes a partial text tile, animates an acknowledgement prompt, waits for repeated A/B, then clears layout and tiles. |
| sub_08040994 | 40994..40A00 | 108 | Removes the active graphics through animation or a clear rectangle, then advances substage. |

The seven callback tables are reconstructed separately in `src/effect_work_data.c` and strictly verified with modern GCC as typed data. They span `0x083B291C..0x083B2994` (120 bytes, 30 function pointers). Each start is referenced by the corresponding verified dispatcher; the final end is established by the independently referenced next table at 0x083B2994, used by code with a literal at 0x08041694. The arrays contain 9, 5, 6, 6, 1, 2, and 1 entries, respectively. No anonymous trailing pointers were added to a table based on appearance alone.

The primary stage table begins at 0x083B291C, and the script-byte dispatcher table begins at 0x083B2940. The six-entry arrays at 0x083B2954 and 0x083B296C are byte-identical but remain separate definitions at their independently used addresses. Table targets at 0x08040B50 and 0x08040B5C are declared as zero-argument callbacks pending reconstruction; their Thumb address types are supplied in the data spec. Every pointer, including both primary-table dummy entries, matches the reference encoding.

The partial-tile address is `0x06000280 + 64 * (u8)(((x + 8) / 8) - 1) + 1664 * line`. The byte cast is observable in the original shift sequence. The initial clear uses CpuFastSet with 16 words; the partial flush at 0x0804056C uses CpuSet with 32 halfwords. Both move 64 bytes. Code at 0x08040820 reads the low byte of the canonical repeated-key halfword, so mask 3 tests A and B.

## Byte-script commands

The interpreter reads the current byte at `script[position]`. Values below 0xF7 enter the glyph/layout path. Its switch handles the following commands; the case order in matching source preserves the ROM jump-table and branch layout.

| Byte | Observed action |
| --- | --- |
| F7 | Delay helper 0x080407A4; yields unless delay is FF. |
| F8 | Toggles font-selection byte 0x27 and advances one byte. |
| F9 | Secondary text path, or pending line-wrap/acknowledgement work. |
| FA | Delay helper 0x0804070C, including its input-skip path. |
| FB | Graphics command helper 0x0803FEB8, then yields. |
| FC | Acknowledgement helper; advances one byte after completion. |
| FD | Line-wrap or acknowledgement helper; advances when that work completes. |
| FE | Advances one script byte. |
| FF | End/advance helper 0x08040820, then yields. |

The interpreter sets wait byte 0x13 to zero before entering the loop. Helpers can set it to one, and the interpreter reloads the byte after every command. No speculative bounds checks or command remapping were added.

## Work layout evidence

The complete interval now matches in ordinary C: 28 routines and 4,164 bytes, including all literal pools, embedded jump tables, and padding. The final additions are `sub_0803FEB8` (384 bytes, graphics-script command), `sub_0804070C` (152 bytes, input-skippable delay), and `sub_080407A4` (124 bytes, delay without input skip). The only external function newly required by the graphics command is the bank mapping helper `sub_08044B34(u32)` at its observed Thumb entry point.

The two delay initializers cache the current position, reload position for the script-byte read, store the delay byte, then reload that byte before testing FF. A narrow, read-only `EffectDelayWork` view uses volatile position/delay members for the explicit rereads while writes use the normal work view. This reproduces every observed access without instruction edits or register constraints. It is a provisional access model; the original qualifiers and any concurrency rationale are unproven. Applying volatile access to writes would introduce additional reads with this compiler, which are absent from the reference and were rejected.

Both delay helpers initialize from the byte after the current command. FF immediately advances the script by two; other nonzero values count down until zero. The skippable variant also checks work byte 0x89 and repeated A/B; when that byte is zero and input is present, it clears the delay and advances two bytes. Zero initialization followed by a non-FF byte does not consume that byte immediately.

The fourth delivery adds `sub_08040038` (`0x08040038..0x080402B4`, 636 bytes) and `sub_080402B4` (`0x080402B4..0x0804056C`, 696 bytes), bringing the verified total to 3,504 bytes across 25 routines. The named const ROM-array declarations are compiler-sensitive: casting literal addresses to pointers generated different address arithmetic and register allocation. Their successful use establishes a compatible declaration, not the original source spelling.

The private `EffectWork` view covers the first 0x28 bytes at `0x03000440`. Word offset 8 stores the script pointer, halfword 0x0C stores the current script position, byte 4 selects the stage, and byte 0x1B selects a nested substage. Byte 0x1C is used as the palette blend counter. Offset 0x20 holds a secondary byte-stream pointer; 0x24 indexes that stream. Other names describe operations seen in these routines and do not establish the original declaration or gameplay meaning.

The larger routines use byte metrics at `0x083B4E08` or `0x083B5008` and 64-byte glyph records at `0x084BFC64` or `0x084C59A4`. They combine glyph words in scratch storage at `0x02020000` and `0x02020040`, with shifts in multiples of four bits, then copy completed tiles to VRAM beginning at `0x06000280`. Further matching work is retained in the experiment directory.

The primary compositor scans ahead until a control byte greater than F7 or a space byte 00. It adds the next space's width when present, truncates the accumulated width to a byte, and requests wrapping when the current x plus that width exceeds 208. It renders one character per call, accumulating pixels in 16 words; a glyph crossing an eight-pixel boundary contributes to both the emitted tile and the remaining scratch tile. Completed tiles set wait byte 0x13 so the interpreter yields.

The secondary compositor chooses its byte stream from work offsets 0x9E, 0xB2, 0xC6 or 0xDA for selectors 1 through 4; selector 0 and all other values use 0x03002B74. It measures until a byte greater than F7, increments secondary position after each glyph, and advances the main script by two bytes when the measured stream is exhausted. Its source retains the selector switch within the measurement loop, matching the observed reloads and jump table.
