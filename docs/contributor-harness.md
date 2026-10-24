# Contributor harness

`tools/cd2.py` is the single entry point for contributing matched code, by hand or with any AI agent. Every command
prints text by default and one JSON object with `--json`, so any agent framework can drive it.

The design rule: **trust no contributor and no model, only verification they cannot touch.** Nothing you write
decides what counts as matched. Matches are recomputed from your source against your own copy of the game, with a
pinned compiler and the maintainers' symbol table.

## Setup (once)

You need:
- your own copy of Crackdown 2's title-update XEX, `default_patched.xex` (SHA1 `EC7B1636...`; the base `default.xex`
  is refused);
- the Xbox 360 XDK 9328, extracted (not installed). Its compiler and linker must be the exact builds in
  `config/toolchain.txt`, or every tool refuses to run;
- Windows with PowerShell and git; Python 3.8+ with the `py` launcher; Rust (cargo) with the Visual Studio C++ build
  tools that rustup's installer offers.

```
git submodule update --init
powershell -File tools\build_tools.ps1                 # jeff and objdiff-cli, built from source
py -I tools\cd2.py config --xdk <path>\XDK             # where the extracted XDK is (written to local.json)
py -I tools\cd2.py setup <path>\default_patched.xex    # about 30 s
py -I tools\cd2.py doctor                              # everything "ok"
```

`local.json` holds machine-specific settings and is ignored by git. The environment variable `XDK_DIR` overrides it.

You need no debug databases (PDBs) and no disassembler. Everything contributors use is in the repository:
- the reference types are in `include/ref/`;
- the curated headers are in `include/`;
- each task's assembly comes from your own copy of the game, through `show`.

Only maintainers who curate headers from the reference builds use `tools/headers/ref_dump.ps1`, with `config
--ruffking-pdb ... --burn-pdb ...` and resymc (`powershell -File tools\build_tools.ps1 resym`).

`setup` extracts the executable and splits the game with jeff, into one target object per source file
(`config/splits.txt`), under `build/cd2` (ignored by git). Nothing from the game ever enters the repository.

## The work loop

| Step | Command | What you get |
|---|---|---|
| Find work | `cd2.py tasks [file] [--tier N]` | Open functions of the scaffolded files, easiest first. Tier 1: up to 24 instructions; 2: up to 80; 3: up to 250 or a jump table; 4: larger, or VMX128 vector code. |
| Read the task | `cd2.py show <address>` | File, size, tier, status, neighbouring functions and their status, hints (LTCG, jump tables, VMX), and CD2's assembly with symbolic labels. |
| Start | `cd2.py claim <address> <mangled symbol prefix>` | Maps the function to the symbol you are writing, e.g. `?Update@cChaseBehaviour@AI@@`. The claim is local (`build/cd2/claims.json`). |
| Edit | your editor | Source in `src/`, types in `include/`. Use the shared headers; see `include/README.md`. |
| Check | `cd2.py check <file.cpp> [--ltcg] [--explain]` | Source policy, compile, then every mapped function of the file: `EXACT`, a percentage, `LTCG EXACT`, `missing` or `WRONG TARGET` (bytes match but a call or address resolves elsewhere than in CD2). `--explain` adds the mismatch findings for each function not yet exact. Each run is logged to `build/cd2/attempts.jsonl`. |
| Compare | `cd2.py diff <file.cpp> <address>` | objdiff's instruction diff, CD2 against yours, showing only the differing regions, with **findings**: what kind of mismatch it is and what usually fixes it (below). Call targets and addresses are not flagged here, because `check` verifies them exactly. |
| Close the gap | `cd2.py search <file.cpp> <address> [--apply]` | Once the structure is right, tries source transformations itself and keeps whatever brings the function closer (below). Writes the file only with `--apply`. |
| Before a pull request | `cd2.py verify` | Every gate; a maintainer runs the same gates on your pull request before merging it. |

CD2 was built with link-time code generation (`docs/feasibility.md` section 4). Most functions, float code included,
still compile identically in a plain build. Where LTCG gathered a function's float constants behind one base register
(`addi rX, anchor`, then `lfs f, d(rX)`), only `--ltcg` can produce it: `show` and the findings say so when CD2's
code has that shape.

**When a function is exact,** add it to `config/matched_functions.json` in your pull request (address, size, mangled
symbol prefix). Before merging, a maintainer recomputes every entry (`cd2.py review`, below); an entry that is not
exact is not merged.

## Mismatch findings

`diff` and `check --explain` classify each difference (`tools/mismatch.py`). Each finding comes with the CD2 addresses,
a hint and the `docs/matching-notes.md` entry that explains it. They are listed most fundamental first:

| Finding | Usual cause |
|---|---|
| stack frame size differs | a local or a returned struct of another size, or one local more or fewer |
| different registers saved | more or fewer values live across calls (hoisted constants, locals versus re-reads) |
| a call where CD2 has the code inline / CD2 calls out of line | the callee's `inline` status in the header |
| float constants: CD2 loads them the LTCG way | link-time code generation: check with `--ltcg` |
| field offset differs | a header layout is wrong: fix the header, not the function |
| load/store width or sign differs | the field's type (bool/char/int, short signedness, float/double) |
| signed versus unsigned compare | the expression's type |
| single bit: extract versus mask | a bit tested in place versus converted to a bool local |
| branch condition inverted | if/else arm order, early returns |
| instructions only in CD2 / only in ours | expression shape, recomputation versus reuse |
| stack slot differs | declaration order and scope of locals |
| operands swapped | where each value was defined (a value computed in its own statement) |
| same instructions, registers numbered differently | value order and lifetimes: a job for `search` |

`py -I tools/mismatch.py --self-test` checks each category against synthetic code.

## Automatic search

`search` reshapes a function without writing new code (`tools/search.py`). It tries these transformations:

- swap the operands of a commutative operator;
- flip a comparison;
- swap the arms of an if/else, negating the condition;
- swap two adjacent statements;
- write a test against zero in another form (`p`, `p != 0`, `n > 0`, `0 < n`);
- change `i++` to `++i`;
- replace a local with its initializer at every use.

Each candidate is compiled and scored by the number of words that match CD2. Each round keeps the best improvement, so
transformations combine, until the function is exact or nothing helps.

`cd2.py search-test` is the proof that it works. It breaks solved functions with one transformation each, then
requires the search to restore an exact match: 25 of 25 at the last run. Replacing a local with its initializer is the
one transformation it cannot undo, because C++03 has no `auto`.

## Benchmark

To measure a model or an agent before it takes real tasks, re-solve solved functions (`tools/bench.py`). The **suite**
(`config/bench_suite.json`) is a fixed set of 20 tasks: 8 of tier 1, 8 of tier 2, and the whole of tiers 3 and 4. It
stays fixed so that results are comparable between models and over time.

```
py -I tools\cd2.py bench run --model NAME --agent AGENT [--tier N] [--limit N] [--timeout SECONDS]
py -I tools\cd2.py bench report [--model NAME]           # tasks solved, attempts, time, by model and tier
```

`--model NAME` is the label the results are filed under. `AGENT` is one of three kinds.

**`chat:<model>`: any model, through any OpenAI-compatible API** (`tools/bench_chat.py`). This is the way to compare
models, cheap and local ones included: every model gets the same scaffold, and it is sandboxed by construction. The
model never touches a file or a shell. It asks for files from the workspace (`READ <path>`; anything outside is
refused) and answers with a function body, which the agent splices in and checks, sending the result back. It stops at
EXACT, after `--rounds` replies (12) or when the model gives up. Set the endpoint and the key in the environment:

| Provider | `CD2_LLM_BASE_URL` | Example `chat:` model |
|---|---|---|
| OpenAI | `https://api.openai.com/v1` (the default) | `chat:gpt-4.1-mini` |
| Anthropic | `https://api.anthropic.com/v1/` | `chat:claude-haiku-5-5` |
| Google Gemini | `https://generativelanguage.googleapis.com/v1beta/openai/` | `chat:gemini-2.5-flash` |
| OpenRouter (many models, one key) | `https://openrouter.ai/api/v1` | `chat:deepseek/deepseek-chat` |
| DeepSeek | `https://api.deepseek.com/v1` | `chat:deepseek-chat` |
| Ollama (local, free) | `http://localhost:11434/v1` | `chat:qwen2.5-coder:32b` |
| LM Studio (local, free) | `http://localhost:1234/v1` | the loaded model's name |

`CD2_LLM_API_KEY` holds the key (local servers need none). `CD2_LLM_OPTIONS` is a JSON object merged into every
request, for example `{"temperature": 0}`. Token use is recorded with each result. The model names are examples;
use the names your provider lists.

```
$env:CD2_LLM_BASE_URL = "http://localhost:11434/v1"            # PowerShell; cmd: set CD2_LLM_BASE_URL=...
py -I tools\cd2.py bench run --model qwen-coder-32b --agent chat:qwen2.5-coder:32b
```

**`claude:<model>`: Claude Code as an agent** (`tools/bench_claude.py`), sandboxed by its own permission system. It may
read and edit the workspace and run only the task's check: no other commands, no files outside, no web, no MCP
servers, and none of your settings, CLAUDE.md files or memory. If the installed version lacks a flag this needs, it
refuses to run.

**`kilo:<provider/model>`: Kilo Code's CLI as an agent** (`tools/bench_kilo.py`), for example
`kilo:openrouter/deepseek/deepseek-chat`. Its permission rules come through `KILO_CONFIG_CONTENT`, which overrides the
global and project configuration: everything denied, then reading and editing the workspace allowed, and of the shell
only the task's check; no paths outside the workspace, no web, no subagents. `kilo run` without `--auto` refuses
whatever it would have to ask for. It refuses to run while your global Kilo configuration sets permissions of its own.
Set up Kilo's credentials once as its documentation describes. This preset follows Kilo's documentation but was not run
against Kilo here: try one task first (`--limit 1`) and read `agent.log` in the workspace.

**Any other agent: its command.** Codex, Aider, Gemini CLI, OpenHands, a script of your own: anything that can run
unattended. The runner starts the command in the task's workspace:
- `TASK.md` is piped to its standard input;
- `{task}` and `{workspace}` in the command are replaced by the paths;
- `CD2_TASK`, `CD2_WORKSPACE` and `CD2_CHECK` (the command that scores the workspace) are set.

For example `aider --message-file {task} --yes-always --no-git` (check your agent's current flags). Give such an agent
no web access (the solutions are public) and, if it has a sandbox mode, confine it to the workspace: the runner cannot
stop an unrestricted shell from looking elsewhere on the machine.

**IDE agents** (Kilo Code's, Cline's or Roo Code's VS Code extension, Cursor, Copilot's agent mode, Windsurf, ...) work
through the suite by hand:

```
py -I tools\cd2.py bench prepare --model NAME        # every suite task's workspace (or --tier N / --limit N)
    ... open each workspace folder in the editor and tell the agent: "Do the task in TASK.md." ...
py -I tools\cd2.py bench score --model NAME          # the final verdict of every task, then `bench report`
```

Open the workspace folder itself, not the repository, so that the agent's project is the workspace. In the agent's
settings, while benchmarking: no web or browser tools; no reading or writing outside the workspace; edits inside it
may be approved automatically; and of the commands only the task's check (Kilo Code: the `bash` and
`external_directory` permissions; Cline and Roo Code: auto-approve with an allowed-commands list). Time and tokens are
not recorded in this mode; attempts are, through the check command.

What the harness guarantees for every kind of agent:
- **The workspaces are outside the repository**, in `%LOCALAPPDATA%\cd2-bench\<model>\<address>` (or
  `cd2.py config --bench-dir`, or `CD2_BENCH_DIR`; never inside the repository). A workspace holds the source file with
  the one function's body blanked, a copy of `include/` and the notes, and `TASK.md`. No solution, no git history, and
  none of the repository's agent instructions are next to it.
- **The verdict is the harness's.** After the agent exits, the runner checks the workspace once more; that check is the
  result. The results are kept beside the workspace, not in it, and a forged result file changes nothing.
- **The source policy applies**, with only the workspace and the XDK as allowed origins: no `__emit` of CD2's words, no
  `#include` of the repository's own file, no inline assembly or pragmas.
- **Copying is flagged.** `bench report` counts solutions identical to the repository's. That is expected for tiny
  functions and suspicious for long ones.

The suite's solutions are public once the repository is, so a model trained after that may have seen them. Compare
models with that in mind, and refresh the suite (`bench suite --make`, maintainers) as new functions are solved.

By hand, one task at a time: `bench prepare <address> --model NAME`, work in the workspace, then
`bench check <address> --model NAME`.

`cd2.py bench selftest` proves the harness, and `verify` runs it. On every suite task, an oracle agent that pastes the
known solution must reach EXACT, and so must the chat agent driven by a stand-in model (a local mock API, which also
tries to read outside its workspace and must be refused). A do-nothing agent must reach EXACT on none. On one task per
tier, three cheating agents must fail: one emits CD2's instruction words, one includes the repository's file, one
forges its result.

## Rules

The source policy is enforced on the **preprocessed** source (`cl /P`), so macros cannot hide anything. Only lines
from this repository are checked. `cd2.py lint` runs it and `cd2.py lint --self-test` proves it works.

- Not allowed: inline assembly (`__asm`), `__emit`, `__declspec(naked)` and `__declspec(allocate)`, `__pragma`, and
  any `#pragma` other than `pack`, `warning` and `once`. These would let code match without being source; `#pragma
  optimize` or `inline_depth` would change code generation for one function.
- Not allowed: `#line`, which would disguise where code comes from, and including files from outside the repository
  and the XDK.
- Matched functions must be in an ordinary code section (`.text`, or the compiler's own `.text$yc`/`.text$yd` for
  static initializers and at-exit destructors).
- Flagged for review: `goto`. It is rarely what the original source did.
- No invented duplicates of shared bases. Game classes derive from `cNonGameBase`, prototypes from
  `GOM::cObjectPrototype` (`include/README.md`).

## For agents

Every command accepts `--json` and exits with 0 only on success. The fields that matter:

- `tasks`: `tasks[]` with `address`, `size`, `file`, `tier`, `features` (instructions, calls, float_ops, vmx,
  jump_table, loops), `status`, and `symbol`.
- `show`: `assembly`, `hints[]`, `neighbours[]`, `status` and `symbol`.
- `check`:
  - `functions[]`, with `status`, `plain` (percent), `name` (the compiled symbol) and `tracked`;
  - `relocation_problems[]`, `policy_errors[]` and `policy_warnings[]`;
  - `ok`, which is true when every tracked function of the file is exact and there are no problems. Tracked means
    already matched (a manifest entry not marked work in progress), so `ok` says nothing regressed; the function you
    are working on is judged by its own `status` (`EXACT`).
- `diff`: `diff.match_percent`, `diff.differences` (counts by kind), and `diff.rows[]` with `cd2`, `ours`, `kind` and
  `cd2_address`. Rows with `gap` mark omitted equal instructions.

A useful loop:
1. `show`, then write the function and `check`.
2. While it is not exact, read `diff`'s findings and fix the most fundamental first.
3. When only small differences remain, run `search`.

Read `docs/matching-notes.md` for the compiler's habits. Agents' own reports are never evidence: only `check` and
`verify` output counts, and the attempt log records every run.

**MCP:** `tools/mcp_server.py` exposes the same commands as tools for any agent that speaks the Model Context Protocol:
`cd2_status`, `cd2_tasks`, `cd2_show`, `cd2_claim`, `cd2_unclaim`, `cd2_check`, `cd2_diff`, `cd2_search`, `cd2_lint`,
`cd2_verify` and `cd2_bench_check`. Register it as a stdio server: the command is `py`, with the arguments
`-I tools/mcp_server.py`. Each tool returns the command's JSON.

## Reviewing contributions

There is no CI: a maintainer verifies each pull request on their own machine, with the game, before merging it.

```
git fetch origin pull/123/head:pr-123
py -I tools\cd2.py review pr-123 [--record-facts]
```

`review` needs a clean checkout of main. It applies only the pull request's own changes to `src/`, `include/`,
`config/matched_functions.json` and `docs/matching-notes.md` (those it added, changed or deleted since it branched),
runs every gate with this checkout's tools and config, and restores the checkout. A pull request therefore cannot
change the gates that judge it. Its changes anywhere else (tools, config, tests, `.github/`) are listed separately and
fail the review: they need reading by hand, and merging only if intended. With `--record-facts` it records the target
facts for the new manifest entries first (below); commit `config/target_facts.json` with the merge.

## Verifying without the game

For every function in the manifest, maintainers record facts in `config/target_facts.json` (`cd2.py facts record`, or
`review --record-facts`, with the game). From these facts a match can be confirmed, but no code can be recovered:

- a hash of CD2's bytes with the linker-filled fields masked, and the positions of those fields;
- the CD2 address each relocation resolves to;
- the float constants referenced, and hashes of the referenced strings (their text is not stored);
- for LTCG, the constants CD2 loads directly and a hash of the masked code.

`cd2.py verify --facts` then reaches the same verdicts as the game-based gates, on a machine with the XDK but without
the game. The normal `verify` also checks that the facts are current. `py -I tools/facts.py --self-test` plants a wrong
call, a changed string, a changed constant and a changed constant in a function exact only under LTCG; each must be
caught.

## Trust model

| Risk | Control | Status |
|---|---|---|
| Claiming results without verification | A maintainer recomputes everything before merging; agent reports are ignored | `review` (see [Reviewing contributions](#reviewing-contributions)) |
| Editing the gates, config or the symbol table | Tools and `config/` are maintainer-owned; `review` judges with main's tools and lists every change outside the contribution paths | `review`; optionally `.github/CODEOWNERS` with code-owner review |
| Matching by similarity instead of by symbol | Every comparison is by symbol, against `config/matched_functions.json` | Done |
| Right bytes, wrong call target or global | Relocation targets resolved and checked repository-wide (`tools/relocs.py`) | Done; `check` reports `WRONG TARGET` |
| Code that is not source (asm, emit, pragmas, custom sections) | Source policy on the preprocessed source; code-section check | Done, with self-tests |
| Another compiler build or other flags | Toolchain pinned by hash; flags defined once in `tools/verify_src.py` | Done |
| The same function claimed by two files, or code in the wrong file | Ownership gate (`tools/check_integrity.py`) | Done, with self-test |
| Duplicate stand-in types | Shared headers and the types check; review | Partly: the types check catches identical names, not the same class under two names |
| Running a contribution's code | `review` runs no contributor code except the compiler on their source; their tools are never applied | `tools/sweep.py` specs are Python: local use only |
| Distributing game code | Nothing from the game is stored; targets come from each contributor's own XEX | Done; `verify --facts` compares against recorded hashes and addresses (`config/target_facts.json`) |

What automation cannot prove: that names are right, that the source is what the developers wrote, and that
stand-ins reflect reality. These need provenance notes in headers (where each name and layout comes from) and human
review.

## What comes next

- Run the benchmark with real models (cheap and strong), tier by tier, to see what each can do unaided.
- Grow the mismatch findings and the search transformations as `docs/matching-notes.md` grows.
- Fill in `.github/CODEOWNERS` if you want GitHub to request your review on maintainer-owned files.
