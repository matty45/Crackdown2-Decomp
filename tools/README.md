# Tools

All tools read Crackdown 2's code at run time from your own extracted `default.exe`. Extract it from the title-update XEX `default_patched.xex` only; the tools refuse other builds. Nothing from the game is stored in this repository.

**No binaries:** the repository holds source and text only.
- External tools are git submodules of their source repositories under `external/`, pinned to exact commits (see `external/README.md`).
- `build_tools.ps1` compiles them into `build/tools/bin/`, which git ignores. Our fixes to them are source patches in `patches/`.
- `check_integrity.py` fails if a binary file appears anywhere git would track it.

```
git submodule update --init
powershell -File tools\build_tools.ps1
py -I tools\cd2.py setup <path>\default_patched.xex
```

**Start here: `cd2.py`**, the contributor tool (`docs/contributor-harness.md`).
- Work commands: `setup`, `doctor`, `status`, `tasks`, `show`, `claim`, `check`, `diff`, `lint`.
- `verify` runs every gate below, plus their self-tests.
- Every command takes `--json`.

The compiler and linker must be the builds pinned in `config/toolchain.txt`; every gate refuses another toolchain.

**Working folders:** every tool works in `build/cd2/tmp/<pid>_<tool>...` (`verify_src.work_dir`), never in the system's
temporary folder, and removes its folders when it exits. A process that is killed never gets to; the next tool that
starts removes the folders of processes that no longer run.

**Build cache:** `buildcache.py` reuses the object of a source under `src/` when nothing the compiler read has changed
(the pinned toolchain, the command line, the source, every header it opened, and the set of header names under
`include/` and `src/`), so a gate recompiles only what an edit touched. `CD2_NO_CACHE=1` turns it off; `cd2.py review`
and `cd2.py facts record` always run without it. Its size is capped by `CD2_CACHE_MB` (default 2048).

Every file is compiled with the game's flags (`verify_src.FLAGS`). The exceptions are libraries CD2 linked that were
built with other settings: `config/file_flags.txt` (maintainers only) adds `/Ob0`–`/Ob2`, `/D` macros or `plain` per
file or directory, with the evidence. Nothing else is accepted. A plain object, meaning every `.c` file (CD2's Rich
header lists no LTCG C objects) and every file marked `plain`, has no LTCG gate. Its bodies never enter another file's
LTCG model either. Functions in `.c` files are named by their exact C name (`lua_gettop`), not by a mangled prefix.

## Gates (all must pass)

| Tool | Checks |
|---|---|
| `verify_src.py <default.exe> [--self-test]` | Plain build: every function in `config/matched_functions.json` is byte-exact by symbol. **Relocation targets** (`relocs.py`): every call, global, vtable, string and constant of an exact function must resolve to the same CD2 address, consistently across the repository (one name, one address; one address, one name unless declared in `config/symbol_aliases.txt`). This catches a call to the wrong function whose bytes still match. **Data** (`relocs.check_all_data`): every symbol an exact function references that the object defines as data (a vtable, an initialized global), the data its pointers lead to, and the vtables located through their class's own matched virtuals must equal CD2's bytes outside their relocations, at exact sizes from a `/Z7` build (`cvtypes.py`); zero-initialized data must be zero in CD2; each pointer (a vtable slot) is resolved through CD2's word and joins the reference checks; data must not run over the next located symbol, and a vtable must not be shorter than CD2's when its next word is a function of the same file. Strings are compared whole. Weak externals (`??_E` for `??_G`) resolve to their default. Every exact function must also be in an ordinary code section (`.text`, `.text$yc`, `.text$yd`). `--self-test` plants a wrong call, synthetic cases (some of which must be accepted) and the data plants (`DATA_PLANTS`: a changed initial value, a datum left zero where CD2 initializes it, swapped slots, a table missing slots, an anchored table shifted, a long string changed late). |
| `cvtypes.py` | The size of every global and static an object defines, from the CodeView records of a `/Z7` build of it (`S_GDATA32`/`S_LDATA32` and their types): the data checks' exact extents. |
| `verify_ltcg.py <default.exe> [filter]` | LTCG build. CD2's game code was built with `/GL` + `/LTCG`; this builds the same functions under LTCG with a generated model of the rest of the program (global and static-function escapes, constant registrations, a pool seed). Functions marked `"ltcg": true` are exact only here. |
| `check_integrity.py [--self-test]` | Ownership, duplicates and binaries; needs no game files. Checked against `config/splits.txt`: every function lies in its file's range, no address is claimed twice, folded functions are declared, link order is consistent, no type or non-inline function is defined twice, no binary is present, and `config/file_flags.txt` holds only allowed options (and no `"ltcg"` function in a plain object). `--self-test` plants one violation of each kind and fails unless all are caught. |
| `headers/check_headers.ps1` | The curated headers compile, layout checks hold, and the layout check's own self-test fires. |
| `relink.py <default_patched.xex> [workdir] [--resplit]` | **Round trip** (about 5 minutes): jeff splits the XEX into objects, the XDK linker links them at the original base, and the linked memory image must equal the original word for word (`RESULT: IDENTICAL`, exit 0). This proves the splitter, the relocations and the object order reproduce the game. Not linker output, so checked separately: the import words (the XEX packager replaced them with import records, so they must hold exactly what the linker writes) and the link metadata (debug time stamp, CodeView GUID and age). It also reports relocation completeness: the size of the base relocation table compared with the original's. Rerun with `--resplit` after changing jeff or its patches. `--substitute <file or directory/> ...` relinks with our own plain objects in place of those files' units (in `<workdir>/substitute`; `verify` runs it on `src/middleware/`), `--self-test` plants one word in our code and one in our data and requires exactly that word to differ (in `<workdir>/selftest`). Unresolved names in our objects fail it. |

## Working tools

| Tool | Use |
|---|---|
| `mismatch.py [--self-test]` | The mismatch classifier behind `cd2.py diff` and `check --explain`: turns an instruction diff into findings with hints. |
| `search.py [--self-test]` | The automatic source search behind `cd2.py search` (`cd2.py search-test` proves it restores broken functions). |
| `bench.py` | The benchmark behind `cd2.py bench` (`suite`, `run --agent`, `report`, `selftest`): agents re-solve solved functions in isolated workspaces; the suite is `config/bench_suite.json`. |
| `bench_chat.py` | The built-in benchmark agent (`--agent chat:<model>`): any model behind an OpenAI-compatible API, sandboxed by construction. |
| `bench_claude.py` | Claude Code as a sandboxed benchmark agent (`--agent claude:<model>`). |
| `bench_kilo.py` | Kilo Code's CLI as a sandboxed benchmark agent (`--agent kilo:<provider/model>`). |
| `facts.py record <default.exe>` / `verify` / `--self-test` | Target facts: confirm matches without the game file (`cd2.py verify --facts`). |
| `mcp_server.py` | The `cd2.py` commands as MCP tools, for any agent that speaks the Model Context Protocol. |
| `check_tu.py <packet> <file.cpp> [--diff Fnn] [--ltcg]` | The measurement batches' harness, superseded by `cd2.py check`/`diff` for contributors (it needs packets built with IDA): compares a work-in-progress source with every target of a packet built by `packets/build_cd2.py`. A byte-exact function whose references point elsewhere than CD2's is reported as `WRONGTGT`, not exact (needs `CD2_EXE`). |
| `sweep.py <default.exe> <spec.py>` | Compiles named source variants and reports how each matches chosen functions. Use it to find the source shape behind an instruction pattern. |
| `packets/build_cd2.py`, `packets/build_ruffking.py` | IDA scripts that build per-file packets: CD2 targets, and RuffKing reference material. |
| `build_tools.ps1` | Builds jeff and objdiff-cli from the submodules, with the patches in `patches/<tool>/` applied in order; `build_tools.ps1 resym` adds resymc (maintainers). |

Research material, including the compiler reverse-engineering in `research/compiler_re/`, is in `research/`. The compiler idioms learned so far are in `docs/matching-notes.md`.
