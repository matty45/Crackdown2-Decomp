# Batch: RetClassName in set-up files

The first batch match (2026-11-01): 43 `RetClassName` functions, each returning its class's own name from slot 11 of
the class's primary vtable, in files that had no code yet. Every one was checked `EXACT` by `cd2.py check` before it
went into the manifest, and `verify` passed afterwards.

The scripts take the repository root first and write their results next to their inputs (use a scratch folder):

1. `survey.py <root> <tasks json> <out json>`: the open functions that only return a string's address
   (`lis` / `addi r3` / `blr`), with the file's class (from its set-up comment), the vtable slots CD2 puts them in,
   and whether the class is declared in `include/`. The tasks file is `cd2.py tasks --tier 1 --json`.
2. `bases.py <root> <survey json> <out json>`: for those returning their own class name from slot 11, RuffKing's base
   class (from the header the file comment names) and whether it is modelled in `include/`.
3. `gen.py <root> <bases json> [--write]`: declares each class in its own header (`include/<Namespace>/<Class>.h`),
   deriving from RuffKing's base, in dependency order, and defines `RetClassName` in its source file. A class is
   generated only if its base chain reaches a class that is already modelled; already-declared classes and files with
   code are skipped. Without `--write` it only reports; with it, it lists what it wrote in `written.json`. Claim each
   function (`cd2.py claim <address> <symbol>`) before checking.
4. `checkall.py <root> <written json> <out json>`: runs `cd2.py check` on every written file and reports each
   function's status.

Left for later batches: the classes whose RuffKing base chain does not reach a modelled class (34), classes already
declared in another header (6), and the class names returned from slots 13 and 17 (another hierarchy).
