# Measurement batch: decompile one whole source file, @@CLASS@@ (Crackdown 2, Xbox 360)

Goal: reconstruct the C++ source file that defines `@@CLASS@@` (and its header) so that its functions compile to
**byte-identical** PowerPC code. This batch measures the per-file method on varied code, so follow the steps and report
honestly. Partial results are valuable data.

Two earlier files were done this way and are good models; read them first:
- `<repo>\src\CHARACTER\cNPCTintProfile.cpp` (7/7 exact)
- `<repo>\src\GangManager\cFactionConfigData.cpp` (6/7 exact, including a 776-byte function)

Their headers are in `<repo>\include\` (`CHARACTER/`, `GangManager/`, plus the shared
`rws/`, `editor/`, `rw/`, `cd2/` headers). Read `include\README.md` for the header conventions.

## Method (follow in order)
1. **Check the split.** `@@CLASS@@/candidates.txt` lists the candidates in `@@CLASS@@/targets/`:
   - the functions around `MakeNew` (some belong to neighbouring files);
   - vtable entries that the link order list moved into the hot region (some are shared base-class functions defined in other files);
   - the registrar's dynamic initializer and at-exit destructor.

   `@@CLASS@@/cd2_vtable.txt` is CD2's vtable for the class. Decide which candidates this file really defines.
2. **Scaffold the header.** Read all of the file's assembly first, then write `@@CLASS@@/work/@@CLASS@@.h`.
   - Reuse repo headers wherever they apply. Don't redefine `RWS::*` classes.
   - Reference material:
     - `@@CLASS@@/reference_ruffking/`: the class's object file from the later RuffKing build, with pseudocode, disassembly and vtables. The code may differ from CD2.
     - `@@REFHDR@@`.
     - To dump any other reference type: `powershell -File <repo>\tools\headers\ref_dump.ps1 "Namespace::Type" [-NoDeps]` (writes into `include\ref\ruffking\`; that's the only repo location you may write to). Use `-List "name"` to find full type names.
   - Work out CD2's real layout from the offsets used in CD2's code. CD2 sizes can differ from RuffKing's: this object is `@@SIZE@@` bytes in CD2. End each class with `CD2_LAYOUT_CHECKS`.
   - For base classes you can't reconstruct fully, a minimal stand-in of the right size, with the right virtual-slot count, is acceptable. Say what you did.
3. **Implement the functions** in `@@CLASS@@/work/@@CLASS@@.cpp`. Skip any that resist and come back to them.
4. **Attack the tough ones** with `--diff Fnn` and the notes.
5. **Keep notes:** append every non-obvious finding to `@@CLASS@@/NOTES.md` (it starts as a copy of the shared notes).

## Harness

    py -I @@ROOT@@\check_tu.py @@ROOT@@\@@CLASS@@ <your .cpp> [--diff Fnn]

It uses the fixed CD2 compiler and flags `/Ox /Ob1 /Gy /GF /GR- /GS- /fp:fast`. The repo `include/` directory is on the include path.

**Important:** list every function you implement in `@@CLASS@@/work/map.txt`, one `Fnn symbol-substring` per line (e.g. `F11 ?MakeNew@@@CLASS@@`). Mapped targets are verified by **symbol**. Unmapped targets are paired by similarity, which can falsely report EXACT for same-shape functions. Only trust results marked without "(similarity pairing)". Linker-filled fields are masked.

## Budget and discipline
- At most **30 harness runs**. Read each input once; work from harness output afterwards. Don't re-read large files repeatedly.
- Write only in `@@ROOT@@\@@CLASS@@\work\`, `@@ROOT@@\@@CLASS@@\NOTES.md` and `include\ref\ruffking\` (dumps only).
- Prefer natural source a programmer would have written.

## Final report
Write `@@ROOT@@\@@CLASS@@\results.json`:
`{"class": "@@CLASS@@", "functions": [{"id": "Fnn", "address": "...", "belongs": true/false, "exact": true/false, "best_percent": n, "size_insns": n, "notes": "..."}], "harness_runs": n, "header_notes": "...", "split_notes": "..."}`
Then reply with a short summary: the split decision, what matched, what didn't and why (especially large functions),
what you added to the notes, and recommended changes to the shared repo headers.
