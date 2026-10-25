# Research tools (feasibility study, 2026-10-22)

These are the scripts and pilot materials behind [`docs/feasibility.md`](../../docs/feasibility.md). They were written for one-off measurements, not as project tooling. Many take a work directory as their first argument (the folder where the IDB dumps and JSON files were written) and the original machine's folders appear as placeholders (`<scratch>`, `<CD2 dir>`, `<XDK>`, ...), so expect to adjust paths before reuse. Nothing here contains game bytes or disassembly; those dumps are regenerated from the IDBs.

Python: run with `py -I script.py ...` (Python 3.13, standard library only). IDA scripts run inside IDA (IDAPython), e.g. through the `ida-pro-mcp` `execute_python` tool.

## scripts/

| Script | Runs in | Purpose |
|---|---|---|
| `dump_funcs.py` | IDA | Per-function features: normalized-instruction hashes (strict: registers and small offsets; loose: mnemonics only), callees, referenced strings. Set `MARKER_REGS=(13,14)` to drop RuffKing's `mr r13,r13`/`mr r14,r14` trace markers. |
| `cmp.py`, `cmp2.py`, `cmp3.py` | Python | Unique 1:1 hash matches between dumps, string-anchored pairs, per-reference contribution, Skate overlap |
| `pairs.py`, `classify.py` | Python | Classify differences between string-anchored pairs (offsets vs registers): the evidence for the compiler match |
| `xexinfo.py` | Python | Parse XEX2 headers: static library versions, base file format, original PE name |
| `libfuncs.py` | Python | Locate Lua/zlib functions in CD2 through reference symbols |
| `coff.py` | Python | Minimal MS COFF (PowerPC big-endian) reader: functions, relocations, relocation-masked comparison |
| `fingerprint.py`, `misses.py`, `cmpcomp.py`, `cmpcomp2.py` | Python | Compile Lua (or ATG) with both XDK compilers and flag sets, score against CD2, compare 8153 vs 8327 |
| `pdbinfo.py` | Python | Minimal PDB (MSF 7.0) reader: DBI modules, section contributions, `S_COMPILE2/3` compiler versions and LTCG flag |
| `pdbsum.py`, `libpaths.py` | Python | Code size per library/compiler; middleware build paths (versions) |
| `layout.py`, `inline.py`, `gamelayout.py`, `gameinline.py` | Python | LTCG tests: object grouping and order in CD2 vs RuffKing, callee-count asymmetry |
| `composition.py`, `unknown.py` | Python | Label CD2 functions by origin (game/XDK/Havok/...) and inspect unlabelled regions |
| `gamepairs.py`, `gamepairs_dump.py`, `pickdiff.py`, `truthsim.py` | Python | Game-code pair analysis and ground-truth similarity checks |
| `fuzzy.py`, `fuzzy2.py` | Python | Register-free opcode 4-gram matcher with an inverted index (RuffKing, Burn) |
| `contain.py` | Python | Containment-similarity coverage of game code |
| `propagate.py` | Python | Call-site name propagation from confident matches |
| `vtmatch.py`, `nameanchor.py`, `anchk.py` | Python | Vtable matching by slot voting; class-name-anchored vtables; precision check |
| `typeov.py`, `typeov2.py` | Python | CD2 class-name strings vs reference type names |
| `fncmp.py`, `jo.py` | Python | jeff vs IDA vs `.pdata` function sets |
| `pesecs.py`, `pedirs.py`, `peimports.py` | Python | PE sections, data directories, imports (and the `.reloc` check) |
| `mkpad.py`, `secdiff.py`, `textdiff.py`, `textdiff2.py`, `brdiff.py`, `rdatadiff.py` | Python | Relink experiment: padding object, per-section diffs, difference classification, REL24 hypothesis test |
| `tubound.py` | Python | Object-boundary padding statistics in RuffKing |
| `sizedist.py` | Python | Game-code function size distribution |
| `pickpilot.py`, `pilot_pick.py` | Python | Pilot function selection (agent pilot, manual pilot) |
| `scanlua.py` | Python | Scan game data for Lua scripts or bytecode |

## ltcg_test/
`main.c` + `build.ps1` build Lua 5.0.2 into an Xbox 360 exe with (`gl`) and without (`plain`) `/GL` + `/LTCG`; `cmp_ltcg.py` compares both builds with each other and with CD2.

## probes/
`gs.cpp` (stack-cookie code pattern), `fp.cpp` + `fpcmp.py` (`/fp:precise` vs `/fp:fast` vs `/fp:strict`), `fnbytes.py` (extract a function's bytes from a linked exe via its map).

## manual_pilot/
Hand-written matching attempts (`StartMission` and `OnEnter` exact, `InitParam` variants best 51%) and `check.py` (compile and diff against an IDB-dumped `target_<ea>.hex`). The attempt sources are not published: the exact ones are in `examples/matching/`, and the repository holds no unverified reconstructions of game code.

## agent_pilot/
- `BRIEF.md`: the instructions given to the pilot agents (packet layout, harness, rules, report format).
- `check.py`: the harness. It compiles with the fixed CD2 flags, masks relocated fields, prints a side-by-side disassembly diff via `dumpbin`, and logs every run to `attempts.log`.
- `haiku/`, `sonnet/`: each agent's `results.json` and the harness logs. Their `.cpp` attempts are not published (the exact ones are in `examples/matching/`; the others are unverified reconstructions of game code), and neither are the packet inputs (target bytes, disassembly, pseudocode, reference dumps, `resym` headers), which are game-derived.

## agent_pilot_large/
The pilot on four large functions: `BRIEF.md`, the harness `check.py`, `results.json` and the per-function harness logs.
The attempt sources are not published (none reached an exact match; the best was 89.5%).

## tu_pilot/, tu_pilot2/
The whole-file pilots: `BRIEF.md`, `results.json`, harness logs and the helper scripts. Their results are the source files
`src/CHARACTER/cNPCTintProfile.cpp` and `src/GangManager/cFactionConfigData.cpp` (with their headers); the agents' working
copies are not published.

## batch1/, batch2/
The measurement batches: per class, the candidate list (addresses and sizes), the agent's notes and `results.json`; the
batch's brief template and scripts. The sources they produced are in `src/`.

## scaffold/
The automatic set-up of 372 source files from registered classes; see its own `README.md`.

## compiler_re/
Reverse engineering of the XDK compiler's code generation; see its own `README.md`.

## jeff_patches/
- `rjkiv-jeff-v0.5.2.patch`: the two fixes needed for the original jeff to split CD2 (section-end guard in `executor.rs`; unfinalisable blocks are "not a function" in `slices.rs`).
- `chimpsatsea-jeff-fork.patch`: the fixes tried on the fork (its `.pdata` end-address assertion plus the section-end guard).
