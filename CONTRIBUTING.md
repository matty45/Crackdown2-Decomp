# Contributing

Thank you for helping. You can work by hand or with any AI agent; the rules are the same.

## Before you start

1. Set up once (see the [README](README.md#quick-start)) and make sure `py -I tools\cd2.py doctor` is all "ok".
2. Read [docs/matching-notes.md](docs/matching-notes.md). It saves hours.
3. Pick a task and tell others you are on it: comment on the source file's issue, or open one with the **Claim a
   task** template, so that two people do not write the same function.

## The work loop

```
py -I tools\cd2.py tasks [file] [--tier N]           # open functions, easiest first
py -I tools\cd2.py show <address>                    # the brief: CD2's assembly, neighbours, hints
py -I tools\cd2.py claim <address> <symbol prefix>   # e.g. ?Update@cChaseBehaviour@AI@@ (the MANGLED name)
    ... write the function in its source file under src/ ...
py -I tools\cd2.py check <file.cpp> [--ltcg] [--explain]
py -I tools\cd2.py diff <file.cpp> <address>         # what differs, and the usual cause of each difference
py -I tools\cd2.py search <file.cpp> <address>       # tries source variations for the last few percent
```

Every command takes `--json`. The full reference is [docs/contributor-harness.md](docs/contributor-harness.md).

## Rules

Most of these are enforced by the gates, and a pull request that breaks one is not merged. The rest (marked stand-ins,
natural source) are checked in review.

- **Matches are proven, not claimed.** Only `check` and `verify` output counts. A pull request description saying
  "exact" carries no weight.
- **No tricks:**
  - no inline assembly, `__emit`, naked functions or custom sections;
  - no `#pragma` other than `pack`, `warning` or `once`;
  - no `#line`;
  - no includes from outside the repository and the XDK;
  - no pointer arithmetic to reach memory (a cast to `char *` plus an offset, a pointer turned into an integer, a
    hard-coded address): declare the member or global with its type and use it by name.

  These are checked on the preprocessed source.
- **The right file.** A function belongs to the source file whose address range in `config/splits.txt` holds it, even
  if it looks like another class's code (inline and template functions are emitted where they are used).
- **One definition.** Every type is defined once, in `include/` (or in the one source file that owns it). Game classes
  derive from `cNonGameBase` (`include/gom/non_game_base.h`) and prototypes from `GOM::cObjectPrototype`. Do not invent
  your own copy of a base class: ask, or extend the shared header.
- **Stand-ins are marked.** If you must model an unknown class, give it the right size and slots, and say at the top
  of the header that it is a stand-in and what evidence you have.
- **Natural source.** Write code a developer would have written. `goto` is flagged automatically; reviewers also look
  for odd constructs such as needless `volatile` or dummy temporaries.
- **No binaries, no game data.** The repository holds source and text only. Never commit anything extracted from the
  game.

## Maintainer-owned files

Pull requests may not change these without a maintainer's agreement (`cd2.py review` lists such changes for the maintainer):
- `config/`;
- `tools/`;
- `tests/`;
- `.github/`;
- `AGENTS.md`, `CLAUDE.md` and `.mcp.json`;
- `.gitmodules`, `.gitattributes`, `.gitignore` and `LICENSE`.

Two exceptions in `config/`:
- you may **add** entries for functions you matched to `config/matched_functions.json`: the address, size and mangled
  symbol prefix, plus `"ltcg": true` if the function is exact only under `--ltcg`;
- you then **record** their target facts with `py -I tools\cd2.py facts record`, which rewrites
  `config/target_facts.json` from your copy of the game (never edit it by hand). The maintainer records them again
  from their own copy when reviewing (`cd2.py review --record-facts`).

## Pull-request checklist

- [ ] `py -I tools\cd2.py verify` passes (paste its last lines into the pull request).
- [ ] New exact functions are added to `config/matched_functions.json`, and their facts recorded
      (`py -I tools\cd2.py facts record`).
- [ ] Anything non-obvious you learned is added to `docs/matching-notes.md` (pattern, then cause or fix).
- [ ] No binaries, no game data, no machine-specific paths.

## Working with AI agents

Point your agent at [AGENTS.md](AGENTS.md). Claude Code reads it through `CLAUDE.md`, and agents that speak MCP can use
`tools/mcp_server.py` (registered in `.mcp.json`). Agents follow the same rules. You are responsible for what your
agent submits, so review its source before you open a pull request.

To measure a model or an agent before it takes real tasks, run the benchmark: `py -I tools\cd2.py bench run --model
NAME --agent AGENT`. AGENT is `chat:<model>` for any model behind an OpenAI-compatible API (cloud or local), the
command of any agent, or `claude:<model>` / `kilo:<provider/model>`; IDE agents use `bench prepare` and `bench score`.
See [docs/contributor-harness.md](docs/contributor-harness.md#benchmark).
