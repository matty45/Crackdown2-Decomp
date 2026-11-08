# Lua 5.0.2 (middleware)

This directory is **not decompiled game code**. It is the original source of Lua 5.0.2, the scripting language
Crackdown 2 links as `lua.lib`, with the few changes CD2's build made to it. Everything under `src/middleware/` is
middleware; nothing outside it is (`config/middleware.txt`).

## Origin and license

- Source: the Lua 5.0.2 release (`lua-5.0.2.tar.gz`, lua.org, 2004). Each file keeps its upstream `$Id` line.
- License: MIT, see `COPYRIGHT` (kept from the release). The notice stays with the files.
- Layout: the release's `src/*.c`, `src/lib/*.c` and `include/*.h` are kept together in this one directory, so every
  file finds the headers next to it. Only the objects CD2 links are here: no `lua.c`/`luac.c` (the standalone
  programs), `ltests.c` (the test build) or `lopcodes.c` (data only, no code).

## How CD2 built it

- Compiled as C with the game's compiler (XDK 15.00.8153) and `/Ox`, without `/GL` (CD2's Rich header has no LTCG C
  objects), so these files have no LTCG check.
- `LUA_NUMBER=float`: CD2's numbers are single precision.
- Inlining differs per object: `/Ob2` for most files, `/Ob1` for `ldo.c` and `lstring.c`. CD2 inlines more than `/Ob1`
  and less than `/Ob2`, so neither setting reproduces every function. `config/file_flags.txt` gives the evidence.
- Link order (CD2's text): lapi, lauxlib, lstate, lbaselib, ltablib, liolib, lstrlib, lmathlib, ldblib, loadlib,
  ldebug, lmem, ldo, lgc, ltm, lvm, lobject, lstring, lfunc, ltable, lzio, ldump, llex, lparser, lundump, lcode
  (`config/splits.txt`).

## CD2's changes to the release

Each is shown by CD2's code; nothing else in these files differs from the release.

1. **`lmem.c`: allocation through replaceable functions.** The release calls `realloc` and `free`. CD2 calls them
   through two static function pointers, `l_reallocfn` and `l_freefn`, which start out at wrappers of `realloc` and
   `free`, and adds two setters the game calls during start-up to route Lua's memory to its own heap. The setter that
   stores into the pointer initialised with the realloc wrapper is `lua_setreallocfn`, the other `lua_setfreefn`.
   These four names are ours; CD2 has no symbols for them.
2. **`ldo.c`: `luaD_throw` does not exit.** After calling the panic function, CD2 returns instead of calling
   `exit(EXIT_FAILURE)`.
3. **`loadlib.c`: no DLL loader on Xbox.** The release selects the Windows `LoadLibrary` loader under `_WIN32`; CD2 has
   the stub that reports that `loadlib` is not enabled. Written here as `#if defined(_WIN32) && !defined(_XBOX)`; the
   bytes are the same whatever the original spelling was.

## Matching rules

The release breaks two of the repository's matching rules, which `config/middleware.txt` waives for this directory
only:

- **R4 (typed members, not offsets).** Lua keeps stack positions as byte offsets so that they survive a stack
  reallocation (`savestack`/`restorestack` in `ldo.h`, used by `luaD_checkstack` and `incr_top`), stores a string's
  characters right after its header, reserves `EXTRASPACE` bytes before each state, steps through byte buffers and
  casts reader state from `void *`.
- **R17 (no fake code).** `struct lua_longjmp` holds a `volatile int status`, which must survive the `longjmp`.

The rules exist so that reconstructed game code cannot hide offsets and casts a decompiler produced behind matching
bytes. This code is not reconstructed: it is the published source, as its authors wrote it, and CD2's bytes come from
it. Rewriting it to satisfy the rules would replace the original with code nobody shipped. Every other rule applies,
and `lint` and `check` still list each waived finding.

## Open

568 of CD2's 642 Lua functions are exact. The other 74 (25 KB, including the interpreter loop `luaV_execute`, 6,076
bytes in CD2) differ in what was inlined, not in what the code does. CD2's build did not give `static` functions
that are called once their usual inlining bonus: compiling with the backend's hidden `/d2inlS` limit at 40 or below,
or with every `static` function made external, reproduces CD2's choices (604 and 610 exact), but neither is a setting
the original build used, so neither is used here. Ruled out so far: `/Ob0-2`, `/O1`, `/O2`, `/Os`, `/TP`, `/Oi-`,
`/Oy-`, `/Gy-`, `/Zi`, `/Z7`, `/GS`, `/fp:precise`, the PGO inlining profile, and the reference builds' Lua project
flags (`-Ox -Os ... -Zi -TC`), a single-file (unity) build, LTCG, the 14.00 compilers of older XDKs, and another
compiler build: XDK 8276's compiler is byte-identical to XDK 9328's. `docs/matching-notes.md` ("Middleware") has
the details.
