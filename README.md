# Crackdown 2 decompilation
(SLOP CODED SORRY, DONT HAVE TIME TO SPEND YEARS ON THIS)

A **matching decompilation** of Crackdown 2 (Xbox 360, title-update build): C++ source that, compiled with the
original Xbox 360 XDK compiler and the game's flags, produces code byte-identical to the retail executable.

Contributions are welcome **by hand or with any AI agent**. Every claimed match is recomputed by tools the contributor
cannot influence (see "How correctness is guaranteed").

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
