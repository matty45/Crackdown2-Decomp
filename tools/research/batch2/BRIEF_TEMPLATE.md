# Measurement batch 2: decompile one gameplay source file, @@CLASS@@ (Crackdown 2, Xbox 360)

Goal: reconstruct the C++ source file that defines `@@FULL@@` (and its header) so that its functions compile to
**byte-identical** PowerPC code. Batch 1 measured simple editor-attribute classes. **This batch measures gameplay logic**
(state machines, physics, maths), so the logic functions are what matter most. Report honestly: partial results and
clear blockers are valuable data.

## Read first (once)
- `<repo>\docs\matching-notes.md`: shared compiler idioms and traps (your copy, to append to, is `@@ROOT@@\@@CLASS@@\NOTES.md`).
- Model files, all byte-exact:
  - `src\VFX\cAmbientVFXSpawner.cpp` (RetClass/IsA/StaticCreateClass pattern, LTCG-only functions);
  - `src\VFX\cRopes.cpp` (STL vectors, pools, multiple bases);
  - `src\GameManagement\cGameModeArena.cpp` (two vtables, messages, std::list/string).
- `<repo>\include\README.md`: the shared headers. **Reuse them; don't redefine their types:**
  - `rws/attributes.h`, `rws/classfactory.h`, `editor/guid_event_handler.h` (GUID lookups via `cGUIDLinker<T>::LinkToObject`);
  - `fun_runtime/class.h` (`cClass` for RetClass/IsA/StaticCreateClass), `fun_runtime/randgen.h`;
  - `cd2/memory.h`, `cd2/layout.h`, `rw/rwmem.h`.

## Method (in order)
1. **Split.** `@@CLASS@@\candidates.txt` lists the candidates in `@@CLASS@@\targets\`:
   - the functions around `MakeNew` (wide window; many belong to neighbouring files);
   - vtable entries that the link order list moved into the hot region (some are shared base-class functions);
   - the registrar's initializer and at-exit destructor.

   `cd2_vtable.txt` is CD2's vtable for the class. `reference_ruffking\` holds the class's object file from the later RuffKing build (pseudocode, disassembly, vtables). Its code may differ from CD2, but it shows which functions live together. Decide which candidates this file defines.
2. **Header.** Read the file's assembly, then write `@@CLASS@@\work\@@CLASS@@.h`.
   - Work out CD2's layout from the offsets CD2's code uses. The object is @@SIZE@@ bytes in CD2.
   - End each class with `CD2_LAYOUT_CHECKS`.
   - Dump reference types with `powershell -File <repo>\tools\headers\ref_dump.ps1 "Ns::Type" -NoDeps` (`-List "name"` finds full names). Use `-NoDeps` for big classes; with dependencies, resym can crash.
   - For unknown bases, a minimal stand-in of the right size and virtual-slot count is fine. Name it and say so.
3. **Implement** in `@@CLASS@@\work\@@CLASS@@.cpp`. Do the easy functions first, then the logic functions. Skip any that resist and come back to them.
4. **Attack the tough ones:**
   - `--diff Fnn`;
   - the notes;
   - listings (below);
   - sweeps: `py -I <repo>\tools\sweep.py <exe> <spec.py> <workdir>` compiles named source variants and reports each one's match. See its docstring, and `tools\research\compiler_re\sweeps\arena_handleattributes.py` for an example spec.
5. **Notes:** append every non-obvious finding to `@@CLASS@@\NOTES.md`.

## Harness (PowerShell; set the variable in the same command each time)

    $env:CD2_EXE='@@EXE@@'; py -I <repo>\tools\check_tu.py @@ROOT@@\@@CLASS@@ <your .cpp> [--diff Fnn] [--ltcg]

- **List every function you implement in `work\map.txt`**, one `Fnn symbol-substring` per line. Mapped targets are verified by symbol. Only trust results without "(similarity pairing)".
- **CD2's game code was built with link-time code generation (LTCG).** Most functions match in the plain build the harness does by default. A function that loads float constants is different: CD2 usually loads them from a constant pool through a base register (`addi rN, <pool>` then `lfs f0, disp(rN)`), which a plain build can never produce. For those, add `--ltcg`. It builds the file under LTCG with a model of the rest of the program and adds an `ltcg` column for mapped targets. A function that is exact only under LTCG counts as exact; say so in results.
- **Listings** show source lines interleaved with code and every temporary's stack slot (useful for stack-layout puzzles):

      powershell -File <repo>\tools\research\compiler_re\cc.ps1 -Src <your .cpp> -Out <work>\l -Extra @('/FAcs', '/Fa<work>\l.cod')

## Budget and discipline
- **Token budget: about 300k.** There is no cap on harness runs, but each run costs tokens; prefer `--diff` on one target and local experiments.
- Read each input once; work from harness output afterwards.
- Write only in `@@ROOT@@\@@CLASS@@\work\`, `@@ROOT@@\@@CLASS@@\NOTES.md` and `<repo>\include\ref\ruffking\` (dumps only). Never modify repo files.
- Prefer natural source a programmer would have written.

## Final report
Write `@@ROOT@@\@@CLASS@@\results.json`:
`{"class": "@@CLASS@@", "functions": [{"id": "Fnn", "address": "...", "belongs": true/false, "kind": "logic|boilerplate|compiler-generated", "exact": true/false, "exact_build": "plain|ltcg", "best_percent": n, "size_insns": n, "notes": "..."}], "header_notes": "...", "split_notes": "...", "stand_ins": ["..."], "shared_headers_used": ["..."]}`

- "logic" = gameplay code (state machines, update/tick, maths); "boilerplate" = attribute handling, factory/RTTI, constructors/destructors, registrars.

Then reply with a short summary:
- the split decision;
- what matched and what didn't, and why, **separately for logic and boilerplate functions**;
- the biggest blockers;
- what you added to the notes;
- recommended shared-header changes.
