# Matching notes: compiler behaviour and traps (Crackdown 2, XDK 15.00.8153)

Read this before starting a file. It is a catalogue of reusable mechanisms: a source shape and the code it produces, or
a trap and how to recognise it. Add an entry only for a mechanism you showed with an A/B test (one source change, one
codegen change) that will help with other functions. What you tried on one function goes in "Open functions" at the
end, in one line, and is removed when the function matches. History belongs in git, not here.

## Shared bases
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

## Codegen idioms
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
  - A constructor with about 20 stores, or a chain of in-class constructors (CAttributeHandler, base, derived with an
    embedded handler), is not inlined into `MakeNew` unless each is `__forceinline`. A loop helper CD2 inlines
    (`AIDamageCache::Read`) also needed it.
  - In-class virtuals called qualified (`Base::OnVFXFinished()`) are inlined.
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
  in two 64-bit registers (`ld r4 / ld r5`).
- String-id hash (inlined `GetStringID`): `int mult = <chain>; int id = 0; for (char c = *s; c != 0; c = *++s)
  id = id * mult + c;` with `mult` declared before `id`.

## Patterns by kind of function
- **Class-factory registrar** (an initializer near 0x82F.., 76 bytes, and its at-exit destructor near 0x830..):
  `static RWS::CClassFactory::CRegistrar <Class>Registrar("<name>", <Class>::MakeNew, <size>, false);` in the class's
  namespace. The size argument is the class's size; the `MakeNew` it passes often builds the class's prototype.
  Identical `MakeNew`s are folded, so several registrars may pass one address (`config/symbol_aliases.txt`).
- **`MakeNew`:** `return new X(packet);`, or `new X()` when the constructor gets only `this`. The class's own code starts
  at its `RetClassName` (lis/addi/blr returning the class name).
- **`SpawnFromPrototype(proto, mem)`:** `if (pMem) return new (pMem) X(); return 0;` when CD2's constructor takes no
  arguments (RuffKing's often takes the prototype).
- **`RetClassName`:** returns the class-id string; define `static const char *const pcXClassID = "X";` in the `.cpp`
  (constant-folded to lis/addi, no load).
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
- **`work/map.txt` needs substrings of MANGLED names** (`??__EcFooRegistrar@`, `??_9Base@NS@@$BBMA@AA`), not demangled
  text.
- Listings: add `/FAcs /Fa<file>.cod` to see source lines interleaved with code and every compiler temporary's stack
  slot (`tv143 = 80 ; size = 8`); `dumpbin /disasm` on an object shows what was really emitted.
- A `switch` compiled to an inline jump table puts its data words in `.text` right after the `bctr`; the checker masks
  them as relocations and checks their destinations.
- In Git Bash, `cl /flag` arguments get path-mangled: `export MSYS2_ARG_CONV_EXCL='*'` first.
  `cl /d1reportSingleClassLayout<Class>` prints the layout and every vtable, including thunks.
- **Try source shapes systematically** with `cd2.py search`, or `tools/sweep.py <default.exe> <spec.py>` for named
  variants (example specs in `tools/research/compiler_re/sweeps/`).

## Open functions
One line each: what is ruled out. Remove the line when the function matches.
- `AI::cPedestrianBase` destructor pair in Pedestrian.cpp (0x824A8E68 deleting, 0x824A8EB8 body): the deleting wrapper is shared by cPedestrianBase, Pedestrian and PedestrianGuard (slot 0 of 0x8200B1F8, 0x82108DB0, 0x8200AE78), so 0x824A8EB8 is the implicit `~cPedestrianBase` (Pedestrian.obj's COMDAT copy; it tail-calls `~cNonGameBase` 0x826536C8), not `~Pedestrian`. With implicit destructors `??_GPedestrian` is plain EXACT and the body LTCG EXACT, but the single-file LTCG model inlines `~cPedestrianBase` into `??_GPedestrian` (5/20 words) where CD2's whole-program build kept the call; left out until the model sees its other callers.
- `PHYSICS::cSurfaceProfile::MakeNew` (0x82695F98), `VFX::cVFXSurfaceProfile::MakeNew` (0x827CCBD0), `unknown::cOutlines2::MakeNew` (0x827A4000): recovered cNonGameBase hierarchy gives EXACT deleting wrappers and IsA methods, but factories retain this in r31 instead of using the base constructor's return in r3 under plain and standard LTCG builds (same cross-module constructor-return issue as the crowd/streaming factories).
- `GameManagement::cGameModeSpawnPoint::MakeNew` (0x8284D6F0): identity-matrix initialization has the correct stores, but misses CD2's matrix-address calculation; an inline `SetIdentity` helper, including its reference return, and standard source search did not restore it. Destructor is EXACT.
- `Prop::cGasCanister::MakeNew` (0x82743708): reconstructed the prototype's identity matrix and defaults; forcing the constructor inline restores its stores, but plain and standard LTCG checks remain 32.8% because the constant loads and scheduling differ. Standard source search found no improvement. Moving the scalar defaults into the constructor body and routing matrix construction through the reference SetIdentity helper produce no codegen change (both experiments reverted).
- `Billboard::BillboardData::HandleAttributes` (0x829115D0): recovered resource-map lookup and event-string assignments; the standard compile inlines string construction where CD2 calls it, while CD2 inlines GUID-map insertion and stores the GUID where the shared header still calls AddEntityToMap.
- `UI::ApplyGamma` (0x82897B38): the recovered `(32 - float(value - 1)) * 2 * 0.03125` formula folds the two multipliers together even under the standard LTCG model; CD2 retains both multiplies and multiple constant bases.
- `UI::cUIControl::~cUIControl` deleting wrapper (0x82897FF8; 24/32 words): corrected the Load/Save-only secondary interface and inlined the destructor; the save-manager load still follows the vptr stores, unlike CD2. A local manager copy and both singleton/unregister statement orders do not resolve it.
- `UI::cUIControl::cUIControl` (0x82897EC0): restored options registration and the 3-second autosave display default; the standard compile still saves registers for its scattered float constants and schedules the callback stores differently.
- `cGameModeArena::GetRandSpawnPointInList<T>` (0x8284EC80, 0x8284ED60; 48/55 words): CD2 tests the size with
  `srawi. r8,r10,2; beq`, then recomputes it for the `Rand` argument. Ruled out: a size local, const-reference or
  64-bit bounds and indices, real `std::vector` indexing, modulo and Rand-local variants, an early-return size test,
  a result local, a signed `operator[]` index (no change) and a signed `size()` (worse). The instructions and their
  order are identical; only the allocator's choice differs (CD2 reuses r9 for the data pointer, ours takes r4).
- `VEHICLE_CONTROL::Flatten2D` (0x82782D70; 16/29 words under LTCG): the `fmadds`/`fmuls` operand order. Ruled out:
  square temporaries, sqrt and powf variants, signed products, double intermediates, /fp:precise and /fp:strict. The
  written order of the two sums makes no difference (/fp:fast reorders them and merges the second into the first),
  nor does testing the stored `out[]` values, declaring `x` before `z` (worse), or /fp:precise or /fp:strict with
  either order (worse), `#pragma optimize("g", off)` (0%), `__fsqrts` or a double `sqrt` (no change), inline
  helpers reading `out[]` (worse), and a length helper in another file under LTCG (not inlined under /Ob1). CD2
  computes the two sums separately, in opposite orders. Best lead (91.7% by objdiff): `if (normalise && x * x + z * z
  < 0.01f) { zero } else if (normalise) { normalise }`. The square-root sum is then not available on every path, so it
  is computed again exactly as in CD2. But our build, plain or LTCG, keeps the second `normalise` test, which CD2 does
  not have, and the test squares z first where CD2 squares x first. Also ruled out: by-value and struct-copy
  helpers, a three-component length with y = 0 (loses the fmadds), a conditional expression for `inv`,
  /O1, /O2, /Os.
- `AI::cChaseBehaviour::Update` (99%): one compare, `cmpwi` in CD2 against our `cmplwi` on the word at `+0x4E4`; the
  field's type is the lead. Chase F37 (0x824CEB38) needs a shared float-constant base register (LTCG limit).
- `cCrowdZoneDataHolder::MakeNew` (0x8244A770) and `cStreamingDataHolder::MakeNew` (0x8244C010): `new` of a
  field-less cNonGameBase whose constructor CD2 inlines, then stores the vptrs through r3, the base constructor's
  return value. That is cross-module LTCG inlining (CD2 knows the constructor returns `this`); a plain compile keeps
  `this` in r31 even with `__forceinline`, and the LTCG model does not inline the constructor.

- `AI::cAiPlayer` physical virtual slot 62 (0x823E7A38): two `RetCharacter()` calls around a null guard collapse to one load and 12 instructions instead of CD2's 18; the second safe-pointer conversion needs original helper evidence. Probe reverted.
- Patrol-event factories (`cFreakExplodeEvent`, `cFreakSniperEvent`, `cReaperJumpEvent`, `cReaperPropAttackEvent`): corrected shared RWS bases and the 0x90-byte layout; still 5 extra instructions because CD2 uses the return of cBasePatrolRouteEvent's constructor directly, while the standard build retains this in r31. The base constructor at 0x824BFA80 is not in a scaffolded split, so it cannot be promoted as a matched LTCG dependency.
- Shader deleting destructors (representative 0x82791E38): an out-of-line singleton-clearing destructor gives
  19.2%; an inline destructor is not emitted without a construction/vtable use. Do not add an artificial use to
  emit it. Shader constructors also encode an object-derived integer ID; recovering that interface is separate
  work under R4. Destructor probe reverted; the 38 callback/getter pairs are promoted independently.
- Runtime inheritance registration: 133 more 104-byte initializers match using the shared cInheritanceRegistrar.
  The remaining 12 in this family need individual missing parent/child type and hierarchy recovery; the two
  cVector push_back calls followed by RecursivelyAddParent are already identified.
- Spawning-registration remainder: the distinct 80-byte cGrappler initializer (0x82FD3740) needs its missing class/base declarations recovered. All 117 initializers in the 72-byte family are EXACT; their atexit functions are outside claimable scaffolded splits.
- Equipment hierarchy follow-up: CD2 constructors confirm cEquipment : cNetDynamicBody + cStateMachine,
  cWeapon : cEquipment, cCWWeapon/cGrenade : cWeapon, cCWHeavyWeapon : cCWWeapon,
  cCloakingDevice/cExplosiveGrenade : cGrenade, and cCWSatchelCharge : cExplosiveGrenade. The explosion callback
  is at +0x9C0 in cExplosiveGrenade. These shared declarations unlocked 13 more inheritance initializers and the
  final 3 spawning initializers. Descriptor bodies at 0x822E5B60/0x8262FE78 are outside claimable scaffolded splits;
  keep their declarations and do not put their bodies in a neighbouring source file.
- Script metadata getter lead (38 registered script-type objects, 81 name strings and 2 other pointer targets
  in a scan of 121 12-byte global-address getters): representative 0x824556F8 returns
  the 0x24-byte object initialized by 0x82F85E30 through 0x82772828 with child/parent script-type names. This is
  cScriptHost virtual slot 1, currently unnamed; recover the shared metadata interface and actual class ownership
  before adding more getters. Do not copy the historical byte-global/GetPtr stand-ins to other game classes.
- Class-query batch: 64 class-name getters and 26 RetClass descriptor getters are EXACT. Classification needs
  both target data and virtual-slot evidence: name strings at primary slot 11 identify RetClassName; descriptor
  loads at registered-class slot 0 identify RetClass. The same three-instruction size also includes script metadata
  and enum-name getters; it does not establish ownership or return type by itself.
- Sim::cTimeOfDay::RetClassName (0x82773BF0): adding a virtual to the historical field-only stand-in shifts its
  checked phase offset. Recover its actual C++ bases before adding the getter; probe reverted.
- IsA batch: cCrowdZoneDataHolder (0x8244A810) is EXACT in plain and LTCG builds. The former
  cFactionConfigData attribution at 0x82676298 was removed: IDA identifies cFactionInfo instead. cRefractor (0x826105F0) and the existing FreakBase body (0x824ABBB0) are plain EXACT but 21/23 under
  LTCG without a live vtable; do not promote them. cCharacterInterface (0x8254E7B0) has EXACT instructions in both
  builds but conflicts with its constructor's distinct g_GlobalConstants target (0x830ACBD8 versus 0x830C0E04).
  The new cRefractor/cCharacterInterface probes were reverted; FreakBase's pre-existing body is unchanged.
- Placement-factory batch: 26 guarded 24-byte factories are EXACT in both builds using placement new and the
  CD2 constructor ABI that takes only this. Later reference constructors take a prototype argument, but the CD2
  factory does not forward one. Constructor chain evidence restored the shared AI and equipment bases; the
  cNPCArmourySetup attribute tag is an empty global type in RuffKing, not an invented padding base.
  cHelicopter (0x826B8AE0), cLandVehicle (0x826C0E20), and the remaining vehicle factories require further shared
  vehicle-base recovery; their new probes were reverted rather than relying on the historical flat stand-ins.
- Descriptor ownership correction: 0x82676288/0x82676298 read the cFactionInfo descriptor (ID 1038, size 0x220),
  installed by cFactionInfo's constructor 0x826766E0 at +0x14. They are not cFactionConfigData methods; the prior
  misattributed IsA manifest entry and source were removed. Likewise, 0x82676DB8 belongs to cGangInfo,
  0x827FA5E0 to cLinkedVFXSpawner and 0x82802398 to cBeamManager. Do not name folded helpers after the source file.
  Six further RetClass getters with confirmed matching descriptor names are promoted independently.
- Script metadata classification: 0x82772828 registers both game-class and AI-event descriptors. Getter ownership
  must follow the registered child name: for example 0x824D82C0 is AIE_SQUAD_TARGET, not Squad;
  0x82676318 is AIE_GANG_ENFORCER_LEVEL_CHANGED, not cFactionConfigData. The descriptor getters in the
  equipment, camera, hinged-prop and world-manager files remain candidates once the shared metadata interface
  is recovered. Targets 0x834146C4 and 0x82274520 are not registered script-type objects in this scan.
- Prototype Init batch: 18 slot-5 CAttributeHandler::Init overrides return the file-local Ret_OK object and
  check EXACT in plain and LTCG builds. Prototype ownership comes from the MakeNew constructor that installs
  the table. Shared interface declarations follow the reference prototype chain from cNonGameBase/cGameBase
  through cBody/cDynamicBody and equipment/weapon/grenade variants. These declarations do not establish
  instance fields or allocation sizes; do not use their incomplete sizeof values in factories.
  Remaining candidates need vehicle/character prototype recovery or reconciliation of the existing namespace-level
  cHWProjectilePrototype with the reference nested type; do not create a second definition for it.
  Follow-up: 14 additional prototype Init overrides are EXACT in plain and LTCG builds, using the recovered
  vehicle prototype interface chain and constructor-confirmed equipment, character and prismatic-prop bases.
  Where no reference names a prototype, its descriptive name is explicitly ours. These interface declarations
  do not recover complete instance storage. The remaining BeaconMission slot-5 body increments a halfword,
  rather than returning Ret_OK; the heavy-projectile nested/namespace-level type conflict remains unresolved.
- Mission inheritance batch: 8 additional 104-byte initializers are EXACT in plain and LTCG builds after
  restoring cMissionBase's standalone mission interfaces, cMission, and the child mission bases. Shared Load/Save
  declarations now live in SaveGame/cLoadSaveObject.h; the UI interface is unchanged. Named inherited-field checks
  establish the mission interface offsets, not the complete instance storage or sizes for allocation. Those fields
  and the pre-existing constructor/factory WIPs still require individual recovery.
- Script registrar batch: 41 typed registrars give 82 EXACT initializer and cleanup functions in plain and LTCG
  checks. CD2 0x82772828 constructs their 0x24-byte descriptor with child/parent names and two lists;
  its base table has two slots (destructor and method registration). The following table belongs to
  a method wrapper, not a third registrar virtual. The template name is ours. Ten concrete tables
  fold to 0x82100494; the initializer stores establish the alias group. The remaining 135 descriptors
  need their event/standalone C++ types identified before instantiating this template; do not invent tag types.
- Split follow-up: newly owned shared-base methods add 14 EXACT StaticCreateClass bodies, 14 class-pointer
  initializers and 10 registered-class RetClass getters. CD2 descriptor names/IDs/sizes and slot-0 tables
  establish ownership. Initializer 0x82FDFAE0 belongs to cDynamicBody, correcting its old cBody attribution.
  cVehicle/cInterestingObject still need actual instance bases before adding virtual getters to their stand-ins.
  cGameBase::RetClass (0x824CDC40) and cScriptHost::RetClass (0x823E5800) are byte-exact probes but lie
  outside both the order-list region and their classes' cold ranges; excluded until their surviving COMDAT
  copies' actual source ownership is established. Do not disguise cold code as a hot split entry.
- Folded-table follow-up: cGasCanister's constructor (0x82743828), cLaunchPadTargetLocation's constructor
  (0x82714450) and BillboardData::MakeNew (0x82911410) are promoted after declaring their observed inherited
  vtable aliases. The gas-canister factory and Billboard attribute handler remain partial.
- `VFX::cBloom` destructor (0x827919B8, 76.5%; LTCG 17/34) and MakeNew (0x827918C8, 19.5%): body `g_pBloom = 0;
  UnLinkMsg(RWS::iMsgRunningTick);` has the right instructions, but CD2 stores the primary vptr first and the global
  between the +0x30 and +0x38 vptr stores; `search` found nothing. Deleting destructor and IsA are EXACT.
  `Audio::cVOAScheduler` destructor (0x82837050, 35/36 words) has the same symptom: CD2 restores cDebugPageHandler's vptr
  before clearing ms_pInstance. Defining the global in its own file (as RuffKing does) changes nothing in either.
- cCWSatchelCharge's second base at +0x9D0 is unidentified (table 0x82123C68: methods creating, releasing, showing
  and hiding a handle at +4 registered with the manager at 0x83800958+0x6C); it blocks the cProxMine destructor and
  the cStickler/cMag factories. cBeaconProp's second base at +0xE40 (table 0x82103E08, 5 slots, own deleting
  destructor 0x8269B7D8) blocks its constructor 0x8245C470.
- `AI::Scrounger` constructor (0x824BABB0): FreakBase's constructor then `m_eAttackBone(eSB_RightHand)` (RuffKing, at
  0x120); the size check needs FreakBase 16-byte aligned, i.e. the flat NPCBehaviourSM stand-in rebased on NPCBehaviour.
- Script metadata getters: 17 further cScriptHost slot-1 getters are EXACT in plain and LTCG builds using the
  existing typed script registrars. `RetScriptTypeRegistration` is our descriptive name; the returned objects are
  the 0x24-byte descriptors constructed by 0x82772828, not runtime cClass objects. Manager constructor/destructor
  evidence recovers cCameraManager : cNonGameBase and cScriptManager/cZoneManager/cWorldManager : cNonGameBase,
  cDebugPageHandler (+0x7C); their later reference builds can have different bases. Remaining flat stand-ins need
  their own hierarchy recovery before adding overrides.
  Follow-up: the remaining three candidates (cVirtualCamera, cStaticInterestingObject and cPopulationZone) also
  check EXACT in both builds. CD2's constructors establish cVirtualCamera : cGameBase, cDebugPageHandler (+0x120),
  cInterestingObject : cScriptHost (size 0x40), cStaticInterestingObject : cInterestingObject, CAttributeHandler
  (+0x40), CEventHandler (+0x58), and cPopulationZone : CAttributeHandler, cZone (+0x18). cZone is a cScriptHost
  plus a narrow cStringc at +0x1C, size 0x38. The latter two classes are standalone script objects rather than
  members of the cNonGameBase hierarchy. Their two inheritance registrations are independently EXACT.
- Allocation-factory follow-up: 14 more guarded 68-byte factories are EXACT in plain and LTCG builds, using the
  observed allocation size and an out-of-line constructor declaration. Unrecovered instance fields stay opaque;
  allocation sizes are checked against both the factory and descriptor/registrar, not inferred from the bases.
  cNetGameAISpawnPoint and cNetGamePickupSpawnPoint call the shared cNetGameSpawnPoint constructor (0x8284D908).
  cRenderToTextureManager calls cNonGameBase. cVOAScheduler needs its real HandleEvents override declared to be
  concrete. cCameraManager/cCharacterAnimSetManager/cRenderToTextureManager IsA probes remain 21/23 under LTCG
  without their destructor definitions and were reverted at that stage. cGenVehicleProfile::IsA is 23/23 under
  LTCG with its reference's inline destructor declaration. See the manager-cleanup follow-up below.
- Manager cleanup follow-up: cZoneManager's destructor, deleting wrapper, IsA and six interface thunks are EXACT
  in plain and LTCG builds. The pointer at +0x80 owns the population-zone pool; its observed table starts with
  cDebugPageHandler's registered-class entries and destructor slot 2. cPopulationZonePool is our descriptive
  interface name, not an allocation layout. cRenderToTextureManager's IsA, deleting wrapper and three thunks are
  also EXACT after recovering its eight-byte POD vector at +0x88; the element/field names are ours. Destructor
  0x827A9EA8 remains 26/35 words because CD2 interleaves its singleton clear with vptr restoration and the vector
  load; search found no improvement. cCameraManager uses the shared pointer-list destructor at +0x7C and +0x160,
  unlinks iMsgRunningPostTick/iMsgPausedPostTick, and clears its singleton; the inline cleanup makes IsA EXACT
  under LTCG, but its deleting wrapper is not emitted without its constructor body.
- cGenVehicleProfile's constructor restores the 26-entry VFX array to -1, clears the four 12-entry damage arrays,
  and sets the AI gear-change ratio to 0.6. Attribute cases distinguish the reference-named arrays. The typed
  constructor has the correct loop bodies but keeps this in r31 rather than the base constructor's returned r3;
  search found no improvement. Its deleting destructor and three adjustor thunks are independently EXACT in both
  builds with the constructor body present; the constructor itself is not promoted.
- `VFX::cParticleEffectResourceHolder`: RuffKing's cParticleEffectResource.h contains this class too; CD2 confirms
  cNonGameBase, a cVector<const char *> at +0x7C and priority at +0x8C. RetClass, IsA and the deleting wrapper are
  EXACT. Destructor 0x827EEB98 is 45/50 words (five register differences in the repeated vector size test);
  MakeNew 0x827EDB88 retains r31 where CD2 uses the base constructor's r3. Default versus packet constructor
  signatures and search do not resolve either. Descriptor factory 0x82349300 and initializer 0x83009930 are
  outside the scaffolded split, so their bodies remain undefined here.
- Network spawn-point cleanup: cNetGameSpawnPoint's destructor and deleting wrapper are EXACT in both builds
  with the reference-named arena string at +0x60 and arena index at +0x7C. Its constructor (0x8284D908) remains
  partial: CD2 retains a matrix-address calculation absent from the typed identity initialization; search and
  an inline SetIdentity helper do not improve it. cNetGameAISpawnPoint's RetClass, IsA and deleting wrapper,
  plus cNetGameAIVehicleSpawnPoint's RetClass and IsA, are independently EXACT. An implicit AI-spawn destructor
  omits the derived primary-vptr restoration; declaring an inline empty virtual destructor adds precisely those
  three instructions. The shared GUID-handler guidance is therefore not universal. The AI constructor and
  vehicle factory retain r31 where CD2 uses the base constructor's returned r3; search found no improvement.
- cScriptManager's deleting wrapper is EXACT in both builds. Constructor/destructor evidence establishes
  32 cStringc entries at +0x80 and the search-path vector at +0x418. Destructor 0x827705D8 remains partial:
  the compiler's vector-destruction helper passes allocator/tag arguments absent from CD2's two-argument helper,
  and the stack frame and singleton/vptr scheduling differ. Standard and Fun_Runtime allocators and search
  do not resolve this. Its RetClass/IsA targets are outside the scaffolded split and remain declarations only.
