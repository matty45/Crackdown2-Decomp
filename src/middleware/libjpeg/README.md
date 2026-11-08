# IJG libjpeg 6b (middleware)

This directory is **not decompiled game code**. It is the original source of the Independent JPEG Group's libjpeg,
release 6b, which Crackdown 2 links as `libjpeg.lib` for Scaleform's JPEG support, unchanged. Everything under
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

None found: every function matched so far compiles exact from the release.

## Open

315 of CD2's 329 libjpeg functions are exact. The other 14 (in jchuff, jcparam, jcphuff, jddctmgr, jdhuff,
jdmarker, jdmaster, jquant1 and jquant2) differ in what was inlined: CD2's inlining lies between `/Ob1` and `/Ob2`,
as Lua's does (`src/middleware/lua/README.md`). Ruled out: C, `/O2`, `/O2 /Ob1`, `/O2 /Os`, `/Ox /Os`, `/O1 /Oi`,
`/GS`, `/fp:fast`, `/fp:strict`, and the backend's `inlS` limit.

## Matching rules

The release breaks two of the repository's matching rules, which `config/middleware.txt` waives for this directory
only: R4, because its memory manager hands out blocks that every module casts to its own structures and steps through
by offsets; R17, because its unrolled DCT and dithering code is written with regular index expressions such as
`inptr[DCTSIZE*1]` and `errorptr[dir3+0]`. As for Lua (`src/middleware/lua/README.md`), this is the published source
as its authors wrote it, not a reconstruction, so the rules have nothing to check here.
