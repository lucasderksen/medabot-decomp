# Equipment and encounter storage

`src/encounter_records.c` reconstructs all **13,252 bytes** at
`083BEB94..083C1F58` in five objects. Shared bounds and the observed 40-byte
record layout are in `include/encounter_records.h`.

| ROM range | Storage |
| --- | --- |
| `083BEB94..083BEC10` | 124 byte palette selectors |
| `083BEC10..083BF210` | 192 eight-byte equipment records |
| `083BF210..083BF510` | 192 four-byte weighted encounter choices |
| `083BF510..083C1B80` | 246 forty-byte encounter records |
| `083C1B80..083C1F58` | 246 pointers, one to each consecutive encounter record |

`0804387C` copies equipment byte zero to work `C29`, then clears `C2B`.
`08011DE4` copies the first two bytes and uses byte one as a label selector.
`08048088` returns equipment byte two or three for input modes zero or one.
The last four bytes of every stored equipment record are zero.

`08011E20` selects one of four encounter indices using random thresholds
39, 69 and 89, giving 40/30/20/10 weights when the random helper returns
0..99. Every stored choice is below 246. When work `C2D` is nonzero, it uses
the existing work `C2A` encounter index instead. It copies the selected forty
bytes to `03001800` through the original byte-copy helper.

The encounter header contains an asset index, an unresolved byte, a member
count, and a selection mode. Three twelve-byte members follow. Their first
four bytes feed the four-part display/setup helpers; the remaining eight bytes
are retained without speculative field names. `08011FEC` and `08012024` use
the header's member count and stride twelve. If selection mode is zero,
`08011E20` makes four independent weighted draws for each of the three members,
then writes that member's four results. **All 246 stored records have mode one**,
so the random-parts branch is bypassed for this bank.

Equipment and choice indices are unchecked bytes despite only 192 stored rows.
Indices 192..255 read adjacent ROM storage: equipment reads continue into the
choice bank, and choices continue into the beginning of the encounter bank.
The affected readers use integer ROM address arithmetic before conversion to
pointers. Palette consumers use the same form for unchecked part indices.
All 42 functions in the five affected source files remain byte-identical under
their existing agbcc profiles; no game-code or function credit is added.

`tools/check_encounter_records.py` executes the original Thumb readers and the
real `08041D04` copy helper. Only `08043C94` is stubbed with explicit random
values. It checks 1,024 equipment queries, 512 copies, 2,304 weighted encounter
loads and all 246 direct loads, including all 64 extra equipment/choice indices.
Full work/transfer/scratch buffers, saved registers and SP are compared.
A separately labelled synthetic ROM control changes record zero's mode and
three choice lists to exercise twelve independent random-parts draws. Its
reverse-order choices detect premature overwriting of the source choices.
This control is not evidence that a shipped record enters that branch.

Reproduction artifacts are `build/more/encounter_records*_spec.json`,
`encounter_*_spec.json`, `encounter_records_audit.json` and
`encounter_records_cpu.json`. The full gate is `checkpoint_encounter_records.log`.
