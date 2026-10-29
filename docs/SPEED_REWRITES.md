# Reusable speed rewrites (7 October 2026)

The first speed-pipeline trial starts from `e8b168e`. The isolated
`speed_pipeline` checkout rebuilt all 8,388,608 ROM bytes identically before
candidate work. Root supplied 120 remaining draft inputs: 60 larger functions
and 60 historical near candidates. Their selection scores are historical;
only the results below are fresh compiler and byte checks.

## Learned source rules

`tools/rewrite_drafts.py` now tries four bounded, conservative variants:

- `captured_key_identity`: `(keys & 1u) & keys` for an ordinary unsigned
  snapshot, or a new unsigned snapshot assigned at the original key-read
  expression. Each direct RAM site gets its own fresh local, including sites
  in different arguments of one call. The rule does not move, narrow, merge or
  repeat a RAM read. Precedence-sensitive partial expressions, volatile locals
  and shadowed unsigned locals are refused. The existing `read_key_low_byte`
  rule remains a separate byte-gated candidate transformation.
- `share_full_width_zero`: a `u32` zero feeds proven integer stores and integer
  returns. Accepted lvalues include explicit integer casts, typed scalar
  pointers, byte backing arrays and established top-level integer members of
  `FrameObject`. Unknown, pointer and nested union members are refused.
- `share_zero_at_first_store`: the same zero is initialized inside the first
  store. A straight-line top-level store must dominate all replacements; the
  rule refuses preceding branches, loops, labels and returns.
- `sink_pointer_initialization`: combine an adjacent pointer-address
  assignment with its store. The value must be a literal or an ordinary
  integer local, and the address cannot contain a call or increment. Memory
  value expressions and volatile local values are refused. This can combine
  with the shared-zero rule without extending the hardware pointer lifetime.

All new rules edit only the named function. Comments and strings are preserved.
Fresh names avoid collisions. The 40-variant budget reserves 12 slots for new
rules and their interactions, deduplicates identical sources and forbids
combining the two alternative zero initializations. Generation stops once
the old and learned slot budgets are filled; it stores at most the final
40 variants plus one initial applicability result per transform. Legacy-only
runs can still fill all 40 slots, and sparse old sets allow more learned rows.

## Compiler and acceptance bounds

The default profile set remains the draft's historical best plus
`-fprologue-bugfix`, deduplicated. Only captured-key-identity variants and the
unmodified `original_profile_control` additionally try:

```text
-O2 -fprologue-bugfix -fno-force-mem
-O2 -fprologue-bugfix -fno-force-mem -fno-cse-skip-blocks
```

These retain expensive optimization passes, which remove unused constants
that can survive text-exact `-O1` probes. `--all-profiles` explicitly opts every
variant into the wider, more costly profile sweep. The larger trial below
found no benefit from that broad sweep for zero variants, so it is not the
final default.

Each task uses root's reusable `batch_session()` matching context. A result
requires exact complete function bytes, no extra candidate sections, a fresh
production `-Werror` compile and no extra strict-object sections. Staging is
not integrated progress; root still reviews declarations, integrates and
runs the complete-ROM checkpoint.

Persistent failed-probe keys are `v2:` hashes of source, flags and compilation
context. Context includes the compiler binary contents, all project headers,
the m2c macro header, the compiler adapter, `config/symbols.json` and the
baseline ELF contents. It is computed once per immutable worker process.
Older text-and-flags-only cache keys cannot suppress retries. Header, symbol,
compiler and baseline changes invalidate the cache.

## Measured acceptance

The first bounded comparison used eight targets, up to 12 legacy variants and
12 learned variants plus an original-source profile control per target. A
second comparison used 16 additional targets, up to 12 legacy variants and
13 learned/control variants. Both used two worker processes. Compiled probe
counts include attempts rejected for draft type errors; they are not match
counts. The wide profile sweep in these historical trials corresponds to the
final tool's explicit `--all-profiles` option.

| Trial | Legacy probes | Additional learned probes | Strict new functions / bytes | Wall time |
| --- | ---: | ---: | ---: | ---: |
| First eight targets | 67 | 200 | 1 / 76 | 32.21 s combined |
| Additional 16 targets | 171 | 559 | 0 / 0 | 22.73 s legacy; 57.97 s learned |
| Changed safety-guard variants, cached | 0 | 16 | 0 / 0 | 3.74 s |

The trials cover 24 distinct remaining functions and 1,013 unique probe
attempts. They produced one distinct strict acceptance, `08025308`, 76 bytes:
`read_key_low_byte+captured_key_identity` with `-O2 -fprologue-bugfix
-fno-force-mem -fno-cse-skip-blocks`. Its single key read is a byte snapshot at
the original short-circuit expression, followed by the unsigned identity.
Its helper declaration is explicitly `extern` for integrator compatibility.
Final default-policy revalidation reproduced it in nine probes / 1.80 seconds;
`tools/accept_draft.py` then repeated the strict gate. Normal staged paths are
`build/m2c/sub_08025308/{candidate.c,spec.json}`.

These are acceptance measurements on a bounded selected sample, not a
forecast of whole-project throughput. No larger function was accepted by
this trial. Larger drafts still need type and control-flow repairs before
register-allocation variants can help them.

## Reproduction and focused tests

```powershell
python -m unittest discover -s tests -p test_rewrite_drafts.py -v

# Use freshly generated or separately preserved raw draft inputs for comparison.
python tools/rewrite_drafts.py --legacy-only --variant-limit 12 --jobs 2 --names sub_0806DAA4 sub_0803F998 sub_080611E8 sub_08064A80 sub_080256EC sub_0800EA98 sub_08025308 sub_080238A0
python tools/rewrite_drafts.py --learned-only --all-profiles --variant-limit 13 --jobs 2 --names sub_0806DAA4 sub_0803F998 sub_080611E8 sub_08064A80 sub_080256EC sub_0800EA98 sub_08025308 sub_080238A0

# Bounded final-policy run; valid cached failures are skipped.
python tools/rewrite_drafts.py --learned-only --variant-limit 13 --jobs 2 --limit 16
```

The 30 focused tests cover unsigned identity, memory-read preservation,
independent multi-argument captures, scope, comments, idempotence, zero
initialization dominance, integer type proofs, pointer/value restrictions,
reserved variant slots, profile gating and content-based cache invalidation.
Root owns the separate matching-session and complete-ROM validation tests.

Ignored local reports: `build/speed_rule_benchmark.json`,
`build/speed_rules_second_{baseline,learned}.log`,
`build/speed_rules_final_guards.log`, `build/speed_rules_final_winner.json` and
`build/speed_rules_final_acceptance.log`. The first report retains the exact
successful source and per-target fresh attempt counts; historical selection
metadata remains in `build/speed_evaluation_set.json`.
