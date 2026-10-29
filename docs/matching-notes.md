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
- **Never reach memory by pointer arithmetic.** If CD2 reads `lwz r3, 0x50C(r31)`, the source read a member at 0x50C: declare it in the class's header with a `CD2_OFFSET` check and use it by name, even if the best name you have is `m_word50C`. A global read from a fixed address is a declared global with a name and a type, so the relocation check can see which one it is. `*(int *)((char *)this + 0x50C)`, a pointer converted to an integer or a hard-coded address gives the same instructions but proves nothing, and the source policy rejects it. Downcasts and upcasts go through `static_cast` along the real base chain. Typed pointer code the original had (walking an array with `p + i` or `++p`, `end - begin` for a count or an index) is fine: the rule is against standing in for declarations, not against pointers.
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
- Rechecked 2026-10-26: an explicit `RWSGUID` local makes `HandleAttributes` worse (29.7% versus 32.4%); direct nested return remains better.
- Open, `IsVFXFinished`: one word. CD2 tests bit 12 with `extrwi r10,r11,1,19`; we always get `rlwinm r10,r11,0,19,19`, also for `(x >> 12) & 1` and for a bitfield.

### VFX/cRopes.cpp (20 of 25 exact)
- Split: the 8 functions before `RetClass` belong to a neighbouring effect class; the hot-region vtable entries are shared base-class functions. A shader reload helper (stand-in `ReloadShader`) sits after the thunks and belongs here.
- Layout: CAttributeHandler at 0, polymorphic bases at 0x18, 0x1C, 0x30, 0x38 (stand-ins), a debug-page handler (vptr only) at 0x7C, fields from 0x80. The compiler-made adjustor thunks (-0x7C, -0x18, -0x38, -0x1C) match with this layout.
- Custom-allocator vectors: `allocate()` must be a STATIC out-of-line allocator member (called with just the count), `deallocate` is an inline `XDestroyHeapBlock`; `clear()` and `push_back()` are out of line in CD2, hence the `cVector<T>` wrapper that defines them out of class.
- Pool `GetOne` is inlined only with `__forceinline` and the single-result form (`T *result; if (used < cap) { ... result = pRet; } else result = 0; return result;`). `ReturnOne`: `avail[putI] = p; ++putI; --used; if (putI >= cap) putI = 0;` (`if (++putI >= cap)` schedules differently). `Reset`: unsigned `if (used > 0)` and `(int)diff / (int)sizeof(T)` (a `divw` by a register holding 48); the compiler unrolls the 600-element loops by 6.
- `~cPool() { Reset(); }` with an out-of-line `~cPoolBase()` reproduces the pool's scalar deleting destructor.
- `GetRopeSegment`/`ReturnRopeSegment` are static (they read the global `g_pRopes`, no `this`).
- Open: the constructor has one extra dead `addi r11,r30,0x7C` (address of the debug-handler subobject) that shifts scheduling; `ShowRopeSegments`' frame is 0x70 in CD2 against our 0x60 (not explained by the variadic argument count); the `RetClass`/`IsA` thunks at -0x4C imply a subobject at 0x4C with no vptr store in the constructor; `Render` (443 instructions, D3D and VMX128) was not attempted.
- Rechecked 2026-10-26: moving `g_pRopes = this` before `CreateRopeVertexDecl(elements)` improves the constructor score from 34.9% to 42.2%; still not exact.

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
- Rechecked 2026-10-26: a shared union for `p` and `mem` removes the stack-slot finding; objdiff reports no instruction differences, while strict `check` remains 96.1%, so it is not exact.
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

## First matches in automatically set-up files (2026-10-25)

### Prop/cTrafficLight.cpp (UpdateRenderMatrix exact)
- **Name a virtual slot from its chain of base calls.** cTrafficLight's override calls cProp's (0x826DA5B8), which first
  calls the same slot of its own base, PHYSICS::cBody (0x82683DC0). The bottom of the chain shows what the slot does:
  it copies the body matrix into the render matrix, so slot 26 is UpdateRenderMatrix (now named in
  `gom/non_game_base.h`). Slots 31 and 32 are EnterRenderableState and LeaveRenderableState.
- **Class sizes without a PDB.** A registrar's initializer passes the class size to the class registration, as does
  StaticCreateClass. A prototype's size is the allocation in its MakeNew.
- **Identical-code folding across class families.** cProp's and cVehicle's UpdateRenderMatrix are one folded copy that
  lies in cVehicle's code. Name a call after the class the source names (`cProp::UpdateRenderMatrix`). Its address is
  not evidence of the owner. Whoever matches cVehicle's adds the pair to `config/symbol_aliases.txt`.

### PLAYER/cPlayer.cpp (SetAITargeting exact)
- **Script-method registrations name functions RuffKing does not have.** A class's script-binding function (cPlayer's
  is 0x8271F230) pairs each method-name string with its function's address. It named the target SetAITargeting and
  its neighbours SetAIActive, IsAIActive and IsAITargeting, where RuffKing only suggested SetAIActive.
- **An if/else store gives CD2's select.** `if (b) p = &m_A; else p = &m_B;` with two members of different derived
  types compiles to the merged form (both addresses computed, one branch, one store) with no ternary or cast.
  `if (m_bFlag || !bArg)` gave CD2's test order directly.
- **CD2's player character.** CD2's `cCwTransCharacter` / `cCwTransCharacterWrapper` are Burn's `cPlayerCharacter` /
  `cPlayerCharacterWrapper` (headers under `include/CHARACTER/`). `cCharacter::m_pTargeting` is at 0x1524 in CD2
  (0x1534 in RuffKing).

## Partial-match audit (2026-10-26)

- **cChaseBehaviour::V108 (0x824CEE70) is now EXACT.** Put the player-link downcast in
  `HostLinks::RetPlayer()`, defined in the class, and call it at all three uses. This preserves the
  host+0x7C subobject address and the second link load. Direct field access lets the compiler remove
  both instructions. `check` confirms all 28 mapped functions in the file, including relocation targets.
- **cGameModeArena::HandleAttributes (0x8284E6D8): checker limitation identified.** The candidate and
  target both have 280 words, and objdiff reports no instruction differences. All eleven strict mismatches
  are the jump-table entries at function offsets 0x78..0xA0: the COFF object has zero placeholders with
  relocations, whereas the executable has linked addresses. `coff.compare` only masks a relocation when
  the first six bits agree, which fails for these data words. Keep this function partial (96.1%); source
  changes cannot resolve that comparison without changing the table or checker. No tool was modified.
- **Remaining eight manifest partials were rechecked.** Current plain scores: faction `MakeNew`
  0x826761B0 17.0%; ambient VFX `HandleAttributes` 0x827F9370 32.4%; ropes constructor 0x828060B8
  42.2%, `ShowRopeSegments` 0x82806D40 85.3%; arena `HandleAttributes` 96.1%, both random-spawn
  instantiations 0x8284EC80/0x8284ED60 87.3%; helicopter `Flatten2D` 0x82782D70 58.6%.
- **Unsuccessful variants:** faction list initialization order; rope debug-handler constructor/abstract
  forms; GUID const-reference/value parameters, explicit locals, memberwise copies and memcpy; random
  generator integer types, modulo forms and nested overloads, vector begin/subscript accessors; scalar
  norm operand orders, float/double locals, sqrt intrinsics, inline helpers, division forms and vector
  dot/normalization methods. Automated search also found no improvement in the tested partials.
  Unhelpful experimental source changes were discarded. Faction and helicopter were also checked with
  LTCG, without an exact result. The three existing ambient VFX random-time functions remain LTCG EXACT.
- **Local claims also audited:** traffic-light `EnterRenderableState` 0x82747898 is EXACT and was added
  to the manifest. `Pedestrian::IsA` 0x824A8D60 and `cPedestrianBase::IsA` 0x824A90F0 pass plain
  `check`, but each has only 21/23 matching words in the LTCG model. They remain unpromoted local claims
  because adding them makes the full verification fail. The explosion-level-info claims and traffic-light
  constructor claim have no matching compiled definitions; they are missing implementations, not partials.

## Jump-table checker fix (2026-10-26)

- The user authorized a focused exception to the tools/tests editing rule. `coff.functions` now retains
  ADDR32 relocation sites separately from instruction relocations. The byte comparison masks those data
  words fully, while retaining the opcode check for relocated instructions. `relocs.resolve` then checks
  each ADDR32 against its same-function label plus its embedded addend; unsupported external references
  fail closed. Changed labels, addends, out-of-range destinations and unaligned destinations are rejected.
- The same destinations are checked in recorded-facts mode. LTCG comparisons normalize only the explicitly
  identified table sites to function-relative destinations, so a retargeted linked table still fails.
- `cGameModeArena::HandleAttributes` (0x8284E6D8) is now `check` EXACT, including all relocations, and
  280/280 words under LTCG. Its C++ was unchanged by this fix. Seven manifest partials remain.
- Thirteen synthetic regression tests in `tests/test_jump_table_relocations.py` cover the COFF parser,
  instruction masking, local-label resolution, signed addends, wrong destinations, LTCG and recorded facts.
  They run as a new gate in `cd2.py verify` and need neither the game nor the XDK.
- Additional source probes found no improvement: faction list-initialization helper/inheritance forms,
  scanf scalar/one-element-array storage, random-index local lifetimes and element return types, GUID lookup
  parameter/return ABI and copy-constructor forms. These experimental source changes were not retained.


### Additional WIP probes (2026-10-26)

- IDA reconfirms the ambient-spawner GUID sequence: returned value, intermediate copy, and lookup argument
  occupy three separate stack slots. Eighteen inline GUID-return wrapper variants (value/reference parameters,
  const returns and explicit copied locals) all remain 24/74 words. Adding an empty GUID destructor does not
  preserve the missing copy; explicit memberwise/loop copy constructors reduce the score to 23/74.
- Arena random-bound parameters by const reference or signed/unsigned 32-bit value remain 48/55 words.
  Changing the vector subscript parameter to references or a 64-bit index also leaves 48/55. Narrowing the
  random bound to 16 bits introduces another instruction; a 64-bit bound changes the division.
- Helicopter signed-product and double-intermediate probes do not reproduce the target's two differently
  ordered single-precision multiply/add sequences. One signed-product form reaches 18/29 words but uses
  different arithmetic instructions, so it was not retained. Ordinary identity operations are optimized away.
- Faction list constructor statement permutations and int/unsigned int/unsigned long counters retain the
  extra saved register (at best 9/53 words). Source statement order alone does not control these stores.
- All probes above were compiled in scratch directories. No candidate was promoted and all seven WIP
  manifest entries remain unresolved. Next investigations should examine original helper/type structure
  and compiler scheduling rather than repeating these expression/parameter permutations.

### Rope initialization-order correction (2026-10-26)

- Re-reading the target establishes that `g_pRopes = this` occurs after `CreateRopeVertexDecl`. Restored
  that source order; the earlier move before the call improved a positional score but did not reproduce
  target behavior. The constructor remains WIP (38/109 words), with the missing debug-handler address
  calculation shifting the comparison. Do not move this assignment before the call to improve the score.
- Empty inline debug-handler initialization helpers (member, static pointer/reference, self-return and
  virtual forms) all leave the same 38/109 result. No helper variants were retained.
- IDA confirms the console output callee saves the variadic argument registers and formats a wide string.
  Other small scanf/console callbacks also put scalar locals at stack offset 0x60, whereas an inspected
  scanf callback without console output uses 0x50. This supports investigating the original console call
  declaration or wrapper, rather than adding arbitrary padding to ShowRopeSegments.
- Scratch declarations returning int, float, double, 64-bit integer, vector or a small POD aggregate all
  leave ShowRopeSegments at 29/34 words. An unused return type alone does not explain the extra stack slot.

### Reference-type investigation (2026-10-27)

- Local RuffKing PDB dumps identify cDebugPageHandler constructors taking a wide name (optionally a bool),
  and inheritance from cRegisteredClass. The reference debug handler is 0x24 bytes, versus the observed
  four-byte CD2 subobject, so its full layout cannot be copied. Named-constructor and out-of-class inline
  variants still produce 38/109 words for the rope constructor; no header changes were retained.
- The faction helper destructor at 0x8276F0C0 writes the same primary/secondary vtable addresses seen in
  cNonGameBase's base construction: primary at +0 and secondary at +0x14. This connects the local cConfig
  stand-ins to the shared safe-deletion interfaces and warrants a hierarchy audit before more expression
  sweeps. Do not infer a shared class size solely from the next base offset.
- The reference cSafeDeletablePointerBase derives from cLinkedListItem (vptr, next, previous) and ends
  with a pointer to cSafeDeletable, not a count. Changing the faction stand-in's last field from integer
  to pointer, and testing this base/derived split, did not improve MakeNew (best 9/53 words).
- Scratch-only floating-point flag diagnostics also failed to match Flatten2D: fast 17/29, precise 8/29,
  strict 9/31. Repository compiler settings were not changed.

### Console callback diagnostics (2026-10-27)

- RuffKing's cRopes module symbols list the ShowRopeSegments parameters `object`/`cmdLine` and one
  local, `nDoPosInfo`; no additional local buffer is described. This does not prove CD2's frame layout,
  but weakens the hypothesis that the source needs an extra local.
- Scratch optimization-mode diagnostics did not produce an exact callback, arena random-spawn function,
  or Flatten2D. /Ot, /O2, /Ob2 and /Oy- retain their existing scores; /Os and /O1 worsen all three.
  No compiler settings or source candidates were retained.

### Ambient GUID assignment match (2026-10-27)

- `cAmbientVFXSpawner::HandleAttributes` (0x827F9370) is now `check` EXACT in plain and LTCG builds,
  74/74 words, with no relocation problems. All 21 mapped functions in the file pass.
- The missing copy came from using copy initialization instead of assignment. Declare a GUID, assign
  `it->GetAs_RWSGUID()` to it, then pass it to LinkToObject. Define the existing RWSGUID assignment
  operator inline with four explicit member assignments and return `*this`. A loop generates different
  code (25/75 words); nested copies and copy constructors do not reproduce the assignment's temporaries.
- The shared header now contains that assignment implementation. Six manifest WIP functions remain.

### IDA WIP audit and accessor fixes (2026-10-28)

- Opened the CD2, RuffKing and Burn IDA databases. Six manifest WIP entries remain:
  faction MakeNew (0x826761B0), rope constructor/ShowRopeSegments
  (0x828060B8/0x82806D40), arena random-spawn templates
  (0x8284EC80/0x8284ED60), and Flatten2D (0x82782D70).
- Also audited unpromoted local claims. Three cCharacterEntityIF accessors now pass strict
  plain and LTCG checks: GetFloatConditional (0x823EBFB8, 16/16 words), CheckField548
  (0x823EC1B8, 15/15), and GetBool38_50 (0x823EC378, 10/10).
  Use RetCharacter() for the second null test after the safe-pointer downcast; an integer
  subtraction and volatile temporary do not reproduce it. For GetFloatConditional, cast
  the actual cSafeDeletable pointer to cCharacter and immediately read its flag: CD2 has
  no extra null guard after the conversion. A bool local materializes GetBool38_50's result.
- Implemented the four previously missing explosion-info claims: RetClassName,
  scalar deleting destructor, registrar and registrar destructor. All are strict EXACT.
  CD2's registrar confirms size 0x80. Field offsets agree with the reference layout;
  factory defaults use the shared g_GlobalConstants. The factory is not promoted.
- New scratch probes did not improve the six manifest WIP functions: arena Rand local,
  modulo and index-type variants, real std::vector indexing; rope explicit member/base
  initializers and named debug-handler constructor arguments; faction list-body/store
  permutations; Flatten2D square temporaries, sqrt variants and powf expressions.
  Arena compiler-search (150 budget, two rounds) also found no improvement. No such
  source variants were retained. Original arena and console namespace edits predated this run.
- Streaming-factory constructor inlining reproduces more of the body but introduces
  a saved this register absent in CD2; its original source was restored. Chase V104's
  LTCG model still does not reproduce its shared constant-base register and frame.
- Other unpromoted claims remain: two pedestrian IsA functions (plain EXACT but not
  accepted by the LTCG model), traffic-light constructor, chase V104, crowd-zone factory
  (missing), and streaming-data factory. These are separate from the six manifest WIPs.
- Final verification: VERIFY: PASS; 542 plain exact, 545 LTCG exact, six manifest WIP. Header layout/self-tests and git diff --check pass.


### Shared hierarchy correction and rope constructor (2026-10-28)

- IDA identifies the former faction cConfigBase stand-in as cScriptHost: the runtime
  class initializer at 0x8276ED30 names cScriptHost, ID 1009, size 0x1C. Its destructor
  at 0x8276F0C0 restores primary and registered-interface vtables at +0/+0x14 and
  calls the cSafeDeletable destructor at 0x8264B398. cSafeDeletable itself has only
  one virtual destructor; the six-slot table previously attributed to it belongs
  to cScriptHost. cRegisteredClass is four bytes. The flag at cScriptHost+0x18
  accounts for the remaining bytes before cNonGameBase's network base.
- Corrected cNonGameBase to inherit cScriptHost, retaining all interface and field
  offsets. CD2's four-byte debug handler also inherits cRegisteredClass, with
  RetClass, IsA and a virtual destructor. This missing inheritance caused the
  rope constructor's apparently dead base-address calculation to disappear.
- cRopes::cRopes (0x828060B8) now passes strict plain and LTCG checks, 109/109 words,
  including relocation checks. Its RetClass/IsA adjustment thunks at 0x82807380
  and 0x82807388 also pass both models, 2/2 words each, and are promoted.
- Declare the std::vector reserve instantiation external: its implementation is
  owned by another translation unit (0x826104B8). Otherwise the single-file LTCG
  model specializes both reserve calls to 600 and removes their size arguments.
- Further scratch-only expression, return-lifetime, random-generator extraction,
  scalar-alignment and constructor-hierarchy probes did not finish the other five
  manifest WIPs. In particular the corrected faction hierarchy alone does not
  fix its constructor scheduling. No unsuccessful variants were retained.

### Faction factory and shared sentinel initialization (2026-10-28)

- `cFactionConfigData::MakeNew` (0x826761B0) now passes strict plain and LTCG
  checks, 50/50 words, including relocation consistency. All seven mapped
  functions in its source file pass both models.
- Replace the local cConfigBase hierarchy with the existing cScriptHost. The
  pointer-list sentinel constructor initializes only m_pPtr; the owning
  cSafeDeletable constructor then links next and previous to the sentinel.
  Initializing next/previous to zero first leaves two extra stores. Initializing
  the circular links in the member constructor retains the extra saved r31.
- The inline constructor definitions are local to the faction translation unit;
  other files retain their existing out-of-line cSafeDeletable construction.
  Shared pointer-list fields now have explicit offset and size checks.
- CD2 stores 0x820FC01C for both the script-host and final faction registered
  interfaces in MakeNew. cScriptHost's destructor at 0x8276F0C0 restores the same
  table. The user authorized the corresponding ICF alias in symbol_aliases.txt.
- Four manifest WIPs remain: ShowRopeSegments, both arena random-spawn template
  instantiations, and Flatten2D. Scratch-only probes of modulo helper inlining,
  vector subscript return types, complete spawn-point inheritance, nonstatic
  arena methods under LTCG, scalar alignment, and floating-point helper/member
  expressions did not yield another exact match. No unsuccessful variant was
  applied to the source files.
- Final verification: VERIFY: PASS; 546/546 plain matched functions and 549/549
  LTCG matched functions pass, with four manifest WIPs. Header layout checks,
  recorded-fact validation, all verification self-tests, and git diff --check pass.

### Rope callback and visible variadic callee (2026-10-28)

- The unchanged ShowRopeSegments implementation (0x82806D40) passes strict
  `check --ltcg`, 34/34 words including relocation checks, when the real
  GDb::ConsoleOutput definition is compiled as a separate /GL dependency.
  A declaration-only stub leaves the frame 16 bytes smaller. Merely declaring
  the callee noinline, or providing an inline body, does not reproduce it.
- Reconstructed ConsoleOutput at 0x825D0CF0 independently passes strict plain
  and LTCG checks, 23/23 words: wchar_t buffer[256], va_start, and a call to
  _vsnwprintf_s(buffer, 255, _TRUNCATE, fmt, args). IDA confirms that retail CD2
  discards the formatted result; the reference builds also output it.
- The user authorized adding the owning source/split and compiling this
  source-backed dependency in the LTCG model. Comparison, masking, and
  relocation-validation logic were not changed. The dependency registration is
  currently explicit in verify_ltcg.py; broader build-model cleanup remains.
  The user subsequently confirmed that the correct match should be retained.
- Final verification: VERIFY: PASS; 547/547 plain matched functions and 551/551
  LTCG matched functions pass. Three manifest WIPs remain: both arena random
  spawn-point templates and Flatten2D. Target facts and git diff --check pass.

### Standard verifier restored (2026-10-28)

- The user discarded the one-off ConsoleOutput dependency extension in
  verify_ltcg.py. With the restored tool, ShowRopeSegments is 29/34 words in
  both plain and LTCG checks. Its manifest entry is WIP again, superseding the
  experimental promotion above. Four manifest WIPs remain.
- The independent ConsoleOutput implementation remains subject to the normal
  checker and does not inject a callee definition into the rope compilation.
- Re-ran the restored verifier: VERIFY: PASS; 547/547 plain matched functions,
  550/550 LTCG matched functions, and four WIPs. ConsoleOutput independently
  remains EXACT, 23/23 words, in plain and LTCG checks. Facts were regenerated;
  verify_ltcg.py has no Git diff and git diff --check passes.

### LTCG model sees matched callees (2026-10-29)

- CD2 was linked as one program, so LTCG saw the body of every callee. The LTCG
  model used to replace every external function with an opaque stub, which hid
  bodies the real build could see. ShowRopeSegments (0x82806D40) shows the
  effect: its frame is 16 bytes larger only when LTCG sees
  GDb::ConsoleOutput's body.
- The model now follows one rule for every file (`verify_ltcg.dependencies`,
  used by verify, `check --ltcg` and the facts gate): another repository file
  is compiled with /GL and linked in when this file calls functions that file
  has matched, and only if every symbol this file takes from it is such a
  function. LTCG therefore sees only bodies the gates prove exact. Data,
  unmatched functions and everything else stay stubs. Nothing is listed by
  hand, and it goes one level deep.
- `verify_ltcg.py --self-test` proves it: ShowRopeSegments matches with
  ConsoleOutput matched, and stops matching when ConsoleOutput's entry is
  marked work in progress.
- Result: no matched function changed; ShowRopeSegments is matched again,
  with `"ltcg": true`. Two files currently pick up dependencies: cRopes
  (ConsoleOutput) and cCHordeArena.
- If a function differs only in its frame size or in which registers survive a
  call, and it calls a function that is not matched yet, match that callee
  first: its body may be what the caller's code depends on.
