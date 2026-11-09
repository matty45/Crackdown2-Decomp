# IJG libjpeg 6b (middleware)

This directory is **not decompiled game code**. It is the original source of the Independent JPEG Group's libjpeg,
release 6b, which Crackdown 2 links as `libjpeg.lib` for Scaleform's JPEG support. Everything under
`src/middleware/` is middleware; nothing outside it is (`config/middleware.txt`).

(The XDK's `d3dx9i.lib` carries its own, separately built copy of libjpeg. That copy is Microsoft's library code and
is linked as-is; it is not this directory.)

## Origin and license

- Source: libjpeg release 6b (27 March 1998), as redistributed in the `3rdParty/jpeg-6b` folder of the Scaleform GFx
  3.3 SDK. `README` is the release's own and states the IJG license, which permits this use provided the notice is
  kept.
- `jconfig.h` is the release's `jconfig.vc`, its configuration for Microsoft Visual C++, copied as the release's
  `install.doc` describes. (The copy in the Scaleform SDK adds three lines for Windows CE, which do nothing on Xbox.)
- Only the files CD2's objects are built from are here: the compressor and decompressor core, the `jmemansi` memory
  back end, and the integer, fast and float DCTs, in CD2's text order (`config/splits.txt`). The source and
  destination managers (`jdatasrc`, `jdatadst`) are not linked: Scaleform supplies its own.

## How CD2 built it

`libjpeg.lib` is Scaleform's build, and RuffKing's PDB records the same library (`Obj\Xbox360\Msvc90\Release`,
15.00.8153) as C++: Scaleform's jpeg project compiles every file as C++. So these `.c` files are compiled with `/TP`,
optimised for size (`/O1`, as CD2's Scaleform code is), with the compiler's default floating-point model
(`/fp:precise`) and with `NO_GETENV`, jpeg-6b's own switch for a platform without `getenv()` (the Xbox CRT declares
none). Inlining is `/Ob1` except in three files; `config/file_flags.txt` gives the evidence for each setting.

Compiled as C++, the constant tables are separate foldable data: CD2's linker merged `std_huff_tables`' two identical
DC value tables into one copy (`config/symbol_aliases.txt`).

## CD2's changes to the release

No behavior changes found. Explicit inlining annotations on helpers in jcparam, jcphuff, jdmarker, jquant1 and
jquant2 reproduce CD2's observed calls and expansions. Their original spelling is unknown;
the comments identify the affected target callers, and all existing matches in the affected files remain exact.

## Match coverage

All 329 functions in CD2's Scaleform libjpeg source inventory pass `check`. `/Oi` preserves all 322 previously
tracked matches and makes the remaining seven exact: jpeg_gen_optimal_table, both finish_pass_gather implementations,
jinit_inverse_dct, jpeg_make_d_derived_tbl, get_dht and prepare_range_limit_table. The published MEMZERO/MEMCOPY calls
remain intact; `/Oi` controls their intrinsic expansion and scheduling. See `config/file_flags.txt`.

## Matching rules

The release breaks three of the repository's matching rules, which `config/middleware.txt` waives for this directory
only: R1, for its conditional placeholder definitions of internal structures; R4, because its memory manager hands out blocks that every module casts to its own structures and steps through
by offsets; R17, because its unrolled DCT and dithering code is written with regular index expressions such as
`inptr[DCTSIZE*1]` and `errorptr[dir3+0]`. As for Lua (`src/middleware/lua/README.md`), this is the published source
as its authors wrote it, not a reconstruction, so the rules have nothing to check here.
