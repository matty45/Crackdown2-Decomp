# Matching-decompilation pilot: large functions (Crackdown 2, Xbox 360)

You are writing C++ that compiles to **byte-identical** PowerPC machine code for four large functions (171-286
instructions) from the retail Crackdown 2 executable. This pilot measures how agents cope with large functions, so
report honestly. Partial matches are useful data: a high match percentage counts.

## Established facts (do not re-investigate)
- Xbox 360 XDK compiler 15.00.8153 (MSVC 2008 era), flags `/Ox /Gy /GF /GR- /GS- /fp:fast`, no C++ exceptions, no RTTI.
- `this` in r3, args r4..r10 / f1..; return r3/f1. Non-volatile r14-r31 (more saved => `__savegprlr_N`).
- `char` is signed, `wchar_t` native, `bool` 1 byte. Virtual call: `lwz r11,0(rX); lwz r11,N(r11); mtctr; bctrl` (slot N/4).
- Idioms seen so far: branch layout follows source order (if/else arm order matters; `switch` differs from an if-chain);
  a bool kept live in a local across calls (`bool ret = true; ... if (!f()) ret = false; return ret;`) produces
  `addic/subfe` or `subfic/subfe/and` sequences; constants used after calls get hoisted into non-volatile registers;
  stack-frame size and local-variable placement follow declaration order and lifetimes.

## Packets L1..L4 (in your workspace)
- `target.hex`: exact bytes of the target. `cd2_disasm.txt`: address, raw word, IDA disassembly (names like
  `sub_XXXXXXXX` are unnamed; some names were assigned by hand and may be wrong). `cd2_pseudocode.c`: Hex-Rays output.
- L1 and L2 also have `reference_ruffking/`: the same codebase in a *later* game build (Ryse prototype, Nov 2010) with
  real symbols. Its version may differ from Crackdown 2. Trust `cd2_disasm.txt` for offsets.
- L3 and L4 have no reference (Crackdown 2-only code).

## Harness

    py -I <scratch>\agentpilot_large\check.py <packet_dir> <your_file.cpp> <symbol-substring>

It prints a one-line summary and then **only the differing regions** (at most 60 lines). Fix the first differing region
first, then re-run. Linker-filled fields (call targets, global/string addresses) are masked. Declare whatever minimal
types/externs you need inside the .cpp (padding arrays to place fields at the right offsets). No game headers exist.
Flags are fixed.

## Token discipline (important: this pilot measures cost)
- Read each packet's files once. Do not re-read the full disassembly after every run; use the harness output.
- Never use `--full`.
- Write the whole function first, then iterate on the differing regions.

## Rules
- Work only inside your workspace. Write sources in the packet directories (e.g. `L1\a.cpp`).
- At most **8 harness runs per packet**. Stop a packet at `EXACT MATCH`. Keep your best attempt and move on otherwise.
- Prefer natural source code a game programmer would have written.

## Final report
Write `<scratch>\agentpilot_large\results.json`: a list of
`{"packet": "L1", "exact": true/false, "best_percent": <number>, "harness_runs": <n>, "file": "<best .cpp>", "notes": "<what was hard, 1-2 sentences>"}`
and finish with a short plain-text summary.

