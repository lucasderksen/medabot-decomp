# Working on the Medabots decompilation

These rules apply to every contributor, human or AI agent.

Keep the complete ROM byte-identical. Stage candidates with `tools/match.py`,
integrate them, then run `tools/build.py`. Record compiler settings, observed
behaviour and matching status accurately.

## Git workflow

`main` holds only integrated, fully matching trees.

- Parallel workers use their own worktree and branch, created with
  `python tools/worktree.py create <identity>` (path
  `../medabot-decomp-worktrees/<identity>`, branch `work/<identity>`). Run
  `python tools/build.py` there once before `tools/match.py`. Never build
  or stage experiments in another worker's checkout.
- Integrate in the main checkout, then commit each accepted batch with
  `python tools/checkpoint.py "<batch summary>" --push`. It reruns the full-ROM
  build and the tests in that invocation and commits nothing on failure; an
  older `build/medabots.gba` is not evidence that the latest attempt passed.
- Every push to `main` records progress (code region and whole ROM) via
  `.github/workflows/progress.yml`; never edit the `progress` branch by hand.

## Draft generation

Before hand-writing a function, try `python tools/m2c_candidate.py <address>
--match` (see [docs/M2C.md](docs/M2C.md)). It decodes the function from the ROM,
runs m2c with the project headers and compiles the draft through the real agbcc
profile. Treat the output as a draft: verify bounds, replace placeholder names
and casts, and stage the final source with `tools/match.py` as usual.
For any mismatch, `python tools/asm_diff.py <spec> --output-dir <dir>` shows an
aligned instruction diff. For a near-miss (right size, a few differing
instructions), `python tools/permute.py <name> --cflags="..."` searches C
variations, keeps `register T x asm("rN")` pins in place, and byte-verifies any
score-0 result.

## Matching process

- Time-box each function to about 25 minutes of hand work. If it is not
  matching by then, start `tools/permute.py` on it in the background, record
  one line with `tools/target_queue.py --record <name> --minutes N --note ...`
  and move on. Do not write per-function research documents.
- For register-only near-misses run `tools/try_flags.py` (every flag profile the ROM already uses),
  `tools/try_wraps.py` and `tools/try_decls.py` before the
  permuter (see docs/IDIOMS.md). Then try the variable-sharing sweeps
  `tools/try_reuse.py`, `tools/try_merge.py` and `tools/try_scope.py`
  (output in build/sweeps/). They change semantics freely: accept a winner
  only after checking by hand that every merged or reused variable is dead
  where it is reused.
- Fall-off-end returns are accepted when the reference itself returns
  whatever is left in r0. Each such function gets a one-line comment saying
  so ("Falls off the end like the reference", inside the body) and naming
  what every caller sees in r0 on the fall-off paths; accept it with
  `tools/accept_draft.py --fall-off-end`.
- Also accepted, each with a one-line comment saying exactly what it
  reproduces: `volatile` parameters when the reference stores and
  immediately reloads them and no other form fits, and uninitialized reads
  that copy the reference (including real bugs in the shipped ROM).
- Fake matches are accepted once the time-box is spent and no natural form
  has turned up: register pins (`FORCE_REGISTER(T x, rN)` from
  `include/global.h`),
  `do { } while (0)` wraps beyond what reads naturally (nested wrap padding),
  and dead stores or dead padding statements. Behaviour must stay that of
  the reference: a dead store must really be dead, and a wrap must not
  capture a `break` or `continue`. Put a one-line
  `/* FAKE MATCH: <what and why> */` comment on each fake construct so
  `grep -rn "FAKE MATCH" src` finds every one for a later cleanup pass.
  Still rejected: `volatile` on ordinary RAM, instruction patches and
  assembly presented as C.
- Data needs no native consumer check. A data span is accepted as typed
  source once the full ROM stays byte-identical and its type and bounds
  follow from the ROM (referenced labels, alignment, record size). Bytes
  whose consumer or meaning is unknown become a labelled
  `const u8 gUnknown_<address>[]` array instead of staying `.incbin`.
  Native fixture checks are optional quality work, not an acceptance gate.
- Workers integrate in their own worktree with
  `python tools/m2c_integrate.py --prefix m2c_<identity>` so new source files
  never collide, then commit 5-15 matched functions per commit on their branch.
  One integration checkout merges worker branches and runs one
  `tools/checkpoint.py` per merged batch.
- Functions that do not match yet are NONMATCH functions
  (`src/non_matching/<name>.c` with the original code in
  `asm/non_matching/<name>.inc`, see [docs/NONMATCHING.md](docs/NONMATCHING.md)).
  Keep the C attempt there and its row in docs/NONMATCHING.md at the best
  result; `python tools/try_draft.py <name> src/non_matching/<name>.c` compiles
  it as it is. `tools/m2c_integrate.py` replaces the NONMATCH entry once the
  function matches. Unmatched code that is still an `.incbin` gap gets one with
  `python tools/nonmatch.py <name>`.
- Only document findings that help many functions (compiler idioms in
  [docs/IDIOMS.md](docs/IDIOMS.md), struct
  layouts); put struct knowledge in `include/` headers rather than prose.
  The remaining unmatched functions and fake matches are listed in
  [docs/NONMATCHING.md](docs/NONMATCHING.md).
