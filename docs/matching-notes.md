# Matching notes: compiler behaviour and traps (Crackdown 2, XDK 15.00.8153)

Read this before starting a file. It is a catalogue of reusable mechanisms: a source shape and the code it produces, or
a trap and how to recognise it. Add an entry only for a mechanism you showed with an A/B test (one source change, one
codegen change) that will help with other functions. What you tried on one function goes in "Open functions" at the
end, in one line, and is removed when the function matches. History belongs in git, not here.

## Shared bases
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
- `Fun_Runtime::RetVal` results (`Init`, `Term`, ...) come back through the hidden pointer, r3, with `this` in r4.
  `Ret_OK` (0) and `Ret_FAIL` (-1) are namespace-scope `const RetVal` objects, one copy per file: Ret_OK in .bss,
  Ret_FAIL in .data, no initializer code. The compiler loads them rather than folding (`include/fun_runtime/retval.h`),
  so a "global" a small function copies into `*r3` is usually the file's `Ret_OK`. The relocation check treats names
  with internal linkage per file.

## Codegen idioms
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
- **The LTCG model can drop an unused `this`.** A virtual that never uses `this` (some `IsA` overrides) can come out of
  the model with its argument in r3 instead of r4 (21/23 words): a limitation of the model, not of the source.
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
- `cGameModeArena::GetRandSpawnPointInList<T>` (0x8284EC80, 0x8284ED60; 48/55 words): CD2 tests the size with
  `srawi. r8,r10,2; beq`, then recomputes it for the `Rand` argument. Ruled out: a size local, const-reference or
  64-bit bounds and indices, real `std::vector` indexing, modulo and Rand-local variants.
- `VEHICLE_CONTROL::Flatten2D` (0x82782D70; 16/29 words under LTCG): the `fmadds`/`fmuls` operand order. Ruled out:
  square temporaries, sqrt and powf variants, signed products, double intermediates, /fp:precise and /fp:strict.
- `AI::cChaseBehaviour::Update` (99%): one compare, `cmpwi` in CD2 against our `cmplwi` on the word at `+0x4E4`; the
  field's type is the lead. Chase F37 (0x824CEB38) needs a shared float-constant base register (LTCG limit).
- `CHARACTER::cCharacterInterface`'s prototype `MakeNew` (0x8254E810): exact with a nested
  `cCharacterInterfacePrototype : GOM::cObjectPrototype` and `return new cCharacterInterfacePrototype(attr);`, but its
  secondary vtable is another name for the shared 0x821327A4 table and needs an alias entry.
- `cPedestrianBase::IsA` (0x824A90F0) and `Pedestrian::IsA` (0x824A8D60): exact in a plain build, 21/23 words in the
  LTCG model (see "The LTCG model can drop an unused `this`").
