# Shared notes: non-obvious compiler behaviour and traps (Crackdown 2, XDK 15.00.8153)

Append to this file whenever you learn something that wasn't obvious. Keep each entry short: pattern, then cause or fix.
These notes are shared knowledge for every agent and person working on the decomp. Read them before starting a file.

Note: the repo headers already include the cNPCTintProfile fixes below (inline accessors in `rws/attributes.h`,
`cd2/memory.h`, `rws/classfactory.h`, `editor/guid_event_handler.h`). Workarounds such as defining accessors inline
in a `.cpp` are no longer needed.

## Shared bases (2026-10-24)
- **Every game object is a cNonGameBase** (`include/gom/non_game_base.h`; constructor 0x82653588, 48 callers):
  - CAttributeHandler at 0;
  - RWS::CEventHandler at 0x18 (6 slots);
  - Fun_Runtime::cSafeDeletable at 0x1C (6 slots in CD2);
  - Fun_Runtime::cRegisteredClass at 0x30 (RetClass, IsA);
  - Network::cNetRoleObject at 0x38 (6 slots);
  - 0x7C bytes in all, with 68 primary slots.

  Projectiles and equipment reach it through cGameBase (constructor 0x82650610).
- **Every prototype is a GOM::cObjectPrototype** (`include/gom/object_prototype.h`; constructor 0x82654118, which takes the packet only): ResourceManager::cStreamingResourceClient at 0x18, 0x70 bytes. Its client vtable 0x821327A4 is shared by every derived prototype (ICF).
- Before the batch files were unified, cRopes, chase, the helicopter and the flocket each had their own stand-ins for these bases, with different slot guesses: one put RetClass and IsA in the 0x1C base, another counted them as primary slots. The byte comparison cannot see this, since vtable contents are not compared.
- **To identify a base**, use these four checks:
  1. Follow the constructor chain to an out-of-line base constructor that other classes also call.
  2. Compare the slot count of each secondary vtable: it is the base's, exactly.
  3. Read the base's own vtable, stored by the inlined base constructors before the final vptrs. Pure slots are `_purecall`.
  4. Name slots from the reference builds only where CD2's bodies agree (`RetUniqueID` returns `m_nUniqueID`; slot 4 returns `"Unnamed Non-Game Object"`).
- `Fun_Runtime::RetVal` results (`Init`, `Term`, ...) come back through the hidden pointer, r3, with `this` in r4. `Ret_OK` (0) and `Ret_FAIL` (-1) are namespace-scope `const RetVal` objects, one copy per file. Ret_OK is in .bss and Ret_FAIL in .data, with no initializer code. The compiler loads them rather than folding (`include/fun_runtime/retval.h`). The relocation check therefore treats names with internal linkage per file.

## Codegen idioms (known so far)
- `x ? true : false` and `x != 0` compile identically. A *materialised* bool (`addic/subfe` or `subfic/subfe/and`) comes from a bool local kept live across calls: `bool ret = true; ... if (!f()) ret = false; return ret;`.
- Constants used after calls get hoisted into non-volatile registers (e.g. `li r29,1`). That changes the save helper (`__savegprlr_29` vs `_30`) and shifts every later instruction.
- Branch layout follows source order: the order of if/else arms and of early returns matters. A `switch` produces different code from an if-chain, and the case order/default placement matters.
- Byte swizzles only produce `rlwimi`/`inslwi` for particular expression shapes, e.g. `(x>>24)|((x>>8)&0xFF00)|((x<<8)&0xFF0000)|(x<<24)`. Write `HIBYTE(x)` as `(unsigned char)(x >> 24)`.
- Calling virtual slot N needs the class to declare N virtuals before it. Use the real headers in `include/` rather than dummy virtuals where possible.
- Returning through one local result variable merges stores.
- Static-local guards: `flag & 1` test on a global, then `flag |= 1`.
- Stack slots: locals are ordered by SIZE ascending (smaller nearer sp), ties by first appearance, not by declaration order (shown in `cArenaLinker::GetArena`, where unknown struct sizes could be fitted this way). The compiler may reuse a slot when lifetimes don't overlap, and the target sometimes keeps them separate.
- With `/fp:fast`, `a*b+c` becomes `fmadds`.
- **Evaluation order around calls.** In `global == f()` MSVC makes the call first and loads the global after it; to load it before (`lwz r29, global` then `bl`), copy it to a local first. A field re-read (`i += m_nCount`) and a local copy (`i += n`) give different operand orders.
- **Return types shape the caller.**
  - A virtual returning `unsigned int` is tested with `cmplwi`, `int` with `cmpwi`, and `bool` adds `clrlwi`.
  - A helper's return-struct SIZE changes the caller's frame (a 4-byte struct gave 0x80, a 16-byte one 0x90).
  - A forwarded `return p->Virtual();` passes the hidden return pointer straight through only when the return type has a constructor; a POD goes through a temporary.
  - A hidden-return temporary passed directly to another call (`f(a, b, sub->GetInfo())`) avoids the copy a named local adds.
- **Template helpers need `inline` under `/Ob1`**, or they stay calls.
- **Multiple inheritance.**
  - A function that lives only in a non-primary vtable is compiled with `this` = that subobject (no thunk). Helpers it calls must be members of that base, or you get `addi -N` plus a null check.
  - Mangled adjustor-thunk names encode the offset (`WPA@` = -0xF0), so a stand-in base chain that regenerates them byte-exact is a free layout check.
  - Read subobject offsets from the consecutive vtables in `.rdata`: a table starts where an adjustor thunk for the next subobject begins.
- **`__declspec(novtable)`** on a polymorphic second base removes the dead vptr store its constructor would add. It is probably an abstract interface in the original.
- **Pointers to virtual members** (`&C::Slot`) make the compiler emit 16-byte `vcall` thunks (`??_9C@@$B...`), named after the class that declares the slot.
- **Downcast from a base subobject:** `static_cast<P*>(basePtr)` gives `cmplwi; addi -0x1C; bne; li 0`; `X *x = xs ? static_cast<X*>(xs) : 0; if (x) ...` gives the jump-threaded form.
- **Member initialization order.** Members with default constructors (e.g. `Vec3`) are initialized in declaration order before the body. To match CD2's interleaving, put scalar fields in the mem-initializer list too; body assignments come after all of them.
- **`Vec3` passed in a vector register** (`lvx128 v1` before a call) means a `__vector4` parameter: `union { __vector4 v; struct { float x, y, z, w; }; }` with the copy constructor `v(o.v) { x = o.x; w = 0.0f; y = o.y; z = o.z; }`, including `<ppcintrinsics.h>`.
- Bool from `||`: `return a == b || f();` (or `bool r = a || b; return r;`) gives the branchy `li 0 / bne / li 1 / clrlwi`. `if/return true/return false` folds into `beqlr` + `li r3,1`; an `unsigned char` local tested with `!= 0` adds `clrlwi; addic; subfe`.
- Constructor called with only `this` (r4 untouched) means the constructor takes no packet argument: `MakeNew` is `new X()` / `new X`, even though `MakeNew` itself receives the packet.
- Inline constructor store order follows the order of assignments in the BODY, not member declaration order.
- `/Ob1` and chained in-class constructors: a chain (CAttributeHandler, then base, then derived with an embedded handler) needed `__forceinline` on each in-class constructor before CD2's inlining into `MakeNew` was reproduced. Single plain in-class constructors were inlined without it.
- A `short` member passed to an `int` parameter (`f(m_nHandle)` with `void f(int)`) gives `lhz` + `extsh`; a `short` parameter loads straight into r3 and shifts the scheduling.
- Signed versus unsigned compares follow the expression type exactly: `cmpwi` against a byte-swapped value needs `(int)rwSwap32(x) == 1`.
- Inlined MSVC 2008 STL: `std::string::c_str()` is `res >= 16 ? ptr : buf` (that arm order); vector `erase`/`clear` inline `memmove_s` from `<string.h>`; vector code matching CD2 needs `#define _SECURE_SCL 0` before any STL header.
- GUID lookups go through `Editor::cGUIDLinker<T>::LinkToObject` (`include/editor/guid_event_handler.h`): static in CD2, copies the GUID from a const reference into a local, then calls the static `FindEntityInMap` with its address.

## Traps
- The reference build (RuffKing) contains no-op trace markers `mr r13,r13` / `mr r14,r14`. CD2 has none. Ignore them.
- RuffKing names on *tiny* functions are often wrong: the linker merged identical functions (COMDAT folding), so a vtable slot can carry another class's name.
- CD2 was linked with a function order list: about the first 2 MB of `.text` (`0x821D0000`–`0x823D0000`) holds functions pulled out of their source files. A file's functions can be split between its main body and that region.
- Names in the CD2 disassembly were partly assigned by hand and may be inaccurate. Names with an `auto-name` comment come from exact matches and are reliable.
- IDA ends some functions early, so a target slice can lack its last words: after `bl atexit` (IDA treats `atexit` as no-return; every registrar initializer is affected, missing `addi r1 / lwz r12 / mtlr / blr`) and after a tail-call `b` (the compiler's unreachable trailing `blr` is dropped). `tools/packets/build_cd2.py` now extends over exactly those words. If a diff shows only extra trailing words on our side, read the bytes after the slice before chasing it.
- **Operand order of commutative float ops follows where the values are defined, not the source order of the operands.** Swapping `a * b` changes nothing. In `CalcRand*`, CD2's `fmuls f7, f8(rand), f11(max - min)` came only from `float r = (float)Rand(); float f = r * (max - min) * k + min;`, i.e. the conversion in its own statement.
- **Extract versus mask for single bits.** Testing a bit in place (`(x >> 12) & 1`, `x & 0x1000`, or a bitfield read) gives `rlwinm rD, rS, 0, 19, 19` (mask). Converting it into a `bool` or `unsigned char` local first (`bool b = ((x >> 12) & 1) != 0;`) gives `extrwi rD, rS, 1, 19`.
- **Recomputed values come from repeated calls.** CD2 computing `size()` twice, with `srawi.` for the test and again after a store that may alias, means the source called `size()` twice. A local `n` computes it once. `srawi.` instead of a mask test came from an `unsigned` pointer-difference `size()` with `if (size() > 0)`.
- **Try source shapes systematically** with `tools/sweep.py <default.exe> <spec.py>`: a spec lists target functions and named variants (text replacements in the source and headers), and the tool reports each variant's match. Example specs are in `tools/research/compiler_re/sweeps/`.
- **Game code is LTCG** (`/GL` + `/LTCG`). Check LTCG-sensitive functions with `tools/verify_ltcg.py <default.exe> [file filter]`; it models the rest of the program automatically. Mark functions that are exact only under LTCG with `"ltcg": true` in `config/matched_functions.json`. Most functions compile identically without it, but a function that loads float constants does so in CD2 through a base register pointing at the program-wide constant pool (`addi rN, 0x820F8C80; lfs f0, 0x84(rN)`). A plain compile emits one `lis` per constant instead and can never match. Check with `tools/research/compiler_re/ltcg_check.py`, and don't spend effort on such a function in a plain build.
- **LTCG limit: functions with many scattered float constants.** CD2's link-time codegen knows the layout of the program-wide constant data and shares one base register between all constants within ±32 KB, so a constructor that loads 14 constants may use three bases. The per-file LTCG model packs a file's constants close together and cannot reproduce that, so such functions can only be confirmed in a full-program build. Example: the `cHelicopterController` and `cFlocketPrototype` constructors, whose stores and values match.
- **The registrar's `MakeNew` often builds the class's PROTOTYPE** (a separate attribute-handler object), not the class itself, and can live far from the class's code; the registrar's size argument is the class's size. The class's own code starts at its `RetClassName` (lis/addi/blr returning the class name), which `tools/packets/build_cd2.py` now centres the candidate window on.
- **Which file a function belongs to is decided by its address, not by what it looks like.** Outside the order-list region the linker lays out each object's functions contiguously, so every function inside a file's range (`config/splits.txt`) was emitted by that file's object. That includes another class's inline or template functions and surviving copies of folded code. `tools/check_integrity.py` rejects claims outside the file's range.
- **A byte match is not enough: references must point where CD2's do.** The byte comparison masks call targets and addresses, so a call to the wrong function with the same signature still "matches". The gates and `tools/check_tu.py` resolve every relocation against CD2 (`WRONGTGT` in the harness). The first run found a real case: the helicopter prototype's deleting destructor called `~CAttributeHandler`, where CD2 calls its intermediate base `cVehicleControllerPrototype`'s destructor, because the stand-in base chain skipped a level. Model the real base chain (RuffKing) rather than the shortest one that matches. Names that embed an address (`Ext_82954E48`) must be right.
- **Identical-code folding (ICF).** The linker folds byte-identical functions into one copy, so several classes can share one address (5 `MakeNew` addresses are shared by 20 classes; registrar data shows it). The folded copy belongs to the file whose range contains it. Other files that define the same function mark their entry `"folded": true` in the manifest, and a maintainer lists it as `folded` in `config/splits.txt`.
- **`work/map.txt` needs substrings of MANGLED names** (`??__EcFooRegistrar@`, `??_9Base@NS@@$BBMA@AA`), not demangled text; the harness now warns about entries that match nothing.
- Listings: add `/FAcs /Fa<file>.cod` to see source lines interleaved with code and every compiler temporary's stack slot (`tv143 = 80 ; size = 8`).
- A `switch` compiled to an inline jump table puts its data words in `.text` right after the `bctr`. The harness listing hides them on the target side only, so `--diff` is misaligned below the `bctr`; compare words side by side instead.
- In Git Bash, `cl /flag` arguments get path-mangled: `export MSYS2_ARG_CONV_EXCL='*'` first. `cl /d1reportSingleClassLayout<Class>` prints the layout and every vtable, including thunks.

## cNPCTintProfile pilot findings (all 7 belonging functions exact)
- Repo-header accessors declared out of line but INLINE in CD2: `CAttributeCommandIterator::IsFinished`, `CAttributeDataChunkIterator::IsFinished` (`pCurrChunk_->size_ == 0`), `CAttributeCommand::GetAs_UInt32` (`chunk_.data_`), `CAttributeHandler::CAttributeHandler()` (`m_Flags(0)` then `m_InstanceId.Clear()`), `RWSGUID::Clear()` (4 word stores). Without them you get `bl` calls where the target has loads. Workaround without touching the header: define them `inline` in the .cpp before first use (legal even though the header declares them non-inline).
- `RWSGUID::operator=` is out of line in CD2 too; copies of GUIDs must be via the implicit copy constructor (`: m_GUID(g_null)`, by-value parameter), never `a = b`.
- HandleAttributes branch layout (blt 8 / bne, case 8 body first, `<8` arm after) = `switch (it->GetCommandId()) { case 8: ...; break; case 0: case 1: ... case 7: {...} }` with all 8 labels listed. `if/else` chains and `default: if (<8)` do NOT give it. The `<8` arm calls `GetCommandId()` a second time (no caching).
- The nIndex assert in RuffKing's HandleAttributes is absent in CD2 (retail strips it); don't write it.
- Scalar deleting destructor with NO vptr stores in the body (target F6): do not declare a destructor on the derived class or on `Editor::cGUIDEventHandler<T>`. An empty user-written `~X() {}` makes the compiler store the vptr before calling base dtors; an implicit dtor does not. (The same "no vptr store" shows the template handler has no dtor of its own; identical vtables folded by ICF explains why both vptr stores in the ctor use the same address.)
- Inline-copy scheduling: the ctor passes `GetInstanceId()` (hidden-return RWSGUID) to a by-value param. Block copy (4 lwz then 4 stw from the returned pointer) was only produced when `Register(T*, const RWSGUID& id) { RWSGUID guid = id; AddEntityToMap(guid, p); }` copies from a reference. A by-value `Register(T*, RWSGUID)` gives interleaved lwz/stw, and a named local in the caller swaps the two stack slots.
- `operator new(size)`/`operator delete` in CD2 are plain `XCreateHeapBlock(size)`/`XDestroyHeapBlock(p)` calls (no memtype/file/line as in RuffKing); declaring global replacements in the .cpp is enough. Registrar string/class-id: `static const char *const pcClassID = "..."` defined in the .cpp (constant-folded to lis/addi, no load).
- Harness: pairing is greedy by similarity; an unfinished function may be paired with an unrelated compiler-made one (e.g. a template's deleting dtor). Dump the obj with dumpbin to see what was really emitted.
- 0x8255E0D8 (VMX math using bytes at +1 and vectors at +0x10/+0x20/+0x30) is NOT part of cNPCTintProfile.cpp (it is the neighbouring file).

## cFactionConfigData pilot findings (GangManager/cFactionConfigData.cpp; F08, F13, F14, F15, F18, F19 exact; F07 not)
- Split: F01-F06 and F09-F12 are other files' code (a pool class with 0x1C-byte elements, tiny global accessors); F16/F17 are another class's ctor/dtor (it shares the same second base). Harness trap: tiny functions with the same shape (F09, F12: `lis/lwz|addi/blr`) get a false EXACT pairing with our functions (F12 steals RetClassName from F08). Check by name/address, not by the EXACT flag.
- Multiple inheritance: CD2's class is CAttributeHandler plus a polymorphic second base at 0x18. Evidence: the ctor stores a second vptr at 0x18 (secondary vtable follows the primary one, +0x34), and the destructor body (F14) stores ALL subobject vptrs (0, 0x18, 0x2C), then calls the second base's out-of-line dtor on this+0x18 and the CAttributeHandler dtor on this.
- Vptr stores of inlined base ctors: MSVC drops the earlier of two stores to the same vptr slot (dead-store elimination) when base ctors are inlined, so a chain of bases/members collapses to one store. They SURVIVE when an intermediate class is itself a most-derived-style class with an out-of-line virtual destructor: `class B : public B1, public B2 { virtual ~B(); }` keeps B1/B2's stores plus B's plus the derived's (target: three stores to 0x2C, two to 0x18). Members (even with virtual dtors) always collapse to one store.
- A base class with its own ctor that initialises a field (`B2() : m_bFlag(false)`) leaves a dead `addi r10,r10,0x14` (subobject address) in the inlined derived ctor and changes scheduling. Initialise the field in the enclosing class's ctor body instead (`B() { m_bFlag = false; }`).
- Switch lowering with a zero case: `beq` to the case-0 body, then `bdz` for 1..N and a final `b` for the last case, happens when `case 0` is written AFTER the other low cases in source: order 1,2,3,4,5,0,6 reproduced the target exactly (case bodies are laid out in source order). Case 0 first or 0..6 in order gives `bdzne` chains with 0 as the fall-through.
- A nested `switch (x) { case 0..3 }` without default compiles to `cmplwi 3; bgt; mtctr; cmpwi 0; bdzf; bdzf; bne` (the ctr trick).
- `fctidz` + `stfiwx` (not `fctiwz`) = float converted to UNSIGNED int. Declare the destination field `unsigned int`.
- GUID passed to a lookup: a static inline wrapper `void *Find(const RWSGUID &id) { RWSGUID guid = id; return FindEntityInMap(guid); }` (callee takes const RWSGUID&) reproduces the 4 lwz/4 stw copy of the returned temp into a second stack slot, then a call with the slot address. A by-value RWSGUID parameter gives `ld r3 / ld r4` register passing instead.
- Subobject pointer null test: `&p->m_member` followed by `if (ptr)` gives the single `addic. r11,r9,0x18; beq`. A derived-to-base pointer conversion adds a second null test.
- Float attribute read: CAttributeCommand::GetAs_float is inline in CD2 (`lfs f0,8(r3)`), then `float mem; RwMemNative32(&mem, 4)` byte swaps in place through the stack (stfs / lwz / swizzle / stw / lfs). The swizzle is the usual `(x>>24)|((x>>8)&0xFF00)|((x<<8)&0xFF0000)|(x<<24)`.
- Inlining: a ctor with about 20 stores is NOT inlined into MakeNew by default (/Ox) although the target inlined it. `__forceinline` on the ctor reproduces the store sequence, but F07's scheduling/register allocation still differs (ours spills a lis constant to non-volatile r31; the target fits in r4-r11). Unresolved.
- Tooling: the harness leaves the obj in work/; `dumpbin /disasm` on it (XDK TechPreview\Mar09Compiler\bin\win32) shows what was really emitted when the harness cannot pair a function (HandleAttributes was unpaired until the case order was right). Compiling variants directly with cl (same flags) for store-order experiments saves harness runs.

## Compiler flags correction (2026-10-23)
- **Game code is compiled with `/Ob1`**, not the `/Ob2` that `/Ox` implies: only functions marked `inline` or defined inside the class are inlined. Evidence: `cFactionConfigData`'s scalar deleting destructor calls the out-of-line destructor in CD2, and only `/Ob1` reproduces that. All 15 earlier game-code matches are unchanged under `/Ob1`.
- The full game-code flag set is now `/Ox /Ob1 /Gy /GF /GR- /GS- /fp:fast` (all repo tools use it).
- Lua (a separate library project) was built with the default inlining. It matches 32/33 under `/Ox` but 31/33 under `/Ox /Ob1`. Different projects in the build used different flags.
- Consequence: a function defined out of line in a .cpp is never inlined, so if CD2 inlined something, the original had it `inline` or defined in the class body. Conversely, an inline-defined constructor may still not be inlined by `/Ob1` heuristics (`cFactionConfigData::MakeNew` is open).

## Measurement batch 1 findings (2026-10-23; 46 of 59 belonging functions exact, see config/matched_functions.json)

### VFX/cAmbientVFXSpawner.cpp (16 of 21 exact)
- Split: cAmbientVFXPrototypeBase `RetClassName` and deleting dtor, cAmbientVFXPrototype `MakeNew`/`RetClassName`/dtor, the cAmbientVFXSpawner functions, and the registrar pair. The functions right after them (PrototypeBase `MakeNew`/`HandleAttributes`, cAmbientVFXSpawnerBase `RetClass`/`IsA`/update/spawn/release) are another file, so `cAmbientVFXSpawnerBase::ms_RandGen` is defined there, not here.
- In-class virtuals called qualified (`Base::OnVFXFinished()`) are inlined: `OnVFXFinished` becomes a virtual call to `ReleaseVFX` (slot 9).
- Float range test: `if (start < end) { if (p < start || p > end) fail; } else if (p > end && p < start) fail;` reproduces `CanSpawn`; writing the `>=` arm first inverts the layout.
- `if (Base::ReleaseVFX()) { ...; return true; } return false;` (success arm first) matches; `if (!Base::ReleaseVFX()) return false;` does not.
- Static local class descriptor: `static cClass *p = new cClass(id, name, size); return *p;` reproduces the guard, `XCreateHeapBlock(0x5C)` and the out-of-line `cClass` constructor.
- Open, `CalcRand*` (3 functions): same instructions, but CD2 loads its two float constants (1/32767 and -1000.0) through one base register (`addi r30, anchor`, displacements 0x84 and 0x3D4, r30 saved in the prologue); ours uses one `lis` per constant. Unsigned, int, double and divide variants never produced the anchor. Lead: two fields of one global constants struct would load this way (RuffKing's `Fun_Runtime::tGlobalConstants` has float members).
- Open, `HandleAttributes`: CD2 has three 16-byte GUID slots (return buffer, a 4-load/4-store copy, then a second interleaved copy passed by address). One or two nested copies, an explicit temporary, a named local in the caller, a by-value `LinkToObject` (RuffKing's signature) and a by-value `FindEntityInMap` all leave two slots.
- Open, `IsVFXFinished`: one word. CD2 tests bit 12 with `extrwi r10,r11,1,19`; we always get `rlwinm r10,r11,0,19,19`, also for `(x >> 12) & 1` and for a bitfield.

### VFX/cRopes.cpp (20 of 25 exact)
- Split: the 8 functions before `RetClass` belong to a neighbouring effect class; the hot-region vtable entries are shared base-class functions. A shader reload helper (stand-in `ReloadShader`) sits after the thunks and belongs here.
- Layout: CAttributeHandler at 0, polymorphic bases at 0x18, 0x1C, 0x30, 0x38 (stand-ins), a debug-page handler (vptr only) at 0x7C, fields from 0x80. The compiler-made adjustor thunks (-0x7C, -0x18, -0x38, -0x1C) match with this layout.
- Custom-allocator vectors: `allocate()` must be a STATIC out-of-line allocator member (called with just the count), `deallocate` is an inline `XDestroyHeapBlock`; `clear()` and `push_back()` are out of line in CD2, hence the `cVector<T>` wrapper that defines them out of class.
- Pool `GetOne` is inlined only with `__forceinline` and the single-result form (`T *result; if (used < cap) { ... result = pRet; } else result = 0; return result;`). `ReturnOne`: `avail[putI] = p; ++putI; --used; if (putI >= cap) putI = 0;` (`if (++putI >= cap)` schedules differently). `Reset`: unsigned `if (used > 0)` and `(int)diff / (int)sizeof(T)` (a `divw` by a register holding 48); the compiler unrolls the 600-element loops by 6.
- `~cPool() { Reset(); }` with an out-of-line `~cPoolBase()` reproduces the pool's scalar deleting destructor.
- `GetRopeSegment`/`ReturnRopeSegment` are static (they read the global `g_pRopes`, no `this`).
- Open: the constructor has one extra dead `addi r11,r30,0x7C` (address of the debug-handler subobject) that shifts scheduling; `ShowRopeSegments`' frame is 0x70 in CD2 against our 0x60 (not explained by the variadic argument count); the `RetClass`/`IsA` thunks at -0x4C imply a subobject at 0x4C with no vptr store in the constructor; `Render` (443 instructions, D3D and VMX128) was not attempted.

### GameManagement/cGameModeArena.cpp (10 of 13 exact)
- Split: cGameModeArena's functions, `cArenaLinker::GetArena` (found by its message string "cGameModeArena*"; RuffKing has it in the same object), the two `GetRandSpawnPointInList<T>` instantiations and the registrar pair. Before them is cCHordeArena (derived, 0x110 bytes, own vtable); after them are the barrier classes.
- Two-vtable classes: the `addi r3,r3,-0x18; b <deleting dtor>` thunk is generated by the compiler once the second base (vptr at 0x18) has a virtual destructor first and the derived class overrides the destructor; nothing to write. RuffKing's second base is `RWS::CEventHandler` (14 virtuals, 0x48 bytes, a short handle at +4).
- Inlined std::list sentinel (`_Buynode`): `Node *n = Alloc(); if (n) n->next = n; Node **pp = &n->prev; if (pp) *pp = n;` (two separate null tests).
- Vector destructor bodies are inlined into the owner's destructor in reverse declaration order, arrays last to first.
- Inlined `SendMsg`: `if (msg.pTarget != g_NullTarget && *msg.pTarget != 0) Dispatch(msg);`, with `g_NullTarget` a global pointer variable (CD2 0x83821310).
- GUID slots: `RWSGUID g = GetListGUID(list, i); void *p = LinkToObject(g);` puts the hidden-return temporary at the lower slot (0x60) and the copy at 0x70, as in CD2; `LinkToObject(GetListGUID(...))` swaps them.
- `push_back(T *const &)` forces `p` into a stack slot; CD2 reloads `p` from it after the call.
- String-id hash (inlined `GetStringID`): `int mult = <chain>; int id = 0; for (char c = *s; c != 0; c = *++s) id = id * mult + c;` with `mult` declared before `id`.
- An 11-case switch (0..10) became an inline jump table; case bodies are in source order (case 7 before case 6 in CD2).
- Open, `HandleAttributes` (95%): CD2 keeps the address-taken `void *p` of case 0 in the same slot as the float `mem` of cases 3/4 (0x50); ours is at 0x54. Moving `p`'s declaration (function, case, loop scope) did not merge them.
- Open, `GetRandSpawnPointInList`: CD2 tests the size with `srawi. r8,r10,2; beq`, then recomputes it for the `Rand` argument. Using the size only for the test folds to `clrrwi; cmpwi`; keeping it in a local gives `srawi.` but no recompute. The arm order `if (n) return list[Rand(n)]; return 0;` is right. `Rand(max)` is `divwu` plus a `twllei` zero trap.

## Measurement batch 2 findings (2026-10-23; gameplay files; 71 of 96 belonging functions exact, logic 22 of 43)

### AI/cChaseBehaviour.cpp (26 exact; 11 logic)
- The primary vtable has 119 slots: CAttributeHandler 0..10, cNonGameBase 11..67 (11 is RetClassName), then NPCBehaviourSM's and the class's own 68..118. Slot numbers come from `lwz rX, N(vptr)` (N/4). RetClass and IsA are not primary slots: they are the cRegisteredClass vtable (+0x30), which the linker placed right after the primary. The batch first read them as slots 119 and 120.
- With an out-of-line base constructor, the derived constructor stores every subobject vptr (0, 0x18, 0x1C, 0x30, 0x38) from the base chain alone. The bytes then match with any bases of the right size and polymorphism, which is how four files came to model cNonGameBase four different ways (see "Shared bases" below).
- A handle that is tested and then passed as an argument (`m_h = Ext(globalPtr, m_h)`): the early `lwz r4` is the tell; decompilers hide the second argument.
- Open: `Update` (99%, the same 97 of 98 words in a plain and an LTCG build) differs in one compare only: CD2 tests the word at `+0x4E4` with `cmpwi` (signed), ours with `cmplwi` (unsigned); its float constants load the plain way and match. (The batch notes blamed the constant pool; the word-by-word LTCG compare shows otherwise.) F37 (`0x824CEB38`, open) loads two float constants through a base register (`addi r30, anchor`, below the pool), which the LTCG model does not reproduce. F39/F40 keep `host + 0x7C` live in a register for later reads (`lwz r11, 0xC(r10)`) while the first read folds the displacement, and no arrangement of a `&host->m_Links` local reproduced it. Not attempted: intrusive-list walks, a 1008-byte function with a static state table, member-pointer delegate invokers.

### Equip/cFlocket.cpp (28 exact incl. 11 thunks; 4 logic)
- 11 subobjects; the primary vtable has 375 slots. The same RetClass/IsA base appears three times (+0x30, +0x120, +0x510); the override's `this` is the first, so the later tables' thunks subtract 0xF0 and 0x4E0.
- `SpawnFromPrototype(proto, mem)` ignores the prototype: `if (pMem) return new (pMem) cFlocket(); return 0;`. CD2's constructor takes no arguments (RuffKing's takes the prototype).
- Writing back three floats through one pointer (`Vec3 *p = &m_hint; ... p->x = v.x;`) reuses the register that held the vector load's address; `m_hint.x = ...` re-derives `0x484(r31)`.
- Not attempted: three large logic functions (653, 262 and 148 instructions), VMX128 matrix math, event/sound API calls.

### VEHICLE_CONTROL/cHelicopterController.cpp (17 exact; 9 logic, all small)
- The file starts at the prototype's `MakeNew`; the 25 functions before it are `cVehicleController`'s (the helicopter's base, 0x840 bytes in CD2 against RuffKing's 0x870).
- The functions first named `GetControllerType`, `GetControllerTypeFor` and `GetStaticControllerType` are `Term()`, `Init(const GOM::cSpawner *)` and the prototype's `Init(const CAttributePacket &)`. All three return a `Fun_Runtime::RetVal` through the hidden pointer (r3; `this` in r4). Their "controller type" globals are the file's `Ret_OK` and `Ret_FAIL`. Evidence: their vtable slots (6, 18, and slot 5 of the prototype's vtable) and RuffKing's `cHelicopterController::Init`, which has the same body.
- `Term` calls `cNonGameBase::Term` (0x826538B8), although `cVehicleController` overrides `Term` (0x82781CF0). `cVehicleController::Term` is inline, `{ cNonGameBase::Term(); return Ret_OK; }`: inlined into the helicopter's `Term`, its load of `Ret_OK` is dead. The out-of-line copy exists only for the vtable.
- Positive modulo `i = idx % n; if (i < 0) i += m_nCount;` (field re-read) and wrap-around `if (idx < 0) i = size() + idx; if (idx >= size()) i -= size();` with an inline `size()` computed three times.
- Open: `fmadds`/`fmuls` operand choice in a clamped cross product and an xz normalisation; two state transitions that inline an intrusive-list `front()` three times (needs the real list types); the VMX128 code.
