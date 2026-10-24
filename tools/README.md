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

## Gates (all must pass)

| Tool | Checks |
|---|---|
| `verify_src.py <default.exe> [--self-test]` | Plain build: every function in `config/matched_functions.json` is byte-exact by symbol. **Relocation targets** (`relocs.py`): every call, global, vtable, string and constant of an exact function must resolve to the same CD2 address, consistently across the repository (one name, one address; one address, one name unless declared in `config/symbol_aliases.txt`). This catches a call to the wrong function whose bytes still match. Every exact function must also be in an ordinary code section (`.text`, `.text$yc`, `.text$yd`). `--self-test` plants a wrong call and five synthetic cases (one of which must be accepted). |
| `verify_ltcg.py <default.exe> [filter]` | LTCG build. CD2's game code was built with `/GL` + `/LTCG`; this builds the same functions under LTCG with a generated model of the rest of the program (global and static-function escapes, constant registrations, a pool seed). Functions marked `"ltcg": true` are exact only here. |
| `check_integrity.py [--self-test]` | Ownership, duplicates and binaries; needs no game files. Checked against `config/splits.txt`: every function lies in its file's range, no address is claimed twice, folded functions are declared, link order is consistent, no type or non-inline function is defined twice, and no binary is present. `--self-test` plants one violation of each kind and fails unless all are caught. |
| `headers/check_headers.ps1` | The curated headers compile, layout checks hold, and the layout check's own self-test fires. |
| `relink.py <default_patched.xex> [workdir] [--resplit]` | **Round trip** (about 5 minutes): jeff splits the XEX into objects, the XDK linker links them at the original base, and the linked memory image must equal the original word for word (`RESULT: IDENTICAL`, exit 0). This proves the splitter, the relocations and the object order reproduce the game. Not linker output, so checked separately: the import words (the XEX packager replaced them with import records, so they must hold exactly what the linker writes) and the link metadata (debug time stamp, CodeView GUID and age). It also reports relocation completeness: the size of the base relocation table compared with the original's. Rerun with `--resplit` after changing jeff or its patches. |

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
| `headers/ref_dump.ps1` | Maintainers only: dumps reference types from the RuffKing or Burn PDB (via resym) into `include/ref/`. Contributors never need the PDBs. |
| `packets/build_cd2.py`, `packets/build_ruffking.py` | IDA scripts that build per-file packets: CD2 targets, and RuffKing reference material. |
| `build_tools.ps1` | Builds jeff and objdiff-cli from the submodules, with the patches in `patches/<tool>/` applied in order; `build_tools.ps1 resym` adds resymc (maintainers). |

Research material, including the compiler reverse-engineering in `research/compiler_re/`, is in `research/`. The compiler idioms learned so far are in `docs/matching-notes.md`.
