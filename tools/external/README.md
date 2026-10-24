# External tools (git submodules)

The repository stores no tool binaries. Each tool is a git submodule pinned to an exact commit, built from source by
`tools/build_tools.ps1` into `build/tools/bin/` (ignored by git). Requirements: git and Rust (cargo).

| Tool | Submodule | Pinned at | Built | Notes |
|---|---|---|---|---|
| jeff | `tools/external/jeff` (<https://github.com/rjkiv/jeff>) | v0.5.2, `6a023e5` | `jeff.exe` | Built with the patches in `tools/patches/jeff/` (below), applied in order to an exported copy, so the submodule stays unmodified. |
| objdiff | `tools/external/objdiff` (<https://github.com/encounter/objdiff>) | v3.8.3, `9aeec9c` | `objdiff-cli.exe` | |
| resym | `tools/external/resym` (<https://github.com/ergrelet/resym>) | `5be0938` (0.4.0+) | `resymc.exe` | Maintainers only (PDB dumps): a recursive clone does not check it out (`update = none`); `build_tools.ps1 resym` checks it out and builds it. Dumping a large class WITH dependencies can crash (it tried to allocate 128 GB for `VFX::cRopes`). Use `tools/headers/ref_dump.ps1 <type> -NoDeps` and dump the needed bases one by one. |

```
git submodule update --init
powershell -File tools\build_tools.ps1          # jeff and objdiff; or name tools: jeff | objdiff | resym
```

jeff patches (`tools/patches/jeff/`):

| Patch | Fixes |
|---|---|
| `0001-cd2-split-fixes.patch` | jeff crashes on Crackdown 2 without it: stop execution that walks past the end of a section (`executor.rs`); a block that cannot be finalised means "not a function" (`slices.rs`). |
| `0002-msvc-branch-relocation-fields.patch` | Branch relocations (REL24/REL14): MSVC's PPC linker adds the instruction's field to the target and subtracts the instruction's offset within its section, so the field must hold minus that offset, not the original displacement. Without it every relinked cross-object call lands off target. |
| `0003-keep-same-section-short-branches.patch` | A conditional branch (REL14) whose target is in the same object section keeps its original instruction and gets no relocation: the distance is preserved, while the convention of 0002 (minus the offset, in a 16-bit field) cannot express offsets of 32 KB and more. Without it the linker reports 139 fixup overflows. |
| `0004-zero-pair-displacements.patch` | The PAIR record after each REFHI carries the low half of the displacement in its symbol-index field. jeff left the target symbol's index there, so the linker's carry into the high half (`lis`) came out one off. |
| `0005-relocation-addends.patch` | Relocated fields carry the addend (the target's offset from its symbol), in the form the XDK linker expects (measured with hand-made objects): ADDR32 holds it; REFHI holds its high half adjusted for the sign of the low half, which goes in the following PAIR; REFLO holds the low half; REL24/REL14 hold the addend minus the instruction's offset. Without it, pointers and calls into the middle of a function (exception tables, funclets) land on its start. |
| `0006-external-global-labels.patch` | Labels with global scope are written as external symbols, not with the LABEL storage class (which other objects cannot see). Without it, `.pdata`, unwind data and calls to the `__savegprlr_N`/`__restgprlr_N` entry points from other objects stay unresolved. |
| `0007-unique-string-names.patch` | Detected strings are named by their MSVC literal mangling, so identical contents at different addresses got the same name and every reference bound to the first copy. Only the first copy keeps the name; the others are named by address. |
| `0008-msvc-ori-is-not-a-relocation.patch` | A `lis`/`ori` pair is never relocated in MSVC code (REFHI is adjusted for a signed low half, so the compiler pairs `lis` with `addi` or a load/store). jeff, following dtk where Metrowerks does use `ori`, relocated constants that fall in the address range, and their high half came out one too high. |

With all eight, `tools/relink.py` reproduces the image exactly. One known gap: jeff's tracker misses about 240 address loads whose high half stays in a register far from its use (LTCG code). Their bytes are copied, so the round trip is exact. They would only matter in a build where objects move (`relink.py` reports the gap as relocation completeness).

The patches are LF diffs against the sources as stored. `build_tools.ps1` exports with `core.autocrlf=false`, and `.gitattributes` keeps the patches LF on checkout. To change a patch, rebuild the series in a scratch git repository: commit the export, apply each patch as a commit, edit, and write each commit back out with `git diff <commit>~1 <commit>`.

To move a tool to a newer version:
1. Check out the new commit in its submodule.
2. Rebuild, and re-check that the patches still apply.
3. Re-run the gates.
