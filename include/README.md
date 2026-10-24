# Headers

| Path | What | Compiled? |
|---|---|---|
| `cd2/layout.h` | compile-time size and offset checks (`CD2_LAYOUT_CHECKS`, `CD2_SIZE`, `CD2_OFFSET`) | yes |
| `rws/attributes.h` | RenderWare Studio attribute framework: `CAttributeHandler`, `CAttributePacket`, `CAttributeCommand`, iterators, `RWSGUID` | yes, verified |
| `rw/rwmem.h` | RenderWare stream byte-order helpers (`RwMemNative32`), inline as in CD2 | yes, verified via `cFactionConfigData` |
| `editor/guid_event_handler.h` | `Editor::cGUIDLinkerBase`, `cGUIDLinker<T>::LinkToObject` (GUID lookups), `cGUIDEventHandler<T>` | yes, verified via `cNPCTintProfile`, `cFactionConfigData`, `cGameModeArena` |
| `fun_runtime/class.h` | `Fun_Runtime::cClass` (runtime class descriptor, inline `IsA`/`HasAncestor`) and `tGlobalConstants` | yes, verified via `cAmbientVFXSpawner::IsA` and `cRopes::IsA` |
| `fun_runtime/randgen.h` | `Fun_Runtime::cRandGen` (inline LCG) | compiles; **not yet verified** (no exact function uses it) |
| `fun_runtime/retval.h` | `Fun_Runtime::RetVal` and the per-file constants `Ret_OK` (0), `Ret_FAIL` (-1) | yes, verified via `cHelicopterController` (`Init`, `Term`) |
| `fun_runtime/safedeletable.h` | `Fun_Runtime::cSafeDeletable` (CD2's has 6 virtual slots) and its pointer-list head | yes (layout); slot names partly inferred |
| `fun_runtime/class.h` | also `Fun_Runtime::cRegisteredClass` (the RetClass/IsA interface, 8 bytes in CD2) | yes |
| `rws/eventhandler.h` | `RWS::CEventHandler` (6 virtual slots, as RuffKing and CD2) | yes (layout, slots) |
| `network/netrole.h` | `Network::cNetRoleObject` | yes (layout, slots) |
| `gom/object_prototype.h` | `GOM::cObjectPrototype` and `ResourceManager::cStreamingResourceClient`: the base of every prototype | yes, via the chase, flocket and helicopter prototypes |
| `gom/non_game_base.h` | `cNonGameBase`: the base of every game object (5 bases at 0, 0x18, 0x1C, 0x30, 0x38; 68 primary slots; 0x7C bytes) | yes, via `cRopes`, `cChaseBehaviour`, `cHelicopterController`, `cFlocket` |
| `<Namespace>/<Class>.h` | per-class headers (`CHARACTER/`, `GangManager/`, `VFX/`, `GameManagement/`); unknown bases are named stand-ins of the right size and slot count, described at the top of each header | yes, with the matching `src/` file |
| `ref/<build>/` | raw reference type dumps from two later builds of the same codebase, RuffKing (Ryse prototype) and Burn (Crackdown 3 alpha), made by maintainers with `tools/headers/ref_dump.ps1` (resym output). They are in the repository so that contributors need no PDB. | no, reference only |

XDK headers are real and come from the XDK itself (`XDK\include\xbox`), so they are not copied here.

## Conventions for curated headers
- Source: the reference dumps in `ref/` (RuffKing first, Burn second). Treat a dump as a starting point, never as truth for CD2. A type that is not dumped yet can be requested from a maintainer: dumping needs the reference PDBs, contributing never does.
- Keep the member order, the access specifiers and the order of virtual functions exactly as in the PDB. Access is encoded in mangled names, and virtual order *is* the vtable.
- Drop compiler-generated members (`__vecDelDtor`, `__local_vftable_ctor_closure`); the compiler regenerates them.
- End every class with `CD2_LAYOUT_CHECKS` covering its size and its key field offsets. A wrong layout then fails the build (C2118).
- Verify against **CD2** before trusting a layout:
  - field offsets as used in CD2's code (the disassembly);
  - the slot count and order of the class's CD2 vtable;
  - `cl /d1reportSingleClassLayout<Class>`, which prints the compiler's own layout.
- Beware of folded names: tiny functions in the reference builds were merged by the linker (identical COMDAT folding), so a vtable slot can carry another class's name. Example: slot 5 of `cNPCTintProfile`'s vtable is labelled `UI::cTexture::cTexture`.
- **Do not invent a stand-in for a base that already exists.** Game classes derive from `cNonGameBase` and prototypes from `GOM::cObjectPrototype`. Recognise them by the base constructor a class's constructor chain calls (0x82653588, 0x82654118) or by their vptr offsets (0x18, 0x1C, 0x30, 0x38 for game objects). Only the part of a hierarchy that is not yet known gets a stand-in, and the stand-in derives from the shared base. A base modelled twice under different names is invisible to the byte comparison, because vtable contents are not compared; `docs/matching-notes.md` ("Shared bases") describes how to identify one.
- Run `tools/headers/check_headers.ps1` after every header change. It compiles `tests/headers/layout_test.cpp` with the CD2 compiler and flags, and self-tests that the checks fire.

## Verified so far
- `rws/attributes.h`: layouts match the RuffKing PDB. In CD2, `CAttributeCommand` data sits at +8 (from `cNPCTintProfile::HandleAttributes`), and `CHARACTER::cNPCTintProfile`'s CD2 vtable has the same 13 slots, the first 11 being `CAttributeHandler`'s virtuals in this header's order.
