# Pilot: decompile one whole source file, CHARACTER/cNPCTintProfile.cpp (Crackdown 2, Xbox 360)

Goal: reconstruct the C++ source file `cNPCTintProfile.cpp` (and its header) so that every function in it compiles to
**byte-identical** PowerPC code. This tests a per-file method, so follow the steps in order and report honestly.

## Method (follow in order)
1. **Check the split.** Decide which target functions really belong to this file. The candidates are in
   `cNPCTintProfile/targets/`:
   - F1 `0x8255DFE8`: likely the constructor `cNPCTintProfile(const RWS::CAttributePacket&)`.
   - F2 `0x821D0300`: `HandleAttributes`. It was moved into the hot region by the linker's order list.
   - F3 `0x8255DF80`: `MakeNew`. The class registrar registers it.
   - F4 `0x8255DFD8`: `RetClassName`.
   - F5 `0x8255E0D8`: unknown; it may be the next file. Decide.
   - F6 `0x821D0A20`: the scalar deleting destructor (vtable slot 0). It's a compiler-generated COMDAT; decide whether this file defines what generates it (e.g. the virtual destructor).
   - F7 `0x82FAF4E0`: dynamic initializer of the static `cNPCTintProfileRegistrar`.
   - F8 `0x8303D140`: its at-exit destructor.

   Also see `cd2_vtable_82114610.txt` (CD2's vtable for the class, 13 slots).
2. **Scaffold the header.** Read all of the file's assembly first, then write `cNPCTintProfile/work/cNPCTintProfile.h`
   with the class declaration, in PDB order:
   - Base classes come from the repo header `rws/attributes.h` (`RWS::CAttributeHandler`, `CAttributePacket`, commands, iterators). Do **not** redefine them.
   - Use the reference dumps in `<repo>\include\ref\ruffking\`: `CHARACTER_cNPCTintProfile.h`, `RWS_CClassFactory_CRegistrar.h`, `Editor_cGUIDEventHandler_CHARACTER_cNPCTintProfile_.h`.
   - `_XMCOLOR` comes from the real XDK header: `#include <xtl.h>` then `#include <xnamath.h>`.
   - End the class with `CD2_LAYOUT_CHECKS` (`cd2/layout.h`): size `0x50`, `m_anPalette` at `0x2C`, `m_nPaletteSize` at `0x4C`. These offsets are confirmed by CD2's code.
   - For template members you can't reconstruct yet (e.g. `Editor::cGUIDEventHandler<...>`), an opaque member of the right size is acceptable. Note what you did.
3. **Implement the functions** in `cNPCTintProfile/work/cNPCTintProfile.cpp`. Skip any that resist and come back later.
4. **Then attack the tough ones.** Use the per-function diff (`--diff Fn`) and `NOTES.md`.
5. **Keep notes.** Whenever something wasn't obvious, append it to `NOTES.md` (shared knowledge for future agents).

## Inputs
- `cNPCTintProfile/targets/Fn_ADDR/`: `target.hex`, `cd2_disasm.txt`, `cd2_pseudocode.c` (Hex-Rays; a hint, not truth).
- `cNPCTintProfile/reference_ruffking/ruffking_cNPCTintProfile_obj.c`: the same file's functions from the later RuffKing build (pseudocode plus disassembly). The code may differ from CD2.
- Repo headers: `<repo>\include\` (on the include path automatically). See its `README.md` for conventions.
- A previous pilot got F2 (`HandleAttributes`) to ~91% without a real header. Its notes: the branch layout needed a `switch`, and the byte swap needed the exact shift form listed in `NOTES.md`.

## Harness

    py -I <scratch>\tupilot\check_tu.py <scratch>\tupilot\cNPCTintProfile <file.cpp> [--diff F2]

It compiles your file with the fixed CD2 compiler and flags (`/Ox /Gy /GF /GR- /GS- /fp:fast`) and pairs each target
with your best-matching compiled function. It prints a per-function table, and the differing regions for `--diff Fn`.
Linker-filled fields are masked. Every run is logged.

## Budget and discipline
- At most **25 harness runs in total**. Read each input file once; work from the harness output afterwards. Never re-read whole disassembly listings repeatedly.
- Work only in `<scratch>\tupilot` (write in `cNPCTintProfile/work/`, append to `NOTES.md`). Don't modify the harness or the repo headers. If a repo header needs a change, describe it in your report instead.
- Prefer natural source a programmer would have written.

## Final report
Write `<scratch>\tupilot\results.json`:
`{"functions": [{"id": "F1", "belongs": true/false, "exact": true/false, "best_percent": n, "notes": "..."}], "harness_runs": n, "header_notes": "...", "split_notes": "..."}`.
Then reply with a short summary: what matched, what didn't and why, what you added to `NOTES.md`, and any header
fixes you'd recommend.

