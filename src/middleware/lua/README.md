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

Behavior changes below are shown by CD2's code. Inlining annotations recover its observed call boundaries; their
original spelling is unknown.

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
4. **`liolib.c`: Xbox environment and exit stubs.** CD2's OS registration table at `0x82020660` names `exit` at
   `0x82940618` and `getenv` at `0x8293FE68`. Their bodies return zero and one respectively, with no CRT or Lua calls.
   The `_XBOX` guards preserve the release's implementations on other platforms; the original guard spelling is unknown.
5. **`lbaselib.c`: no environment fallback for LUA_PATH on Xbox.** `getpath` tries the Lua global and then the
   default path, with no CRT environment call. `require` retains calls to all three path helpers.
6. **`lmathlib.c`: single-precision conversions.** The degree/radian constant has `lua_Number` precision. The two
   bounded `random` cases convert the floored integer to `lua_Number` before adding the bound; CD2 separately
   converts the two integer operands and adds them in single precision. All 25 math-library functions check exact.
7. **`lauxlib.c`: archive extensions.** The original names are unknown. `luaL_setfileopen` replaces an fopen-compatible
   callback, whose initial target is CRT fopen; `luaL_setarchive` stores a serialized archive pointer. The archive helpers
   hash unsigned filename bytes with FNV-1 and lowercase names in place. The installer and stream readers establish a count, 0x110-byte filename/hash/offset/size records, and following payload bytes.
   Shared checked types live in `include/lua/`; `luaL_loadfile` first tries the archive and then the replaceable file callback.
8. **Explicit inlining boundaries.** `__inline` and `__declspec(noinline)` retain CD2's observed helper calls and
   expansions without changing function linkage or upstream algorithms. Each annotation has a target-call comment;
   isolated compiler probes preserve prior exact functions, and every promoted caller passes `check`, including
   relocation and source-policy checks. These annotations model the observed result, not a recovered compiler command.

9. **`lvm.c`: interpreter arithmetic.** Binary arithmetic independently coerces both operands before testing success.
   Add/subtract/multiply/divide fallback dispatch uses the shipped opcode values; power uses its separate power
   metamethod. The complete 6,076-byte interpreter loop passes `check`, preserving the other 17 VM functions.

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

## Match coverage

All 641 Lua functions in the corrected source inventory pass `check`. IDA confirms that `reallymarkobject` spans
`0x82946980..0x82946A30` (176 bytes); jeff's analysis splits off its last 12 bytes as a second function. The match
itself proves the full extent: `reallymarkobject` compiles exact over all 176 bytes, so `tools/cd2.py` drops any
function start inside a matched function's manifest extent, in its inventory and in the symbol list `setup` splits
with. There is no 642nd function.

IDA also confirmed source ownership for the archive/loadfile tail, interpreter loop, and five CRT time forwarding
thunks preceding liolib. Their source splits now include those ranges. Selectively inlined helpers share one
implementation with retained out-of-line entries where target callers require both forms; blanket noinline or
changing static linkage does not reproduce the target.
