# Later display helpers

The assigned interval is `0x08046D1C..0x0804763C`, ending before the existing dispatcher. Address-based function and RAM names remain provisional.

The first three ordinary C functions are integrated in `src/later_helpers.c`, verified byte-for-byte with normal agbcc default flags: `0x08047414..0x08047428` (20 bytes), the empty function at `0x08047570..0x08047574` (4 bytes including alignment), and `0x08047574..0x0804763C` (200 bytes). The original staged source, header, manifest, and verification results remain under `build/experiments/compiler_input/later_helpers_ready*`. The parent worker integrated these sections and the two helpers below, totaling five functions and 752 bytes; the complete ROM still matches.

The setup routine stores three pointers at offsets 0, 4, and 8 of `RecordDisplayWork`: a `RenderWork *`, a source pointer, and a data pointer. It also clears `RenderWork.byte1094`. Production now uses the three canonical pointer fields directly, with the same exact output.

The reset routine calls the byte-zero loop at `0x08049714` on fifteen RAM regions. The verified destination/length pairs are `03005310/60`, `030057A0/56`, `03006D14/4`, `030057DC/4`, `0300534C/4`, `030055A0/512`, `03006D40/512`, `03006F40/52`, `03006D38/8`, `03006D20/16`, `030057D8/4`, `03005590/4`, `03005350/576`, `03006D30/4`, and `030064A0/0x874`. These lengths describe observed writes rather than complete semantic buffer types. The reset helper itself remains copied outside this assignment.

Other established function boundaries are `46D1C..47204` (1256 bytes), `47204..4725C` (88), `4725C..47414` (440), and `47428..47570` (328). The first routine composes display records, the second updates flags in two 48-byte records, and the latter routines dispatch asset operations and update interpolated values; detailed roles remain under investigation.

Verification command:

```powershell
python tools/match.py build/experiments/compiler_input/later_helpers_ready.json --output-dir build/experiments/compiler_input/later_helpers_ready
```

The fourth integrated helper, originally delivered as `later_helpers_next.c/.h/.json`, reproduces all 88 bytes of `47204..4725C` with default flags. It loads the pointer stored at `03005308` separately for each of two 48-byte records. At offset 44, bit 0 is cleared and bit 1 set when bit 0 was set; otherwise bit 2 is cleared only when bit 1 is clear and both bits 3 and 2 are set. Nested conditions preserve the three separate reference tests. Explicit invariant locals and an integer byte-address calculation preserve initialization and ADD operand order without instruction patches or register constraints.

The asset-operation dispatcher at `4725C..47414` is now integrated and strictly verified: 440 bytes, default flags, staged as `later_helpers_dispatch_ready.c/.h/.json`. It has eight argument slots: the first and fifth are unused, followed by the observed work pointer, signed case selector, table index, palette value, bank value and enabled/mode value in their original positions. Its decoder calls use the canonical seven-argument `sub_08045E6C` interface. Cases 0/1/2/3 select command tables at `0807EE70`, `0807F610`, `0807FDB0`, `08080550`, with table row widths of 16/16/16/32 bytes and starting tile values 320/416/480/544. Bank 2 adds 352. Cases 1 and 2 additionally walk four-byte commands while their low six bits are nonzero, skipping entries whose byte1 has bit7 set, and invoke `sub_08046034` with the corresponding command table. The decoder receives the word's low six bits; the traversal reads byte fields. Separate decoder and traversal cursor lifetimes, with pointer initialization before its offset, reproduce the reference's two register-copy instructions and long-branch layout. No instruction patches or fixed registers are used.

Production uses the canonical `RecordDisplayWork` fields at offsets 0/4/8 directly. The original staged local view remains as matching evidence; its field offsets agree. The shared eight-slot interface is now canonical. The command tables are integrated as typed data, as described below.

Four command tables are independently bounded and integrated as typed `u32` arrays in `src/later_commands.c`; the exact staged evidence remains in `later_commands_ready.c/.json`: `7EE70..7F610`, `7F610..7FDB0`, and `7FDB0..80550` each contain 122 rows of four words (1,952 bytes apiece); `80550..81490` contains 122 rows of eight words (3,904 bytes). Every row reaches a zero low-six-bit selector within its fixed width. The following byte-order table begins at `08081490` and has a separate literal reference at `08046654`, excluding it from the final command array. Raw command words preserve the observed selector, skip bit, and remaining unknown fields. Their 9,760 bytes are integrated, with a passing full-ROM comparison.

`src/later_renderer_order.c` reconstructs the 50-byte flip-path selector
ordering at `08081490..080814C2`; two following padding bytes remain raw.
Those bytes are a permutation of 0..49, and the preceding command tables' stored
low-six-bit selectors do not exceed 49. `tools/check_later_renderer_order.py`
executes only the original three lookup instructions for all 256 byte indices,
including neighboring ROM reads; it does not test the complete renderer.

The 1,256-byte compositor at `46D1C` has a complete isolated C reconstruction but does not yet match. It records a request in one of the 48-byte records when input flag4 is clear. A pending flag causes template decoding and caching at `work+12+slot*96`; a later flag8 path restores cached templates, concatenates non-terminated command words into a zeroed 32-word buffer, and calls the copied renderer at `465B8`. Byte16 selects which template command list contributes. The four 24-byte ROM templates at `7EE10/7EE28/7EE40/7EE58` have a separate exact 96-byte delivery, `later_templates_ready`, now integrated with a passing full-ROM comparison. Initial compositor output is 1,220 bytes; mode reuse and command-buffer pointer lifetime variants remain unmatched. Flags and broader role names are provisional.

The isolated compositor candidate also passes 34 optional emulated comparison scenarios, saved as `later_compositor_base_address/cpu-results.json`. These cover both record slots, flag branches, a negative-index sentinel, final command-table rows, and coordinate/priority arguments. The check compares record, template, work and marker RAM plus normalized dependency calls, and poisons caller-saved registers after those calls. Decoder `45E6C`, adjustment `46034`, renderer `465B8`, and `memset` are deterministic stubs; this is neither a hardware test nor full-game validation. Reproduce with `C:\ProgramData\miniconda3\python.exe build/experiments/compiler_input/verify_later_compositor_cpu.py`. The tested candidate is 1,240 bytes against the reference's 1,256 and remains isolated.

A local scratch aggregate containing the tile-base halfword before the 32-word command buffer reproduces the reference's 1,256-byte section, 184-byte stack frame, tile base at SP+16 and buffer at SP+20. It remains a structural checkpoint rather than a byte match. Separate locals are placed in the reverse order regardless of declaration order; sequential command-pointer/selector assignments and supported loop-option variants do not yet resolve the register allocation.
