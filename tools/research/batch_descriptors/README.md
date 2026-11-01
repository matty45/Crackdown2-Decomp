# Batches: class descriptors, RetClass, IsA, placement factories, sweep (2026-11-01)

Second round of batch matching, after `../batch_retclassname/`. The manifest went from 1,039 to 1,420 matched
functions. Every function was checked `EXACT` by `cd2.py check` before it went into the manifest, and `verify` passed
after each batch.

| Script | What it does | Matched |
|---|---|---|
| `scc.py` | census of functions calling the cClass constructor (0x8264A890): StaticCreateClass, by shape | |
| `scc_gen.py` | StaticCreateClass with a constant ID (152/156 bytes), for classes declared once; ID, name and size read from CD2's arguments | 56 |
| `scc_counter.py` | the same with `g_nBehaviourClassID++` (164 bytes; `include/AI/BehaviourClassID.h`) | 28 |
| `gen4.py` | StaticCreateClass for classes declared nowhere: stand-in headers with only the static descriptor members (bases not modelled) | 58 |
| `rc_plan.py` | pairs each matched StaticCreateClass with the initializer that stores its result (the descriptor pointer) and the RetClass that reads it | |
| `rc_gen.py` | the descriptor pointer `ms_p<X>Class = &<X>::StaticCreateClass()` (its initializer) and RetClass | 47 + 19 |
| `rc_fix0.py` | replaces placeholder definitions `ms_p<X>Class = 0` with CD2's initialization | 38 (+5 from `rc_gen.py`) |
| `isa_gen.py` | IsA (`return ms_p<X>Class->IsA(c);`); most are exact only in a plain build until the file installs the class's vtable | 1 |
| `spawn_gen.py` | SpawnFromPrototype of the tail-call shape (out-of-line default constructor) | 3 |
| `sweep.py` | functions already written but never claimed: a compiled function equal to exactly one open function of the file (plus 25 written RetClass claimed from `rc_plan.py`'s list) | 43 + 25 |
| `chain.py` | (research) a class's base chain from CD2's constructors; works only partly | |

Pitfalls the batches hit:
- `check` on one file cannot see a name resolving to several addresses across files; only `verify` does. The sweep
  matched 14 compiler-generated destructors that called `~cNonGameBase` where CD2 calls an intermediate base's
  destructor (the stand-in hierarchies skip levels); they were removed.
- Placeholder globals that were really class descriptors showed up as relocation conflicts and were renamed
  (`g_pTargetClass` = `cCharacter::ms_pcCharacterClass`, `g_nVehicleTypeTag` = `cHelicopter::ms_pcHelicopterClass`).
- IsA needs `check --ltcg`: without code in the file that installs the class's vtable, the LTCG model drops its
  unused `this` (see docs/matching-notes.md).
- Set-up comments name the namespace `unknown` when it is not known; the repository already uses that namespace.
