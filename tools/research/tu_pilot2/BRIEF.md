# Pilot: decompile one whole source file, GangManager/cFactionConfigData.cpp (Crackdown 2, Xbox 360)

Goal: reconstruct the C++ source file for `GangManager::cFactionConfigData` (and its header) so that every function in
it compiles to **byte-identical** PowerPC code. This pilot measures larger functions with the per-file method. Follow
the steps in order and report honestly; partial results are valuable data.

A previous pilot matched every function of `CHARACTER/cNPCTintProfile.cpp` this way. Its source is in
`<repo>\src\CHARACTER\cNPCTintProfile.cpp` and is a good model to read first: it's the
same kind of class, an RWS attribute handler with a registrar.

## Method (follow in order)
1. **Check the split.** Candidates are in `cFactionConfigData/targets/`:
   - F01-F17: every function in CD2 from `0x82675C08` to `0x826767E0`, around `MakeNew` (F07 `0x826761B0`) and `RetClassName` (F08 `0x82676278`). Some belong to neighbouring files. Decide which belong.
   - F18 `0x82FDCB00`: the registrar's dynamic initializer (registers the class name, `MakeNew` and size `0x50`).
   - F19 `0x83040248`: its at-exit destructor.
   - `cd2_vtable.txt`: CD2's vtable for the class, so you can tell which functions are this class's virtuals.
   - The RuffKing build (`reference_ruffking/`) has 5 functions for this class (destructor, `RetClassName`, constructor, `MakeNew`, `HandleAttributes`). **CD2's class is bigger** (`0x50` bytes vs RuffKing's `0x34`), so expect extra fields and possibly extra functions.
2. **Scaffold the header.** Read all of the file's assembly first, then write `cFactionConfigData/work/cFactionConfigData.h`:
   - Base classes come from the repo headers: `rws/attributes.h`, `rws/classfactory.h`, `cd2/memory.h`, `cd2/layout.h`. Read `<repo>\include\README.md`.
   - Reference dumps are in `<repo>\include\ref\ruffking\`: `GangManager_cFactionConfigData.h` (with dependencies) and `RWS_DynamicAllocationPolicy.h`.
   - Work out CD2's real layout (`0x50` bytes) from the offsets used in CD2's code, and end the class with `CD2_LAYOUT_CHECKS`.
3. **Implement the functions** in `cFactionConfigData/work/cFactionConfigData.cpp`. Skip any that resist, then come back.
4. **Attack the tough ones** with `--diff Fnn` and `NOTES.md`.
5. **Keep notes:** append every non-obvious finding to `NOTES.md`.

## Harness

    py -I <scratch>\tupilot2\check_tu.py <scratch>\tupilot2\cFactionConfigData <file.cpp> [--diff F15]

It compiles with the fixed CD2 compiler and flags and pairs each target with your best-matching compiled function. It
prints a per-function table, and the differing regions for `--diff`. Linker-filled fields are masked. The repo
`include/` directory is on the include path. Targets you decide don't belong can be ignored; say so in the report.

## Budget and discipline
- At most **35 harness runs in total**. Read each input once; work from the harness output afterwards.
- Work only in `<scratch>\tupilot2` (`cFactionConfigData/work/`, `NOTES.md`). Don't modify the harness or the repo. Describe recommended repo header changes in your report.
- Prefer natural source a programmer would have written.

## Final report
Write `<scratch>\tupilot2\results.json`:
`{"functions": [{"id": "F15", "address": "...", "belongs": true/false, "exact": true/false, "best_percent": n, "size_insns": n, "notes": "..."}], "harness_runs": n, "header_notes": "...", "split_notes": "..."}`
Then reply with a short summary: the split decision, what matched, what didn't and why (especially the large
functions), what you added to `NOTES.md`, and any repo header changes you'd recommend.


