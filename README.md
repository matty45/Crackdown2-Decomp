# Crackdown 2 decompilation
(SLOP CODED SORRY, DONT HAVE TIME TO SPEND YEARS ON THIS)

A **matching decompilation** of Crackdown 2 (Xbox 360, title-update build): C++ source that, compiled with the
original Xbox 360 XDK compiler and the game's flags, produces code byte-identical to the retail executable.

Contributions are welcome **by hand or with any AI agent**. Every claimed match is recomputed by tools the contributor
cannot influence (see "How correctness is guaranteed").

## Status (2026-11-11)

| | |
|---|---|
| Functions in the game | 74,550 (corrected function inventory), 14.3 MB of code |
| Source files set up | 528 (77 of them open-source middleware) |
| Functions matched | 11,666 (9,682 in a plain build, 1,984 more under link-time code generation), 984 of them open-source middleware |
| Full relink of the split game | byte-identical round trip (`tools/relink.py`) |
| Middleware objects relinked in place of the split's | byte-identical: zlib, libjpeg and Lua, 77 objects, code, data and layout (a `verify` gate) |

The count flatters the progress: 6,798 of the matched functions are header-constant initializers, the same run of
about 20 short functions that most source files repeat (36 bytes on average; see "Header constants" in
[docs/matching-notes.md](docs/matching-notes.md)). About 11,650 more sit in the initializer runs of objects that have
no source file yet, and about 500 in 100 set-up files are held back by the reference check (one name at two addresses,
described in the same note).

### How much is left

Every function of the executable, by where it stands, in code bytes. `py -I tools\cd2.py status` prints this
breakdown and the per-file numbers.

**Game code (what this project decompiles)**

| | Functions | Code | |
|---|---:|---:|---:|
| Matched | 10,681 + 1 folded copy | 466.9 KB | 3.2% |
| In progress (tracked in the manifest, not yet exact) | 3 | 0.5 KB | 0.0% |
| Open in the set-up source files | 3,693 | 1.19 MB | 8.3% |
| Game span not yet split into source files | 15,124 | 3.90 MB | 27.2% |
| Order-list region, not yet assigned (hot functions of every object, game and library) | 2,856 | 1.61 MB | 11.2% |
| Initializers and at-exit destructors, not yet assigned (every object's) | 17,038 | 0.59 MB | 4.1% |

At least 5.1 MB of game code is left, plus the game's share of the order-list region and of the initializers. The
matched code is about 5.9% of the game code, counting the whole order-list region and all unassigned initializers as
game code.

**Open-source middleware (its published source in `src/middleware/`, see below)**

| | Functions | Code | |
|---|---:|---:|---:|
| Matched: Lua 5.0.2 641 of 641, zlib 1.2.3 14 of 14, libjpeg 6b 329 of 329 | 984 | 215.6 KB | 1.5% |
| Open | 0 | 0 | 0% |

**Library code (linked from prebuilt libraries: identified in `config/library_splits.txt`, not decompiled)**

| | Functions | Code | |
|---|---:|---:|---:|
| XDK and C runtime | 7,509 | 2.79 MB | 19.4% |
| Scaleform GFx | 6,572 | 1.41 MB | 9.8% |
| Havok | 2,530 | 0.73 MB | 5.1% |
| Wwise | 2,663 | 0.45 MB | 3.1% |
| RenderWare AI | 198 | 45.8 KB | 0.3% |
| Other (transport, xlip, ...) | 1,175 | 0.27 MB | 1.9% |
| Library span not yet identified | 3,524 | 0.69 MB | 4.8% |

**Data (CD2's `.rdata` and `.data`, 11.4 MB)**

| | Data | |
|---|---:|---:|
| Located and checked: what matched functions reach (vtables, initialized data, constants, strings) | 245.0 KB | 2.1% |
| In source files' data ranges (`config/splits.txt`), not located yet | 36.0 KB | 0.3% |
| In no source file's range yet | 11.1 MB | 97.6% |

The middleware's data is proven whole by the round trip above, not only where its functions reach it.

- **Middleware:** CD2 links three open-source libraries outside the XDK: Lua 5.0.2 (`lua.lib`), zlib 1.2.3
  (`zlibXenon.lib`, inflate only) and IJG libjpeg 6b (Scaleform's `libjpeg.lib`). Their original source lives in
  `src/middleware/<library>/`, each with a README giving its origin, license, how CD2 built it and what CD2 changed.
  Original source is not reconstructed code, so the matching rules it breaks are waived for its directory only
  (`config/middleware.txt`). All 984 functions in the corrected inventory match; recovered platform adaptations,
  archive extensions and compiler behavior are documented in [docs/matching-notes.md](docs/matching-notes.md)
  ("Middleware"). Proprietary XDK implementations stay linked from the pinned SDK.
- **Older compilers:** CD2's PE header lists 609 C++ objects (Havok and RenderWare AI) from VS2005-era XDK compilers,
  14.00.1835, 1863, 2712, 2909 and 4404, which can never match with the pinned 15.00.8153 compiler. Older XDKs ship
  them, but the tools use only the pinned one.

## What you need

- **Your own copy of the game**: the XEX patched with the latest title update, `default_patched.xex` (SHA1
  `EC7B163617CD725F50B0CCA665AAF943F9BC6D8A`). The tools refuse any other build.
- **The Xbox 360 XDK 9328**, extracted (not installed). Its compiler must be the exact build pinned in
  `config/toolchain.txt`.
- Windows with PowerShell and git.
- Python 3.8 or later, with the `py` launcher (every command uses it).
- Rust (cargo), to build the tools. Its default Windows toolchain needs the Visual Studio C++ build tools, which the
  rustup installer offers to install.

You need no IDA, no debug databases (PDBs) and no reverse-engineering experience to start: every task comes with the
game's assembly, hints and the shared notes.

## Quick start

```
git clone --recurse-submodules <this repository>
cd <repository>
powershell -File tools\build_tools.ps1                 # builds jeff and objdiff-cli from source
py -I tools\cd2.py config --xdk <path>\XDK             # where your extracted XDK 9328 is
py -I tools\cd2.py setup <path>\default_patched.xex    # verifies the XEX, splits the game (about 30 s)
py -I tools\cd2.py doctor                              # everything "ok"
py -I tools\cd2.py tasks --tier 1                      # easy open functions
py -I tools\cd2.py show <address>                      # a task brief with the game's assembly
```

Then write the function in its source file and run `py -I tools\cd2.py check <file.cpp>` until it reports `EXACT`.
`diff` shows what still differs and why; `search` tries the last source variations for you.

## Contributing

- **[CONTRIBUTING.md](CONTRIBUTING.md)**: the workflow, the rules and the pull-request checklist.
- **[docs/contributor-harness.md](docs/contributor-harness.md)**: every command, the mismatch findings, the automatic
  search, the benchmark, and the trust model.
- **[AGENTS.md](AGENTS.md)**: instructions for AI coding agents (Claude Code reads it through `CLAUDE.md`).
  `tools/mcp_server.py` offers the same commands as MCP tools, registered in `.mcp.json`.
- **[docs/matching-notes.md](docs/matching-notes.md)**: what the compiler does, learned the hard way. Read it before
  your first function.

## How correctness is guaranteed

`py -I tools\cd2.py verify` runs every gate. Before merging a pull request, a maintainer runs the same gates on it with
the main branch's tools (`cd2.py review`), and it is merged only when they pass.

- **Bytes:** every matched function compiles to the game's code with the pinned compiler, compared by symbol and never
  by similarity.
- **References:** every call, global, constant and string resolves to the same address as in the game. A function that
  calls the wrong function fails even if its bytes match.
- **Data:** the data matched functions reach (vtables, initialized globals, constant tables) equals the game's, and
  every pointer in it (a vtable slot) resolves to the same address as in the game.
- **Ownership:** every function is in the source file whose address range holds it, and no function or type is defined
  twice.
- **Matching rules:** a function counts only when its bytes match *and* no matching rule fires in it (no assembly,
  no pointer arithmetic in place of declared members and globals, no fake code such as `volatile` or unused locals,
  globals declared once in a header); otherwise it is `MATCH-PENDING`.
- **Self-tests:** each gate is shown, by planting errors, to catch what it claims to catch.
- **Without the game:** `verify --facts` reaches the same verdicts from recorded hashes and addresses.

## Repository layout

| Path | Contents |
|---|---|
| `src/` | the decompiled source files; `src/middleware/` holds the published source of the open-source libraries CD2 links, not decompiled code |
| `include/` | shared, verified headers |
| `config/` | maintainer-owned ground truth: file ranges, matched functions, symbol aliases, the pinned toolchain, recorded facts, the benchmark suite |
| `tools/` | the contributor tool `cd2.py` and the gates; `tools/external/` holds tool submodules built from source |
| `docs/` | the contributor guide, the matching notes, the feasibility study and the log of changes to the maintainers' IDA database |
| `data/symbols/` | names suggested for the game's functions by automatic matching against the reference builds |
| `examples/matching/` | the first matched functions, from the feasibility pilots, with throwaway types |
| `tests/` | header layout tests and gate self-tests |

## Credits

**The game.** Crackdown 2 was developed by Ruffian Games and published by Microsoft Game Studios in 2010. This project
exists to study and preserve their work.

**Open-source libraries** whose original source is in `src/middleware/`, each under its own license:
- Lua 5.0.2, by Roberto Ierusalimschy, Luiz Henrique de Figueiredo and Waldemar Celes (Tecgraf, PUC-Rio), under the
  MIT license (`src/middleware/lua/COPYRIGHT`).
- zlib 1.2.3, by Jean-loup Gailly and Mark Adler, under the zlib license.
- libjpeg 6b, by Thomas G. Lane and the Independent JPEG Group. This software is based in part on the work of the
  Independent JPEG Group.

**Tools** built from source in `tools/external/`:
- [jeff](https://github.com/rjkiv/jeff) by rjkiv, the Xbox 360 splitter behind `setup` and the relink round trip,
  itself forked from encounter's [decomp-toolkit](https://github.com/encounter/decomp-toolkit).
- [objdiff](https://github.com/encounter/objdiff) by encounter, whose instruction alignment drives `diff`, `search`
  and the objdiff report.
- [resym](https://github.com/ergrelet/resym) by ergrelet, for browsing the types of the reference builds' PDBs.

**Ideas.** Tracking data beside code, per-file data ranges and the objdiff project file follow the example of
ChimpsAtSea's [Halo Reach decompilation](https://github.com/ChimpsAtSea/Reach) and the decomp-toolkit projects before
it.

**Contributors.** Everyone who has worked on this repository; `git shortlog -sn` lists them.

Thank you to everybody that has helped contribute to this project and the people that have made these amazing tools that have made this project possible.


## Legal

This is a fan project for preservation and study. It is not affiliated with or endorsed by Microsoft, Ruffian Games
or Xbox Game Studios. The repository contains no code, data or assets from the game and no part of the XDK. Every
contributor works from their own legally obtained copy of the game.

## License

[GNU Affero General Public License v3.0 or later](LICENSE) (`AGPL-3.0-or-later`).

The tools in `tools/external/` are git submodules of their own projects, under their own licenses (jeff, objdiff and
resym are MIT or Apache-2.0). The patches to them in `tools/patches/` are offered under the same terms as the tool
they modify.
