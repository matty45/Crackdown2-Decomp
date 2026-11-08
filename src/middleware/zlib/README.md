# zlib 1.2.3 (middleware)

This directory is **not decompiled game code**. It is the original source of zlib 1.2.3, the compression library
Crackdown 2 links as `zlibXenon.lib`, unchanged. Everything under `src/middleware/` is middleware; nothing outside it is
(`config/middleware.txt`).

## Origin and license

- Source: the zlib 1.2.3 release (July 2005, Jean-loup Gailly and Mark Adler), as redistributed unmodified in the
  `3rdParty/zlib-1.2.3` folder of the Scaleform GFx 3.3 SDK. `README` is the release's own.
- License: the zlib license, stated at the top of `zlib.h`. The notice stays with the files.
- Only the files CD2's objects are built from are here. CD2 links the inflate side of zlib alone: `uncompr`, `inflate`,
  `zutil`, `inffast`, `inftrees`, `adler32` and `crc32`, in that text order. The linker dropped everything the game
  never calls (deflate, the gz* file functions, inflateBack, ...).

## How CD2 built it

RuffKing's PDB records the compile command of the same zlibXenon project: `-Ox -DNDEBUG -D_XBOX -D_LIB -D_MBCS -GF -MT
-Gy -TC`, with the XDK 15.00.8153 compiler. `-Ox` includes automatic inlining (`/Ob2`, `config/file_flags.txt`); the
other differences from the game's flags change nothing in these files. The objects are plain C, without `/GL`.

`inflate` itself lies in the order-list region at the start of `.text` (`config/splits.txt`, `hot`).

## CD2's changes to the release

None. Every one of CD2's zlib functions compiles exact from the release.

## Matching rules

The release breaks two of the repository's matching rules, which `config/middleware.txt` waives for this directory
only: R4, because it reads buffers a word at a time through `u4` pointer casts, copies its state through casts, and
(in 16-bit MS-DOS code not compiled here) moves far pointers by offsets; R17, because `crc32.c` guards its run-time
table with `volatile` flags. As for Lua (`src/middleware/lua/README.md`), this is the published source as its authors
wrote it, not a reconstruction, so the rules have nothing to check here.
