# Compiler reverse engineering (started 2026-10-23)

Target: the Xbox 360 back end `c2.dll` 15.00.8153 (XDK 9328, `bin\win32`), image base `10B00000`, timestamp `48F0660D`.
Its PDB (`c2.pdb`, GUID+age `909FC027C8904EE3B271151E21A36FBF13`) is **not** on the Microsoft symbol server, so the work is
symbol-less. Nothing from the binary is stored here except option and source-file names.

## Findings so far
- **Game code is LTCG** (`/GL` + `/LTCG`). See docs/feasibility.md section 4. `ltcg_map.py` classifies every CD2 function by how it loads float constants. `ltcg_check.py` builds each repo source both plainly and with LTCG and compares the results with CD2.
- **Listings work.** Add `/FAcs /Fa<file>.cod` to the normal flags (see `cc.ps1`). The listing interleaves source lines, names each compiler temporary with its stack slot and size (`tv143 = 80 ; size = 8`), shows relocations by symbol, and prints the per-function compile flags (`/Ogtu`).
- **Option table** (`c2_options.txt`, UTF-16 strings in the DLL). Notable entries:
  - inliner thresholds `-inlS#`, `-inlT#`, `-inld#` and about 25 more `-inl*`;
  - Xbox code-generation switches `-QXnobdnz`, `-QXnoloopreduction`, `-QXnonov08`, `-QXnopreinc`, `-QXSTALLS`, `-QVMX128`, `-QVMXReserve`, `-QGPRReserve`;
  - `-nodatasort`, `-schdat#`, `-stkfill#`, `-db#`;
  - PGO switches `-Pogo*`, `-pgo#`, `-pgu#`.

  `cl` forwards back-end options as `/d2<option>`. Their effects are not yet reverse-engineered.
- **Back-end source files** (`c2_source_files.txt`, from assertion paths) map the phases:

  | File | Phase |
  |---|---|
  | `p2\color.c`, `p2\regasg.c` | register allocation |
  | `p2\stack.c` | frame and stack-slot packing |
  | `p2\ppc\lower.c`, `p2\ppc\code.c` | instruction selection |
  | `p2\globopt.c`, `p2\dag.c`, `p2\lur.c` | optimizer, DAG, loop unrolling |
  | `p2\inline.c`, `p2\pogoinline.c` | inlining, PGO inlining |
  | `p2\list.c` | listings |
  | `p2\ltcg.c` | LTCG |
- The inliner prints diagnostics such as "won't be inlined (too big)" and "InlBadCandidate said not to inline %s into %s". The option that enables them is not yet found.

## No PGO (`pgo_scan.py`)
Profile-guided optimization splits cold code out of functions, which leaves cross-function jumps and branch-only fragments. CD2 has none:
- All 22,898 branches into the middle of another function go to one 21-instruction helper at `0x82F1E420`, the register-restore helper `__restgprlr_N`.
- 1 of 42,610 `.pdata` functions is entered only by branches.

The hot region at the start of `.text` therefore comes from a link order file. CD2 is **LTCG without PGO**.

## How LTCG output depends on the rest of the program
LTCG code depends on whole-program facts, so a per-file LTCG test must model them. Two mechanisms are found and reproduced so far. Each one turned a plain-exact function that differed under our LTCG build into an exact LTCG match.

1. **Address-escape analysis of globals.**
   - **Rule:** a global whose address no `/GL` code takes is treated as unaliased. Stores through pointers can then be reordered around its loads, and dead stores before them are deleted.
   - **What doesn't count:** unresolved globals, and globals defined in a plain (non-`/GL`) object, both count as unaliased.
   - **Example:** the `cNPCTintProfile` constructor matches CD2 under LTCG only when `Editor::g_GUIDNull` is non-`const` (CD2 keeps it in writable `.data`) **and** some `/GL` code takes its address (`escape_example.cpp`). With `const`, unresolved, or defined without an escape, LTCG deletes the base-class vptr store and hoists the GUID loads, which costs three extra non-volatile registers.
2. **The constant pool and `const`-global registration** (`c2.dll` `sub_10B7C9E7` in `p2\misc.c`, list at `0x10C26CB4`).
   - **Materializing a float/double constant:**
     - If a symbol with that value is already registered, it is loaded directly from that symbol.
     - Otherwise, in LTCG mode (flag `10C3E19C`, set from the `-ltcg` flag `10C3DE78`) and without **`-QXnonov08`** (flag `10C26CA8`), it is appended to the current `__pool@_N` (0x8000 bytes each) and loaded as base register + displacement.
     - Otherwise it becomes a `__real@xxxxxxxx` COMDAT, loaded directly.
   - **Registration:** `sub_10B46026` registers a value when codegen reads the initializer of a `const` global, so later literals with that value load from the global.
   - **In CD2:** 1.0f (`0x8208E84C`) and 0.0f (`0x820F7680`) are such globals. They are loaded directly about 2,400 and 2,900 times across LTCG game code, while rarer constants (1/32767, -1000, -0.03, 255) are pooled. The pool still holds early copies of 0.0f and 1.0f, created before the globals were seen. `constform.py` lists the form per function.
   - **Example:** `cAmbientVFXPrototype::MakeNew` matches CD2 under LTCG (66/66 words) once a `/GL` object defining and reading `const float` globals 1.0f and 0.0f is linked first (`constregs_example.cpp`).
3. **Pool layout** (found after the first two). With the const registrations added, `CalcRandInitSpawnTime` loses some scheduling around global addresses (53/54 down to 34/54), so the link's composition still matters.

   **Resolved:** this was the pool layout. With 0.0f/1.0f registered, 1/32767 became the pool's first entry, and a constant at pool offset 0 is addressed as the pool symbol itself (`lis` + `lfs pool@l`) instead of through a base register. Seeding the pool with a dummy constant restores CD2's form.

## The LTCG verifier (`tools/verify_ltcg.py`)
For each manifest source it models the rest of the program automatically:
- **escapes:** a copy of the source with an array taking the address of every data symbol in the plain object. It is compiled with `/Dprivate=public /Dprotected=public` to reach non-public static members. Taking the address of a declared-but-undefined global is enough. `/alternatename` references and `/EXPORT` do not count as escapes.
- **constant registrations:** `const` globals for every float/double constant that CD2 loads directly in the file's functions.
- **a pool seed.**

All 63 tracked functions are exact under it, including the three `CalcRand*` that only match under LTCG (`"ltcg": true` in the manifest).

## Source-shape sweeps (`tools/sweep.py`)
Compiles named variants (text replacements in the source and headers) and reports each target function's match. Specs live in `sweeps/`. Results so far:
- **`CalcRand*`:** `fmuls` operand order follows definition order (a local for the random value).
- **`IsVFXFinished`:** `extrwi` needs the bit in a `bool` local.
- **`GetRandSpawnPointInList`:** an unsigned pointer-difference `size()` called twice gives 87%; register numbering is open.
- **The arena's `HandleAttributes` slot sharing:** none of 6 variants helped (`sweeps/arena_handleattributes.py`).

## Open
- What enables the inliner and other dumps (the `-db#` / `-schdat#` semantics).
- Operand order of commutative float ops (`CalcRand*`: CD2 `fmuls f7,f8,f11`, ours `f7,f11,f8`; source operand order does not change it).

## Scripts
| Script | Purpose |
|---|---|
| `peinfo.py <dll> <ascii.txt> <utf16.txt>` | PE header, PDB record, string dump |
| `anchor_scan.py <default.exe>` | float loads by constant page: direct `lis`+`lfs` versus base+displacement |
| `ltcg_map.py <default.exe> <out.csv>` | per-function LTCG classification using `.pdata` |
| `ltcg_check.py <default.exe> <workdir> [filter]` | plain versus LTCG versus CD2 for every manifest function |
| `cmpsym.py <t.pe> <t.map> <default.exe> <symbol> <addr> <size>` | one function from an LTCG test image against CD2 |
| `cc.ps1 -Src -Out -Extra` | compile with the game flags plus extra options (e.g. `/FAcs`) |
| `pgo_scan.py <default.exe>` | PGO test: cross-function branches and branch-only fragments |
| `constform.py <default.exe> <lo> <hi>` | per function in a range: float constants loaded directly versus from the pool |
| `constref.py <default.exe>` | direct-load counts of the 0.0f/1.0f globals, and their pool copies |
| `ltcg_check.py ... --inc DIR --escape FILE` | the LTCG check with an extra include directory and an escape file |
| `escape_example.cpp`, `constregs_example.cpp` | the environment files used in the experiments above |
