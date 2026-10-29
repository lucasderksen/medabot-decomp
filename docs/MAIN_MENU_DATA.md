# Main-menu, save and credits data

`src/main_menu_data.c` reconstructs 3,530 bytes in 152 objects with the normal
modern GCC data profile. The complete `08483534..08483FD8` tail contributes
2,724 bytes; 53 ASCII credits strings at `080AFCF4..080B000E` and the three
credits-list pointers at `080B0014..080B0020` contribute another 806 bytes.
Callback entries use function-symbol relocations, including the four callbacks
whose bodies remain assembly. This batch adds no game-C functions.

The main callback directory contains 30 pointers. The next 40 pointers are
three substate banks of 10, 15 and 15 entries, selected by `0805C0D4`,
`0805CB50` and `0805D704`. Subsequent save, name and related menu directories
contain 7, 14, 8, 7, 8, 16, 10 and 11 entries. Physical boundaries follow the
next object, not the maximum state observed in a playthrough.

The serializer signature is `MEDAROT2 Ver.KBT` plus NUL; the save signature is
`MEDAROT2 NATSUME` plus NUL. Both occupy 17 bytes. The default encoded name
occupies five bytes including FE. Its pointer directory contains one pointer.
Two save-signature alignment bytes and three default-name alignment bytes
are separate objects. The leading palette contains 16 halfwords; its consumers
copy eight words. The following 64-byte boolean lookup is read by `0805B5FC`.

The scene-to-cursor lookup contains 192 bytes. The next cursor data consists
of ten stored X/Y tile-coordinate pairs, two choices of four X offsets,
two choices of four Y offsets and two choices of four frame/group halfwords.
`080605A0` multiplies tile coordinates by eight and selects an animation phase
with `(timer >> 3) & 3`. The timer resets after 96; its halfword increment also
wraps at FFFF. Scene choice 10 reads coordinate bytes from the adjacent X-offset
object in the reference. Stored lengths describe physical objects and do not
justify adding a clamp or changing that behavior. The existing matching
consumer expressions are retained.

`08060620` uses eleven block selectors, indexed by phase/10, to copy a
0x1E0-byte block from `(selector + 1) * 0x1E0`. A separate zero byte aligns
the following callbacks. The 15-by-4 preset-item table is read by `080619B0`:
FF ends a row, and item 20 has an additional mode-dependent condition. Its
consumer remains assembly; the table alone does not establish menu semantics.

The credits directory selects lists with 31, 29 and 107 entries. Their 167
pointers refer to 53 distinct ASCII strings, including a shared blank line.
All string storage and zero padding are retained; the last string ends before
the unrelated bytes at `080B000E`. `08067974` consumes the three line counts
stored at `08483C10`. The general label directory at `08483ED8` contains 64
pointers to packed FE-terminated strings, followed by no extra label; the last
string has three separate zero alignment bytes.

Validation commands:

```text
python tools/match.py build/more/main_menu_data_production_spec.json --output-dir build/more/main_menu_production
python tools/check_main_menu_data.py --output build/more/main_menu_cpu.json
```

All 152 data sections and all functions in the six sources whose declarations
were consolidated match in isolated compilation. The CPU checker runs original
Thumb code for 604 dispatcher cases, 2,156 cursor cases, 64 label lookups and
64 boolean lookups. Dispatch cases intercept only the selected callback body;
the dispatchers' real scroll and frame updates execute, and preserved registers
and stack are checked. Cursor/lookup cases use no stubs. Credits checks validate
the pointer/count layout and string ranges, not rendering or full menu flow.
