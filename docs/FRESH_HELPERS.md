# Later small helpers

The independently referenced block is 08048000..0804842C, 1,068 bytes in eleven functions. Calls at 0804E810/0804E87E enter 48000; the preceding function returns at 47FFA with its final pool at 47FFC. The next dispatcher begins at 4842C and extends beyond the assigned limit, so it is excluded. Return sites, literal pools and direct calls establish these boundaries.

| Entry | End | Bytes | Status |
| --- | --- | ---: | --- |
| 08048000 | 08048038 | 56 | Integrated exact C |
| 08048038 | 08048088 | 80 | Integrated exact C |
| 08048088 | 080480D4 | 76 | Integrated exact C |
| 080480D4 | 080480E4 | 16 | Integrated exact C |
| 080480E4 | 08048174 | 144 | Integrated exact C |
| 08048174 | 08048210 | 156 | Integrated exact C |
| 08048210 | 08048288 | 120 | Integrated exact C |
| 08048288 | 080482CC | 68 | Integrated exact C |
| 080482CC | 0804830C | 64 | Integrated exact C |
| 0804830C | 080483F8 | 236 | Integrated exact C |
| 080483F8 | 0804842C | 52 | Integrated exact C |

Source and strict comparisons are staged under `build/experiments/initialization/fresh_helpers`; production integration remains coordinator-owned. `delivery_first_spec.json` verifies the first three delivered functions, 152 bytes total, using normal agbcc game flags plus `-fprologue-bugfix`.

48000 writes BG0 control 0500 and display control 1F60, configures the object helper with narrowed caller byte, 22 and 7, then clears byte 64 at the partial RAM work beginning 030064A0. The canonical word formal preserves narrowing immediately before the call.

48038 is a three-phase byte state machine on that work byte. Phase zero clears object callback byte 1B and advances; phase one runs 41CD4 and advances only after a nonzero result; phase two returns 41674's result. Other phases return zero. The state-pointer computation uses the base address plus 64 as a word expression, reproducing the reference's explicit addition. The zero-valued result local is also used for the reset store, preserving its observed register reuse.

480D4 reads a word from the pointer table at 08483ED8 indexed by a word-sized caller index. The pointer return is an observed ABI view; broader resource contents and bounds remain pending.

48088 accesses bytes two or three in eight-byte records at 083BEC10, selected by RAM byte 7FE relative to 030057E0; other input modes return zero. The strict source uses a table pointer and a separate word offset computed as index times eight, followed by the field offset; this preserves the observed address scheduling. 483F8 selects a byte from table 0847E644 when work byte C30 is not FF, otherwise work byte C31; a shared result local, retained work pointer and direct byte access reproduce every instruction in its strict source.

All first three batches (seven functions / 664 bytes) are integrated, with coordinator-confirmed full 8 MiB comparison. The 156-byte animation helper is strict exact and staged in delivery_timer; it selects the descriptor via work byte 7FE, requires work byte C34 and descriptor byte two, decrements delay byte C36, and otherwise uploads a descriptor-selected tile frame from the RAM source pointer at 030057DC to VRAM 06009020. Byte C35 wraps to zero on the FF frame sentinel, then increments after transfer; delay becomes two. DMA count is descriptor byte zero times sixteen halfwords, and the control register is read after writing it. Computing the source address before assigning the DMA pointer reproduces the observed scheduling without extra compiler flags.

480E4 copies three X/Y scroll pairs from the partial settings view at 03005310 (X halfwords1E/20/22, Y26/28/2A), resets animation delay, runs the bounded initializer sequence and sets work byte C4C. The settings type describes only observed fields. 48288 loads selected LZ77 resources into consecutive 900-byte VRAM slots until selector helper48684 returns FF; null resource entries fall back to index one. 482CC normalizes its input through48210 and loads the same selected resource into twelve such slots. 4830C performs a 104-word DMA3 copy into0202FA00 when the pointer table entry083F9980 is nonnull; otherwise it installs nine eight-word fallback blocks beginning0202FA00 through0202FB00. Every DMA control read is preserved. Pointer tables remain copied data pending independent bounds.

The completed combined delivery_all_spec.json verifies all eleven routines / 1,068 bytes together, including every literal pool and alignment byte. delivery_all_strict/results.json records exact lengths and SHA256 comparisons. No copied executable bytes, instruction patches or pinned registers are used in this source. The first seven were coordinator-confirmed integrated before the final three deliveries; subsequent integration status is owned by the coordinator.

48210 maps input zero through table083D2B26 and work byteC5C; retains nonzero inputs through AF, BF and CF category checks; and resolves D0..FE through pointer table08413EE0 plus work selector bytes beginningC38. Inputs aboveFE becomeFF. A result greater thanBF, exceptFF, maps to twice its offset fromC0 plus byte6 at03006D38 plus40. Signed word comparisons and the preserved no-op category branches are evidenced in the code; the broader semantic meaning of these categories remains provisional. Separate table/index/base-address locals prevent collapsing distinct source accesses; a separately computed doubled delta preserves final arithmetic order.

The coordinator integrated the completed combined translation unit and confirmed the full 8 MiB ROM SHA256. All eleven rows above are integrated. The strict combined delivery remains delivery_all_spec.json and delivery_all_strict/results.json.
