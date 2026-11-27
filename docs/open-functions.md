# Open functions: what was tried

One entry per open function whose attempt was removed from its source file: what is reproduced, what differs, what was
tried and ruled out. `cd2.py show <address>` prints every entry that names the address, so read it there; nobody needs
to read this file from the top. A function whose source stays in its file is tracked instead as a work-in-progress
entry in `config/matched_functions.json` (`"matching": false` with a `"note"`), which `show` prints too.

Add an entry when you remove an attempt that taught something, under the file that owns the address. Lead with the
function's name and address (`0x82773E90`, or a range `0x82489C08..0x82489C30`), then one short paragraph. Name the
callees and globals that block it by address too, so `show` on them finds the entry. Remove the entry when the function
matches. Reusable mechanisms (a source shape and the code it produces, shown with an A/B test) go in
`docs/matching-notes.md`, not here.

## src/Activity/LongDistanceProps/cLongDistancePropManager.cpp

- cLongDistancePropManager::HandleAttributes (0x823DA998): the command loop, CMD_MAXPROPS field store and vector reserve
  call agree, but rwSwap32 followed by narrowing lets the compiler eliminate CD2's full swap sequence (25/49 words).
  _byteswap_ulong instead folds the payload load into lwbrx (24/49); neither probe was retained.

## src/Activity/SpawnPoint/cSpawnPoint.cpp

- cSpawnPoint constructor (0x823D1F80): Burn's 0x50-byte base layout and CD2's GUID handler at +0x54 establish the
  0x70-byte class. Initializer-list and body initialization, a single captured UID increment and novtable probes did not
  recover CD2's initialization scheduling in either build. Probes removed.

## src/AI/cTRCamLookAtStop.cpp

- cTRCamLookAtStart constructor (0x82487458): recovered tTCamCutParams at +0x90 with a vector, typed cGameBase safe
  pointer and FOV. Default member construction followed by event type 1, vector Zero(), null safe-pointer assignment
  and FOV 60 reproduces the operations, but retains this in r31 across cBasePatrolRouteEvent's call; plain diff has
  68 instructions against CD2's 61, and the local LTCG check reaches 7.4%. CD2 uses the base constructor's returned
  pointer directly (0x824BFA80, unscaffolded). Probe removed; the reference-named typed layout remains.

## src/AI/cBreachHole.cpp

- cBreachHole::ChangeState (0x8246FB40): the natural ExitState(old)/assign/EnterState(new) body is plain EXACT. Local
  LTCG specializes it to 2/27 words and changes the existing StartDeActivateBreachHole from exact to 12/24 words; body
  and claim removed. Do not add fake calls to retain the original ABI.

## src/AI/cCharacterEntityIF.cpp

- Enum registration `RegisterValues` of cMovementTypeScriptRegistration (0x823EECB0), cFaceTargetScriptRegistration
  (0x823EEF80) and cAttackStateScriptRegistration (0x823EF120): keys, values and order are recovered (face target 0, 30,
  90, 181), and direct Lua pushlstring/pushnumber/settable sequences give the right calls (movement type: 58
  instructions against CD2's 60). CD2 anchors its float reads at 0x820F2444 and 0x820F7680, outside the current LTCG
  pool model, with a preserved constant-base register and frame that plain and LTCG builds miss; search did not resolve
  them. Probes removed; investigate the original constant-pool context before retrying.

## src/AI/Mission/AchievementMissions/cPebbleDashMission.cpp

- cCityGliderMission's deleting destructor (0x824898F8), HandleAttributes (0x824899B0) and five thunks
  (0x82489C08..0x82489C30) lie in cPebbleDashMission.cpp's split range but belong to cCityGliderMission's object: split
  fix for the next sync point.

## src/AI/Mission/AU/cBeaconMission.cpp

- tExplosionData constructor (0x82461278, owned by cBeaconMission.cpp): typed matrix/vector defaults and scalar
  assignments give 22/34 words in both builds; scalar initializer lists interleave the matrix stores and give 11/34.
  Explicit vector Set duplicates default stores. Official search found no improvement in 11 compiles; body and claim
  removed. Its typed declaration supports the exact explosion dispatch.

## src/AI/Mission/cCellStrongholdMission.cpp

- `cCellStrongholdMission::Update` (0x82475148): RuffKing's body (early return when complete, then a two-case switch)
  gives every instruction, but CD2 keeps m_fResetTimer and m_fCurrResetTime in f9/f10 across the call to
  RWS::Time::RetDeltaTimeSecs (0x827671D0): whole-program LTCG knows the callee leaves them alone; the single-file
  models reload them (30.6% plain and LTCG). Body removed; the declaration stays for TickUpdate.

## src/AI/Mission/cTacticalObjective.cpp

- cCellStrongholdMission's five thunks (0x82475600..0x82475620) lie in cTacticalObjective.cpp's split range.

## src/Anim/cAnimationProfile.cpp

- `cAnimationProfile::RetSpecificAnimationProfile` mutable overload (0x824E10D0): CD2 expands two profile checks before
  calling the const overload. Direct delegation, explicit const-parent fallback, inline and forceinline forms retain a
  shorter tail-branch sequence. Probe removed; the const recursive overload at 0x824E1090 is exact independently.
- Animation sequence-map construction (0x824E1288, cAnimationProfile.cpp): a natural out-of-line cMap constructor calls
  the SDK tree's _Init instead of expanding its 35 target instructions. Its body/claim were removed; the
  declaration-only wrapper preserves the independently exact specific-profile constructor and factory.

## src/Billboard/BillboardProfile.cpp

- `BillboardProfile` factory/destructor (0x829128E0/0x82912A10): three typed vectors, reserve(9) on the first two and
  XMemSet of the strength-level array give a plain-EXACT factory; LTCG gives 16/52 words. Destructor singleton clearing
  leaves four scheduled stores/moves different (35/39 words); probes removed.

## src/cCwTransCharacter.cpp

- `cCwTransCharacterPrototype::SetAnimationProfile` (0x82539950): reference source
  `RetAnimMgr()->RetrieveAnimProfile(name)` gives 5/19 words under the local LTCG model; CD2 omits the unused manager
  argument. The lookup itself (0x824E5510) is LTCG EXACT with its reference member signature. The caller probe was
  removed; it needs cross-file optimization evidence, not a static replacement signature.

## src/cExplosivesSkillProfile.cpp

- `cExplosivesSkillProfile::MakeNew` (0x827530D0): typed shared base/string/event layout gives 38/48 words with
  forced-inline construction; initializer-list versus body assignment is identical. CD2 stores the primary vptr through
  the base constructor's returned pointer before the secondary tables; the current compiler schedules that store through
  the saved object pointer. Ordinary inline leaves a constructor call. Probe removed.

## src/cGodRaysControl.cpp

- `cGodRaysAddRaysShader` deleting wrapper (0x82796B18): singleton-clearing inline/forceinline destruction is not
  emitted without its constructor; an out-of-line destructor emits a separate derived cleanup call instead of CD2's
  direct base call (5/26 words). Destructor probe removed.

## src/cGrappler.cpp

- cGrappler.cpp's unoptimized code (StaticCreateClass 0x82631B40, 0x826320A8, the 80-byte initializer 0x82FD3740 and the
  later registrars): StaticCreateClass spills every temporary to the stack and 0x826320A8 stores its arguments to their
  home slots, so this code was not built with the game's `/Ox`. The factory, placement factory, class getter, name
  getter and descriptor-pointer initializer are EXACT with `/Ox /Ob1`. A/B: `/Od /Ob0` reproduces the four later
  inheritance/factory/spawning/atexit registrar sequences but breaks the optimized header initializers and prototype
  Init, so whole-file `/Od` is unsupported and no override was kept. The 80-byte initializer also needs its missing
  class and base declarations.

## src/CHARACTER/cCharacterControllerComplex.cpp

- `cCharacterControllerComplex::ZeroEffectsVelocity` (0x8255E598, slot 48): passes the shared zero object's address
  (0x8383A850) straight to the virtual setter at slot 64, whereas our OldVec3 conversion constructs a temporary.

## src/CHARACTER/cCharacterControllerSimple.cpp

- Simple/complex AddEffectsVelocity (0x825646B0/0x8255E538): vector addition and virtual setter dispatch agree, but CD2
  retains an aggregate-copy stage (two 64-bit loads/stores) after the SIMD temporary store. Direct __vaddfp conversion,
  a natural inline operator+, constructor body versus initializer list and value versus reference vector parameters all
  omit that stage (7/24 words in strict checks, 18 versus 24 instructions). The partial bodies and unused wrapper probes
  were removed. Do not manufacture a self-copy to fill the instruction gap; recover the original wrapper. Replacing the
  scalar-view union with a single __vector4 and using an implicit copy constructor also fails: by-value operator
  arguments introduce aggregate copies before the addition; reference arguments still omit CD2's result-copy stage.
  These storage/copy probes were removed.

## src/CHARACTER/cCharacterGlobalDlcProfile.cpp

- `cCharacterGlobalDlcProfile` factory/deleting wrapper (0x82552490/0x82552590): reference field block matches CD2's
  initialized offsets and size 0xA8. Literal defaults and a reference-named SetDefaults helper leave
  constant-hoisting/store-order differences (best 26/59 LTCG words); inline versus out-of-class forced-inline
  singleton-clearing destruction both give 17/26 words. Probes removed; typed layout retained.

## src/CHARACTER/cGameDamageProfile.cpp

- `cGameDamageProfile::HandleAttributes` (0x825560A0): four float cases and creation-packet test agree, but shared GUID
  registration passes handler/GUID/object instead of CD2's GUID/object-reference insertion at 0x82886380 followed by
  m_GUID assignment (112/130 words). Requested the shared inline operation from its header owner; probe removed.

## src/cHunterGathererGameModePrototype.cpp

- Aggregate getters 0x8287E280..0x8287E2A0 (cHunterGathererGameModePrototype.cpp): unidentified. Burn's
  Fun_Runtime::RGBA produces byte copies rather than CD2's word copy, so that return-type probe was removed.

## src/Equip/Gadget/cPulseRifle.cpp

- `cPulseRiflePrototype` constructor (0x8260FEA8): whole-profile memset followed by typed defaults and one shared
  double-tan result gives 12/63 LTCG words; pool/register scheduling remains different. Probe removed; the CD2-evidenced
  profile layout stays.
- `cPulseRiflePrototype::HandleAttributes` (0x8260FFA8): typed profile, double tan and half-angle conversion give
  321/323 LTCG words. The comparison uses plain switch offsets 0x8C..0xC8 even though the LTCG pool anchor shifts the
  table to 0x90..0xCC; the unchanged comparison API with those actual offsets gives 323/323. Official check remains
  nonexact, so the body and claim were removed pending a maintainer tooling fix.

## src/Equip/Weapon/cHarpoonBolt.cpp

- cHarpoonBolt::CheckForReplicationActivation (0x82628228): ownership flag, authority, processed-fixup flag and
  character/body IDs are recovered. Direct early returns, equivalent nested conditions and a result variable do not
  reproduce CD2's branch layout (22 versus 24 instructions for the direct form); search finds no improvement, so the
  body remains removed.

## src/Equip/Weapon/cWeapon.cpp

- `Equip::cWeapon::ProcessReloading` (0x8221BF38): the typed timer decrement and idle transition have the right
  structure, but CD2 keeps this in r3 across its delta-time call (0x827671D0), where the current plain/LTCG model uses
  r31 and restores r3. The callee is unmatched and therefore correctly remains opaque to LTCG; reconstruct and match it
  before retrying. Probe removed.
- `Equip::cWeapon` constructor (0x82609AA8): typed own fields and the shared Mtx default identity constructor give 20/63
  words in plain and LTCG. CD2 retains a matrix-address calculation, reverses the live zero/one constant registers, and
  schedules its timer literal later. Constructor probe removed; its placement factory and both destructor forms are
  EXACT independently.

## src/GangManager/cAgressiveResponseTurretVehicleSetup.cpp

- `cAgressiveResponseTurretVehicleSetup::HandleAttributes` (0x82672BB0): reference SDK APIs are
  RWSGUIDList::Num/GetGUID; registration inlines AddEntityToMap (0x82886228), calling GUID-map Insert (0x82886380)
  before copying m_GUID. The reference map is
  cHashTable<RWSGUID,void*,10,21000,CRWGUIDHashFunctor,std::equal_to<RWSGUID>>; CD2 global 0x8392FAB0 uses the matching
  pool/list/count/mask offsets 0/0xCD160/0xD2160/0xD2164. Recover the canonical container/member implementation for
  local LTCG argument elision rather than inventing a static adapter. No handler body was added.

## src/GangManager/cFactionConfigData.cpp

- cFactionInfo::IsA (0x82676298, in cFactionConfigData.cpp's range): reads the cFactionInfo descriptor (ID 1038, size
  0x220) that cFactionInfo's constructor 0x826766E0 installs at +0x14, as RetClass 0x82676288 does; it is not
  cFactionConfigData's. The misattributed entry and source were removed.

## src/GangManager/cGangManager.cpp

- `cGangInfo` constructor (0x826779A8): named reference fields and four population-block memsets give 63/65 words in
  plain and LTCG; only the saved-this move shifts one instruction early. Scalar initializer-list/body forms, the
  reference-named ClearPopData helper, data-block alignment and standard search do not change it. Constructor probe
  removed; its descriptor factory and RetClass getter are promoted independently. The deleting wrapper is EXACT with an
  inline empty destructor, but is not emitted without the constructor.

## src/ORB/cSkillPickupProfile.cpp

- `ORB::cSkillPickupProfile` constructor (0x82756D70) and deleting wrapper (0x82756E88): checked full field
  layout/default constants; initializer-list versus body assignments and Vec3::Set leave LTCG pool/register differences.
  Inline singleton-clearing destruction reaches 17/26 words in both modes; forceinline does not change it, while an
  out-of-line body adds an absent call. Probes removed.

## src/PHYSICS/cBody.cpp

- `cBody::GetLocalAABB` (0x82683EE8): direct component construction gives 25/26 instructions with different load/store
  order and folded prototype offsets. A reference-named Vec3TohkVector4 helper using mutable SIMD components emits a
  different sequence. Both probes removed; recover the original reference-taking conversion before retrying.

## src/PHYSICS/cWaterProfile.cpp

- `cWaterProfile` factory, deleting wrapper and attribute handler (0x82697560/0x826976B0/0x82697740): construction sets
  the shared max height to 50.0f and the ground level to `CONST_FLOAT_0`. An inline constructor stays out of line;
  `__forceinline` expands the right body but adds five instructions keeping `this` across the external `cNonGameBase`
  constructor, where CD2 uses its returned r3 (the cross-module constructor return of the surface-profile factories):
  recover the base constructor before retrying. The deleting wrapper has the water-zone wrapper's problem. Typed 0x2C
  water settings and case order 0..4,6..8,5,9,10 give 216/219 plain handler words; LTCG hoists its shared float pool
  into an extra saved register, and the expanded cWave::Setup reads another object's g_GlobalConstants. Probes removed;
  the inline empty destructor and design-build override keep the existing IsA's virtual ABI (23/23 words in both modes).

## src/PHYSICS/cWaterZone.cpp

- Water-zone deleting wrapper (0x827082A0): out-of-line destruction adds an absent derived cleanup call; forceinline
  destruction is not emitted without a visible constructor. Probes removed.

## src/Prop/Constrained/cSpinningProp.cpp

- `cSpinningProp::Term` (0x8273EE70): inline reconstructed `cStateMachine::GoTo_State(0)` plus `cPivotBasedProp::Term()`
  gives 22/22 words in plain and LTCG, but exposing that helper body changes existing folded `GoToSpinningFreeState` and
  `GoToSpinningClockWiseState` from 17/17 to 2/17 LTCG words; probe removed, helper visibility remains unresolved.
- `cSpinningPropPrototype::HandleAttributes` (0x8273F628): typed attribute loop and runtime `Pi2 =
  g_GlobalConstants.CONST_FLOAT_PI * 2` give 72/72 code words in plain and LTCG, but both builds leave `Pi2` zero while
  CD2 initializes it to 2*pi. Literal 2*pi hoists into f31 and changes the body. Data checks correctly reject the
  runtime-initializer probe; removed, unpromoted.
- Shared prop-state BeginState (0x8273F8D8): SetMotion(eMT_DYNAMIC), followed by a typed owner conversion and
  physical-state flag test, gives all 33 instructions but branches for the second base conversion where CD2 masks it.
  Probe removed.

## src/Prop/cProp.cpp

- `cProp::UnAttachEffects` (0x8272C5A0): scans six typed 0x70-byte effect records at +0xB00. A short-circuit loop emits
  16 instructions against CD2's 22; a stored boolean with a separate find/release phase gives 9.1% plain, 0/22 LTCG
  words. Defining the scan also changes both water callbacks under local LTCG, even with `noinline`. All scan probes and
  that attribute were removed; the typed records remain.
- `tAttachedEffect::Release` (0x8272C5F8): natural StopEmitters/SetAsOrphan/Release, pointer clear, then handle
  OnReleased is 53/53 LTCG words. Global verification rejects its header-constant ownership: `g_GlobalConstants` is
  0x830B7F30 here but 0x832037C0 in this file's initializers. Body and manifest entry were removed; do not split or
  alias the constant to hide that conflict.

## src/RPG/cPvPSkillset.cpp

- cPvPSkillsetProfile::MakeNew (0x82763828): Burn's rank pointer at +0x18 and six skill pointers at +0x1C establish the
  0x34-byte layout. An inline constructor with the singleton assignment and XMemSet has the correct operations but
  differs in base-clear/vtable scheduling (29/37 words in both modes); initializer-list versus body initialization,
  defining the reference-named singleton in this object, and bounded source search did not improve it. The partial
  factory body was removed.

## src/Sim/cTimeOfDay.cpp

- cTODNotification constructor (0x82773E90): typed fields and event ID, the counter incremented separately and
  days-passed assigned in the body give 19/28 words in plain and LTCG; days-passed in the member list gives 17/28, a
  counter postincrement in the initializer 2/28. Early this/vptr scheduling differs; search finds no improvement, and
  removing the registered-class base changes no code. Table slot 2 is script metadata (0x82773B18), not a virtual
  destructor (the header is corrected). Probes removed.

## src/Vehicle/Agency/cAgencyTank.cpp

- `cAgencyTank` constructor (0x826FCD08): cAgencyCar call, vptrs, out-of-line cFixedVehicleTurret constructor and
  `m_bMarkerAdded = false` give every instruction, but CD2 hoists the cPositionalProxy (+0x420) table store to fifth
  place where ours keeps it ninth (54.9%; initializer-list and body forms identical, search finds nothing). Its deleting
  destructor (0x826FCDD8) and IsA thunk (0x82700760) are EXACT once the constructor emits the table; probe removed.
- `cAgencyTank::SetupTurret` (0x82700238): typed turret/prototype fields and a Vec3::Set temporary give all 28
  instructions but 18/28 words (register numbering differs); standard search finds no improvement. Reference by-value
  SetCrosshairOffset introduces absent copy/frame work. Probe removed; checked layouts and exact Init/Reinitialise
  wrappers remain.

## src/Vehicle/cCar.cpp

- `cCar::LeavePhysicalState` (0x826B7538, slot 27, a tail call to cVehicle's): declared inline in cCar.h; it is only
  emitted where cCar's vtable is, which nothing in cCar.cpp does yet ("missing").

## src/Vehicle/cLandVehicle.cpp

- cLandVehicle's RemoveVehicleLights (0x826C2288) and CanActivateVehicleLights (0x826C2A90) inline functions CD2 also
  keeps out of line (cVehicle::RemoveVehicleLight with the light manager's TermOccludedLight losing its `this`;
  cVehicle::RetDriver 0x823CC0E8): cross-module LTCG inlining the single-file models cannot reproduce.
- `cLandVehicle::RetSteeringMaxAngle` (0x826C4900): the typed steering query and CONST_FLOAT_1 fallback are byte-exact,
  but the function reaches a different g_GlobalConstants copy from RetEngineDamage and IsA in the same source file.
  Probe removed pending recovery of the original constant ownership.

## src/Vehicle/cVehicle.cpp

- Shared carrier-event deleting destructor (0x826CC7C0): an inline empty `cVehiclePickedUpEvent` destructor is not
  emitted; an out-of-line empty destructor gives 5/36 words in both builds. Both probes were removed.
- `cVehicle::HandleTryToCloseAlterantiveDoorPermissionQuery` (0x826DEA30, slot 424): RuffKing's body (RetSwapSeat,
  inline RetVehicleSeat, seat RetStatus == eVSS_Unoccupied, CanSeatDoorBeClosed, IsUpRight) gives every instruction, but
  CD2 keeps the swap seat in r4 across the call to the leaf cVehicleSeat::RetStatus (0x826DFBE8): whole-program LTCG
  knows the callee leaves r4 alone; plain and LTCG models keep it in a saved register (30.6%). Removed.

## src/VEHICLE_CONTROL/cHelicopterController.cpp

- Helicopter-controller file deleting wrapper (0x82783448): the former cHelicopterControllerPrototype claim was
  incorrect. Its table is 0x8214C264, while the prototype constructor installs 0x8214C1A8 with deleting wrapper
  0x82684630. The actual destructor 0x82783498 unregisters events and destroys state through +0x37C; ownership remains
  open.

## src/VEHICLE_CONTROL/cSplineController.cpp

- `std::vector<float, cAllocator<float> >::resize` (0x8277F5B8, cSplineController.cpp): one-argument SDK instantiation
  retains a 12-byte forwarder to the two-argument form (152 bytes); CD2 instead has a 160-byte zero-default expansion.
  Public float copy/copy_backward/fill_n helpers match independently; resize probe removed pending the original inlining
  context.

## src/VFX/cDeityRay.cpp

- Shader deleting destructors (representative 0x82791E38): an out-of-line singleton-clearing destructor gives 19.2%; an
  inline destructor is not emitted without a construction/vtable use. Do not add an artificial use to emit it. Shader
  constructors also encode an object-derived integer ID; recovering that interface is separate work under R4. Destructor
  probe reverted; the 38 callback/getter pairs are promoted independently.

## src/VFX/cLinkedVFXSpawner.cpp

- cLinkedVFXSpawner::ForceStop (0x827FAC48): typed in-play flag, manager unregister and virtual ReleaseVFX call give
  22/24 words in both modes; the this move and virtual-function load swap order. Bounded search did not improve it; the
  partial body was removed.

## src/VFX/cPlaceableLight.cpp

- cPlaceableLight::MakeNew (0x82801E18): needs the base constructor's returned r3 (as the surface-profile factories);
  probe removed.

## src/WorldManager/cStaticEnvironment.cpp

- `cStaticEnvironment::SetInstancePriority` (0x828094D8): a direct `old >= new ? old : new` maximum gives 15
  instructions against CD2's 30; CD2 instead subtracts, compares with zero, indexes a boolean-to-float table and uses
  `fsel`. The probe was removed.

## src/ZoneManager/cAmbienceZone.cpp

- `cAmbienceZone::OnPlayerEnter/OnPlayerLeave` (0x8280FB78/0x8280FC20): Burn's `Audio::ScopedProfile` (GameAudioUtil.h,
  counter 0x838015E0) brackets the game object's static PostEnterEvent/PostExitEvent (0x82838718/0x828389E8) after the
  arguments are evaluated. CD2 stores the decremented counter after the following `m_bPreviously*` byte store, which
  only a whole-program view of the never-address-taken counter allows; plain and LTCG models keep the store first (39/41
  words). Probes and headers removed.

## src/ZoneManager/cPlayerTriggerZone.cpp

- `cPlayerTriggerBase` constructor (0x8280DB80): reference box/vector layout and `reserve(1)` reproduce the stores and
  call, but inline box scale-from-ZeroVec plus shared Mtx initialization gives only 7/79 LTCG words (77 versus 79 plain
  instructions); GUID-store scheduling and box/matrix address calculations still differ. Constructor probe removed.

## Outside the scaffolded files

- Patrol-event factories (`cFreakExplodeEvent`, `cFreakSniperEvent`, `cReaperJumpEvent`, `cReaperPropAttackEvent`):
  corrected shared RWS bases and the 0x90-byte layout; still 5 extra instructions because CD2 uses the return of
  cBasePatrolRouteEvent's constructor directly, while the standard build retains this in r31. The base constructor at
  0x824BFA80 is not in a scaffolded split, so it cannot be promoted as a matched LTCG dependency.
- `cGameBase::RetClass` (0x824CDC40) and `cScriptHost::RetClass` (0x823E5800): byte-exact probes, but they lie outside
  both the order-list region and their classes' cold ranges; excluded until the source ownership of these surviving
  COMDAT copies is established. Do not disguise cold code as a hot split entry.
- `cLoadStream::Read` (0x82767390): the typed reader with separate chunk/buffer checks gives 39/39 words in plain and
  LTCG, but adding it as a matched dependency changes `cVOAZone::Load` from 32/32 to 2/32 LTCG words; `noinline` on Read
  does not restore the caller. Probe and reader claim removed; the whole-program caller context remains unresolved.
