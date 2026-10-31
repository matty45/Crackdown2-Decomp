# Splitting the library code (config/library_splits.txt)

How `config/library_splits.txt` was made (2026-10-31): 18,919 functions in 1,477 library objects (the XDK libraries,
Havok, Wwise, Scaleform, XLSP, ...), from CD2's code compared with RuffKing's. Maintainers only; it needs the RuffKing
executable and PDB, which contributors never need.

## Method

1. **Identity by code.** Every function of both builds is hashed: its words with address immediates masked (as the
   LTCG checker masks them, `verify_ltcg.masked`) and RuffKing's `mr r13,r13` / `mr r14,r14` trace markers removed.
   RuffKing's functions are its PDB section contributions in `.text` (one per function under `/Gy`). A hash that is
   unique in both builds pairs two functions; a hash whose copies all lie in one RuffKing object still gives the object.
   The RuffKing name table (`data/symbols/auto_names_2026-10-23.csv`) adds name anchors (`anchors2.py`).
2. **Minimum size 64 bytes.** Smaller functions are too common to identify: a 16-byte `return Ret_OK` matched Havok
   code. At 64 bytes, no identity inside an existing game file points at a library object.
3. **Copies.** Inline and template functions are emitted in every object that uses them, and each build may keep a
   different object's copy. A run of up to three identified functions whose object has a longer run elsewhere is such
   a copy: it is relabelled when both neighbours agree, otherwise dropped.
4. **Contiguity.** Outside the order-list region the linker lays out each object contiguously, so unidentified
   functions between two identified functions of one object belong to it.
5. **Boundaries.** Between two objects, functions are assigned while their sizes repeat the RuffKing functions after
   the first object's last match, and (from the other side) before the second object's first match.
6. **Library objects only.** RuffKing's own game objects (not from a `.lib`) match CD2 only on generic code, such as
   small initializers, so they are not used.
7. **Game files are fixed.** Nothing inside a `config/splits.txt` range, initializer or at-exit destructor is
   assigned, and no fill crosses one.

Burn's code (newer compiler) adds almost nothing (344 functions) and is not used.

## Game files (config/splits.txt) extended the same day

- `extend.py` + `apply_extend.py`, repeated to a fixpoint: a file grows over the adjacent unassigned functions whose
  users (callers, address-takers, installers of a vtable holding them) all lie in that file. 659 functions in 142
  files; it found, for example, cFactionTargetingProfile's `SetupTargetData` and cAiPlayer's constructor helper.
- `initmap.py`, `initfill.py`, `order_filter.py` + `apply_init.py`: initializer-region functions whose code
  references only one file's functions, or that lie between two of its entries, become its init/atexit entries; 23
  that would break the link order (files' initializers in text order) were dropped, 512 kept.

## Not covered yet

- The game span (0x823D0000-0x82913700): RuffKing's game code differs from CD2's, and the few code matches there are
  generic helpers, not identities. Game files come from CD2's own evidence (`tools/research/scaffold/`).
- The order-list region (0x821D0000-0x823D0000): functions pulled out of their objects, so contiguity does not hold.
- From 0x82F00000: about 27,000 small functions (dynamic initializers and at-exit destructors of every object), too
  small to identify by code.

## Running it

From the repository root, with a work directory `<work>` (it holds the extracted RuffKing executable):

```
py -I tools/research/scripts/pdbinfo.py <ruffking.pdb> <work>/ruff_pdb.json
build/tools/bin/jeff.exe xex extract <RuffKing_Release.xex>      (in <work>: gives RuffKing_Release.exe)
py -I tools/research/splits_libs/anchors2.py <ruffking.pdb> <work>/ruff_pdb.json <work>/anchors.json
py -I tools/research/splits_libs/hashmatch.py <work>               (ident.json)
py -I tools/research/splits_libs/libmap.py <work>                  (libmap.json)
py -I tools/research/splits_libs/writelib.py <work>                (writes config/library_splits.txt)
```
