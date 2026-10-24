# Matching examples

C++ sources that compile, with the original Xbox 360 XDK compiler and Crackdown 2's flags, to code **byte-identical** to functions in the retail Crackdown 2 title-update executable. They come from the feasibility pilots (see [`docs/feasibility.md`](../../docs/feasibility.md), section 10).

The types in each file are minimal stand-ins written for that single function (padding arrays place fields at the right offsets). They are not real headers.

| File | CD2 address | Size | Written by | Effort |
|---|---|---|---|---|
| `AI_cTrainingMission_StartMission.cpp` | `0x82480DA0` | 88 B | Opus 5.5 (manual) | first attempt |
| `UI_HUD_RaceHUD_OnEnter.cpp` | `0x821E6878` | 80 B | Opus 5.5 (manual) | first attempt |
| `CHARACTER_cActionManager_DeactivateMainIF.cpp` | `0x82302E10` | 152 B | Sonnet 5.5 (agent) | 2 harness runs |
| `Equip_cCloakingDevice_ClassGetter.cpp` | `0x822F33C8` | 156 B | Haiku 5.5 (agent) | 7 harness runs |
| `ClosestOfTwo.cpp` | `0x82401C88` | 128 B | Sonnet 5.5 (agent) | 4 harness runs |
| `ClosestOfTwo_alt.cpp` | `0x82401C88` | 128 B | Haiku 5.5 (agent) | 1 harness run |
| `Classify.cpp` | `0x821D0CE0` | 124 B | Sonnet 5.5 (agent) | 3 harness runs |
| `Classify_alt.cpp` | `0x821D0CE0` | 124 B | Haiku 5.5 (agent) | 3 harness runs |

The `_alt` files are independent second solutions of the same functions: different source can compile to the same bytes.

## Compiler and flags

XDK 2.0.9328 `cl.exe` 15.00.8153 (`XDK\bin\win32`):

    cl /c /Ox /Ob1 /Gy /GF /GR- /GS- /fp:fast /D_XBOX /DNDEBUG file.cpp

## Verifying

    py -I verify.py <path to extracted default.exe>

`verify.py` compiles every example and compares it with the original function, read at run time from your own extracted executable. No game bytes are stored in the repository.

- The executable must come from the **title-update** XEX, `default_patched.xex` (SHA1 `EC7B163617CD725F50B0CCA665AAF943F9BC6D8A`). Never use the unpatched base `default.xex`: it is a different build.
- Extract it with jeff: `jeff xex extract default_patched.xex` writes `default.exe` next to the XEX.
- The XDK location comes from `py -I tools/cd2.py config --xdk <XDK>` (or the `XDK_DIR` environment variable).
- Fields filled in by the linker (call targets, global and string addresses) are masked; everything else must be identical.

Last verified 2026-10-24: 8 of 8 exact.

