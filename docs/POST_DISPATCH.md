# Helpers after the state-one dispatcher

The assigned block starts at `0x0804765C`, after the matching dispatcher at `4763C..4765C`, and stops at the validated function boundary `0x08048000`. Direct Thumb BL references confirm the accessor and wrapper entries; independent return sequences and aligned literal pools confirm their ends. The following worker starts at or after `48000`.

The first integrated delivery, `post_dispatch_ready.c/.h/.json`, contains 23 ordinary C functions and 560 strictly matching bytes. Normal agbcc with `-fprologue-bugfix` reproduces every requested section. The option removes unwanted LR saves from conditional leaf helpers and the count loop; non-leaf wrappers and simple getters already match with default flags. No instruction patches, inline assembly, or fixed registers are used. The complete ROM matches after integration of both batches and their typed-data table.

`4765C..476E8` copies the work byte at `030004DC` to `03005349` in case 0, then sets main state/substate to 1/1 and the `0300137C` word to 5 or 13 according to byte `03006468`. Case 1 sets state/substate 1/2 and that word to 0. `47850..47878` handles signed inputs 0..3 by setting state/substate 1/1 and the same word to 5. These describe observed state transitions without assigning broader gameplay roles.

The wrappers at `47BA8/47BB4/47BC0` forward a word argument to `74DE0/74B88/750F0`. Table getters at `47BCC/47BDC/47BEC` read pointer entries based at `083B6590/083BA658/083BBB4C`; the third indexes `row*4+index`. Pointed-to assets and the remaining table payloads remain copied.

`47D4C/47D58/47D74` read and update the word at `03002B70`. Addition wraps at 32 bits and then clamps unsigned values above 99,999. Subtraction computes a 32-bit difference and clamps a negative signed interpretation to zero; the original instruction sequence is preserved. No currency or gameplay meaning is inferred.

Wrappers `47D8C..47E4C` narrow their observed arguments to bytes before invoking earlier helpers. The two-argument wrappers at `47DC0/47DD8` substitute 1 for a zero second argument. `47E4C..47E50` is empty, including the reference alignment. `47F9C..47FBC` counts nine stride-eight records at `030017A0` whose byte 0 equals 3, using the existing partial `State0Record8` type.

The initial isolated batch retained nonmatching do-loop candidates for searches at `47EF0/47F50/47FBC`; the exact for-loop delivery below supersedes them. The intervening switches remain under investigation. The ordinary source is staged only after a byte match; no unverified definitions enter production.

Reproduce the exact delivery with:

```powershell
python tools/match.py build/experiments/compiler_input/post_dispatch_ready.json --output-dir build/experiments/compiler_input/post_dispatch_ready
```

A second integrated delivery, `post_dispatch_next_ready.c/.h/.json`, contains eight functions and 572 bytes with the same compiler flags. `47C00..47C24` calls the empty helper, clears BG0 scroll words, and resets two work bytes. `47C24..47C84` has a two-case display-effect sequence: case 0 invokes the existing start/resume effect routines and advances the work byte; case 1 polls a script helper, resets that byte and increments the second byte when complete. The four argument slots narrow the first three inputs to bytes and preserve the final script pointer.

`47C84..47CE4` computes a digit count with the copied `488AC`, obtains digits using `488E8` in reverse index order, adds 53, copies them to a selected buffer, and writes the FE terminator. `47CE4..47D24` copies at most 16 input bytes, stopping atFE, then terminates the destination. `47D24..47D4C` invokes the existing fixed-format writer `4126C(destination,value)`. It declares a ten-byte unused local digit buffer: agbcc retains this local array's twelve aligned stack bytes, exactly reproducing the reference's stack frame and table address. A scratch aggregate or removing the unused local does not match. No stack assembly or forced register assignments are involved.

These three functions copy the same four-pointer ROM object at `080ABD6C..080ABD7C` into a local structure. Its integrated typed-data delivery, `post_dispatch_buffers_ready.c/.json`, reproduces 16 bytes and points to `gState0TypedWork.bytes+0x9E/+0xB2/+0xC6/+0xDA`, the four observed RAM text buffers. This layout does not establish a broader size for the shared work object.

Searches `47EF0..47F50`, `47F50..47F9C`, and `47FBC..48000` scan the nine stride-eight records whose byte 0 equals 3. The first tests one of bytes 3..6 selected by the second argument and returns a flag. The latter two require all four bytes to equal the input, returning respectively the first matching index or -1, and a flag. Natural for/while forms match every byte; the first do-loop reconstruction emitted a rotated layout. The independently referenced boundary at 48000 closes this assignment.

Production totals are 32 ordinary C functions, 1,292 bytes, plus the 16-byte pointer table. The shared pointer structure is now canonical in `include/post_dispatch.h`; integration and a complete ROM comparison are confirmed. Switches `476E8..47850` and `47878..47BA8` remain copied at this checkpoint. The final integrated metadata lookup at `47E50..47EF0` now matches all 160 bytes with the same flags. It first checks the selected part through `47EF0`, repeats the record scan to obtain the index, calls `42B58(record.byte6,3,metadata)`, returns `metadata[1]-100`, and copies record byte 1 to byte 6 at `03006D38`; absence returns -1. An explicit `u32 address = i*8; address += (u32)base;` reproduces the reference ADD operand order. Its delivery is `post_dispatch_metadata_ready.c/.h/.json`; the parent confirmed integration and a complete ROM comparison.
