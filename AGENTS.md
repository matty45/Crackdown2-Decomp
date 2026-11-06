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
3. **No tricks, no fake code.** A function is matched only when `check` says `EXACT` *and* no matching rule fires in
   it. A function whose bytes match but that breaks a rule is `MATCH-PENDING`: it does not count, and `verify` fails
   while the manifest lists it. The rules (numbered as in the decomp-code-rules catalogue) and what `check` looks for:
   - **R18, assembly is not source:** no inline assembly, `__emit`, `__declspec(naked)` or `__declspec(allocate)`.
     Also never `#line` or a `#pragma` other than `pack`, `warning` or `once` (these fail the whole file).
   - **R4, typed members, not offsets: no pointer arithmetic to reach memory.** No cast to `char *` plus an offset, no
     pointer turned into an integer, no hard-coded address, no raw memory indexed through a cast. When CD2 reads offset
     0x50C of an object, declare the member at 0x50C in the class's header (with its `CD2_OFFSET` check) and use it by
     name, even if all you can call it is `m_word50C`. Declare a global with a name and a type. Reach a base or derived
     class with `static_cast`. Typed pointer code the developers would have written is fine: walking an array with
     `p + i` or `++p`, `end - begin`. Spreading the arithmetic over statements
     (`const char *p = reinterpret_cast<const char *>(this); p += 0x38;`), keeping a pointer in an integer field,
     declaring a member `char *` so that it can be moved by an offset without a cast (`return m_p60 - 0x1C;` is
     `static_cast<cNonGameBase *>(m_pInstigator)` with the member's real type), or casting through `void *` is the
     same thing. Pointer arithmetic gives the same instructions, but it proves nothing
     about the layout, and a hard-coded address has no relocation, so `check` cannot tell whether it is the right global.
     Decompiler pseudocode (`a2`, `v3`, `return (int)this;`, `p - 7`) is full of exactly this: never paste it in and
     tidy it up. A constant subtracted from a pointer just loaded is a cast from a base: find the member's real type.
   - **R17, no fake code:** no `volatile` local (a `volatile` member or global needs a `// volatile: <evidence>` note on
     its line), no unused local, no empty `if`/`else` body or bare `;` statement (empty loop bodies and `case X: ;` are
     fine), no `do { } while (0)` outside a macro, no self-assignment, no `+ 0` or `* 1`.
   - **R2, globals declared once, in their header:** no `extern` variable in a `.cpp`.
   - **R13, vtables from evidence:** no virtuals named `pad`, `dummy` or `unused`; declare the slots CD2 has. A
     function that `show` lists under `vtable` is a virtual: declare it `virtual`, in that slot, in the class that owns
     the table. A two-instruction getter or setter with 0 direct callers is almost always one. Its bytes match whether
     it is virtual or not, so `check` reads the compiled name: a plain member function that CD2 has in a vtable is
     MATCH-PENDING. If the class's header does not declare the slots before it yet, leave the function open.
   - **R1, one declaration per type:** a type is defined once (in `include/`), and with the same `class` or `struct`
     keyword everywhere.

   A finding inside a function's body blocks that function; one at file scope or in a header blocks every function of
   the file. Beyond what `check` can see, ask of every line: would a programmer on the original team have typed this?
   Matching bytes produced by code nobody would write is a fake match even when no rule catches it: dummy temporaries,
   reused variables, padding members that only shift the layout, casts that do nothing.

   When CD2's bytes force an unusual construct (`__forceinline`, a `memset` instead of assignments, an odd statement
   order), say why next to it, as `// RULE-EXCEPTION: R<n>, <the reason the bytes give>` when it bends a numbered rule,
   or in a plain comment otherwise, so the next person does not "clean it up". An exception can bend a style rule but
   never the rules above: fake code is never allowed. `lint` also lists advisory findings that do not block a match:
   placeholder and address-like names (`GetField50`, `m_word50C`, `g_830BBDB4`, or `RetCE3F0`: an address with its
   leading digits dropped is still an address), `goto`, `#if 0`, `!!x`. Renaming a placeholder so that `lint` stops
   listing it, without evidence for the new name, is evasion.
4. **Use the shared headers** in `include/`. Game classes derive from `cNonGameBase` (`include/gom/non_game_base.h`);
   prototypes derive from `GOM::cObjectPrototype` (`include/gom/object_prototype.h`). Never define a second copy of a
   type that already exists: search `include/` first. A missing type gets its own header, one class per header, at
   `include/<Namespace>/<Class>.h`, marked as a stand-in with your evidence (see `include/README.md`). Names and
   layouts need evidence: see "Finding names and layouts" below. Most files' initializer runs open with the same
   header constants (fPhysicsSimulationTick, WORLD_UP_VECTOR, ...): they come from including the constants headers,
   never from a definition in the `.cpp` (`docs/matching-notes.md`, "Header constants").
5. **Stay in the file.** Write a function in the source file that owns its address (`config/splits.txt`).
6. **Nothing from the game in the repository.** Never paste the game's bytes or assembly into a committed file.
7. **Lay a source file out as a programmer would.** All `#include` lines go at the top of the file, after its header
   comment, and nowhere else. A namespace gets one block per file: put a new definition inside the existing block, at
   the place CD2's addresses give it (definitions stay in CD2's order, which also fixes the order of static
   initializers), never in a new `namespace X { ... }` block appended to the file. A second block of the same namespace
   is right only when something that must stay outside it sits in between, such as a global-scope registrar. Scripts
   that add functions in bulk must insert them the same way.

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
2. Work on one function at a time: claim it, write it from the assembly in `show`, `check` the file. Get the structure
   right first: calls, branches, loads and stores. Keep the file compiling at every step: a file that does not compile
   takes every matched function in it out of `verify`, not only the new one. A session can be cut off at any moment,
   so before you stop, remove whatever is not exact.
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
class. Check a virtual's owner the same way: compare its `vtable` lines with those of the class's own `RetClassName`
(primary slot 11). A function in other tables, or in many, belongs to their common base or to a secondary base, and
its offsets count from that subobject. Never pad a class out to a field's offset (`unsigned char m_pad[0x2F0];` before
`m_field2F4`) when its base chain is not modelled (a STAND-IN header, or a base whose header says its layout is
incomplete): the field belongs to a base, and the function waits until the bases are modelled. Where nothing names a
function or field, give it a descriptive name and say in the header that the name is ours.
`refs/` and IDA are evidence for names and layouts, never for a match (only `check` is), and nothing from them goes
into the repository (rule 6).

## MCP

`tools/mcp_server.py` exposes the same commands as tools (`cd2_tasks`, `cd2_show`, `cd2_check`, `cd2_diff`,
`cd2_search`, ...), registered for MCP clients in `.mcp.json`.
