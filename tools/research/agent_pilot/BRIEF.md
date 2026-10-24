# Matching-decompilation pilot: Crackdown 2 (Xbox 360)

You are writing C++ source that compiles to **byte-identical** PowerPC machine code for individual functions from the
retail Crackdown 2 executable. This is a feasibility pilot: we are measuring how well an agent does, so report honestly.

## Setup facts (already established, do not re-investigate)
- Target: Crackdown 2 retail, Xbox 360 (big-endian PowerPC, Xenon). Code is C++ compiled by the Xbox 360 XDK
  compiler 15.00.8153 (MSVC 2008 era) with `/Ox /Gy /GF /GR- /GS- /fp:fast`, no C++ exceptions, no RTTI.
- Calling convention: `this` in r3, then args in r4..r10; floats in f1..; return in r3/f1. Non-volatile regs r14-r31.
  `__savegprlr_N` / `__restgprlr_N` are compiler-generated prologue/epilogue helpers (more saved registers => one of these).
- `char` is signed. `wchar_t` is native. `bool` is 1 byte.
- Virtual calls look like `lwz r11,0(r3); lwz r11,N(r11); mtctr r11; bctrl` (slot = N/4).

## Each packet directory (P1..P7) contains
- `target.hex`: the exact bytes of the target function.
- `cd2_disasm.txt`: address, raw word, IDA disassembly of the target. Names like `sub_XXXXXXXX` are unnamed functions.
  Some names in it were assigned by hand by a human and **may be inaccurate**.
- `cd2_pseudocode.c`: Hex-Rays decompilation of the target (a hint, not ground truth).
- `reference_ruffking/` (only some packets): the same codebase from a *later* game build (Ryse prototype, Nov 2010)
  that has full symbols. Its version of the function may differ from Crackdown 2 (code was changed later). Its build
  inserted no-op trace markers `mr r13,r13` and `mr r14,r14` that Crackdown 2 does not have: ignore them.
  `types_from_ruffking_pdb.h` holds real class layouts from that build. Field offsets in Crackdown 2 may differ:
  always trust the offsets in `cd2_disasm.txt`.

## Harness
Compile and compare (run from anywhere):

    py -I <ROOT>\check.py <packet_dir> <your_file.cpp> <symbol-substring>

- `<symbol-substring>` selects your function from the object file (e.g. `StartMission` or `InitParam@cBaseVisibility`).
- Output: `EXACT MATCH`, or a side-by-side listing of your code vs the target. Lines starting with `>` differ.
- Fields filled in by the linker (call targets, addresses of globals/strings) are masked; you only need the right
  instruction there. You do NOT need real names or real headers: declare whatever minimal classes/structs/externs
  you need yourself in the .cpp (use padding arrays to put fields at the right offsets, declare callees as extern
  functions or member functions with plausible signatures). Do not `#include` game headers (none exist).
- Compiler flags are fixed. Do not try to change them.

## Rules
- Work only inside your own packet directories. Write your sources there (e.g. `P1\attempt.cpp`).
- At most **12 harness runs per packet**. Stop a packet early when you get `EXACT MATCH`.
- Work through all 7 packets. If one is not matching after 12 runs, keep your best attempt and move on.
- Prefer natural, plausible source code (what a game programmer would have written), not assembly-like hacks.

## Final report
Write `<ROOT>\results.json`: a list of objects
`{"packet": "P1", "exact": true/false, "best_percent": <number>, "harness_runs": <n>, "file": "<best .cpp>", "notes": "<one or two sentences: what was hard>"}`
and finish with a short plain-text summary.
