# Crackdown 2 matching decompilation: feasibility study

Status: research complete except for the items in [Open questions](#16-open-questions). The decomp went ahead on 2026-10-24; how to contribute is in [`docs/contributor-harness.md`](contributor-harness.md).
Date of research: 2026-10-22.
Scripts and pilot material referenced below are in [`tools/research/`](../tools/research/README.md).

---

## 1. Summary

A matching decompilation of Crackdown 2 (Xbox 360) is technically feasible. None of the possible blockers held up:

- The exact compiler is available, runs on Windows 11 without installing the XDK, and has been proven byte-exact on CD2 code (library and game code).
- Game code **was** built with link-time code generation (`/GL` + `/LTCG`; corrected 2026-10-23, section 4). Most functions still come out identical to a plain per-object compile (62 of 70 tested), so per-function matching works for the bulk. Functions that load float constants, and some others, need an LTCG build that faithfully reproduces CD2's; that build is not solved yet.
- The toolchain works end to end: jeff (XEX splitter) writes target objects, our compiled objects diff against them in objdiff at 100%.
- **The full-binary relink round trip is exact** (2026-10-24). jeff (with 8 source patches) splits the XEX into objects, the XDK linker links them, and the memory image is identical to the original word for word up to the XEX resources. `tools/relink.py` is now a gate (section 9).
- Cheap agents can match small and medium functions. In a 7-function pilot, Haiku 5.5 and Sonnet 5.5 each matched 3/7 exactly, 4/7 combined.
- Working one whole source file at a time works much better on boilerplate-heavy files: across five of them, Sonnet agents matched 59 of 73 functions (81%).
- **Gameplay logic is much harder.** On three gameplay files (batch 2), agents matched 82% of boilerplate bytes but only 15% of logic bytes, and did not reach the large logic functions. The repo now holds 8 source files with 131 functions exact in a plain build (134 under LTCG).
- **Revised estimate:** ~25–35% of game code from a first pass for ~$1–2k, and ~45–55% after header curation and a large-function pass, in 6–12 months for very roughly $5–15k (section 11).

The hard parts are scale and the hard tail, not technology:

- About 39,000 game-code functions, 1.47M instructions. Functions of 150+ instructions are only 4.4% of the count but 43% of the code, and agent performance on them is untested.
- The two symbol-bearing reference builds (RuffKing / Ryse prototype, Burn / Crackdown 3 alpha) give excellent coverage of **library** code but only weak automatic coverage of **game** code (~4–10% of functions confidently named), because the game code was substantially rewritten after Crackdown 2. Types and class names transfer far better than function bodies (85% of CD2 class names exist in the reference PDBs).
- Plan throughput: the user is on a Claude subscription with 5-hour and weekly caps. A single agent pass over all game functions is estimated at 0.8–1B tokens.

---

## 2. Inputs and where they live

| Item | Path / value |
|---|---|
| CD2 IDB (target, no symbols) | `<CD2 dir>\default_patched_vibe.xex.i64` |
| CD2 XEX (title update, the matching target) | same folder, `default_patched.xex`, SHA1 `EC7B163617CD725F50B0CCA665AAF943F9BC6D8A` |
| Game files (base XEX + data) | `D:\Games\Emulators\Emulators\x360\content\0000000000000000\4D5308BC\00007000\09B757A500AC2C0B1719\` (title ID `4D5308BC`). Contains `default.xex` (base, a different build) and an identical copy of `default_patched.xex`. |
| RuffKing (Ryse prototype, 2010-11-11) | `<RuffKing dir>\` (`RuffKing_Release.xex.i64`, `ruffking_release.pdb`) |
| Burn (Crackdown 3 alpha, 2012-01-12) | `<Burn dir>\` (`Burn_Release.xex.i64`, `burn_release.pdb`) |
| Skate (2007, RW4) | `<Skate dir>\sk8_na_f.xex.i64` |
| Spore (PC, RW4) | `<Spore dir>\SporeApp.exe.i64` |
| XDK installer | `<XDK installer>` |
| XDK, extracted (not installed) | `<XDK 9328>\` |

**Never use** the unpatched/base `default.xex` (in the game content folder) for anything. The only valid input is the title-update `default_patched.xex` (SHA1 `EC7B163617CD725F50B0CCA665AAF943F9BC6D8A`, entry `0x823BF8C8`). Check the hash before using any copy.

**Never use** the `default.pdb` in the Crackdown 2 folder (a fake test PDB) or the PDB in the NHL11 folder (corrupt).

The ~1,042 names already in the CD2 IDB were assigned by hand and may be inaccurate. Treat them as hints.

When the Burn IDB was first opened headless, IDA restored it from leftover unpacked files (`.id0/.id1/.nam/.til` newer than the `.i64`); opening it as-is was approved.

---

## 3. The target binary

### XEX and PE facts (title update build)
- XEX2, retail-encrypted, basic compression (not LZX). Original PE name `default.exe`, image base `0x82000000`, entry `0x823BF8C8`.
- PE file time `0x4CCBFE3A` = 2010-10-30 06:15:06 (the TU build). The base `default.xex` is a different build (entry `0x823A6D58`). The matching target is the TU build because the IDB is of it.
- Static library records in the XEX header: all XDK **2.0.9328** (June 2009 XDK): LIBCPMT, XAPILIB (QFE 9), D3DX9, XGRAPHC, XNET, XBOXKRNL, XONLINE, XMP, XHV2, XRNMS, XAPOBA (QFE 4), XAUDIO2 (QFE 4), XPARTY, **D3D9LTCG**, XMCOREL, **XAUDLTCG**. There are no C1/C2 compiler version records (later compilers stamp these; 15.00 does not).

| Section | VA | Notes |
|---|---|---|
| `.rdata` | `0x82000400`–`0x8216F658` | starts with the IAT (`0x82000400`, `0x468` bytes); debug directory at `0x8201D060` |
| `.pdata` | `0x8216F800`, size `0x53390` | 42,610 function entries |
| `.text` | `0x821D0000`–`0x8304906C` | 14.7 MB; "arch" data directory at `0x83047CBC` (size `0x10C0`) inside it; a tiny `b .`/data/`b .` stub at `0x83048D7C` |
| `PSFD00` | `0x83049200` | |
| `.data` | `0x83050000`, vsize `0x9F84FC` | the CRT static-initializer table (21,834 entries) starts at `0x83050004` |
| `.tls`, `.XBMOVIE`, `.edata` (`0x83A50000`), `.idata` (`0x83A60000`), `.XBLD` | | |
| `.reloc` | `0x83A70200` | **does not contain relocations**: its space holds XEX resources (localised achievement text, compressed data) |

- No RTTI for game classes (only 4 `std` exception classes from the CRT).
- Lua 5.0.2 (`$Lua: Lua 5.0.2 Copyright ...`, with `lua_Number = float`) and zlib 1.2.3 are linked in. Lua is used: 43 functions outside the Lua block call its API, including `luaL_loadbuffer`. No `.lua` scripts or Lua bytecode were found in the loose game data files; scripts may be inside the `.dff` archives.

### Function count
- IDA: 53,005 functions. `.pdata`: 42,610 entries. jeff: 74,551 functions.
- jeff and IDA agree on 52,643 starts (52,194 with identical sizes).
- **The IDB is missing ~21,900 real functions** (656 KB of code): 21,896 of them are already disassembled as code in IDA but were never made into functions, and 85% are referenced by pointers in data (vtables, the static-initializer table). Most are 24–31 bytes. The true function count is about **74,500**.
- 362 IDA-only starts (225 of them ≤8 bytes) are mostly tiny thunks or stubs that jeff merged.
- Update 2026-10-23: the ~21,760 missing functions have been created in the IDB (see `docs/idb-changes.md`).

### Function order list (found 2026-10-23)
CD2 was linked with a function order list (`/ORDER`, or an equivalent profile-guided ordering).

The measurement used the 14.7k exactly matched functions: for each, the RuffKing object it belongs to, then how often neighbouring CD2 functions come from the same object, per 256 KB window.
- **`0x821D0000`–`~0x823D0000` (about 2 MB, ~14% of `.text`):** same-object adjacency is only 0.04–0.12. Library and game functions are interleaved there, pulled out of their objects.
- **From about `0x82950000`:** library code is in normal object order (0.79–0.98).
- The static initializers and at-exit destructors at the end of `.text` are grouped separately, as usual.

Example: `CHARACTER::cNPCTintProfile::HandleAttributes` sits at `0x821D0300`, next to Havok and Scaleform functions. The rest of its source file (`MakeNew` `0x8255DF80`, `RetClassName` `0x8255DFD8`, the constructor) is around `0x8255DF80`.

Consequences:
- **Function-level matching:** none.
- **Splits:** a source file's functions can be divided between its main body and the hot region. Split tooling must allow several `.text` ranges per file.
- **Full relink:** the order list must be reproduced. It can be read off the binary: it is the sequence of functions in the hot region.
- The instrumented RuffKing build (with its trace markers) may be the kind of build such order lists were generated from.

### Composition
Each CD2 function was labelled with the origin of its matched RuffKing/Burn object (library name or game object), then gaps between agreeing neighbours were filled. Of 14.4 MB of functions (IDA's list):

| Origin | MB | % |
|---|---|---|
| Game code (anchored to RuffKing/Burn game objects) | 4.28 | 29.7 |
| XDK libraries | 2.97 | 20.6 |
| Unknown | 2.88 | 20.0 |
| Scaleform GFx | 1.75 | 12.2 |
| Havok | 1.06 | 7.4 |
| Wwise | 0.63 | 4.4 |
| jpeg / zlib / misc | 0.31 | 2.2 |
| Kynapse | 0.24 | 1.6 |
| CRT | 0.15 | 1.0 |
| Lua | 0.10 | 0.7 |

The "unknown" 20% is mostly CD2-only game code: Freaks (`Freak::CheckAttack`), vehicles and Agency vehicles (`cAgencyCar`), the voice-over scheduler (`cVOAScheduler`), the aggressive-response system, spawn points, RW4 `rw::graphics`, and Kynapse pathfinding use (`CPathFinder::FindNextMove::ASTAR`). Game plus engine source is therefore about 6.5–7 MB, against about 7.5 MB of library code.

Using jeff's complete function list, the game area holds **39,024 functions and 1,467,445 instructions**:

| Size (instructions) | Functions | % of functions | Instructions | % of code |
|---|---|---|---|---|
| 0–9 | 16,444 | 42.1 | 87,993 | 6.0 |
| 10–29 | 12,600 | 32.3 | 216,678 | 14.8 |
| 30–59 | 4,619 | 11.8 | 197,973 | 13.5 |
| 60–149 | 3,665 | 9.4 | 332,309 | 22.6 |
| 150–399 | 1,319 | 3.4 | 293,790 | 20.0 |
| 400+ | 377 | 1.0 | 338,702 | 23.1 |

Median 14 instructions, p90 78, p99 394, largest 9,159.

### Middleware versions
From the reference PDBs' library build paths (CD2's library code exact-matches these builds):

| Middleware | Version / build |
|---|---|
| Havok | `havok_august` drop, physics only (`hkxbox360_physicsonly`, `xenon-net_7-1`), built with 14.0.x (VS2005-era XDK) compilers |
| Kynapse | shipped as RenderWare AI (`middleware\rw\ai\lib\xbox360\vc_mt_callcap`), 14.0.2909 compiler |
| Wwise | v2010.2 build 3697 in RuffKing (Profile libs, compiled with 16.0.10224); CD2's matches suggest the same or close |
| zlib | 1.2.3 (`zlib123\projects\zlibxenon`) |
| Lua | 5.0.2 with float numbers (Burn ships it as `lua.lib`) |
| Scaleform GFx | version not recorded |
| NaturalMotion morpheme | RuffKing only; not in CD2 |

Library code without available source or libs (Scaleform, Havok, Wwise, Kynapse; ~3.7 MB) would stay as original binary objects, which is normal practice. The XDK libraries are the exact 9328 versions already on hand and can be linked as-is. "100%" for the project means 100% of game code.

---

## 4. Toolchain

### Extracting the XDK without installing it
`XDKSetupXenon9328.exe` is an unpacker plus four appended CAB archives. 7-Zip lists them with `7z l -t# <exe>`:

| Archive | Size | Contents |
|---|---|---|
| `2.cab` | 327 MB | `XDK\bin\win32` (compilers, linker, tools), `XDK\include`, `XDK\lib\xbox`, `XDK\TechPreview\Mar09Compiler` |
| `3.cab` | 76 MB | installer pieces and redistributables |
| `4.cab` | 54 MB | `XDK\lib\win32`, `XDK\lib\x64` |
| `5.cab` | 497 MB | `XDK\Source\Samples`, `XDK\Source\crt` (CRT source), tools, art, VS80/VS90 project wizards |

Everything was extracted to `<XDK 9328>\`; the separate CABs are in `9328\cabs\`. The extracted files carry the read-only attribute from the CAB.

### Compilers in the XDK
- Default: `XDK\bin\win32` cl/c1/c1xx/c2 **15.00.8153**, link **9.00.8153** ("Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 15.00.8153 for PowerPC").
- Tech preview: `XDK\TechPreview\Mar09Compiler\bin\win32` 15.00.8327.

### Making the tools run on Windows 11
- `cl.exe` runs directly: it ships with `cl.exe.manifest`, which binds the XDK's private runtime assembly (`Microsoft.VC90.CRT` 1.9.7.21022, app-local in `bin\win32`).
- `link.exe`, `lib.exe` and `dumpbin.exe` have no manifest, so `msvcr90.dll` fails to initialise (`0xC0000142`). Fix: copy `cl.exe.manifest` to `link.exe.manifest` (and `lib.exe.manifest`, `dumpbin.exe.manifest`), clear the read-only attribute, and touch the exe's timestamp so Windows drops its cached activation context.
- The tech-preview folder additionally needs `Microsoft.VC90.CRT.manifest`, `msvcr90.dll`, `msvcp90.dll` and `tlbref.dll` copied from `bin\win32` (its C++ front end imports ATL90/TLBREF/MSVCP90).
- With `/XEX:NO` the linker stops after writing the PE instead of also running `imagexex`.
- All of these fixes have already been applied to the extracted folder.

### Which compiler built CD2: 15.00.8153
- Lua 5.0.2 compiled with 8153, `/Ox /Gy /DLUA_NUMBER=float`: **32 of 33** located CD2 Lua functions are byte-identical with relocated fields masked. The miss, `luaG_runerror`, was located through a Skate hash match and is probably a wrong mapping.
- `/O2` gives the same output as `/Ox`. `/Ob1` gives 25/33; `/O1` and `/Os` give 11/33; `double` numbers give 26/33.
- Game code: three hand-written pilot functions and the agent pilots' matches were all compiled with 8153.
- 8327 vs 8153: byte-identical output on all 627 Lua functions, all 2,892 C++ functions of the XDK samples' ATG framework (`/fp:fast`), and every pilot function. They are interchangeable here; **8153 is canonical**.
- CD2 vs RuffKing: of 400 function pairs with identical instruction sequences, all differed only in offsets and constants and never in register allocation. RuffKing's game objects (2,917 modules) were compiled with 15.0.8153 too.

### Compiler flags (game code)

| Flag | Evidence |
|---|---|
| `/Ox` (≡ `/O2` here; implies `/Oi /Ot /Oy`) | Lua fingerprint; size-optimised builds match far worse. Note that the XDK wizard's default Release config favours size (`/Os`), so Ruffian customised this. |
| **`/Ob1`** (game code; corrected 2026-10-23) | CD2's `cFactionConfigData` scalar deleting destructor calls its out-of-line destructor, which only `/Ob1` reproduces. All earlier game matches are unchanged under `/Ob1`. The Lua library was built with `/Ob2` (32/33 vs 31/33), so library projects can differ. **Game-code flags: `/Ox /Ob1 /Gy /GF /GR- /GS- /fp:fast`.** |
| `/Gy` | function-level COMDATs; layout and `.pdata` per function |
| `/GF` | string pooling (XDK default) |
| `/GR-` | no RTTI for game classes |
| `/GS-` | the `__security_check_cookie` routine does not exist anywhere in CD2 (searched by its 6-instruction shape) |
| `/fp:fast` | With this compiler, `/fp:precise` and `/fp:strict` never fuse `a*b+c`, while `/fp:fast` emits `fmadds`. CD2's `UI::WeaponDropScreen::OnUpdate` computes `x * 0.5f + (float)y` with `fmadds`. In the game area 307 functions contain only fused ops versus 33 only unfused (mostly products that are reused, which cannot be fused). Pilot P5 matched under `/fp:fast`. |
| no `/EH` | only 17 C++ EH FuncInfo records (`0x1993052x` magic) exist in the whole binary; `/EHsc` on game code would produce thousands |
| native `wchar_t` | `_W` in RuffKing's mangled names |
| signed `char` (no `/J`) | pilot P6 matched with a plain `char` field that the code sign-extends (`lbz` + `extsb`) |

Defines used in the pilots: `/D_XBOX /DNDEBUG`. Calling convention: `this` in r3, arguments in r4–r10 and f1–, return in r3/f1; `__savegprlr_N`/`__restgprlr_N` helpers when many non-volatile registers are saved.

### LTCG (corrected 2026-10-23: game code IS compiled with `/GL`)
The earlier conclusion ("game objects compiled without `/GL`") was wrong for game code. It rested mainly on Lua, a separate library project built with different flags.

**Evidence that game code is LTCG:**
- **Pool-relative float constants.** The linker merges all float/double constants into one program-wide pool starting at `0x820F8C80`. Game functions load these constants through a base register set to the pool start, with fixed displacements (e.g. `addi r30, pool; lfs f0, 0x84(r30); lfs f0, 0x3D4(r30)`). A compiler working one object at a time cannot know the merged pool's offsets; only code generated at link time can.
- **Counts, using `.pdata` function boundaries** (`tools/research/compiler_re/ltcg_map.py`):

  | Region | Functions using the pool base | Functions loading 2+ pool constants directly |
  |---|---|---|
  | Game code (`0x821x`–`0x828x`) | ~1,000 | 1 |
  | Initializers (`0x82F`–`0x830`) | 3,914 | 0 |
  | Libraries (`0x829`–`0x82E`) | 0 | — |
- **Reproduced.** `src/VFX/cAmbientVFXSpawner.cpp` compiled with `/GL` and linked with `/LTCG` gives `CalcRandInitSpawnTime` the same pool-base form as CD2: 53 of 54 words, against 22% for a plain build. The remaining word is the operand order of one `fmuls`.

**Why the old evidence fit LTCG too:**
- **No cross-object inlining.** Game code uses `/Ob1`, so only functions marked `inline` are inlined, even under LTCG.
- **Exact plain matches.** Most functions generate identically either way.
- **The Lua test.** Lua (`/Ob2`) really was built without `/GL`.

**Consequences for matching** (`tools/research/compiler_re/ltcg_check.py` builds each source both ways):
- 62 of 70 tracked functions are byte-identical with and without LTCG, so plain per-object compiles remain the fast path.
- Functions that load float constants need an LTCG build, and the final relink must reproduce the pool order.
- **No PGO.** CD2 has no hot/cold function splitting: every cross-function mid-function branch goes to the register-restore helper, and only 1 of 42,610 functions is branch-only. The hot region at the start of `.text` is a link order list.
- **LTCG output depends on whole-program facts** that a per-file test must model (details in `tools/research/compiler_re/README.md`):
  1. **Escape analysis.** A global whose address no `/GL` code takes is treated as unaliased. Modelling `g_GUIDNull` as non-`const` with an escaping address made the `cNPCTintProfile` constructor exact under LTCG.
  2. **Constant pool.** `c2.dll` pools a float literal unless a `const` global with that value was already registered. In CD2, 1.0f and 0.0f are such globals (loaded directly ~2,400 and ~2,900 times), while rarer constants are pooled. Registering them made `cAmbientVFXPrototype::MakeNew` exact under LTCG.
  3. **Open:** a further sensitivity to the link's composition (scheduling around global addresses).
- **Practical consequence.** Plain compiles stay the main loop, since most functions come out identical either way.
  - `tools/verify_ltcg.py` builds each source under LTCG with an automatically generated model of the rest of the program: escapes, constant registrations and a pool seed. All 63 tracked functions are exact under it.
  - Three functions (`CalcRand*`) are exact **only** under LTCG and are marked `"ltcg": true` in the manifest.
  - The final full relink, where the whole program is present, should get these effects for free.

---

## 5. Reference builds

### RuffKing (Ryse prototype, 2010-11-11)
- IDB: 83,184 functions (82,240 named), 43,061 local types. PDB: 3,898 modules, linker 9.0 (`mspdb` 8153), 18.23 MB of code contributions.
- Same codebase: the source root is `z:\devbranches\kingdoms\source\code\projects\CarWars\CW\...` ("CarWars" is the Crackdown code project name).
- Game objects are 10.53 MB (57.7%), all compiled with 15.0.8153 and `/GL` (link-time code generation; see section 4). Libraries: libgfx (Scaleform) 1.31 MB, xgraphics 1.27, d3dx9i 0.87, Wwise (`aksoundengine`, 16.0.10224) 0.66, morpheme 0.36, d3d9i 0.30, xaudio2 0.28, Havok (14.0.x) and others.
- XEX static libs: the same 9328 XDK libs plus C1/C2 16.0.10224 records, which come from the prebuilt Wwise libraries.
- It is an internal **instrumented** build: it links `xapilibi`/`d3d9i` and its game code contains no-op trace markers, `mr r13,r13` (55,690 of them, after each prologue) and `mr r14,r14` (65,568, after each call). CD2 contains none. The compiler treats each marker as a barrier (it reloads `this` after it, for example), so markers perturb codegen beyond the marker instruction itself.
- Its game code has drifted substantially from CD2: bodies rewritten, code moved between functions (CD2's `cDefinedShader` constructor contains logic that RuffKing moved into `Reload`), APIs refactored (`Fun_Runtime::RetLocString` became a free function where CD2 goes through a manager instance), and field offsets changed (`cProp::FixupVFXData` uses `0xF4`/`0xDB4` in CD2 vs `0x134`/`0xE24` in RuffKing).
- Even so, it contains most of CD2's classes, including CD2-specific ones (`cAgencyCar`, `cAUMission`, `cAcidBomblet`, `CHARACTER::cNPCTintProfile`, `Equip::cCloakingDevice`).

### Burn (Crackdown 3 alpha, 2012-01-12)
- IDB: 201,488 functions, 55,475 types. PDB: 4,382 modules, linker 10.0.11886, 27.5 MB of code; game objects 12.34 MB.
- Game code compiled with **16.0.11886** (VS2010-based XDK compiler), XDK libs 2.0.20871, plus Kinect (NUI) libraries. A different compiler from CD2, so exact matches are rarer, but as a Crackdown descendant it is closer in content: with containment scoring it matches more CD2 game functions than RuffKing does.
- Also contains some objects compiled with 16.0.10224 and 15.0.8153 (prebuilt libraries).

### Skate (2007) and Spore (PC)
- Skate's exact matches against CD2 (656) are mostly XDK/D3DX shader-compiler code, plus obvious false positives on game code. Its value is RW4 engine types and fuzzy matching. It uses a 2007 compiler.
- Spore is x86 PC; it can only contribute names, types and structure, not code matching. Not used yet.

---

## 6. Recovering names

| Method | Result |
|---|---|
| Exact normalized-instruction hashes, unique 1:1 (functions ≥6 instructions) | RuffKing 12,399 (mnemonic-only) / 11,703 (with registers and offsets); Burn 7,652 (231 not also from RuffKing); Skate 656 |
| ... broken down by the RuffKing object they hit | essentially all library code: 12,369 library vs **1** game; after stripping the trace markers 12,461 library vs 94 game |
| String-anchored pairs (unique string sets) | 1,977 with RuffKing, 361 of them game code. Noisy: code that moved between functions causes wrong pairs. |
| Fuzzy matching (register-free opcode 4-grams, Jaccard, inverted index on rare shingles), RuffKing | 605 game-area functions at J≥0.5 with margin (precision ~94% on the noisy string truth) |
| Same, Burn | 374 game-area functions at J≥0.5 |
| Containment scoring (shared fraction of the smaller function) | ≥0.6: 5,524 of 33,173 game-area functions (16.7%); ≥0.5: 9,573 (28.9%). Burn contributes more than RuffKing. This is an upper-bound estimate of "has a recognisable relative". |
| Call-site propagation from confident matches (pair the i-th calls of matched functions with equal call counts) | RuffKing 12,949 seeds → 18,258 (game 777 → 1,243); Burn 9,519 → 13,774 (game 590 → 878, with 2,531 conflicts) |
| **All of the above combined, game code** | **1,467 of 39,024 game-area functions (3.8% of functions, 7.2% of game bytes)** |
| Vtable matching by slot-candidate voting | 577 of 4,761 CD2 vtables matched (RuffKing has 5,093 vtables / 79,573 slots); 3,031 functions named, only 53 of them game code |
| Class-name-anchored vtables (CD2 `RetClassName()` functions return the class-name string; 559 found) | 390 CD2 vtables anchored, 173 with the same slot count as RuffKing; 2,733 functions named. Unreliable at method level: against independent similarity matches, 10 agree and 61 disagree, because base classes gained or lost virtuals so slots shifted. The **class** is right; the **method** needs matching within the class. |
| Self-naming profiler strings (`Class::Method`) | only 5 functions |
| Class names in CD2 strings that exist as reference types | 293 of 345 Ruffian-style names (85%) |

Conclusions:
- Library code can be named almost completely by automation.
- Game code: about 4–10% can be named confidently today. A combined matcher that identifies the class first (class-name strings, vtables, class factories) and then matches methods within that class's small candidate set should do much better. In the pilot, name lookup inside the class found reference counterparts for two functions (`cNPCTintProfile::HandleAttributes`, `cCloakingDevice::StaticCreateClass`) that whole-binary similarity had missed. A realistic ceiling is perhaps 20–30% of game functions with a usable reference body.
- **Most game functions (~70%+) will be decompiled without a reference body**, but usually with the class and its layout known.

---

## 7. Types and headers

- `resym` (ergrelet/resym 0.4.0, CLI `resymc`) reads these Xbox 360 PDBs and emits full C++ class declarations: fields with offsets, access specifiers, statics, enums, and method signatures including virtuals. Example: `resymc dump -a -x ruffking_release.pdb "AI::cTrainingMission" out.h` takes about a second.
- Its output for `AI::cTrainingMission` agrees with what pilot #1 inferred from CD2 code (`cMission` occupies `0x000`–`0x3C0`, `RWS::CEventHandler` at `0x3C0`).
- Layout drift: of the 94 game functions that are identical to RuffKing's apart from the markers, 35 (37%) use different field offsets. Generated headers therefore need per-class verification against CD2's code. `resymc diff` can compare a type between RuffKing and Burn to see how layouts evolved.
- IDA local types (RuffKing 43k, Burn 55k) are also available, but IDA output is C-like and has no methods.

---

## 8. Source-file (translation unit) boundaries

- No layout signal: functions are 8-byte aligned and the padding between them (0 or 4 bytes) is the same within and between objects in RuffKing, where the boundaries are known.
- Usable signals:
  - The CRT static-initializer table. CD2: 21,834 entries at the start of `.data`; RuffKing: 19,364. One entry per global needing construction, in link (object) order. Header-defined constants (e.g. `fPhysicsSimulationTick`, `IDENTITY_TRANSFORM`) produce one initializer per including file, so the repeating groups mark file boundaries. The initializer functions themselves are grouped at the end of `.text`.
  - Data-reference clustering: an object's functions reference that object's own globals and string literals.
  - RuffKing/Burn object maps for matched code (complete for libraries).
  - jeff's own split inference.
- Accuracy is unmeasured but **can be validated on RuffKing**, whose PDB has the true boundaries.
- Boundaries do not block function-level matching. They matter for object splits and the final relink, and can be refined while decompiling.
- Shape-based alignment of RuffKing objects to CD2 (`tools/research/scripts/tu_align.py`, added 2026-10-23) found only 3–24% of the functions of `cString.obj`, `Fundamental.obj` and `cThread.obj`: RuffKing's game code drifted too much.
- Better anchors:
  - the class registrar's dynamic initializer, which names the class and points at `MakeNew`;
  - the class's vtable, found through its `RetClassName()`;
  - the function order list (above), which explains functions found far from the rest of their file.

---

## 9. Tooling

### jeff (XEX splitter / decomp toolkit)
- Original: `rjkiv/jeff`, v0.5.2 (2026-09-30), Rust, builds in about 30 s with the installed Rust toolchain. Template project: `rjkiv/jeff-template` (configure.py + ninja + objdiff; also used by the Dance Central 3 decomp). `ChimpsAtSea/jeff` is a fork, last updated 2026-01-15. The user previously had trouble with jeff and its forks; each fork fails differently.
- On CD2, the original jeff needed **two small patches** (in `tools/research/jeff_patches/rjkiv-jeff-v0.5.2.patch`):
  1. `executor.rs`: stop when execution walks past the end of a section. Otherwise a fixed-size bitset panics at index 3,793,947, one past `.text`.
  2. `slices.rs`: when a block cannot be finalised (data at the tail of `.text` from `0x83048D98`), treat the candidate as "not a function" instead of aborting.
- The fork needed an extra patch: trust the `.pdata` size when control-flow analysis ends a function early, which happens at the stub at `0x83048D7C`.
- With the patches, a full analysis and split of CD2 takes about **20 s**. It finds 74,586 functions, recovers 42,471 functions from SEH data, and writes objects, assembly and `config.json`.
- Minimal `config.yml`: `object: orig/default.xex`, plus optional `symbols:` and `splits:` paths. Formats are documented in `jeff-template/docs` (splits: `path/to/file.cpp:` then `\t.text start:0x... end:0x...`; symbols: `mangled_name = .text:0xADDR; // type:function size:0x.. scope:global`).
- jeff writes the extracted exe next to the XEX, so run it on a copy.
- Known limitations: relinking into an exe is officially unsupported; LZX-compressed XEXes are unsupported (CD2 is not LZX); `.pdb` input is unsupported; jump-table detection is heuristic. The relink-related bugs (including the 139 bad REL14 relocations) are fixed by the repository's patches; see the relink section below.

### objdiff
- `encounter/objdiff` supports PowerPC COFF (Xenon / Xbox 360) since mid-2025. objdiff-cli v3.8.3 was used.
- **End-to-end test:** a one-unit split (`AI/cTrainingMission.cpp` covering `StartMission` at `0x82480DA0`–`0x82480DF8`), a `symbols.txt` line naming it `?StartMission@cTrainingMission@AI@@AAAXXZ`, our object compiled with the CD2 flags, and a two-line `objdiff.json` (`target_path` = jeff's object, `base_path` = ours). `objdiff-cli report generate` reported **100% code, 100% data, 1/1 functions**, including the unit's `.pdata` entry.

### Full-binary relink experiment
jeff's objects were linked with the XDK linker: `link /BASE:0x82000000 /FIXED /NODEFAULTLIB /ENTRY:mainCRTStartup /FORCE:MULTIPLE /FORCE:UNRESOLVED /XEX:NO`.
- jeff's whole-binary `.pdata` object is rejected (`LNK1223: invalid .pdata contributions`). Replacing it with an equally sized zero-filled `.rdata$zz` padding object put **every section at its original address**.
- `.text`: 9.35% of words differ, and almost all of it has two causes:
  - **6.35%: a jeff relocation-encoding bug.** For 240,935 of 240,980 mismatched branches, the relinked target equals the true target plus the branch's own section offset. jeff's REL24 encoding is not what the Microsoft linker expects. It's a one-line fix in jeff's COFF writer, or a post-pass.
  - **2.58%: a +0x20 shift of `.rdata`.** The linker always emits its own debug directory at the start of `.rdata`, and jeff's objects already contain the original one (at `0x8201D060`). `/PDB:NONE`, `/DEBUG:NONE` and `/RELEASE` do not suppress it.
  - **About 0.42% remains:** references into a few small `.rdata` pieces that were placed in a different order, the arch data block at `0x83047CBC` that jeff treats as code, and the 139 bad REL14 relocations.
- `.data` 96.2% identical (almost all of the difference is the same +0x20 shift); `PSFD00` 98.2%; `.tls`, `.XBMOVIE`, `.edata` and `.idata` 100%.
- Import thunks differ in encoding (jeff writes PE-style `0x800003D1` where the XEX image has `0x000003D1`).
- A real relink also needs per-function `.pdata` (jeff already writes valid per-unit `.pdata` for split units) and a decision on the debug directory.

### Relink round trip: exact (2026-10-24)
`tools/relink.py` reports **0 of 6,897,408 words differ** between the relinked and original memory images, from `.rdata` to `.XBMOVIE`. What it took:

**jeff patches** (`tools/patches/jeff/`, detailed in `tools/external/README.md`):

| Patch | `.text` identical after |
|---|---|
| Baseline | 90.65% |
| REL24/REL14 field = addend minus the instruction's offset (0002, 0005) | 97.00% |
| Debug directory and `.rdata` layout handled in `relink.py` | 98.95% |
| REFHI's PAIR record carries the displacement (0004, 0005) | 99.93% |
| Global labels as externals (0006): 305 unresolved symbols, including `.pdata`, unwind data and the `__savegprlr_N` entry points | |
| Unique names for duplicate strings (0007): 341 `LNK4006` warnings, every reference bound to the first copy | |
| Addends (0005): pointers and calls into the middle of functions | |
| `lis`/`ori` pairs are constants, not relocations (0008) | 100% |

**What the image is.** Past `0x83A50000` the image holds the XEX resources (localized text, `DevXUID`, `CELLXLSP`, per the XEX resource table). The linker's `.edata`/`.idata`/`.XBLD`/`.reloc`, which the PE section table still lists, were consumed by the packager and are not in the image. The original link was not `/FIXED`: the section table keeps the size of its base relocation table (0x14AA88).

**Layout:**
- The linker writes its own debug directory first in `.rdata`. The data before CD2's directory is merged in with `/MERGE` (a merged section goes first).
- The CodeView record goes in `.rdata$debug`; the data after it is linked as `.rdata$x`, 8-byte aligned.
- The `.pdata` object is linked as plain data under another name.

**Not linker output, checked explicitly:**
- **Imports (816 words).** The packager replaced each IAT entry with an import record (`type << 24 | ordinal`), and each thunk's first two instructions with records. The relinked image must hold exactly what the linker writes there: a PE import by ordinal (`0x80000000 | ordinal`, little-endian), and `lis r11` / `lwz r11` loading the entry.
- **Link metadata.** The debug directory's time stamp and the CodeView GUID and age differ on every link. The CodeView path is the original's (`/PDBALTPATH`).

**Relocation completeness (reported, not gated).** Linked without `/FIXED`, the relinked base relocation table is 0x14A69C bytes, 0x3EC short of the original's 0x14AA88. That gap is the absolute references jeff did not recover. Data is essentially complete: only 100 pointer-like data words lack a relocation, and they are not pointers. In code, about 238 `lis` instructions load an address high half without a relocation. Most are in functions that keep the high half in a register far from its use (LTCG code), which jeff's tracker loses. Their bytes are copied, so the round trip is unaffected. They would matter only in a build where objects move.

### Other tools
- `dumpbin /disasm` (tech-preview copy, after the manifest fix) disassembles our PowerPC objects; the agent harness uses it for side-by-side diffs.
- decomp-permuter scores with GNU objdump on ELF and cannot read Microsoft big-endian PowerPC COFF. objdiff-cli or the research `coff.py` comparer can be its scorer instead (a small adaptation).
- decomp.me support for this compiler is unconfirmed and not needed; everything runs locally.
- IDA Pro via the `ida-pro-mcp` server was used for all IDB work.

---

## 10. Pilots

### Manual pilot (Opus, during the study)
Compiled with `/Ox /Gy /GF /GR-`:
- `AI::cTrainingMission::StartMission` (88 bytes): **exact on the first attempt**. The mangled name came out identical to RuffKing's symbol.
- `UI::HUD::RaceHUD::OnEnter` (80 bytes): **exact on the first attempt**, after noticing CD2 goes through a localisation-manager instance where RuffKing calls a free function.
- `AI::cBaseVisibility::InitParam` (148 bytes): best 51% after about a dozen source variants. Learned: the original keeps a local `KyBool bResult = KY_TRUE` live in r29 (forcing `__savegprlr_29`), and the tail is a "mask AND r29" select. Flags were ruled out as the cause.

### Agent pilot
Seven packets, each self-contained (target bytes, CD2 disassembly and pseudocode, plus RuffKing disassembly, pseudocode and `resym` class headers where available), worked by Haiku 5.5 and Sonnet 5.5 in separate copies, at most 12 harness runs per packet. The harness (`tools/research/agent_pilot/check.py`) compiles with the fixed CD2 flags, masks relocated fields, prints a side-by-side diff and logs every run. Brief: `tools/research/agent_pilot/BRIEF.md`.

| Packet | CD2 address | Kind | Haiku 5.5 | Sonnet 5.5 |
|---|---|---|---|---|
| P1 `CHARACTER::cActionManager::DeactivateMainIF` | `0x82302E10` | reference identical apart from markers | 50% | **exact** (2 runs) |
| P2 `Prop::cProp::FixupVFXData` | `0x8272C228` | drifted reference, stack locals | 9.6% | 11.5% |
| P3 `cNPCTintProfile` attribute parser | `0x821D0300` | drifted reference, byte shuffling | 87% | 90.7% |
| P4 `cCloakingDevice` static class getter | `0x822F33C8` | drifted reference, static guard | **exact** (7 runs) | 65% |
| P5 nearest-of-two-points | `0x82401C88` | cold, float maths | **exact** (1 run) | **exact** (4 runs) |
| P6 virtual call + state check | `0x821D0CE0` | cold, virtual slot 122, signed char | **exact** (3 runs) | **exact** (3 runs) |
| P7 `AI::cBaseVisibility::InitParam` | `0x8226E420` | the hard bool idiom | 8.1% | 54.1% |
| Totals | | | 3/7 exact, 41 runs, 190k tokens, 54 tool calls, 8.3 min | 3/7 exact, 44 runs, 132k tokens, 55 tool calls, 8.6 min |

- **Combined, 4 of 7 matched exactly.** Each model solved one the other could not, so several independent attempts per function pay off.
- Haiku under-reported its run count (32 claimed, 41 logged); use the harness logs, not agent self-reports.
- The failures are classic matching problems, not misunderstandings: stack-frame layout and register assignment (P2), instruction scheduling (P3), materialised-bool and constant-hoisting idioms (P4 null path, P7).
- Pilot functions were 31–54 instructions, the 30–59 size bucket. P2 (52 instructions with stack locals) already defeated both models.

### Large-function pilot (2026-10-23)
Four game functions of 171–286 instructions, Sonnet 5.5 only, at most 8 harness runs each. The harness printed a compact diff (only the differing regions). Material: `tools/research/agent_pilot_large/`.

| Packet | CD2 address | Size | Kind | Best (logged) | Runs | What blocked it |
|---|---|---|---|---|---|---|
| L1 `AI::cTrainingUI::ShowControlSet` | `0x82486AA8` | 171 | reference (J 0.74) | 12.8% | 7 | logic fully decoded, but the `switch` dispatch (an `mtctr`/`bdzf` chain with no range check) came out in a different shape, shifting every later address |
| L2 `CHARACTER::cCharacter::ProcessFireWeaponMsg` | `0x8254D130` | 229 | drifted reference (J 0.56) | 11.4% | 6 | the base-to-derived pointer conversion (`p ? p-28 : 0`) needs a specific branch idiom no source form produced |
| L3 (vector/matrix scale and list update) | `0x82465428` | 204 | cold | 41.2% | 9 | stack-slot reuse for VMX splats: frame `0x110` vs `0x100`, so registers and scheduling differ |
| L4 (script-binding registration table) | `0x826CC8F8` | 286 | cold | **89.5%** | 8 | logic and stack frame matched; only where one store is scheduled differs |
| Total | | | | **0/4 exact** | 30 | 206k tokens (~51k per function), 39 tool calls, 12.3 min |

- At this effort level, a cheap model does not finish large functions. It does decode their logic, and it can get close (L4).
- The blockers are compiler-shape problems, not understanding: switch/jump dispatch form, branch versus select idioms, stack-slot allocation, and instruction scheduling.
- Whole-function word-match percentages understate progress, because one early difference shifts every later word.
- Implication: functions of 150+ instructions (43% of game code) need much more effort per function. That means more iterations, a stronger model, a permuter for scheduling and register allocation, and human expertise for idiom puzzles.

### Whole-file pilot: `CHARACTER/cNPCTintProfile.cpp` (2026-10-23) — **first fully matching source file**
The per-file method (see "Working method" in section 12) on one small file, run by Sonnet 5.5. The work was:
- check the split;
- scaffold the header from the repo base headers and the reference dumps;
- implement the functions, skipping tough ones, then return to them;
- append notes as it goes.

Material: `tools/research/tu_pilot/`. Result in the repo: `src/CHARACTER/cNPCTintProfile.cpp` and `include/CHARACTER/cNPCTintProfile.h`. Verify with `tools/verify_src.py`.

- **All 7 functions of the file are byte-exact:** constructor, `HandleAttributes`, `MakeNew`, `RetClassName`, the compiler-generated scalar deleting destructor, and the registrar's dynamic initializer and at-exit destructor. It took 17 harness runs, 130k tokens (~19k per function), 39 tool calls and 6.3 minutes.
- **Split decision:** an 8th candidate given to the agent (`0x8255E0D8`) was correctly excluded. It is the next file's first function: it works on a byte at `+1` and vectors at `+0x10`/`+0x30`, matching no field of this class, and it is not in the class's vtable.
- **Context made the difference.** `HandleAttributes` is the same function that stalled at 87–91% when attempted in isolation (P3). With the whole file, real headers and the shared notes it matched. What unlocked it:
  - 5 accessors that CD2 inlines (now inline in `rws/attributes.h`);
  - CD2's plain `new`/`delete` (`cd2/memory.h`);
  - the implicit destructor;
  - the exact `switch` layout.
- Findings were added to `docs/matching-notes.md`. Header fixes went into the repo headers (`rws/attributes.h`, `rws/classfactory.h`, `editor/guid_event_handler.h`, `cd2/memory.h`).
- Caveat: one small file with no large functions. It shows the method works and that context lifts success sharply. It does not yet show the large-function rate under this method.

### Whole-file pilot 2: `GangManager/cFactionConfigData.cpp` (2026-10-23): large function matched
Same method, a harder file: 19 candidate functions to split, a class that grew in CD2 (`0x50` bytes vs RuffKing's `0x34`, with an unknown polymorphic second base), and a 194-instruction `HandleAttributes`. Material: `tools/research/tu_pilot2/`. In the repo: `src/GangManager/cFactionConfigData.cpp` and `include/GangManager/cFactionConfigData.h`.

- **Split:** 7 of 19 candidates belong. The rest are a pool class, global accessors, and another class's constructor and destructor. The agent identified the unknown second base from that other class.
- **Agent run** (Sonnet, 13 harness runs plus direct compiler experiments, 231k tokens, 63 tool calls, 15 min): 5 of 7 exact, verified by symbol. These include **`HandleAttributes` (776 bytes, 194 instructions) byte-exact**, along with the destructor, `RetClassName`, and the registrar initializer and at-exit destructor.
- **Finish (Opus):** the scalar deleting destructor became exact with the **`/Ob1` flag correction** (section 4). **6 of 7 are now exact.**
- **Open:** `MakeNew`, with the constructor inlined. Our code has identical stores, but the compiler schedules them so that one extra register (`r31`) is needed. A 32-variant permuter over the constructor chain didn't change it. Tracked as work in progress in `config/matched_functions.json`.
- **Harness flaw found:** pairing targets with compiled functions by similarity gives false "EXACT" results for same-shape functions (e.g. deleting destructors that differ only in their call target). Once functions are named, verification must match by symbol, as `tools/verify_src.py` does.
- **Takeaway:** large functions *are* reachable with the whole-file method. The remaining failures are compiler-shape puzzles (inlining decisions, scheduling), which are what a permuter and compiler reverse-engineering are for.

### Measurement batch 1 (2026-10-23): three files in parallel
Purpose: measure the whole-file method on varied code before estimating. Three Sonnet 5.5 agents ran in parallel, one file each, with the same brief (`tools/research/batch1/BRIEF_TEMPLATE.md`) and a cap of 30 harness runs. Every result was re-verified by symbol. Material: `tools/research/batch1/`. In the repo: `src/VFX/cAmbientVFXSpawner.cpp`, `src/VFX/cRopes.cpp`, `src/GameManagement/cGameModeArena.cpp` and their headers.

| File | Belonging functions | Exact | Exact bytes | Agent tokens | Time |
|---|---|---|---|---|---|
| `VFX/cAmbientVFXSpawner` (3 classes, 0x50-byte spawner) | 21 | 16 | 1420 / 2528 | 276k | 15 min |
| `VFX/cRopes` (5 bases, STL vector, object pool, D3D) | 25 | 20 | 2988 / 5348 | 274k | 27 min |
| `GameManagement/cGameModeArena` (two vtables, std::list/vector/string, messages) | 13 | 10 | 1328 / 2888 | 278k | 16 min |
| **Batch** | **59** | **46 (78%)** | **5736 / 10764 (53%)** | **828k** | |

- **Large functions:** `cPool<...>::Reset` (188 instructions) and a `std::vector` range `_Insert` (150) are exact. `cGameModeArena::HandleAttributes` (280 instructions, an 11-case switch) is at 95%, with 3 words differing. `cRopes::Render` (443 instructions, D3D and VMX128) was not attempted.
- **The misses are near-misses with one cause each:** a dead `addi` in a constructor, a stack frame 16 bytes too large, one `extrwi` against `rlwinm`, one stack slot not shared, an `srawi.` that folds into a mask, a float-constant base register, and an extra GUID copy. All are tracked as work in progress with their cause in `config/matched_functions.json`. These are what a permuter and the shared notes are for.
- **Split decisions were correct in all three files.** The agents told neighbouring classes, shared base-class functions and compiler-made thunks apart without help.
- **Shared headers grew:** `fun_runtime/class.h` (`cClass`, verified by two files), `fun_runtime/randgen.h` (unverified), and `Editor::cGUIDLinker<T>::LinkToObject`, named from RuffKing. `FindEntityInMap` turned out to be static in CD2, with no `this` at any call site. Each file also needed stand-ins for unknown bases (`RWS::CEventHandler`-like, std::string, a messaging API). Merging these between batches is real work for a header owner.
- **Packet bug found and fixed:** IDA cuts functions short after `bl atexit` (every registrar initializer) and after tail-call `b` + `blr`. Five targets were truncated; `tools/packets/build_cd2.py` now extends over exactly those words (`tools/research/batch1/trunc_scan.py` checks a packet).
- **Discipline:** one agent wrote its own local compile helper and used only 3 official harness runs. Its token use (274k) was in line with the others, so budget agents in tokens, not harness runs.

### Measurement batch 2 (2026-10-23): gameplay files
**Purpose:** test whether the method transfers to gameplay logic, the biggest uncertainty after batch 1.

**Setup:**
- Three registrar classes chosen because their RuffKing code is mostly logic: `AI::cChaseBehaviour` (AI state machine), `Equip::cFlocket` (projectile physics) and `VEHICLE_CONTROL::cHelicopterController` (flight control).
- Sonnet agents with a ~300k-token budget each, the LTCG-aware harness (`tools/check_tu.py --ltcg`), `tools/sweep.py` and the shared headers.
- Material: `tools/research/batch2/`. In the repo: `src/AI/`, `src/Equip/`, `src/VEHICLE_CONTROL/`.

| File | Belonging functions | Exact | Logic exact | Agent tokens |
|---|---|---|---|---|
| `AI/cChaseBehaviour` (second run; see below) | 35 | 26 | 9 of 16 (incl. `OnEnter`, `OnExit`, `SetTarget`, `TryBindTarget`; `Update` 99%) | 222k (+117k first run) |
| `Equip/cFlocket` | 35 | 28 (11 compiler-made thunks) | 4 of 10 | 247k |
| `VEHICLE_CONTROL/cHelicopterController` | 26 | 17 | 9 of 17 (all small) | 233k |

| By kind | Functions exact | Bytes exact |
|---|---|---|
| Boilerplate (factory, RTTI, constructors, destructors, attributes, registrars) | 30 / 32 | **82%** |
| Compiler-generated (thunks) | 19 / 21 | 74% |
| **Gameplay logic** | 22 / 43 | **15%** |
| All | 71 / 96 | 29% (batch 1: 53%) |

- **Boilerplate transfers; logic is the long pole.**
  - Small and medium logic functions match: state-machine entry and exit, target binding, timers, accessors, lookups, wrap-around helpers.
  - The large ones (148–653 instructions, VMX128 maths, intrusive-list walks) were **not attempted** within the budget.
  - The helicopter's VMX-heavy functions after F48 were not even classified, so the logic share above is, if anything, flattering.
- **The main cost is stand-ins for unknown code:**
  - base classes (`cFlocket` has 11 subobjects and a 375-slot primary vtable; `cChaseBehaviour`'s base has 121 slots);
  - callee APIs (Vec3/Mtx/VMX maths, network field readers, event and sound systems);
  - one agent named every unknown callee `Ext_<address>`.

  This cost falls as shared headers for the common bases (`NPCBehaviourSM`, `cVehicleController`, the projectile base chain, `Vec3`) are curated, so header curation is the critical path.
- **LTCG blocks float-heavy constructors per file.** CD2's link-time codegen shares base registers across constants within ±32 KB of a program-wide constant layout, which the per-file model cannot reproduce (`cFlocketPrototype` and `cHelicopterController` constructors, 14+ constants, all stores matching). These need a full-program build to confirm.
- **Tooling fixes found by the batch:**
  - The packet builder now centres the window on `RetClassName`: for gameplay classes the registrar's `MakeNew` builds a separate prototype and can live far away. That cost one wasted `cChaseBehaviour` run.
  - The LTCG model now takes the address of static and free functions, because LTCG otherwise drops unused parameters of functions whose callers are all known.
  - The harness warns about `map.txt` entries that match no mangled symbol.

### Whole-file method so far (5 files)
59 of 73 functions exact (81%), 7520 of 12748 bytes (59%), 1.19M agent tokens: **~16k tokens per function, ~93 tokens per byte of target code.** Functions of 150+ instructions: 3 of 5 exact, one at 95%, one not attempted. In isolation the same model had matched 0 of 4. Caveat: all five files are RWS attribute-handler classes found through their registrars. They are rich in boilerplate (attribute switches, registrars, deleting destructors, STL instantiations), so gameplay-heavy files (AI, physics, rendering) will likely do worse.

### MSVC PowerPC idioms learned
- `x ? true : false` and `x != 0` compile identically. To get a materialised bool held in a register (`addic`/`subfe` or `subfic`/`subfe`/`and`), keep the bool in a local that stays live across calls (`bool ret = true; ... if (!Base()) ret = false; return ret;`).
- A constant used after calls can be hoisted into a non-volatile register (`li r29,1`), which changes the save helper (`__savegprlr_29` vs `_30`) and therefore every following instruction offset.
- Branch layout follows source order: `if (a < b) return a; return b;` and the order of if/else arms matter (P5, P6). A `switch` produces a different layout from an if-chain (P3).
- Byte swizzles only produce the target's `rlwimi`/`inslwi` forms for particular expression shapes (P3: `(x>>24)|((x>>8)&0xFF00)|((x<<8)&0xFF0000)|(x<<24)`). `HIBYTE(x)` should be written `(unsigned char)(x >> 24)`.
- Calling virtual slot N needs N preceding declared virtuals (agents generated 122 dummy virtuals for P6).
- Returning through a single local result variable merges stores (P4).
- Static-local guards appear as `flag & 1` tests on a global plus `flag |= 1`.

---

## 11. Cost, usage and scale estimates

### Revised after measurement batch 2 (2026-10-23): gameplay logic
Batch 2 replaces batch 1's optimism about logic. Boilerplate matches at ~80% of bytes, but gameplay logic only at ~15% on a first pass. Logic is most of the game code: ~78% of the bytes in batch 2's files, so plausibly 70–80% overall.
- **First pass with the current method** (Sonnet, ~300k tokens per file, today's shared headers):
  - roughly 0.8 × 25% (boilerplate) + 0.15 × 75% (logic) ≈ **25–35% of game code**;
  - about 230k tokens per file; batch 2's files averaged ~5 kB of belonging code;
  - about **0.3–0.5B tokens, ~$1–2k** at API prices.
- **What raises the logic yield**, in order of expected payoff:
  1. **Curated shared headers** for the common base classes and math types. Stand-ins are the main per-file cost, and every file built on a known base gets cheaper.
  2. **A second pass on large functions** with bigger budgets and stronger models (Opus). These were not attempted at all in batch 2.
  3. **A permuter** for register and operand-order near-misses.
  4. **A full-program LTCG build** for float-constant-heavy functions.
- **Revised bottom line:**
  - ~25–35% of game code from a first pass in ~1–3 months for ~$1–2k;
  - **~45–55% after header curation and a second pass, in ~6–12 months, for very roughly $5–15k**, where the large-function pass dominates and is the least certain;
  - **100% is still 2+ years.**
- **Compared with the batch-1 projection** (45–60% in 3–6 months for $3–8k): the first pass is cheaper but yields less, and the middle range moves later and costs more. Header curation becomes ongoing project work rather than setup.

### Revised after measurement batch 1 (2026-10-23)
Superseded by the batch-2 revision above; kept for reference. These numbers replaced the per-function model below.
- **Basis:** the whole-file method's measured ~93 agent tokens per byte of target code (section 10). Game code is ~5.9 MB.
- **First pass, one agent per file:** ~0.55B tokens at the measured rate, so plan for **0.4–1B tokens**. Expected yield: ~50–60% of code bytes on files like those measured. Plan on **~35–50% of game code** to allow for harder gameplay files.
- **API cost** at the earlier ~$2.6 per 1M blended Sonnet tokens: **~$1–3k for the first pass**. A second pass on near-misses with a permuter, the notes and stronger models: ~$1–4k more. Header curation and orchestration: ~$1k.
- **Revised bottom line: ~45–60% of game code in roughly 3–6 months for ~$3–8k of API spend**, up from 35–45% for $3–11k. Large functions are no longer assumed to fail: 3 of 5 matched in context.
- **Subscription:** one 3-file batch used ~0.83M agent tokens, about 60% of a 5-hour window if all tokens count equally. That means ~4–5 files of this size per window. The bulk (0.4–1B tokens) is 40–95 weeks of weekly quota, so the conclusion stands: **use the API for the bulk** and the subscription for infrastructure, headers and the hard tail.
- **New limiting factors** (not tokens):
  - **Split discovery beyond registrar classes.** The 465 RWS registrars anchor 465 files; other files need other anchors (vtables, strings, order-list gaps).
  - **Header curation between batches.** Stand-ins for the same unknown types appear in several files and must be merged.
  - **The near-miss tail.** These are compiler-shape puzzles; permuter time and compiler reverse-engineering are worth more than more agent runs.
- **100% is still likely 2+ years.** Functions like `cRopes::Render` (D3D internals, VMX128) and the scheduling puzzles dominate it.

### Earlier per-function model (before the whole-file method)

All figures here are estimates with roughly ±2–3× error. Measured: token use and success rates for 30–59-instruction functions (the pilot). Guessed: everything for functions of 60+ instructions, which hold 66% of the game code. The large-function pilot (open question 1) is the main way to tighten them.

### Measured inputs
- Pilot consumption: about 27k agent tokens per function for Haiku and 19k for Sonnet (30–55-instruction functions, including retries).
- Rough API-price equivalents: ~$0.005 per function on Haiku 5.5 and ~$0.05 on Sonnet 5.5 (from the reported token totals).
- Subscription meter (the user's numbers for the research session): 631k tokens in the main Opus session, plus 131k (Sonnet agent) and 189k (Haiku agent), ~951k in total. That was about 70% of a 5-hour window and 9% of the weekly limit, i.e. roughly **1.36M tokens per 5-hour window** and **~10.5M tokens per week**, assuming every model's tokens count equally (unconfirmed).

### First agent pass over all game functions

| Size (instructions) | Functions | % of code | Tokens per function | Expected exact on first pass |
|---|---|---|---|---|
| 0–9 | 16,444 | 6% | ~6k (batched per class) | ~85% |
| 10–29 | 12,600 | 15% | ~12k | ~65% |
| 30–59 | 4,619 | 13.5% | ~25k (measured) | ~50% (measured) |
| 60–149 | 3,665 | 23% | ~50k | ~20–30% (guess; P2 at 52 instructions failed) |
| 150–399 | 1,319 | 20% | ~50k (measured, 8-run cap) | **~0%** at 8 Sonnet runs (measured 0/4) |
| 400+ | 377 | 23% | 100k+ | ~0% for cheap agents |
| **Total** | **39,024** | | **~0.6–0.8B tokens** | **~25k functions (65%), but only ~27% of the code** |

### Cost at API prices
- First pass: **~$0.5–1.5k** (Haiku for functions under 30 instructions, Sonnet for the rest).
- Second pass on failures (several attempts per function, Opus on large functions, ~1.5–3B tokens): **~$2–8k**.
- Orchestration and curation (headers, splits, review): **~$0.5–1.5k**.
- **Total: ~$3–11k to reach roughly 35–45% of game code (about 70% of functions) matched**: nearly all small and medium functions plus a few large ones. The large-function pilot lowered this from the earlier 50–70%.
- Large functions (150+ instructions, 43% of the code) on top of that: Opus plus permuter plus human work, perhaps 0.5–2M tokens each with uncertain success. Very roughly **another ~$5–20k+**, and it is human-time-bound.
- Generating candidates through the Message Batches API is 50% cheaper, at the cost of hours of latency per round.

### On the subscription
- First pass, ~0.8B tokens: **~75 weeks** of full weekly quota, or perhaps 15–40 weeks if Haiku/Sonnet tokens use less quota than Opus.
- Second pass: years.
- Infrastructure phase (~5–15M tokens of sessions like the research one): 2–4 weeks; fits fine.
- **Conclusion: the subscription can't carry the bulk agent passes.** Use it for infrastructure, orchestration and hard-tail work, and the API for the bulk.

### Token reductions to make before spending (perhaps 2–4× together)
- Batch many tiny functions into one agent session. 42% of game functions are under 10 instructions, and each currently pays the whole-brief overhead.
- Show agents only the differing region of the diff, and keep packets compact.
- Match trivial functions (getters, thunks, stubs) by script, with no agent.
- Use the Message Batches API for non-interactive candidate-generation rounds.

### Calendar time

| Phase | Work | Time |
|---|---|---|
| 0. Infrastructure | repo and jeff config, IDB repair, symbol pipeline, generated headers, file splits, agent queue and runner | 2–4 weeks of sessions |
| 1. Libraries | naming and splits (mostly automatic) | days |
| 2. Bulk first pass | ~800 agent-hours; with 8–10 parallel agents the limit is quota or rate, not compute | 1–4 weeks (API) |
| 3. Second pass on failures | retries, stronger models, permuter | 1–3 months |
| 4. Hard tail | large functions and idioms agents can't crack | open-ended: months to years, needs human expert time |

**Bottom line (revised after the large-function pilot):**
- **~35–45% of game code (~70% of functions) matched in roughly 3–6 months for ~$3–11k** of API spend.
- The large functions are 43% of the code. Cheap agents decode them but don't finish them (0/4 exact, best 89.5%). They need stronger models, a permuter and human expertise: very roughly **6–18+ more months and ~$5–20k+**, with uncertain success.
- **100% is likely 2+ years**, dominated by that hard tail.

### Other context
- Precedent: the Dance Central 3 Xbox 360 decomp (rjkiv/dc3-decomp, jeff + objdiff) reports about 27% decompiled; that figure comes from a third-party mirror of decomp.dev and is approximate. An earlier attempt by the same author (rjkiv/DComp3) was archived, noting that Xbox 360 tooling did not exist at the time. CD2's game code (~5.9 MB) is larger than most completed matching decomps.

---

## 12. What a project would look like (if started)

1. **Repository skeleton** based on jeff-template: configure.py + ninja + objdiff, the patched jeff, the XDK path configured locally (never committed), and the TU XEX supplied by the user (never committed).
2. **IDB repair:** create the ~21.9k missing functions (from jeff/`.pdata`).
3. **Symbol pipeline:** exact hashes for libraries, then class-first matching for game code (class-name strings, vtables, class factories, then method matching inside the class with similarity, call-site propagation and string usage), validated on RuffKing/Burn. Output `symbols.txt` and a confidence-tracked symbol database.
4. **Types:** generate headers per class with `resym`, verify offsets against CD2 code, and keep one curated header per class.
5. **Splits:** recover object boundaries from the initializer table and data-reference clustering, validated on RuffKing; start with the libraries known from the reference object maps.
6. **Agent work units** of one class or source file each, with a header owner. Cheap models first, several attempts per function, stronger models and a permuter for the tail. Progress is measured by objdiff.
7. **Full relink:** the round trip from jeff's objects is exact (`tools/relink.py`). What remains:
   - substitute compiled objects for jeff's as files match;
   - per-function `.pdata`;
   - regenerate a XEX with `imagexex`.

### Working method (advice from an experienced decomper, adopted 2026-10-23)
1. **Scaffold every source file before implementing it:**
   - make sure its split is generally correct;
   - read all of its assembly and generate sensible headers;
   - then implement its functions, skipping the tough ones.
   Once the file has all its functions, go after the tough non-matches by debugging the compiler and reading the compiler's own decompilation, which lets the agent trace why the compiler emits a given shape. This answers the failures seen in the pilots, which used isolated functions with throwaway types and failed on compiler-shape issues.
2. **Agents keep shared notes** on common, non-obvious behavioural patterns. Section 10's idiom list is the seed.
3. **Agents reverse-engineer the compiler** (the XDK `c2.dll` backend and the `c1xx.dll` front end in IDA) and name its functions, especially the ones that make codegen decisions: switch lowering, register allocation, scheduling, stack-slot assignment.
4. **Work bottom-up.** Scaffold SDK and library headers first (the XDK headers are real; middleware headers come from the reference PDBs via `resym`; no source is needed). Then start with the lowest-level game class that can be identified (e.g. `Fun_Runtime` math and containers, `RWS::CEventHandler`, attribute packets) and work upward.

Compiler switches verified to work with 15.00.8153:
- `/d1reportSingleClassLayout<Name>` prints the compiler's own layout of a class. Use it to check generated headers against the field offsets in CD2's code automatically.
- `/FAcs` writes an assembly listing with source annotations.

---

## 13. Reproducing the key experiments

| Experiment | How |
|---|---|
| Compiler fingerprint on Lua | Download lua-5.0.2, run `scripts/fingerprint.py "/Ox /DLUA_NUMBER=float"` (needs `cd2_lua_bytes.json` dumped from the IDB via `scripts/libfuncs.py`) |
| LTCG test | `ltcg_test/build.ps1 gl` and `build.ps1 plain`, then `ltcg_test/cmp_ltcg.py` |
| `/GS` and `/fp` probes | `probes/gs.cpp`, `probes/fp.cpp`, `probes/fpcmp.py` |
| Function dumps from IDBs | `scripts/dump_funcs.py` (set `MARKER_REGS=(13,14)` for RuffKing) |
| PDB modules, compilers and contributions | `scripts/pdbinfo.py <pdb> <out.json>`, then `scripts/pdbsum.py` |
| Fuzzy matching / propagation / vtables | `scripts/fuzzy.py`, `fuzzy2.py`, `contain.py`, `propagate.py`, `vtmatch.py`, `nameanchor.py` |
| Relink analysis | `scripts/mkpad.py`, `secdiff.py`, `textdiff2.py`, `brdiff.py`, `rdatadiff.py` |
| Agent pilot | `agent_pilot/BRIEF.md` and `check.py` (packets must be regenerated from the IDBs; they contain game bytes and are not stored in the repo) |

Most scripts take the research work directory (where the JSON dumps were written) as their first argument; the original machine's folders appear as placeholders. The pilots' attempt sources are not published: their exact results are in `examples/matching/` and `src/`. See `tools/research/README.md`.

---

## 14. Decisions taken so far

- Goal: a **matching** decompilation.
- Target: the title-update XEX (SHA1 `EC7B1636...`), the build the IDB covers.
- Runner and billing for the agent swarm: not decided. The user is on a Claude subscription with 5-hour and weekly caps.
- Burn's IDB: opened as-is (IDA restored it from its unpacked files).
- The XDK stays extracted, not installed.

## 15. Things that turned out NOT to be problems

- XDK installation on Windows 11: not needed.
- The tech-preview compiler: identical output, irrelevant.
- Missing relocations (`.reloc` holds resources): jeff's heuristic relocations reproduce the image exactly in the relink round trip. The size of the original base relocation table still measures their completeness (0x3EC bytes short, section 9).
- objdiff support for the platform: present and working.

## 16. Open questions

1. **Agent performance on large functions**: partly answered (section 10).
   - In isolation, Sonnet with 8 runs matched 0 of 4 functions of 171–286 instructions (best 89.5%).
   - The whole-file pilot then matched every function of a small file, including one that had failed in isolation, so context matters a lot.
   - Measurement batch 1 answered most of the rest: under the whole-file method, 3 of 5 functions of 150+ instructions are exact and one is at 95%.
   - Still unknown: Opus on the tail, a permuter, and gameplay-heavy files that are not attribute-handler classes.
2. **Header consistency across agents.** Partly answered by batch 1. Parallel agents invented overlapping stand-ins (`cClass` twice, `cRandGen` twice, the GUID lookup in three namespaces); merging them into shared headers cost no matches (59/59 still exact). A real project needs a header-merge step between batches, and agents should be told which shared headers exist.
3. **Accuracy of automatic boundary recovery and class-first naming.** Methods identified; not yet built or validated on RuffKing.
4. **Subscription throughput.** Measure `/usage` per fixed batch to get functions per week.
5. **Runner and billing.** User decision.
6. Minor: the exact Scaleform GFx version; where (or whether) Lua scripts live in the game data; whether `luaG_runerror` really is a mis-mapping.

---

## Sources

- objdiff: <https://github.com/encounter/objdiff>; PowerPC COFF (Xenon) commit <https://github.com/encounter/objdiff/commit/60b227f45e7623e5fb645f5cd3ef456c1f04c71d>
- jeff: <https://github.com/rjkiv/jeff>, template <https://github.com/rjkiv/jeff-template>; fork <https://github.com/ChimpsAtSea/jeff>
- resym: <https://github.com/ergrelet/resym>
- split360 (alternative splitter): <https://github.com/banjo360/split360>
- Dance Central 3 decomp: <https://raw.githubusercontent.com/rjkiv/dc3-decomp/HEAD/README.md>; earlier archived attempt <https://github.com/rjkiv/DComp3>
- Xbox 360 XDK versions (no build table found): <https://docs.cloudbees.com/d/kb-360032828692>
- Lua 5.0.2: <https://www.lua.org/ftp/lua-5.0.2.tar.gz>; zlib 1.2.3: <https://zlib.net/fossils/zlib-1.2.3.tar.gz>
