# Instructions for AI agents

You are contributing to a **matching decompilation** of Crackdown 2 (Xbox 360). Your job is to write C++ that the
original compiler turns into exactly the game's machine code. These instructions apply to every agent: Claude Code,
Codex, Cursor, Aider or any other.

## Before you start

The project runs on Windows only (the original Xbox 360 XDK compiler). Run `py -I tools/cd2.py doctor`. If it is not
all "ok", follow the Quick start in `README.md`. Two inputs must come from the person you work for, so ask them for
the paths: their own copy of the game (`default_patched.xex`) and the extracted Xbox 360 XDK 9328. Never download or
search for either.

## Ground rules

1. **Only tool output is evidence.** A function is matched when `tools/cd2.py check` says `EXACT`, and only then.
   Never report a match you have not seen in `check` output. Never edit a tool to change what it reports.
2. **Do not edit** anything under `tools/`, `tests/` or `.github/`. In `config/`, only add entries for functions you
   matched to `config/matched_functions.json`, and record their target facts with `py -I tools/cd2.py facts record`
   (it rewrites `config/target_facts.json` from the game; never edit that file by hand).
3. **No tricks:**
   - no inline assembly, `__emit`, `__declspec(naked)` or `__declspec(allocate)`, or `#line`;
   - no `#pragma` other than `pack`, `warning` or `once`;
   - **no pointer arithmetic to reach memory**: no cast to `char *` plus an offset, no pointer turned into an integer,
     no hard-coded address, no raw memory indexed through a cast. When CD2 reads offset 0x50C of an object, declare the
     member at 0x50C in the class's header (with its `CD2_OFFSET` check) and use it by name, even if all you can call it
     is `m_word50C`. Declare a global with a name and a type. Reach a base or derived class with `static_cast`.
     Typed pointer code the developers would have written is fine: walking an array with `p + i` or `++p`, `end - begin`.
     Spreading the arithmetic over statements (`const char *p = reinterpret_cast<const char *>(this); p += 0x38;`),
     keeping a pointer in an integer field, or casting through `void *` is the same thing, and `check` rejects it too.

   `check` rejects them on the preprocessed source. Pointer arithmetic gives the same instructions, but it proves nothing
   about the layout, and a hard-coded address has no relocation, so `check` cannot tell whether it is the right global.

   Beyond what `check` can see, ask of every line: would a programmer on the original team have typed this? Matching
   bytes produced by code nobody would write is a fake match, and it does not count: dummy locals, `volatile` to hold a
   value in a register, padding members or extra fields that only shift the layout, empty blocks, casts that do nothing.
   When you choose an unusual construct because only it reproduces CD2's code (`__forceinline`, a `memset` instead of
   assignments, an odd statement order), say why in a one-line comment next to it, so the next person does not
   "clean it up". `lint` warns about `volatile` and about placeholder names such as `GetField50` or `m_word50C`.
4. **Use the shared headers** in `include/`. Game classes derive from `cNonGameBase` (`include/gom/non_game_base.h`);
   prototypes derive from `GOM::cObjectPrototype` (`include/gom/object_prototype.h`). Never define a second copy of a
   type that already exists: search `include/` first. A missing type gets its own header, one class per header, at
   `include/<Namespace>/<Class>.h`, marked as a stand-in with your evidence (see `include/README.md`). Names and
   layouts need evidence: see "Finding names and layouts" below.
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
6. Stop when the function is exact, or when you run out of ideas. Do not distort correct source to raise a score: a
   change that improves the percentage without reproducing what CD2 does is not progress. If you showed a reusable
   mechanism (a source shape that controls the code, with an A/B test), add it to `docs/matching-notes.md`; for a
   function you could not finish, add one line to its "Open functions" list saying what is ruled out.
7. When it is exact, add its entry to `config/matched_functions.json` (address, size, mangled symbol prefix;
   `"ltcg": true` if it is exact only under `--ltcg`), then run `py -I tools/cd2.py facts record`.
8. Before finishing, run `py -I tools/cd2.py verify`. It must pass.

`WRONG TARGET` means the bytes match but a call or global goes elsewhere than in the game: you called the wrong
function, or used the wrong global or constant.

## Finding names and layouts

Every name and every field needs evidence. Use the strongest you have:

1. **Crackdown 2 itself.** `show` prints what the game says about a function: `name` lines are the script-method
   names it is registered under (CD2 builds the function's address, then the name), `vtable` lines are the virtual
   slots that point at it, and `callers` counts the direct calls. A script name is the method's real name, and the field
   a getter or setter touches is named after it (`SetFriendlyFireTolerance` stores `m_fFriendlyFireTolerance`).
2. **The reference builds in `refs/`**, later builds of the same codebase: RuffKing has the most names, Burn's base
   order and offsets are closest to CD2's. Vtable slot numbers differ between the builds: match virtuals by what their
   code does, not by slot. Headers give layouts and member names; each `.cpp` lists the functions
   and globals its object defined, with their addresses in that build. Search them for any class or name, not only the
   one the source file's top comment names. Sizes and offsets often differ: check every one against CD2's code.
   `refs/` is not in the public repository; maintainers have it and provide it on request.
3. **An IDA MCP server, if the person you work for has one**, with CD2's database and the reference builds'
   (RuffKing's and Burn's carry their PDB names): use it for callers, vtables and the reference builds' code. The names
   in CD2's own database were assigned by hand and may be wrong.

A function in your file whose `this` does not fit your class (it reads another class's fields, or several classes
register it under different names) is another class's code that the linker folded into your file: name it after that
class. Where nothing names a function or field, give it a descriptive name and say in the header that the name is ours.
`refs/` and IDA are evidence for names and layouts, never for a match (only `check` is), and nothing from them goes
into the repository (rule 6).

## MCP

`tools/mcp_server.py` exposes the same commands as tools (`cd2_tasks`, `cd2_show`, `cd2_check`, `cd2_diff`,
`cd2_search`, ...), registered for MCP clients in `.mcp.json`.
