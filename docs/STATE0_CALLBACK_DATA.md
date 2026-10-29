# Action and map callback tables

`src/state0_callback_data.c` reconstructs 7,216 bytes: 1,804 function pointers
in 72 tables, compiled with the normal modern GCC data profile. Seventy action
tables cover the existing `gActionDispatchCallbacks_*` declarations; the two
map tables at `083ACE24` and `083AD080` contain 144 and 192 physical pointers.
The header records each physical bound. Callback entries use function-symbol
relocations, preserving repeated handlers and reserved dummy-handler slots.

The action dispatchers select with transfer work byte AA and clear byte B5
before calling. Map dispatchers select with `gUnknown_0300137C`. The phase
dispatcher is gated by `0803EED8`; its alternate render-mode path can clear
an object buffer. Table reconstruction does not change those dispatchers.
Three callback bodies remain assembly: `08020B4C`, `08028130` and `0802D8D0`.
Their pointers are represented in source without counting their bodies as C.

The 724 distinct handler declarations were checked against their current
definitions. `0802FBF4`'s old m2c source carried an unused argument. A fresh
`tools/m2c_candidate.py 0x0802FBF4 --match` produces a no-argument signature
and matches all 72 bytes. Removing the unused formal from the existing source
and its declaration also matches all 72 bytes under its unchanged agbcc flags.
This resolves the callback signature without a cast or a new function claim.

All 72 production data sections match. `tools/check_state0_callback_data.py`
runs every physical slot through its actual native dispatcher with three
initial B5 values: 5,412 cases. It checks the selected pointer, complete transfer
work bytes, preserved R4..R11 and stack. The selected callback body is explicitly
intercepted; `0803EED8` is stubbed to return zero, and render mode stays zero.
The check does not execute every callback body or the alternate rendering
paths. The 1,804 slots are storage coverage, not a claim that every slot is
reachable during gameplay.

```text
python tools/check_state0_callback_data.py --output build/more/state0_callbacks_cpu.json
python tools/match.py build/more/state0_callbacks_production_spec.json --output-dir build/more/state0_callbacks_production
```
