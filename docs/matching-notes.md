# Matching notes: compiler behaviour and traps (Crackdown 2, XDK 15.00.8153)

Read this before starting a file. It is a catalogue of reusable mechanisms: a source shape and the code it produces, or
a trap and how to recognise it. Add an entry only for a mechanism you showed with an A/B test (one source change, one
codegen change) that will help with other functions. What you tried on one function does not go here: when its source
stays in the file, it is a work-in-progress entry in `config/matched_functions.json` (`"matching": false` with a
`"note"`); when you removed the attempt, it is an entry in `docs/open-functions.md`. `cd2.py show <address>` prints
both. History belongs in git, not here.

## Shared bases
- **The prop approach callback is inline in derived callbacks.** CD2 0x8274BB58 includes the
  explosive-pointer test and trigger notification from cProp's slot 226. An out-of-line base
  definition leaves a call and matches only 2/28 LTCG words; placing the small virtual in its
  header gives 28/28 words in both modes, while cProp's own 0x82730450 remains 8/8 words exact.
- **Weapon event metadata belongs to the constructed event, not the weapon.** Table 0x82123CE8 is installed
  after cAIEvent construction in the satchel observer test and returns the AIE_GRENADE_APPEARED descriptor.
  The low-ammo path installs 0x8211F2E8 after constructing a 0x44-byte cAIEvent with type 0x23; that table
  returns the AIE_LOW_AMMO descriptor. Their slot-1 getters at 0x8261A238/0x82607C20 are EXACT in both modes.
  The C++ names cGrenadeAppearedEvent and cLowAmmoEvent are descriptive and ours. Their descriptor initializers
  at 0x82F7CA80/0x82F77C40 are outside scaffolded ranges and remain external declarations.
- **Satchel charges have a separate perception interface.** cCWSatchelCharge's +0x9D0 base is modelled as
  cPerceptionClient (descriptive name ours): six slots, no virtual destructor, and a record pointer at +4.
  Its base table is 0x820FCF3C; satchel table 0x82123C68 changes only slot 5. That override (0x8261B180)
  checks line of sight and can post AIE_GRENADE_APPEARED. The reference satchel interface supplies the
  previously missing primary slots 432..437. cProxMine overrides NowStuck, Unstick and Reorient; retaining
  the satchel declarations there falsely maps one symbol to several addresses. Its destructor and forwarding
  Reorient override are EXACT in both modes. The approved true-return folds cover CanAttachToBody and
  the perception interface's descriptively named RetPerceptionFlag.
- **Position has two distinct virtual interfaces in CD2.** Primary slot 46 is the reference-named `cNonGameBase::RetPosition() const`, returning a `Vec3`. Its default body at 0x823CBEA8 forwards through the cScriptHost subobject at +0x1C, slot 3; that script slot now has the descriptive name `RetScriptPosition` to keep the interfaces separate. Physics and character interfaces override the primary slot. With this signature, `cPlayerTriggerBase::IsVehicleWithin` (0x821D1D20) naturally compiles the primary vehicle-position call followed by its slot-12 point test, exact in both modes.
- **CD2 characters retain the shared physics and replication hierarchy.** Constructors 0x82308218/0x82543408
  establish cCharacterMotion : cNetDynamicBody (0x11F0, 347 primary slots) and cCharacter : cCharacterMotion,
  cSatchelChargeTarget (+0x11F0; 452 primary slots). cIgnitable owns the fire flag at +0x261; cReplicatedClass's
  reference-named m_nObjectID is +0x38 in that base, +0x548 in a character (setter 0x82C2BEA0). Removing the flat
  character stand-in preserves the existing accessors and makes RetCharacterState's slot-371 wrapper exact.
  Burn's cPlayerCharacter supplies names for cCwTransCharacter: its cSkillSet is +0x2CC4, size 0x64 after CD2's
  four-byte debug base; the transform flag is inside it at +0x5C. The typed skill wrappers and power-up query are exact.
- **CD2 player-trigger tables omit reference-build debug virtuals.** cPlayerTriggerZone's table 0x82155B98 has
  18 entries, with OnPlayerEnter/OnPlayerLeave at 16/17. cGameModeTriggerZone adds slots 18..25; start-zone
  getters are 23..25 and its own table ends at CreateGameSession (slot 30). The shared trigger base remains 0xE0;
  cGameModeTriggerZone's wide arena name is at 0xE0 and its complete size is 0x120. cGameModeStartZone then places
  cReplicatedClass at 0x120 and its own fields at 0x350. Its constructor and exact getters support these offsets.
  cArenaLinker now takes shared Fun_Runtime::cString and calls its c_strc conversion to cStringc; all eleven
  existing arena matches remain EXACT in both modes after removing the old auxiliary string stand-in.
- **Replication alignment is a shared-base requirement.** cMissionBase's CD2 constructor (0x8245A748) places
  cReplicatedClass at +0x10 after a four-byte cRegisteredClass base, net role at +0x240 and attributes at +0x248.
  The reference replication class starts its first field at +0x10 and its bit stream at +0x20. A/B: with the old
  four-byte alignment, the mission's named net-role/attribute field checks fail; declaring cReplicatedClass with
  16-byte alignment makes both CD2_OFFSET checks pass. Its size remains 0x230. The earlier physics chain already
  ended at an aligned +0x510, which concealed this requirement; do not insert a padding base to obtain it.
- **Every game object is a cNonGameBase** (`include/gom/non_game_base.h`; constructor 0x82653588, 48 callers):
  - CAttributeHandler at 0;
  - RWS::CEventHandler at 0x18 (6 slots);
  - Fun_Runtime::cScriptHost at 0x1C: cSafeDeletable at +0, cRegisteredClass (RetClass, IsA) at +0x14, so at 0x1C and
    0x30 in cNonGameBase;
  - Network::cNetRoleObject at 0x38 (6 slots);
  - 0x7C bytes in all, with 68 primary slots (11 is RetClassName in every class seen).

  Projectiles and equipment reach it through cGameBase (constructor 0x82650610).
- **Every prototype is a GOM::cObjectPrototype** (`include/gom/object_prototype.h`; constructor 0x82654118, which takes
  the packet only): ResourceManager::cStreamingResourceClient at 0x18, 0x70 bytes. Its client vtable 0x821327A4 is
  shared by every derived prototype (ICF).
- **Primary slot counts of the body chain** (from the table each CD2 constructor stores at offset 0): cNonGameBase 68,
  cGameBase 141 (0x8212CA20), cBody 227 (0x8200C938), cDynamicBody 304 (0x8200D058), cNetDynamicBody 314 (0x82131E80),
  cVehicle 442 (0x82015B40). The headers declare every slot, unnamed ones as `vfN` (N = the slot index), so a class
  derived from them gets its own virtuals at CD2's slots. A class's own count is a hard check on its declarations:
  `/d1reportSingleClassLayout<Class>` lists the table. The reference builds' counts differ in every class, so
  name a slot from RuffKing only where the CD2 body lines up with RuffKing's declaration order (cVehicle.h).
- **An out-of-line base constructor hides the base layout.** The derived constructor then stores every subobject vptr
  (0, 0x18, 0x1C, 0x30, 0x38) from the base chain alone, and the bytes match with any bases of the right size and
  polymorphism. Vtable contents are not compared either. To identify a base:
  1. Follow the constructor chain to an out-of-line base constructor that other classes also call.
  2. Compare the slot count of each secondary vtable: it is the base's, exactly.
  3. Read the base's own vtable, stored by the inlined base constructors before the final vptrs. Pure slots are
     `_purecall`.
  4. Name slots from the reference builds only where CD2's bodies agree (`RetUniqueID` returns `m_nUniqueID`).
- **Slot numbers** come from `lwz rX, N(vptr)` (N/4). RetClass and IsA are not primary slots: they are the
  cRegisteredClass vtable at +0x30, which the linker places right after the primary one.
- **Secondary-base virtual bodies use subobject-relative offsets.** `cPlayer::RetName` is called through the
  cScriptHost base at +0x1C. Placing its name buffer at complete-object offset 0xDA4 produced a body offset of
  0xD88; moving the member to 0xDC0 produced CD2's 0xDA4 and checked EXACT. Account for the incoming base pointer
  before declaring a field from a virtual body's offset.
- `Fun_Runtime::RetVal` results (`Init`, `Term`, ...) come back through the hidden pointer, r3, with `this` in r4.
  `Ret_OK` (0) and `Ret_FAIL` (-1) are namespace-scope `const RetVal` objects, one copy per file: Ret_OK in .bss,
  Ret_FAIL in .data, no initializer code. The compiler loads them rather than folding (`include/fun_runtime/retval.h`),
  so a "global" a small function copies into `*r3` is usually the file's `Ret_OK`. The relocation check treats names
  with internal linkage per file.

- **Prop destructor vptr stores identify the shared physics hierarchy.** Replacing cProp's direct-cNonGameBase
  stand-in with the reference hierarchy made the moving-platform, searchlight and pintle-faceplate destructor
  bodies EXACT without changing them. CD2 subobjects are cBody's debug handler at 0x120, cIgnitable at 0x250,
  hkEntityActivationListener at 0x294, cPositionalProxy at 0x420, cReplicatedClass at 0x510, cExplosionCallback at
  0x7A0, cDynamicObstacleOwner at 0x7A4 and cSatchelChargeTarget at 0x7AC. The proxy and the two non-destructor
  callback interfaces retain their inherited tables; the other interfaces get derived tables. Reuse the shared
  headers rather than adding flat padding or duplicate stand-ins. cFlocket's former cPoly420 is the same
  cPositionalProxy and also remains exact using that shared type.
- **The land-vehicle chain declares every slot CD2 has.** CD2's primary tables: cVehicle 442, cLandVehicle 484,
  cWheelGroup 489, cCar 495 (cAgencyCar/cAgencySports 495, cAgencyTank 497). Each class header lists, from its
  constructor's tables, every slot whose address differs from its base's table (overrides under the base's names, new
  slots as `vfN`), primary and secondary. With them a derived constructor emits a table the data checks accept:
  cAgencySports's constructor (0x826ED3E8) brought its deleting destructor and 12 adjustor thunks EXACT in both builds.
  A class whose destructor slot holds cCar's copy (0x826FCDD8; cAgencyCar, cAgencyBuggy, cAgencySUV, cAgencyTank)
  declares no destructor. Empty and constant-returning slots shared program-wide (0x82580578, 0x8288FB78, 0x827E56A8,
  0x828D83F8, 0x82457958) need their `vfN` names in `config/symbol_aliases.txt`.

## Codegen idioms
- **Parallel-array store order chooses the induction base.** Turret setup MakeNew (0x82672A40)
  gives 60/62 plain words when its reset loop clears turret/weapon/gunner entries: XDK uses
  object+0x48 as the loop pointer. Gunner/turret/weapon order selects object+0x3C and matches
  CD2. The reference member order and offsets stay the same; the loop comment records this constraint.
- **Recheck a member after virtual termination when deletion and clearing share a guard.** In `cWaterZone::Term`
  (0x82708338), Term may change the phantom member. CD2 rechecks it and skips both delete and clearing when null.
  A/B: `delete p; p = 0` after the virtual call gives 39/42 words; guarding both statements with `if (p)` gives
  EXACT in plain and LTCG builds. Keep the explanatory comment so the second guard is not simplified away.
- **Explicit success/failure branches can retain boolean normalization.** `cRenegadeOrb::EnterPhysicalState`
  (0x82757468) calls `cNonGameBase::EnterPhysicalState`, returns false on failure, then true on success.
  A/B: directly returning the base call produces one tail-branch instruction; the explicit failure branch
  produces CD2's 44-byte call/normalization wrapper, EXACT in plain and LTCG builds.
- **Shared inline constructors must be visible to every owner that expands them.** cAudioBaseProfile's constructor
  (0x82527860) called cSafeDeletable out of line while its circular-sentinel constructor body lived only in
  cFactionConfigData.cpp. Moving that same body into cSafeDeletable's header makes the audio constructor EXACT
  in plain and LTCG, preserving the faction profile's 31 checked functions. The profile initializes m_bReset
  in its body after the event-ID constructor.
- **A parent-walk loop can come from tail-recursive fallback.** `cAnimationProfile::RetSpecificAnimationProfile` (0x824E1090) checks its own slot, then delegates to the parent's const overload. The compiler hoists the handler index and turns recursion into CD2's 16-instruction loop, exact in both modes. An explicit while loop with a cached result emits a 15-instruction conditional return instead; re-reading the slot at its final return emits 18 instructions. Preserve the recursive source rather than trying to force its loop's registers.
- **Tail-recursive setters preserve body store order in the parent path.** `cMission::SetResetFlag` (0x8245A520, descriptive name ours) reaches 12/14 words with reset assigned before completion is cleared. Clearing completion first gives 14/14 in both builds, although the entry path still stores reset first. The differing loop stores can appear as a field-offset finding; both layouts are identical, and their `CD2_OFFSET` checks remain valid.
- **Build a typed array range from its saved begin after setup calls.** In ORB::cSkillPickupManager construction (0x82756238), spelling the end as the member array plus its count hoists the adjacent random-generator address across five calls and saves an extra register. Keeping the array begin for memset, then creating a separate iterator and end from that begin after the calls, reproduces the target without changing the operations: 56/56 words in plain and LTCG builds. Reusing the saved begin as the iterator instead removes a move that CD2 retains.
- **Enum registration objects keep the virtual Lua ABI visible to LTCG.** Character-state registration
  (0x82540308) is 22/22 words in a plain build when only the method exists, but LTCG removes unused `this`
  and moves `lua_State*` from r4 to r3. CD2 initializer 0x82FACB88 calls the shared four-byte registrar
  constructor (0x827729A8), installs table 0x82112CA8, and registers cleanup 0x8303CE60. Recovering that
  actual static instance makes the unchanged method 22/22 words under LTCG too; the initializer and
  cleanup independently check 18/18 and 5/5 words in both builds. Adjacent AI enum objects at
  0x838035F0..0x83803600 confirm the four-byte stride. Use the middleware's published Lua header with
  its verified float number ABI rather than duplicating C API declarations.
- **Load-stream bounds checks remain separate in CD2.** At `cLoadStream::Read` (0x82767390), checking the chunk end and buffer end in two consecutive `if` statements gives 39/39 words in plain and LTCG. Combining the predicates with `||` gives 9/39 words: the compiler moves the shared failure block after the copy and merges the initial unloaded return. Both checks invalidate the stream before returning false; keep their original structure.
- **Inherited overload declarations can move a new virtual slot.** Adding cNonGameBase::Init(CAttributePacket const&) before RetClassName caused the compiler to place its new Init(cSpawner const*) overload ahead of primary slot 11, shifting the tables despite unchanged matched function bodies. Moving the inherited overload beside the existing spawner overload restores all 68 slots; the plain data checks then report no table-extent or multi-address errors from this shift.
- **Ambient-spawner destruction inlines the base's immediate cleanup.** CD2's cLinkedVFXSpawner deleting
  wrapper (0x827FA870) destroys its GUID handler, restores cAmbientVFXSpawnerBase's table, then calls TermVFX
  (0x827FA3B0). Declaring the base destructor out of line mislabeled TermVFX and omitted the three table-restore
  instructions. An inline base destructor calling the reference-named TermVFX restores those instructions and
  makes the deleting wrapper EXACT. Its own base deleting wrapper at 0x822E6768 independently has the same
  table-store/TermVFX sequence; the virtual ReleaseVFX path at 0x827FA210 instead performs fade/release handling.
- **Safe-pointer insertion belongs to the typed constructor.** CD2's cObjectInstigatorEvent constructor
  (0x823EC280) initializes each payload, installs its typed safe-pointer vptr, then links the node. A/B: putting
  insertion in cSafeDeletablePointerBase leaves extra base/derived vptr stores (22/57 LTCG words); initializing
  the payload in the base and inserting from the typed constructor gives 57/57 words in both builds. The constructor
  and deleting wrapper now pass with the constructor's evidenced typed safe-pointer table alias.
- **Checkpoint vectors need the real wrapper, and the clear call must select the intended layer.**
  At cCheckpointArena::AddCheckpoint (0x8284E248), the legacy cVec declaration keeps the pointer parameter on
  the stack across append; using the shared Fun_Runtime::cVector exposes its real append body and restores CD2's
  preserved pointer register, making the 92-byte function EXACT. Top-level const on the parameter did not help.
  At OnShutDownLevel (0x8284E1E8), cVector::clear calls its wrapper out of line, and explicit iterator erase reloads
  the end pointer; qualifying the reference-named MyBase::clear inlines the standard-container clear and is EXACT.
- **Spawning registrars are another shared initializer family.** A static GOM::cProtoRegistrar constructed from
  `Class::StaticCreateClass()` and `Class::SpawnFromPrototype` reproduces 117 72-byte initializers. The shared
  constructor at 0x82657690 takes a typed placement factory returning RWS::CAttributeHandler*. CD2 atexit bodies
  restore the registrar vptr, supporting the inline empty virtual destructor. A/B at 0x82F9A1C0: the old
  void* prototype parameter makes the registrar fail to compile; correcting it to GOM::cObjectPrototype*
  makes the initializer EXACT and preserves the existing factory match. The type matters even when unused.
- **Shader reload callbacks form callback/getter pairs.** The 100-byte callback guards its concrete singleton,
  calls virtual slot 2 (`Reload(bool)`), reloads that singleton and passes its vertex/pixel shaders to the cached
  shader setters at 0x82B8A7B0/0x82B8A780. The following 12-byte virtual getter returns the callback. CD2's
  constructors establish the shared 0x64-byte cShader layout, with shader pointers at 0x3C/0x40 and list link at
  0x60; shader entry strings and defines distinguish the concrete permutations. All 38 recovered pairs check
  EXACT. A/B at 0x82791B58: capturing the singleton before Reload and retaining it across that call gives 84%;
  reloading it after Reload gives EXACT. These setters bind cached shaders; they do not release shader objects.
- **Animation-profile attribute forwarding is a reusable hierarchy.** The 44 profile wrappers first call
  `cSpecificAnimationProfile::HandleAttributes(packet)`, then the concrete profile-data base's
  `HandleAttributeData(*this, packet)`. RuffKing/Burn name both bases; CD2's shared constructor at 0x824E00A8 proves
  the first base's size (0x3C), event-handler subobject (0x18), event ID (0x1C) and two sequence maps (0x24).
  Qualifying both calls reproduces the direct calls and all 44 wrappers check EXACT. Most second bases start at
  0x3C. A/B: giving `cProfileDataHand2HandFull` its real 16-byte alignment (the reference has Vec3 arrays) changes
  its wrapper's second-base adjustment from 0x3C to CD2's 0x40 and makes it EXACT. Its complete size stays 0x3EE0;
  do not insert a padding base to obtain the adjustment.
- **Batch attribute-handler destructors by source shape, not byte length.** The 92-byte deleting wrappers for
  `cVFXPriorityTable`, `cRPGGlobalsInterface`, `cHUDPingProfile`, `cGameModeVFXProfile`, `cArenaBarrier`,
  `cGameModeSpawnPoint` and `cScatterMeshResources` store the derived vptr and call `~CAttributeHandler`.
  An inline, user-declared empty destructor reproduces that sequence. A/B: moving `cVFXPriorityTable`'s empty
  destructor from out-of-line to in-class changes its wrapper from a call to the derived destructor (21.7%) to EXACT.
  Other 92-byte functions in the same scan were ordinary destructors freeing arrays or wrappers destroying GUID
  handlers; check calls, stores and reference declarations before applying the pattern.
- **XDK memory fill versus CRT intrinsic.** `cHUDPingProfile::MakeNew` calls `XMemSet` to clear its four static
  ping times. `memset` becomes four inline integer stores; `XMemSet` reproduces the external fill call. CD2 also
  inlines the profile constructor: changing its `inline` to `__forceinline` changes a constructor call to the full
  initialization sequence and makes the factory EXACT.
- **LTCG can remove unused `this` without a live vtable.** cTrafficLight::IsA was plain EXACT but 21/23 under LTCG: its class argument moved from r4 to r3. Reconstructing the actual destructor and its active-list unlinking emitted the class vtable and restored 23/23 EXACT without changing IsA. A descriptor initializer alone did not fix it.
- **Default string construction includes the allocator subobject.** In cLoadingInfo's factory, a hand-modelled small-string buffer reproduced every store but lost one object-address calculation. Using the real `std::basic_string` base with the shared `Fun_Runtime::cAllocator` restored that instruction and checked EXACT; keep the library representation rather than adding a temporary to mimic it.
- **String-attribute assignment and the LTCG assign specialization.** `m_strName = it->GetAs_char_ptr();` (the
  implicit `cString(const char *)` conversion) addresses the temporary through its stack slot, as CD2 does;
  `m_strName = Fun_Runtime::cString(it->GetAs_char_ptr())` passes the constructor's returned pointer instead (95.7% at
  cAmbienceZone::HandleAttributes, 0x8280FA50). The single-file LTCG model then sees the `basic_string::assign(const
  basic_string &, size_t, size_t)` template body and specializes away its 0/npos arguments (14/70 words), where CD2's
  shared copy (wide 0x82438418, narrow 0x82438A70) keeps all three. Declaring the instantiation `extern template` in
  the source file (as for the vector reserve in cRopes.cpp) gives EXACT in both builds (cAmbienceZone, cVOAZone,
  cGameModeTriggerZone). The latter's unchanged explicit string temporary becomes 80/80 words under LTCG
  once that shared assign instantiation is external; it was already plain EXACT.
- **A typed safe-pointer assignment can create a temporary.** The reference `cSafeDeletablePointer<T>` has a
  converting `T *` constructor and copy assignment, with no raw-pointer assignment overload. Thus `pAttacker = 0`
  in `AIDamageCache::Flush` constructs, assigns and destroys a temporary. The real `cLinkedListItem` base puts its
  final vtable store after unlinking; restoring that base changes the cache constructor from 71.4% to EXACT.
- `x ? true : false` and `x != 0` compile identically. A *materialised* bool (`addic/subfe` or `subfic/subfe/and`) comes
  from a bool local kept live across calls: `bool ret = true; ... if (!f()) ret = false; return ret;`.
- Constants used after calls get hoisted into non-volatile registers (e.g. `li r29,1`). That changes the save helper
  (`__savegprlr_29` vs `_30`) and shifts every later instruction.
- Branch layout follows source order: the order of if/else arms and of early returns matters. A `switch` produces
  different code from an if-chain, and the case order/default placement matters. Examples: `if (Base::Release()) { ...;
  return true; } return false;` (success arm first) and the float range test `if (start < end) { if (p < start || p >
  end) fail; } else if (p > end && p < start) fail;` both need that arm order.
- **Switch lowering.**
  - Case bodies are laid out in source order; an 11-case switch (0..10) becomes an inline jump table.
  - A small `switch (x) { case 0..3 }` without default compiles to `cmplwi 3; bgt; mtctr; cmpwi 0; bdzf; bdzf; bne`
    (the ctr trick), with case 0 as the fall-through body when it is written first.
  - `beq` to the case-0 body, then `bdz` for 1..N and a final `b`, happens when `case 0` is written after the other low
    cases (order 1,2,3,4,5,0,6 reproduced one target).
  - A test like `blt 8 / bne`, case 8's body first, needs every label listed: `case 8: ...; break; case 0: ... case 7:`.
    `if/else` chains and `default: if (<8)` do not give it.
  - Compares in value order whose first body is the one tested last (`cmpwi 1; beq L; cmpwi 2; bne end; <case 2>;
    L: <case 1>`) are a switch written in that body order, not an `if/else if`: cFinalMission's
    OnEnterGlobalMissionState (0x8246C248) is 52.5% as `if (== 1) .. else if (== 2)` and EXACT as `switch { case 2:
    ...; case 1: ... }`. Range compares (`cmplwi 1; blt; cmplwi 10; blt; <default>`) with the default's body first
    come from `default:` written first and each range's labels listed (its GetSaveStateForMissionState, 37.5% as
    nested ifs); the mission save-state and client-notification overrides follow these two shapes.
- Byte swizzles only produce `rlwimi`/`inslwi` for particular expression shapes, e.g.
  `(x>>24)|((x>>8)&0xFF00)|((x<<8)&0xFF0000)|(x<<24)`. Write `HIBYTE(x)` as `(unsigned char)(x >> 24)`.
- Calling virtual slot N needs the class to declare N virtuals before it. Use the real headers in `include/` rather
  than dummy virtuals where possible.
- Returning through one local result variable merges stores; the single-result form (`T *result; if (...) { ...;
  result = p; } else result = 0; return result;`) also decides whether a small helper inlines.
- Static-local guards: `flag & 1` test on a global, then `flag |= 1`. A static local class descriptor `static cClass *p
  = new cClass(id, name, size); return *p;` reproduces the guard, `XCreateHeapBlock(0x5C)` and the out-of-line `cClass`
  constructor.
- Stack slots: locals are ordered by SIZE ascending (smaller nearer sp), ties by first appearance, not by declaration
  order (shown in `cArenaLinker::GetArena`, where unknown struct sizes could be fitted this way). The compiler may reuse
  a slot when lifetimes don't overlap, and the target sometimes keeps them separate.
- With `/fp:fast`, `a*b+c` becomes `fmadds`.
- **Evaluation order around calls.** In `global == f()` MSVC makes the call first and loads the global after it; to
  load it before (`lwz r29, global` then `bl`), copy it to a local first. A field re-read (`i += m_nCount`) and a local
  copy (`i += n`) give different operand orders.
- **Return types shape the caller.**
  - A virtual returning `unsigned int` is tested with `cmplwi`, `int` with `cmpwi`, and `bool` adds `clrlwi`.
  - A helper's return-struct SIZE changes the caller's frame (a 4-byte struct gave 0x80, a 16-byte one 0x90).
  - A forwarded `return p->Virtual();` passes the hidden return pointer straight through only when the return type has
    a constructor; a POD goes through a temporary.
  - A hidden-return temporary passed directly to another call (`f(a, b, sub->GetInfo())`) avoids the copy a named local
    adds.
- **Inlining: the game code is built with `/Ob1`.** Only functions marked `inline` or defined in the class body are
  inlined; a function defined out of line in a `.cpp` never is. So if CD2 inlined something, the original had it inline,
  and accessors that CD2 inlines must be inline in the shared headers (several in `rws/attributes.h` are, for this
  reason). The reverse does not hold: `/Ob1`'s heuristics still decline some inline functions.
  - **Template helpers need `inline` under `/Ob1`**, or they stay calls.
  - **A container destructor's element loop.** cVehicle's destructor (0x826CE0E8) expands cVectorip's destructor and
    its `destroy(first, last)` loop over the turrets. Ordinary in-class inline keeps one or both as calls under `/Ob1`;
    `__forceinline` on both expands them. The loop shape decides the schedule: `for (; first != last; ++first)
    first->~T();` advances after the call (95.9%); `while (first != last) (first++)->~T();` advances before it, as CD2
    and RuffKing's own copy do (99.9%).
  - A constructor with about 20 stores, or a chain of in-class constructors (CAttributeHandler, base, derived with an
    embedded handler), is not inlined into `MakeNew` unless each is `__forceinline`. A loop helper CD2 inlines
    (`AIDamageCache::Read`) also needed it.
  - In-class virtuals called qualified (`Base::OnVFXFinished()`) are inlined.
  - A destructor can be too large for ordinary `inline` even when its source body is empty: restoring many
    inherited tables is part of its compiled body. cBeaconProp's deleting wrapper (0x8245C2A8) is only 1/57 words
    with ordinary inline because it calls a separate destructor. `__forceinline` yields all 57/57 words in plain
    and LTCG, including the table restores and the cMissionCriticalProp destructor call. The complete base chain
    and constructor also generate its thirteen adjustment thunks naturally; do not handwrite their adjustments.
  - An inline override that calls its base and returns a constant (`{ cNonGameBase::Term(); return Ret_OK; }`) leaves
    a dead load of the constant when it is inlined; its out-of-line copy exists only for the vtable.
  - Restoring an inline helper the original used can keep instructions a direct field access loses: a downcast helper
    defined in the class (`HostLinks::RetPlayer()`), called at all three uses, kept a subobject address and a second
    load that direct access let the compiler remove.
- **Multiple inheritance.**
  - A function that lives only in a non-primary vtable is compiled with `this` = that subobject (no thunk). Helpers it
    calls must be members of that base, or you get `addi -N` plus a null check. Example: cAiPlayer's RetName override of
    the cScriptHost slot reads `0x4E8(r3)` for a field at 0x504.
  - Mangled adjustor-thunk names encode the offset (`WPA@` = -0xF0), so a stand-in base chain that regenerates them
    byte-exact is a free layout check. A base that appears several times (the flocket's RetClass/IsA base at +0x30,
    +0x120, +0x510) gives one thunk per extra copy.
  - Read subobject offsets from the consecutive vtables in `.rdata`: a table starts where an adjustor thunk for the next
    subobject begins.
  - The `addi r3,r3,-0x18; b <deleting dtor>` thunk is generated by the compiler once the second base has a virtual
    destructor and the derived class overrides the destructor: nothing to write.
- **A class's vtable brings its thunks, deleting destructor and IsA.** Adjustor thunks (`subi r3,r3,N; b`), the
  deleting destructor and an LTCG-exact IsA are emitted only by an object that installs the vtable: one that defines
  the constructor, a placement factory inlining it, or an out-of-line destructor. Give the stand-in its real base
  (the inheritance registrar names it; the destructor's tail call identifies the base's destructor by the vtable it
  stores) and define that one function; the rest come with it. A/B: cLift with `~cLift() {}` on cPrismaticProp took
  16 functions to EXACT. A base whose destructor lies outside its file's range (order-list region) can still define
  it in its own file to emit the vtable; claim only the in-range functions.
- **Inline or out-of-line destructor: read CD2's deleting destructor.** When CD2's `??_G` contains the destructor's
  body (vptr stores, member and base destructors) and the class has no separate `??1`, the destructor is inline in the
  header, and only a function that installs the vtable emits the `??_G` (an inline constructor in MakeNew); an
  out-of-line `X::~X() {}` gives a `??_G` that calls a `??1` instead, in plain and LTCG builds. When CD2's `??_G` only
  calls a `??1` in the same file, define the destructor out of line. A/B on cDocksMission (0x824745D8): out-of-line
  13.9%; inline destructor plus MakeNew's inline RuffKing constructor EXACT, with IsA and five adjustor thunks.
  `check` only reports the thunks once claimed: their names are `??_E<class>@<ns>@@W<offset>@` (offset in MSVC's
  hex letters, 0x248 = `CEI`), `?RetClass@...@@WBA@` and `?IsA@...@@WBA@` for the registered-class copy at +0x10.
- **The vfptr slot takes the class's alignment.** In a 16-byte-aligned class (a Vec3 member) the first field after
  the vptr is at +0x10, as RuffKing's offsets show (cRefractorBeam's m_pProfile); no padding member is needed.
- **An implicit destructor can leave no deleting destructor of its own.** cClusterGrenade declares none, so its
  deleting destructor equals cExplosiveGrenade's and its thunks reach that copy (0x8261D3A0); NPCArmedBehaviour's
  inline empty destructor gives CellGuard, CellMinigun, CellRocket and Peacekeeper one folded copy (0x824C17F0).
- **Vptr stores of inlined base constructors.** MSVC drops the earlier of two stores to the same vptr slot when base
  constructors are inlined, so a chain of bases or members collapses to one store. The stores survive when an
  intermediate class has an out-of-line virtual destructor: `class B : public B1, public B2 { virtual ~B(); }` keeps
  B1's and B2's stores plus B's plus the derived's. Members always collapse to one store.
- A base class whose own constructor initialises a field (`B2() : m_bFlag(false)`) leaves a dead `addi` of the subobject
  address in the inlined derived constructor. Initialise the field in the enclosing class's constructor body instead.
- **`__declspec(novtable)`** on a polymorphic second base removes the dead vptr store its constructor would add. It is
  probably an abstract interface in the original.
- **Pointers to virtual members** (`&C::Slot`) make the compiler emit 16-byte `vcall` thunks (`??_9C@@$B...`), named
  after the class that declares the slot.
- **Downcast from a base subobject:** `static_cast<P*>(basePtr)` gives `cmplwi; addi -0x1C; bne; li 0`;
  `X *x = xs ? static_cast<X*>(xs) : 0; if (x) ...` gives the jump-threaded form. For the second null test after a
  safe-pointer downcast, call the inline `RetCharacter()`-style accessor; integer arithmetic does not reproduce it.
  Going through the conditional `RetCharacter()` from another inline (`PLAYER::cPlayer::RetLocalPlayerCharacter()`)
  adds a register copy (`clrrwi rX, rY, 0`) before the `-0x1C`; converting the safe pointer itself
  (`return g_pLocalPlayer->m_pCharacter;`, its `operator T *`) does not. A/B on cBreachHoleMission::IsLocalPlayerNearby
  (0x82473330): 29.4% through RetCharacter, EXACT through the conversion operator.
  RuffKing declares both the static `cPlayer::RetLocalPlayerCharacter` and namespace
  `PLAYER::RetLocalPlayerCharacter`. The static accessor directly converts the safe pointer;
  the namespace wrapper guards the singleton. This distinction gives cProp's carry hook
  (0x8272AB30) 12/12 words in both modes, while all four guarded mission/zone callers remain exact.
  Equipment inherits the net-body carry method at 0x822C5A30; its reference interface has no
  override. Removing the redundant declaration resolves the equipment/net-body relocation-name conflict.
- **Subobject pointer null test:** `&p->m_member` followed by `if (ptr)` gives the single `addic. r11,r9,0x18; beq`. A
  derived-to-base pointer conversion adds a second null test.
- **`Fun_Runtime::g_GlobalConstants` is per object file**: a `static` object defined in `fun_runtime/class.h`, as in RuffKing
  (one per object in its symbol lists). CD2 has a copy at a different address for each file (0x830ACBD8, 0x830C0E04, ...),
  so one external declaration makes the relocation check see one name at several addresses. Its constructor keeps
  the members opaque: with a visible aggregate initializer the compiler folds `CONST_FLOAT_0` into a literal, where CD2
  loads it.
- **A safe-pointer member initialised from null (`m_pCharacter(0)`)** goes through the converting constructor: the
  null payload is stored before the typed pointer's vptr, and the whole constructor schedules differently. The
  default constructor stores the vptr first. Read which store comes first in CD2 (cCharacterInterface's constructor:
  60% with the default constructor, exact with `(0)`).
- **Zeroed words: an array value-initialised in the list (`m_a()`) schedules differently from separate scalars**
  (`m_a(0), m_b(0), m_c(0)`); zeroing the array in the body moves the stores after every list member. cPedestrianBase's
  constructor matches only with three scalars.
- **`Fun_Runtime::ZeroVec` is an `OldVec3` in CD2** (three floats; every read is +0, +4 or +8), and a `Vec3` built from
  it goes through `Vec3(const OldVec3 &)`: each component is reloaded after the previous store, then w = 1.0.
- **Two safe pointers with the same pointee type share one vtable-address load; CD2 building it twice means two types**
  (the linker folds the tables later). cAiPlayer's constructor matches only with different pointee types.
- **A singleton pointer only the constructor and destructor touch is file-local.** CD2's cBaseJumperMission stores
  `this` to 0x838009C0 in the middle of a Vec3 member's initialization and clears it after the destructor's first
  member load: the compiler moved the stores freely, which it does only for a variable whose address nothing outside
  the file can see. A/B: as an external static member, MakeNew (0x82488FB0) 50/58 and the deleting destructor
  (0x824890A8) 32/42 words, plain and LTCG; as a `static` variable in the source file, with the constructor and
  destructor defined there `__forceinline`, both EXACT. Check the global's cross-references before choosing.
- **Member initialization order.** Members with default constructors (e.g. `Vec3`) are initialized in declaration order
  before the body. To match CD2's interleaving, put scalar fields in the mem-initializer list too; body assignments come
  after all of them. Inline constructor store order follows the order of assignments in the BODY, not member
  declaration order.
- **Zeroing a POD member: memset in the body.** CD2 zeroing a struct member with integer `stw` stores *after* the other
  members are built (a GUID event handler, say) is `memset(&m_Data, 0, sizeof(m_Data))` in the constructor body; for 36
  bytes it becomes a `stwu` loop with `ctr = 9`. Float assignments `= 0.0f` give `stfs`, and `: m_Data()` in the
  initializer list zeroes it before the other members.
- **Destructors.** A scalar deleting destructor with no vptr stores in its body means the class has no user-declared
  destructor: an empty `~X() {}` makes the compiler store the vptr before calling the base destructors. Vector members'
  destructors are inlined into the owner's in reverse declaration order, arrays last to first.
- **`Vec3` passed in a vector register** (`lvx128 v1` before a call) means a `__vector4` parameter:
  `union { __vector4 v; struct { float x, y, z, w; }; }` with the copy constructor
  `v(o.v) { x = o.x; w = 0.0f; y = o.y; z = o.z; }`, including `<ppcintrinsics.h>`.
- Writing back several floats through one pointer (`Vec3 *p = &m_hint; ... p->x = v.x;`) reuses the register that held
  the vector load's address; `m_hint.x = ...` re-derives the member address.
- Bool from `||`: `return a == b || f();` (or `bool r = a || b; return r;`) gives the branchy
  `li 0 / bne / li 1 / clrlwi`. `if/return true/return false` folds into `beqlr` + `li r3,1`; an `unsigned char` local
  tested with `!= 0` adds `clrlwi; addic; subfe`.
- An if/else store gives CD2's select: `if (b) p = &m_A; else p = &m_B;` with two members of different derived types
  compiles to the merged form (both addresses computed, one branch, one store) with no ternary or cast.
- Constructor called with only `this` (r4 untouched) means the constructor takes no packet argument: `MakeNew` is
  `new X()` / `new X`, even though `MakeNew` itself receives the packet.
- A `short` member passed to an `int` parameter (`f(m_nHandle)` with `void f(int)`) gives `lhz` + `extsh`; a `short`
  parameter loads straight into r3 and shifts the scheduling.
- Signed versus unsigned compares follow the expression type exactly: `cmpwi` against a byte-swapped value needs
  `(int)rwSwap32(x) == 1`. `fctidz` + `stfiwx` (not `fctiwz`) is a float converted to an UNSIGNED int: declare the
  destination `unsigned int`.
- An explicit float `if`/`else` can preserve a branch that a ternary removes. In the spinning prop's anticlockwise
  motor entry (0x8273F7E8), `speed = input < 0 ? input : -input` becomes `fsel` after CreateConstraint
  (29 instructions versus CD2's 35). Assigning `speed` in the two explicit arms emits CD2's branch before
  CreateConstraint and is EXACT in both modes; initializing speed first and conditionally negating gives 33 instructions.
- Safe-pointer conditions also distinguish source forms: in `cStaticEnvironment::ReCalculateResourceState`
  (0x828093C0), `if (resource && ...)` gives CD2's `cmpwi`, whereas `if (resource != 0 && ...)`
  selects the safe pointer's comparison operator and gives `cmplwi`. This A/B changes exactly four words;
  the implicit pointer condition is EXACT in plain and LTCG builds.
- **A pointer from an inline accessor tests signed; a member read tests unsigned.** The null test of a pointer an
  inline function returns compiles to `cmpwi`, the same pointer read as a member to `cmplwi`, with every other word
  equal. A/B on cEquipment::PickUpRequested (0x82605C10): `!m_pOwner` gives `cmplwi` (97.6%), `!RetOwner()` gives
  CD2's `cmpwi` (EXACT, plain and LTCG). On cEquipment::EnterGhostState (0x82605B90) CD2 has `cmplwi`: an accessor
  returning the rigid body's `m_world` gives `cmpwi` whether in-class, out-of-class inline or `__forceinline`, tested
  implicitly or with `!= 0` (96.8%), and the member read gives EXACT. So a `cmpwi` against 0 on a loaded pointer
  points to an accessor in the original, a `cmplwi` to a field access.
  At cMissionCriticalProp::vf226 (0x8245B5F8), testing a local initialized from RetMCPSpawner still gives `cmplwi`
  (29/30 words). Testing `if (RetMCPSpawner())` directly, then obtaining the pointer inside the guard, gives CD2's
  `cmpwi` and EXACT in plain and LTCG builds. Both helpers' names come from RuffKing; the second accessor read
  is eliminated, leaving the single load CD2 has.
- A loop counter compared with a small constant and masked with `clrlwi rX, rY, 24` after the increment is an
  `unsigned char` (RuffKing declares such bounds `static const unsigned char`).
- A handle that is tested and then passed as an argument (`m_h = Ext(globalPtr, m_h)`): the early `lwz r4` is the
  tell; decompilers hide the second argument.
- Positive modulo `i = idx % n; if (i < 0) i += m_nCount;` (field re-read) and wrap-around
  `if (idx < 0) i = size() + idx; if (idx >= size()) i -= size();` with an inline `size()` computed three times.
- `push_back(T *const &)` forces its argument into a stack slot, which CD2 reloads after the call.
- Inlined MSVC 2008 STL: `std::string::c_str()` is `res >= 16 ? ptr : buf` (that arm order); vector `erase`/`clear`
  inline `memmove_s` from `<string.h>`; vector code matching CD2 needs `#define _SECURE_SCL 0` before any STL header.
  An inlined `std::list` sentinel (`_Buynode`) is `Node *n = Alloc(); if (n) n->next = n; Node **pp = &n->prev;
  if (pp) *pp = n;` (two separate null tests).
- Custom-allocator vectors: `allocate()` is a static out-of-line allocator member (called with just the count),
  `deallocate` an inline `XDestroyHeapBlock`; `clear()` and `push_back()` are out of line in CD2.
- **GUIDs.** Lookups go through `Editor::cGUIDLinker<T>::LinkToObject` (`include/editor/guid_event_handler.h`). The
  shape of each GUID copy decides the stack slots: `Register` copies from a const reference into a local (block copy:
  4 `lwz` then 4 `stw`); the ambient spawner needed a declared GUID assigned with `=` (the header's inline
  `operator=`), not copy-initialized; `RWSGUID g = GetListGUID(list, i); LinkToObject(g);` puts the hidden-return
  temporary at the lower slot, while `LinkToObject(GetListGUID(...))` swaps them. A by-value GUID parameter is passed
  in two 64-bit registers (`ld r4 / ld r5`). A GUID read from an attribute goes into a named local before the prototype
  lookup: passing `it->GetAs_RWSGUID()` straight to it omits CD2's address reload (cSpawnPointBase::HandleAttributes
  0x823D2B38 is EXACT in both builds only with the local).
- String-id hash (inlined `GetStringID`): `int mult = <chain>; int id = 0; for (char c = *s; c != 0; c = *++s)
  id = id * mult + c;` with `mult` declared before `id`.
- **A chain of early returns versus one `&&` return.** CD2's cVehicle::IsOkToInteract (0x826D6FC8) sends every failed
  test to one shared `li r11,0; clrlwi r3` tail: that is `return a() && b() && !c() ...;`. Writing the same tests as
  `if (!a()) return false;` gives each its own epilogue (21.8%). A result variable initialised to `false` and set
  inside the `if` keeps the 0 in a saved register across the calls (`li r30,0` in the prologue, `mr r3,r30` at the
  end): cHelicopter::IsOkToInteract (0x826BDEB0) is EXACT only in that form (3.8% with an early `return !x();`).
  The third shape, `if (a || b || c) return true; return false;`, branches every success to one `li r3,1; blr` and
  converts the last test in place (`li r3,0; cmplwi; beqlr`): cLandVehicle::IsFunctionallyDamaged (0x826C25D8) is
  EXACT that way, 70% as `return a || b || c;`.
- **Helpers CD2 inlines into several files, with no out-of-line copy anywhere,** are header inlines here
  (cVehicle's IsSufficientlyInWater, IsSeatDoorLocked and RetVehicleSeat, cDynamicBody's IsInWater; RuffKing, built
  -Ob1, has them out of line). The `&&` form of IsSufficientlyInWater gives CD2's `li 1 / li 0` pair; a flag set in
  an `if` adds a `li 0` up front.
- **An override that shares its name with a new overload in the same class moves the overload.** cLandVehicle
  overrides cBody's `CustomiseShape(hkShape **)` (slot 151) and adds `CustomiseShape(hkShape **, cLandVehicleData *)`
  (slot 460). With the override declared first, MSVC puts the new overload at the head of the class's new slots (442)
  and shifts the rest; declared after the overload, both land where CD2 has them (0x826C79C8 calls 0x730, slot 460).

- **Particle-effect release in destructors (`VFX/cParticleEffectInstance.h`).** About a hundred CD2 functions expand
  StopEmitters, SetAsOrphan and Release on an owned instance, then clear the pointer. A/B on cGrenade's destructor
  (0x8261E460): `m_StatusFlags |= 0x10` before the spawn-rate store gives the flag store ahead of the constant load
  (94.4%); the spawn-rate store first gives CD2's order. Linking the orphan through `if (m_pNextOrphan)` after the store
  reuses the loaded root as CD2 does; testing `ms_pOrphanRoot` again reloads it. Release's `delete this` must call one
  helper (CD2 0x8245C7F0, the scalar deleting destructor with the destructor expanded, kept in
  cAgencyTowerSegmentMission's object): an inline destructor is called out of line and freed separately (96.6%), a
  `__forceinline` one moves into `??_G`, which stays a call. Plain builds still pass the deleting flag (`li r4,1`) that
  CD2's LTCG dropped, so such destructors are `"ltcg": true`. StopEmitters reads that object's g_GlobalConstants copy,
  0x830B7F30, one of the relocation gate's shared copies.
- **Script-method factories: single use inlines, shared use calls.** In every CD2 RegisterMethods the factory for a
  member-function signature used once is expanded (allocate 0x10, store name, member pointer, then the descriptor
  table), while a signature used several times calls the folded shared factory (0x8273D230 bool, 0x8260A840 int,
  0x8260A8A0 float, ...). The per-file models do not reproduce the single-use expansion (an `inline` factory and an
  /OPT:REF link were tried on cGrenade's 0x8261E148), so a RegisterMethods with a single-use signature stays open; its
  source still makes the compiler emit the vcall thunks (`??_9<Class>@@$B<offset>@AA`) of the virtuals it registers,
  which match on their own.
- **Typed script-method registration and shared pointer lists.** Weapon registrar `0x826098C0` passes native eight-byte
  const-member pointers to 16-byte descriptor factories and inserts the resulting pointers into its first 12-byte list.
  Taking the addresses of the actual virtual members emits the MSVC vcall thunks; never handwrite forwarding functions
  for them. The descriptor has one virtual Lua invocation slot and no virtual destructor. A/B on the same registrar: a
  declaration-only list insertion gives 103/122 words in plain and LTCG builds (the stack stores of the member-pointer
  adjustment are scheduled differently); the full XDK `std::list` gives 122/122 plain words but inlines insertion into
  the LTCG caller (2/122 there); the typed `cPointerList` adapter (`include/fun_runtime/pointer_list.h`), which models
  the node construction, length check and links and keeps allocation and destruction external, gives 122/122 in both
  with no rule findings. That proves the caller, not the insertion body, which is still unmatched; reference `cList`
  derives from `std::list`, so the adapter is marked as an incomplete stand-in. The descriptor constructor initializes
  the name in its base and the member pointer in its derived initializer list: moving the name assignment into the
  derived constructor body reorders two stores (both 96-byte factories 22/24 words); base and member initialization give
  24/24 in both builds.
- **A clamped result goes into its own local.** cWeapon::IncrementClipAmmo computes the clamped amount into a separate
  result with a conditional expression (`const unsigned int added = m_nCurrentClipAmmo + amount > maximum ? maximum -
  m_nCurrentClipAmmo : amount; m_nCurrentClipAmmo += added; return added;`): EXACT in both builds. Clamping the `amount`
  parameter in place changes the branch shape. The same form makes the other three ammo arithmetic methods EXACT.
- **A Havok `hkBool` read through its real helper keeps the sign extension.** cLandVehicle's IsReversing and IsBraking
  call the reference-named cCustomVehicleInstance helpers that return `hkBool` by value
  (`bool(m_pVehicleInstance->IsReversing())`): EXACT in both builds. Converting the field directly omits CD2's sign
  extension; changing `char` to `signed char` alone does not bring it back.
- **Havok SIMD lengths: extract the dot product before `sqrtf`.** In cCustomVehicleInstance::calcMPH (0x82699F08)
  converting `dot3` through `hkSimdReal` first emits a `stvewx` CD2 does not have; `length3` must extract the dot
  product, take `sqrtf`, then construct `hkSimdReal`'s splat (the final float conversion does use `stvewx`). EXACT under
  LTCG only. Its factor is the rounded 2.2369974f, not 2.2369363f.
- **Copy a `Vec3` as a whole vector.** CD2's Vec3 storage is a single `__vector4`. The implicit assignment of our
  scalar-view union expands into scalar copies; `Vec3::operator=` assigning `v = other.v` (`include/fun_runtime/vec3.h`)
  keeps CD2's single vector copy and makes cCharacterControllerComplex::SetEffectsVelocity and SetADMOffset EXACT.

## Patterns by kind of function
- **Header constants (the common initializer sequence).** About a thousand objects open their initializer run with
  the same ~20 functions: static constants defined in headers, so every object that includes the header has its own
  copy and its own `??__E` initializer. Names, headers and line order come from RuffKing's PDB line info (llvm-pdbutil
  `dump -l --modi=N`): `PHYSICS/physicsconsts.h` (fPhysicsSimulationTick, fMAX_TIME_STEP, fSLIP_LIMIT, fSKID_LIMIT),
  `CHARACTER/characterconsts.h` (CHARACTER::gRandGen, fWALK_VELOCITY_THRESHOLD_HALF_SQ, _DOUBLED_SQ),
  `PHYSICS/physicsproject.h` (WORLD_RIGHT/UP/AT_VECTOR, ZERO_VECTOR, IDENTITY_TRANSFORM, IDENTITY_QUATERNION),
  `CHARACTER/cCharacterController.h` (fSlopeDotLimit, fStepDotLimit, fStepDotTan), `CHARACTER/cRagdollProfile.h`
  (nPART_PERCENT_WEIGHT) and `AI/aiconstants.h` (fFACING_TARGET_MIN_DOT_PRODUCT, AI::fTARGET_FACING_ME_MIN_DOT_PRODUCT,
  fPOINT_LOCK_RADIUS_SQ). The blocks come in that order, except that characterconsts.h comes before or after
  physicsproject.h; a file includes the headers whose blocks its run has. The run starts at fPhysicsSimulationTick
  and ends at the file's own initializers (the class pointer, the registrars), which is the ownership evidence for the
  `init` entries in `config/splits.txt`. 3907 initializers in 343 files matched this way first (2026-11-06), all exact
  in both builds. Mechanisms, each shown by A/B on src/AI/cAiPlayer.cpp:
  - A constant computed from another (`X_SQ = X * X`) keeps its initializer; a constant of literals does not get one.
    CD2's LTCG turned the computed middle values (fWALK_VELOCITY_THRESHOLD_HALF, fPOINT_LOCK_RADIUS) into initialised
    data, so they have no initializer in CD2, but the squares load them.
  - hkVector4's constructor from four floats must build the vector through `__lvx` of an aligned array: with plain
    member stores the compiler initialises the object statically and emits no initializer at all ("missing").
    IDENTITY_TRANSFORM also needs hkVector4's vector copy constructor (the default copy goes through two `ld`/`std`).
  - gRandGen's initializer only registers its destructor (`b atexit`): cRandGen's default constructor is inline.
  - `cos` of a float constant needs the double overload spelled out (`(float)cos((double)x)`, what the `cosf` macro
    expands to): with the float overload the LTCG model differs.
  The seven whose constant CD2 loads through the LTCG pool (fPhysicsSimulationTick, the three controller constants,
  nPART_PERCENT_WEIGHT, the two facing constants) are `"ltcg": true`; the LTCG gate names the statics they store to
  from the model link's PDB (verify_ltcg.StaticNames), since the link map lists no static data. gRandGen's at-exit
  destructors (`blr`) share one internal name across files; the relocation check keys such names by file
  (relocs.known_key). 2021 more matched this way, 5928 in all. Still open: fMAX_TIME_STEP, fSLIP_LIMIT,
  fSKID_LIMIT, fPhysicsSimulationTick and nPART_PERCENT_WEIGHT in the 100 files whose matched IsA reads another
  object's g_GlobalConstants copy (LTCG inlined HasAncestor's COMDAT from one object everywhere), since the
  relocation check allows one address per name in a file.
  Each file includes the constants headers directly, under a note. RuffKing's objects have the same constants (for
  example cCarStaticData.obj: physics, character, controller, ragdoll, in CD2's order) but reach them through hundreds
  of headers, and the PDB records no include graph. Moving the includes into our class headers was tested and
  rejected (2026-11-06): no header in `include/` is included by exactly the files whose run has a block (the only
  fits were unrelated, `cd2/layout.h` for the physics constants), so any carrier would add or drop initializers.
  New files for runs without one: a run lying alone between two scaffolded files' runs, at the module RuffKing
  links between those two objects, takes the unassigned text between their ranges (6 files). The other 92 such
  runs come in chains between two scaffolded files, where nothing yet divides the text, and stay unassigned.
- **An object with no code of its own.** Some objects define only data, so their whole contribution to CD2's code is
  the header constants' initializer run and gRandGen's at-exit destructor. Example: NPCArmoury.obj, whose only class,
  cNPCArmourySetup, is an attribute-block class ID that NPCBehaviourPrototype's armoury setup reads. Its run lies inside
  another file's initializers but reads its own g_GlobalConstants copy, so it can match only as a file of its own. Such a
  file gets an empty text range at its place in the link order (`text A A`, where A is the boundary between the
  neighbouring objects' text), so the link-order check still places its initializers and at-exits; `setup` gives jeff
  no unit for an empty range. Evidence needed: both reference PDBs list no functions for the object beyond its
  initializers, and its run sits between its neighbours' runs in RuffKing's module order.
- **Class-factory registrar** (an initializer near 0x82F.., 76 bytes, and its at-exit destructor near 0x830..):
  `static RWS::CClassFactory::CRegistrar <Class>Registrar("<name>", <Class>::MakeNew, <size>, false);` in the class's
  namespace. The size argument is the class's size; the `MakeNew` it passes often builds the class's prototype.
  Identical `MakeNew`s are folded, so several registrars may pass one address (`config/symbol_aliases.txt`).
- **`MakeNew`:** `return new X(packet);`, or `new X()` when the constructor gets only `this`. The class's own code starts
  at its `RetClassName` (lis/addi/blr returning the class name).
  - Most build the class's prototype. The `li r3, size` before the allocation is the prototype's complete size: give
    the prototype that size (opaque storage after the last recovered field) and take its base from the first call in
    its constructor. Out-of-line constructor (88 bytes: allocate, `mr r4, packet`, `bl`): declare it. Inline constructor
    (112 bytes: the base constructor call, then the prototype's vptrs at 0 and 0x18): `__forceinline` constructor
    calling the base's; a store after the vptrs (120 bytes) is a field initialized in its mem-initializer list. 54
    factories matched this way, both builds. The +0x18 vptr is a folded client table (`symbol_aliases.txt`, 0x821327A4,
    or 0x82162A84 for the character prototypes).
  - `new X` returning `addi r3, r3, N` after a null test (64 bytes) converts to a `CAttributeHandler` base at +N: the
    class needs its real bases and complete size.
- **`SpawnFromPrototype(proto, mem)`:** `if (pMem) return new (pMem) X(); return 0;` when CD2's constructor takes no
  arguments (RuffKing's often takes the prototype). The 32-byte form that swaps r3/r4 before `b ctor` is
  `new (pMem) X(pPrototype)`: declare `X(GOM::cObjectPrototype *)`. Either needs a class that converts to
  `RWS::CAttributeHandler *`, so a baseless stand-in first needs its base (the inheritance registrar names it).
  - A large placement factory (144..216 bytes: the guard, `bl` a base constructor with `this`, then the class's vptrs
    and any field initializers) inlines the class's constructor: `__forceinline X() : <fields>() {}` over the real
    base, with the fields RuffKing names at CD2's offsets. 19 factories matched this way; four replaced fake
    out-of-line `X::X() {}` definitions. Such a factory also emits the class's vtable, so its deleting destructor,
    IsA and adjustor thunks can match in the same file (cWeaponisedHelicopter: 16 functions).
- **A class's own empty destructor, when CD2's only stores vptrs and calls the base's**, emits the vtable: `X::~X() {}`
  out of line (cCWFirearm, cWeaponisedHelicopter). Measured on the 90 open deleting destructors (2026-11-06): 86 call
  destructors that free memory, unlink lists or destroy members, so each needs its members typed first; 4 were
  trivial, 3 matched and the fourth (cAgencyGarageDoor) also clears two statics. The open adjustor thunks follow the
  same destructors: pairing compiled thunks with every open one (40 files, 212 thunks) found that 38 objects emit none
  (nothing installs the table), cRigidBodyProfile's 4 match, and cBaseJumperMission's adjust by cMissionBase's offsets
  (0x10, 0x240, 0x248) where the stand-in is a cNonGameBase. IsA, all 38 attempts: 3 EXACT (cCWSatchelCharge,
  cDynamicBody, cPopulationZone), 1 WRONG TARGET (cCharacterInterface), the other 34 PLAIN ONLY (LTCG 21/23) because
  no function in their file installs the vtable. Six more read class pointers of classes not declared here
  (cFactionInfo, cGangInfo, cBeamManager, cLinkedVFXSpawner and two unnamed); cAudioLogContainer is only forward-declared.
- **Prototype deleting destructors that store vptrs and call a base prototype's destructor** come from an inline empty
  destructor in the nearest class whose vptrs they store; derived prototypes without destructors fold into one copy.
  A/B: `virtual ~cCarPrototype() {}` with `virtual ~cVehiclePrototype();` out of line makes 0x826EC1A0 (shared by
  cAgencyCarPrototype, cTruckPrototype and the other car prototypes) EXACT. The copy only exists where an inline
  prototype constructor emits the table.
- **`RetClassName`:** returns the class-id string; define `static const char *const pcXClassID = "X";` in the `.cpp`
  (constant-folded to lis/addi, no load).
- **`RetScriptTypeRegistration`** (our name for cScriptHost slot 1, a three-instruction global-address getter): returns
  the 0x24-byte script-type descriptor that 0x82772828 constructs (`include/fun_runtime/cScriptTypeRegistration.h`).
  0x82772828 registers game classes and AI events alike, so the getter belongs to the registered child name: an AIE_*
  getter is that event class's slot 1, an enum-name getter slot 1 of an enum registrar table a static initializer
  installs. RetClassName, RetClass and these getters have the same size: classify each by the data it returns (a name
  string, a cClass descriptor, a script-type object) and its slot (primary 11, registered-class 0, cScriptHost 1).
- **`HandleAttributes`:** `for (RWS::CAttributeCommandIterator it(packet, pcXClassID); !it.IsFinished(); ++it)
  switch (it->GetCommandId()) { ... }`. A float attribute is
  `{ float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_f = mem; }`: the byte swap goes through the stack (stfs,
  lwz, swizzle, stw, lfs). The retail build strips RuffKing's asserts.
- **`Init`/`Term` returning a RetVal:** through the hidden pointer (see Shared bases). The prototype's
  `Init(const CAttributePacket &)` is slot 5 of its CAttributeHandler table, `Term` slot 6 and `Init(const
  GOM::cSpawner *)` slot 18 of the primary.
- **A function that never uses `this`** and reads globals is static (`cRopes::GetRopeSegment`).
- **Naming a virtual slot:** follow its chain of base calls to the bottom, where the body shows what the slot does
  (cProp's UpdateRenderMatrix calls cBody's, which copies the body matrix: slot 26). Class sizes come from the
  registrar or `StaticCreateClass` (`cClass(id, "name", size)`); a prototype's from the allocation in its `MakeNew`.
- **Class pointers are never `= 0`.** CD2 initializes every `ms_pc<Name>Class` dynamically
  (`= &X::StaticCreateClass();`), so a zero definition is a placeholder that leaves its initializer open. A 40-byte
  initializer calls `StaticCreateClass`; a 176-188-byte one has it inlined (local-static guard, `cClass(id, "name", size)`)
  and CD2 keeps no separate copy: that needs the in-class `static __forceinline` definition (cFreakSniperEvent.h), since
  `/Ob1` declines a plain in-class one (A/B on cAnimParams, 2026-11-07). The class name in the matched `RetClass`/`IsA`
  must be the one whose initializer sets that pointer (NPCBehaviour.cpp's first pair is NPCArmedBehaviour's). The AI
  behaviour classes spell it `ms_p<Name>Class` (RuffKing), everything else `ms_pc<Name>Class`.
- **A stand-in's base comes from CD2's inheritance registrar** (`cInheritanceRegistrar(Own::StaticCreateClass(),
  Base::StaticCreateClass())`; its code calls the base's first), checked against RuffKing: deriving straight from
  cNonGameBase or CAttributeHandler when both name an intermediate class is a placeholder. The registrar names the runtime
  parent, which is not always the C++ base (cChaseBehaviour registers under NPCBehaviour but derives from
  NPCBehaviourSM; the audio vehicle profiles register under cNonGameBase but derive from cAudioBaseProfile): where
  RuffKing's header agrees with ours, keep ours. A `MakeNew` that allocates less than the registered class size builds
  the prototype (`new XPrototype(packet)`, cCwCharacter), not the class.

## Middleware
Middleware with published source lives in `src/middleware/<library>/` (each with a README), its rule waivers in
`config/middleware.txt`, its compiler settings in `config/file_flags.txt`. XDK libraries stay linked from the pinned
SDK: their proprietary implementations (including code derived from PNG, JPEG and zlib) are outside this scope.
- **A library was not built with the game's flags: measure each candidate.** Compile every file of the library
  with a candidate setting, align the compiled functions (source order) with CD2's functions in the file's range
  (address order) by longest common subsequence of exact masked comparisons, and count. Measured (2026-11-08): Lua
  `/Ob2` 563, `/Ob1` 406 (per file: `/Ob1` for ldo.c and lstring.c); zlib `/Ob2` 14/14; libjpeg as C `/O1
  /fp:precise` 297 (`/Ox` 65; `/fp:fast` loses the three float DCTs, `/GS` six), as C++ with `NO_GETENV` and
  per-file `/Ob1`/`/Ob2` 315. The reference PDBs record their middleware objects' language and often the compile
  command (`refs/*/objects.json`: `compiler.language`, `build.cmd`; RuffKing's zlibXenon `-Ox ... -Gy -TC`, Burn's
  Lua `-Ox -Os ... -TC`, RuffKing's libjpeg.lib `Cpp`); check them first, then count.
- **C compiled as C++ changes data folding.** As C, libjpeg's `jpeg_set_linear_quality` reaches its second static
  table through the first (one section); CD2 addresses the two separately, and CD2's linker folded
  `std_huff_tables`' two identical DC tables into one copy. Compiled as C++ (`/TP`), each constant table is its own
  foldable section: both functions come out exact, the second with a `config/symbol_aliases.txt` entry.
- **Byte-identical wrappers are placed by source order.** Lua's math wrappers (`math_sin`, `math_cos`, ...) differ
  only in their callee, so an exact comparison finds several CD2 candidates for each. Within one object the linker
  keeps source order, so the order alignment above places them, and the CRT objects `config/library_splits.txt`
  identifies for each callee (sincos, tan, asincos, atan, fmod, pow, log, exp, ...) agree. That alignment added 24 Lua
  functions a plain hash match had left ambiguous.
- **A WRONG TARGET on a string literal can name the library's configuration.** Lua's `"%lf"`/`"%.14g"` against CD2's
  `"%f"`/`"%.5g"` are the release's own float configuration (`etc/luser_number.h` with `USE_FLOAT`, `LUA_USER_H`).
- **The backend's inliner (XDK 9328 c2.dll, read in IDA 2026-11-08).** Each candidate is inlined when its cost score
  is below `inlS + 5`; `inlS` comes from a parameter profile (60 normally, 2 under PGO) and can be set with the hidden
  `/d2inlS<n>`. In a compile without LTCG (or with `-optref`) a `static` callee referenced once has its score divided
  by 3, which is why `/Ob2` inlines single-caller helpers such as Lua's `correctstack`. Each caller also has a budget
  of 35,000 inlined instructions. A/B on Lua's ldo.c: `/Ob2` 13/23, `/d2inlS` 1..40 23/23, 60 13/23, every `static`
  function made external 23/23. The bonus is withheld from a function flagged externally visible (0x2000; every
  non-static function of a compile without LTCG, and every function under `/Gh`, `/GH`, `/callcap` or `/fastcap`).
  CD2's Lua and libjpeg behave as if their statics were visible too: libjpeg with `LOCAL`/`METHODDEF` made non-static
  gives 320/329 under one setting. No ordinary switch reproduces it (the profiling ones insert calls CD2 lacks;
  `/hotpatch`, `/analyze`, `/openmp`, `/Gm`, `/J`, `/Zl`, `/GT`, `/MD` change nothing). Use such switches only as a
  diagnostic, never in `config/file_flags.txt`: the original build did not pass hidden backend options.
- **Recover individual middleware call boundaries without changing linkage.** With evidence-backed middleware
  edits authorized, explicit `__inline` and `__declspec(noinline)` can reproduce CD2's observed expansions and calls
  under the existing per-file settings. A/B on ldo.c: marking luaD_reallocstack `__inline` adds exact growstack;
  marking luaD_throw adds exact growCI and call; subsequently marking growstack adds exact adjust_varargs and
  tryfuncTM. All 17 original tracked functions stay exact. In lauxlib.c, keeping callalert out of line makes aux_do,
  lua_dobuffer and lua_dostring exact without losing the original 38. Each retained annotation identifies target
  callers; its spelling is reconstructed, not evidence for the original project's compiler command. Do not apply
  blanket noinline: singlevar must stay inline in funcname but out of line in prefixexp, and restore_stack_limit
  must stay out of line in lua_resume but inline in luaD_pcall.
- **Our middleware objects relink to CD2's exact image (2026-11-10).** `tools/relink.py --substitute src/middleware/`
  links all 77 of our objects in place of the split's units, and the image is identical (a `verify` gate). What the
  linker does with a whole object, learned on the way:
  - Each object's sections land in their order in the object: a file's strings sit just before the table that names
    them (lbaselib's function names before `base_funcs`), except a string the linker pooled with an earlier object's
    copy (`"Lua 5.0.2"`, `"k"`, `"__mode"` live with lapi.c's data).
  - CD2 keeps functions nothing calls (lapi.c's `luaA_index`): the libraries were linked whole, so our `/Gy` COMDATs
    need `/INCLUDE` against `/OPT:REF`. Identical functions stay apart (`/OPT:NOICF`): CD2 did not fold jcapimin's
    `jpeg_destroy_compress` into jdapimin's `jpeg_destroy_decompress`.
  - CD2 has several copies of some literals (`""` at 82001050 and 8216E274) and of some library functions (two
    `sprintf`: 82F1A300 for Lua, 8304878C for the game), so a mangled literal name or a library function name does not
    identify one address. The relink refers to what lies outside our units by address.
  - Data nothing references keeps its place: lapi.c's `lua_ident` (the copyright string) is at 8201FCC0.
  - jeff's own relocations hold 7 false ones in these objects (zlib's `crc_table` and libjpeg's dither matrix hold
    values that look like addresses); our objects have none.

## Traps
- **Never reach memory by pointer arithmetic.** If CD2 reads `lwz r3, 0x50C(r31)`, the source read a member at 0x50C:
  declare it in the class's header with a `CD2_OFFSET` check and use it by name, even if the best name you have is
  `m_word50C`. A global read from a fixed address is a declared global with a name and a type, so the relocation check
  can see which one it is. Downcasts and upcasts go through `static_cast` along the real base chain. Typed pointer code
  the original had (walking an array with `p + i` or `++p`, `end - begin`) is fine.
- **Do not distort correct source to improve a score.** A source change that raises the percentage without reproducing
  what CD2 does (moving an assignment before a call it follows, say) is not progress; revert it. If a change loses an
  exact match elsewhere, find out why before going on.
- The reference build (RuffKing) contains no-op trace markers `mr r13,r13` / `mr r14,r14`. CD2 has none. Ignore them.
- RuffKing names on *tiny* functions are often wrong: the linker merged identical functions (COMDAT folding), so a
  vtable slot can carry another class's name.
- CD2 was linked with a function order list: about the first 2 MB of `.text` (`0x821D0000`–`0x823D0000`) holds
  functions pulled out of their source files. A file's functions can be split between its main body and that region.
- Names in the CD2 disassembly were partly assigned by hand and may be inaccurate. Names with an `auto-name` comment
  come from exact matches and are reliable.
- IDA ends some functions early, so a target slice can lack its last words: after `bl atexit` (IDA treats `atexit` as
  no-return; every registrar initializer is affected) and after a tail-call `b` (the compiler's unreachable trailing
  `blr` is dropped). `tools/packets/build_cd2.py` extends over exactly those words. If a diff shows only extra trailing
  words on our side, read the bytes after the slice before chasing it.
- **Operand order of commutative float ops follows where the values are defined, not the source order of the
  operands.** Swapping `a * b` changes nothing. In `CalcRand*`, CD2's `fmuls f7, f8(rand), f11(max - min)` came only
  from `float r = (float)Rand(); float f = r * (max - min) * k + min;`, i.e. the conversion in its own statement.
- **Extract versus mask for single bits.** Testing a bit in place (`(x >> 12) & 1`, `x & 0x1000`, or a bitfield read)
  gives `rlwinm rD, rS, 0, 19, 19` (mask). Converting it into a `bool` or `unsigned char` local first
  (`bool b = ((x >> 12) & 1) != 0;`) gives `extrwi rD, rS, 1, 19`.
- **Reference builds can order bit flags differently.** cCharacterControllerComplex's three flag bytes (+0x300..+0x302)
  use the reverse of the later reference's declaration order within each byte; reversing the groups made all its
  predicates and SetIsInWater EXACT. Take each flag's bit from CD2's masks, not from the reference header.
- **Recomputed values come from repeated calls.** CD2 computing `size()` twice, with `srawi.` for the test and again
  after a store that may alias, means the source called `size()` twice. A local `n` computes it once. `srawi.` instead
  of a mask test came from an `unsigned` pointer-difference `size()` with `if (size() > 0)`.
- **Game code is LTCG** (`/GL` + `/LTCG`). Mark functions that are exact only under LTCG with `"ltcg": true` in
  `config/matched_functions.json` (`check --ltcg`). Most functions compile identically without it, but a function that
  loads float constants does so in CD2 through a base register pointing at the program-wide constant pool
  (`addi rN, 0x820F8C80; lfs f0, 0x84(rN)`). A plain compile emits one `lis` per constant instead and can never match.
- **LTCG limit: functions with many scattered float constants.** CD2's link-time codegen shares one base register
  between all constants within ±32 KB of the program-wide constant data, so a constructor that loads 14 constants may
  use three bases. The per-file LTCG model packs a file's constants close together and cannot reproduce that: such
  functions can only be confirmed in a full-program build (the `cHelicopterController` and `cFlocketPrototype`
  constructors, whose stores and values match).
- **The LTCG model sees only what the repository proves.** A callee's body can change the caller (ShowRopeSegments'
  frame is 16 bytes larger only when LTCG sees GDb::ConsoleOutput's body); the model links in another file's functions
  once they are matched. If a function differs only in its frame size or in which registers survive a call, match the
  callee first. Conversely, declare a template instantiation that another file owns (the `std::vector` reserve at
  0x826104B8) as external, or the single-file model specializes it.
- **The LTCG model can drop an unused `this`.** A virtual that never uses `this` (some `IsA` overrides) comes out of
  the model with its argument in r3 instead of r4 (21/23 words) when nothing in its file installs the class's vtable:
  LTCG then treats the virtual as a function whose callers it knows. In CD2 some constructor always installs it. The
  remedy is the file's own code: once a constructor or placement factory that installs the vtable is matched in the
  file (`Pedestrian::SpawnFromPrototype` for `Pedestrian::IsA`), the virtual comes out exact. Keeping the vtable as a
  link root (`/INCLUDE`) does not help. `check --ltcg` shows such a function as `PLAIN ONLY`.
- **`verify` also builds the whole program** (`py -I tools/verify_ltcg.py <exe> --whole`): every `/GL` game source
  in one `/LTCG` link, where each file sees every other file's bodies, matched or not. Every matched function must be
  exact there too. A function exact in `check` but not in the whole-program model differs because of a body another
  file gives LTCG: an inline the caller's file did not see, or a callee CD2 resolved elsewhere. Neither side wins
  automatically: find which declaration or body CD2 had (below), and when that stays open, mark the function
  `"matching": false` with a note naming the callee.
- **LTCG's inlining threshold depends on the size of the program.** c2.dll adjusts `-inlT` (104) by the IL size of
  the link (+32 up to 50,000, down to -24 above 2,500,000), so the same call is inlined in a small link and not in a
  large one. CD2's decisions fit only the smallest bracket's threshold (136): with c2's own threshold the
  whole-program model left the by-name `cCharacterInterface::AddEquipment`, several class-body destructors and
  `RetFirearmSkillLevel` out of line where CD2 expands them. Both models pass the threshold that gives 136 for their
  size (`verify_ltcg.inline_option`); it belongs to the model link only, never to `config/file_flags.txt`. Call-site
  counts are local estimates (a function's entry, half after a null check, ten times in a loop), not whole-program.
- **A Havok call CD2 makes out of line can name the derived class's function.** `hkWorldObject` declares its own
  `addReference`/`removeReference` (Havok's library copies at 0x82BD22E0 and 0x82BD2300), which hide
  `hkReferencedObject`'s inline `removeReference() const`. Called on an `hkRigidBody`, `removeReference()` must reach
  `hkWorldObject`'s: naming the base's inline gives the same per-file bytes, but the whole-program model then inlines
  the base's body (cTruck::RemoveWedge). The linker keeps an IL COMDAT over a native library copy of the same name, so
  a call CD2 makes into a library's copy of an inline cannot name an inline that some game file defines.
- **Which file a function belongs to is decided by its address, not by what it looks like.** Outside the order-list
  region the linker lays out each object's functions contiguously, so every function inside a file's range
  (`config/splits.txt`) was emitted by that file's object. That includes another class's inline or template functions
  and surviving copies of folded code. `tools/check_integrity.py` rejects claims outside the file's range.
- **A byte match is not enough: references must point where CD2's do.** The byte comparison masks call targets and
  addresses, so a call to the wrong function with the same signature still "matches". The gates resolve every
  relocation against CD2. A real case: the helicopter prototype's deleting destructor called `~CAttributeHandler`, where
  CD2 calls its intermediate base's destructor, because the stand-in base chain skipped a level. Model the real base
  chain rather than the shortest one that matches. Names that embed an address (`Ext_82954E48`) must be right.
- **Identical-code folding (ICF).** The linker folds byte-identical functions and vtables into one copy, so several
  classes can share one address (registrar data shows it for `MakeNew`). The folded copy belongs to the file whose
  range contains it, under the name of the class the source names (cProp's and cVehicle's UpdateRenderMatrix are one
  copy in cVehicle's code). Other files that define the same function mark their entry `"folded": true`, and the
  names go in `config/symbol_aliases.txt` with the evidence.
- **Tiny functions with the same shape** (`lis/lwz|addi/blr`) can be paired with the wrong one of ours by the diff tool:
  check by name and address, not only by the EXACT flag.
- **A function that `show` lists under `vtable` is a virtual: declare it `virtual`, in that slot.** The body compares
  the same whether it is declared virtual or not, and whatever slot it gets (`lbz r3, 0x22C(r3); blr`). Since
  2026-11-06 `check` and `verify` read the compiled name: a plain member function that CD2 has in a vtable is
  MATCH-PENDING (R13). They do not check the slot number. A two-instruction getter or setter with 0 direct callers is
  almost always a slot. Use the slot the class's header already declares (cVehicleController's
  `virtual void AssignVehicle(Vehicle::cVehicle *)`, slot 69). If the header does not declare the slots before it yet,
  leave the function open. The gate removed 46 earlier entries declared this way (cPlayer slots 92..130,
  cCwTransCharacter's accessors at character slots 391..445, and the script-type getters below). Three more came back
  as the `RetScriptTypeRegistration` overrides they are (cAiPlayer, cCharacterEntityIF and cCharacterInterface:
  cScriptHost slot 1, returning their own registrars). Exempt: a script method
  CD2 registers under the function's own name, whose code was folded with a virtual's (`cTimeOfDay::RetPeriod`,
  `cAIEvent::RetSource`, `cPlayer::IsAIActive`).
- **Check whose table it is before you name the class.** Compare the function's `vtable` lines with those of the class's
  own `RetClassName` (primary slot 11). If the function sits in other tables, or in many, it belongs to their common
  base or to a secondary base, not to the file's class. 0x826AB570 (`lbz 0x3601`) is in three small tables (0x82133A90
  and 0x82133AE0 are 0x50 bytes apart), not cTransformingCar's primary 0x8201B8D0, so its `this` is a base subobject
  and 0x3601 is counted from it. Likewise
  0x828583F0 is in three game-mode prototype tables, 0x82607C08 in 13 weapon tables and 0x824D42A8 in 13 NPC behaviour
  tables.
- **Do not pad a class out to a field's offset.** `unsigned char m_pad[0x2F0]; unsigned char m_field2F4;` in a
  STAND-IN header with no bases, or after a base whose header says its layout is incomplete (`AI::cMission`: real size
  0x3C0, "not an allocation layout"), states a layout CD2 does not have: the field belongs to a base (cAgencyATV's
  +0x2F4 lies inside cVehicle). Such a getter waits for the base chain. A field of a class with real bases goes into
  its existing `m_unmodelled` gap with a `CD2_OFFSET` line. Without that line, `int m_dword1110;` followed by
  `unsigned char m_bytes1115[4];` put the array at 0x1114 while its comment said 0x1115.
- **Decompiler pseudocode is not a draft to clean up.** Hex-Rays output (`a2`, `v3`, `*++v2 = *++v3`,
  `return (int)this`, `int p = seat->m_p; p - 28`) brings its integer-typed pointers in as R4 findings and compile
  errors. A constant subtracted from a pointer just loaded (`- 0x1C`) is a cast from a secondary base. Find the
  member's real type and write the cast or the accessor: RuffKing's `cVehicleSeat` holds
  `cSafeDeletablePointer<CHARACTER::cCharacter>` at 0x30 and 0x40. A name made from an address with its leading
  digits dropped (`RetCE3F0` for 0x826CE3F0) is still an address name; `lint` lists it.
- **Keep every file compiling; work one function at a time.** A file that does not compile takes every matched
  function in it out of `verify`, not only the new one: 21 unclaimed functions written into cVehicle.cpp at once took
  its 17 exact functions out of verify. Claim, write one function, `check`, and before stopping remove anything that
  is not exact or does not compile. A session can be cut off at any point.
- **`work/map.txt` needs substrings of MANGLED names** (`??__EcFooRegistrar@`, `??_9Base@NS@@$BBMA@AA`), not demangled
  text.
  For manifest/claim prefixes, include an adjustor thunk's offset code: `??_EcCheckpointArena@GameManagement@@WBI@`
  selects the +0x18-base deleting thunk, while the class-only prefix ending at `@@` deliberately excludes it.
- Listings: add `/FAcs /Fa<file>.cod` to see source lines interleaved with code and every compiler temporary's stack
  slot (`tv143 = 80 ; size = 8`); `dumpbin /disasm` on an object shows what was really emitted.
- A `switch` compiled to an inline jump table puts its data words in `.text` right after the `bctr`; the checker masks
  them as relocations and checks their destinations.
- In Git Bash, `cl /flag` arguments get path-mangled: `export MSYS2_ARG_CONV_EXCL='*'` first.
  `cl /d1reportSingleClassLayout<Class>` prints the layout and every vtable, including thunks.
- **Try source shapes systematically** with `cd2.py search`, or `tools/sweep.py <default.exe> <spec.py>` for named
  variants (example specs in `tools/research/compiler_re/sweeps/`).
- **Check a class's whole override set against CD2's table before trusting its header.** Several vehicle-chain
  headers carried override blocks generated from the wrong tables (cDynamicBody's from cProp's and cVehicle's,
  cVehicle's from cHelicopter's and cWeaponisedHelicopter's; their address comments were wrong too). Compute the
  slots where CD2's table differs from the parent's (CD2 IDB: cNonGameBase 0x8212CDC0, cGameBase 0x8212CA20, cBody
  0x8200C938, cDynamicBody 0x8200D058, cNetDynamicBody 0x82131E80, cVehicle 0x82015B40, cHelicopter 0x820168E8) and
  compare them with the slots `/d1reportSingleClassLayout<Class>` shows as the class's own. A wrong override stays
  invisible until a derived constructor emits the table; then it is WRONG DATA. Slot ranges of that chain:
  cNonGameBase 0..67, cGameBase 68..140, cBody 141..226, cDynamicBody 227..303, cNetDynamicBody 304..313,
  cVehicle 314..441.
- **Renaming a placeholder virtual also renames its alias.** `config/symbol_aliases.txt` lists mangled names
  (`?vf304@cEquipment@Equip@@UAAXXZ`); after a rename the old spelling no longer exists and the data check reports
  the shared body "referenced under several names". Respell the alias in the same change, and rename only within
  the hierarchy that owns the slot (cCharacter's or cGrenade's `vf418` is another class's slot 418).
