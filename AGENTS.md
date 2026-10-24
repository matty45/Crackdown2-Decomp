# Instructions for AI agents

You are contributing to a **matching decompilation** of Crackdown 2 (Xbox 360). Your job is to write C++ that the
original compiler turns into exactly the game's machine code. These instructions apply to every agent: Claude Code,
Codex, Cursor, Aider or any other.

## Ground rules

1. **Only tool output is evidence.** A function is matched when `tools/cd2.py check` says `EXACT`, and only then.
   Never report a match you have not seen in `check` output. Never edit a tool to change what it reports.
2. **Do not edit** anything under `tools/`, `tests/` or `.github/`. In `config/`, only add entries for functions you
   matched to `config/matched_functions.json`.
3. **No tricks:**
   - no inline assembly, `__emit`, `__declspec(naked)` or `__declspec(allocate)`, or `#line`;
   - no `#pragma` other than `pack`, `warning` or `once`.

   `check` rejects them on the preprocessed source.
4. **Use the shared headers** in `include/`. Game classes derive from `cNonGameBase` (`include/gom/non_game_base.h`);
   prototypes derive from `GOM::cObjectPrototype` (`include/gom/object_prototype.h`). Never define a second copy of a
   type that already exists. If a type is missing, add it to the right header, marked as a stand-in with your
   evidence.
5. **Stay in the file.** Write a function in the source file that owns its address (`config/splits.txt`).
6. **Nothing from the game in the repository.** Never paste the game's bytes or assembly into a committed file.

## The loop

Run everything from the repository root. Add `--json` to any command for machine-readable output.

```
py -I tools/cd2.py doctor                          # the environment is ready (all "ok")
py -I tools/cd2.py tasks --tier 1                  # pick an open function, easiest first
py -I tools/cd2.py show <address>                  # its brief: CD2's assembly, neighbours, hints
py -I tools/cd2.py claim <address> <symbol prefix> # the MANGLED name prefix of the function you will write
py -I tools/cd2.py check <file.cpp> --explain      # EXACT, a percentage, or WRONG TARGET, with findings
py -I tools/cd2.py diff <file.cpp> <address>       # the differing instructions, and what usually causes them
py -I tools/cd2.py search <file.cpp> <address>     # automatic source variations for the last few percent
```

How to work:
1. Read `docs/matching-notes.md` before your first function, and the header of the class you work on.
2. Write the function from the assembly in `show`. Get the structure right first: calls, branches, loads and stores.
3. Read the `diff` findings and fix the **first** one; they are ordered from most to least fundamental. A wrong
   field offset is a header problem: fix the header, not the function.
4. Floats: the game was built with link-time code generation. If a finding says "float constants: CD2 loads them the
   LTCG way", run `check --ltcg`; a function that is exact only there gets `"ltcg": true` in its manifest entry.
5. When only register numbering or ordering differs, run `search`. Use `--apply` to keep its result.
6. Stop when the function is exact, or when you run out of ideas. Leave a short note on what you tried in
   `docs/matching-notes.md` if it would help the next person.
7. Before finishing, run `py -I tools/cd2.py verify`. It must pass.

`WRONG TARGET` means the bytes match but a call or global goes elsewhere than in the game: you called the wrong
function, or used the wrong global or constant.

## MCP

`tools/mcp_server.py` exposes the same commands as tools (`cd2_tasks`, `cd2_show`, `cd2_check`, `cd2_diff`,
`cd2_search`, ...), registered for MCP clients in `.mcp.json`.
