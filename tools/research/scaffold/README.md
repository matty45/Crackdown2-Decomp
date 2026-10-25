# Setting up source files automatically

How the files marked `auto:` in `config/splits.txt` were set up (2026-10-25): 372 files for 374 registered game classes,
4,290 functions, from CD2's own structure. Maintainers only; contributors never need this.

## Method

1. **RetClassName ties a registrar to its class.** Every registered class has a 12-byte `RetClassName()`
   (`lis rX, hi; addi r3, rX, lo; blr`) returning the class-name string its registrar passes. The vtable holding that
   function is the class's primary vtable. 430 of 465 registrars have exactly one.
2. **Markers.** A class's markers are its RetClassName, its MakeNew (unless another registrar shares it) and the
   functions of its primary vtable that no other registered class's primary vtable holds (its own overrides; shared
   slots may be a base class's), within 32 KB of RetClassName and outside the hot and initializer regions.
3. **Core.** The file's range runs from the first marker to the end of the last. Outside the hot region the linker lays
   out each object's functions contiguously, so every function inside belongs to the file. The range never extends
   past the evidence: functions before the first or after the last marker stay unassigned.
4. **Rejected** when: another class's marker lies inside; game functions named from more than one RuffKing object lie
   inside; it overlaps an existing file; the markers are over 128 KB apart; or there is only one marker.
5. **Link order.** The accepted ranges, sorted by their initializers, must also be sorted by address (the linker emits
   both in object order). None had to be dropped, and `tools/check_integrity.py` (check 5) confirms the order across
   all files, old and new.
6. **One file per object.** Neighbouring classes whose RetClassName comes from the same RuffKing object share a file
   (2 merges). Each file is named after its main class, under its namespace from RuffKing/Burn names (a two-to-one
   majority; otherwise at the top of `src/`).

**Validation:** for each of the 7 hand-verified files whose class has markers, the derived range lies inside the
verified one (cFactionConfigData's is identical).

## Running it

Run from the repository root, with a work directory holding the inputs:

```
py -I tools/research/scaffold/anchors.py <work>    # CD2 functions named from RuffKing -> their RuffKing object
py -I tools/research/scaffold/cores.py <work>      # class cores, the checks above, the validation
py -I tools/research/scaffold/names.py <work>      # namespaces
py -I tools/research/scaffold/plan.py <work>       # files to create (plan.json, splits_new.txt)
py -I tools/research/scaffold/apply.py <work>      # writes config/splits.txt and the source files
```

Inputs in the work directory:
- `ruff_pdb.json` (modules and section contributions, from `scripts/pdbinfo.py`), `ruff_funcs.jsonl` and
  `burn_funcs.jsonl` (function lists with PDB names, from `scripts/dump_funcs.py`);
- `cd2_registrars.json` (per registrar: class name, name string, MakeNew, size, initializer, at-exit destructor) and
  `cd2_vtables.json` (vtables and their slots), both extracted from the CD2 IDB with IDA during the feasibility study;
  the scripts that made them were not kept;
- `cd2_labels.json` (library or game origin per function, from `scripts/composition.py`).

The CD2 executable itself comes from `cd2.py setup`. Re-running finds nothing new once files exist (ranges overlap).

## Reference dumps

```
py -I tools/research/scaffold/ref_dumps.py <work>  # include/ref/<pdb>/<Namespace_Class>.h for every new class
py -I tools/research/scaffold/link_refs.py <work>  # each new source file names its class's dump
```

One class at a time, as `tools/headers/ref_dump.ps1 <Type> -NoDeps` (the type only; its bases are named, not expanded):
RuffKing's PDB first, Burn's when RuffKing lacks the class. Each resymc process needs well under 100 MB and is stopped
if it ever passes 2 GB. Never use `resymc dump-all`: it builds every type of the PDB in memory at once and can exhaust
all of a machine's memory. Existing dumps are kept, so the script can be re-run after an interruption.

Result (2026-10-25): 317 of the 372 files have a reference layout (313 new dumps, 1.3 MB; peak 109 MB per process).
The classes of the other 55 are in neither later build: CD2's own, whose layout comes from CD2's code alone.
