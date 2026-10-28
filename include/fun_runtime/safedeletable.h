// Hierarchy correction (2026-10-28): the six-slot table at 0x82146F00 belongs
// to cScriptHost, identified through its runtime class descriptor. cSafeDeletable
// itself has one virtual destructor (table 0x8212BED8). The historical slot
// interpretation below is superseded by include/fun_runtime/scripthost.h.
// Fun_Runtime::cSafeDeletable: an object that nulls the safe pointers to it when it dies. Polymorphic base of every
// game object (cNonGameBase, at 0x1C). Name, size (0x14) and the list head at +4 (itself polymorphic) from the RuffKing
// and Burn PDBs, which agree with CD2: cNonGameBase's constructor (0x82653588) stores the list head's vptr at 0x20.
// CD2's class has six virtuals where the PDBs have only the destructor (its own vtable is 0x82146F00). Burn has
// RetPosition and RetName as virtuals of cNonGameBase, and CD2's slots 3 and 4 behave as those: slot 3 returns a
// position by value ((0,0,0,1) by default), and cNonGameBase's slot 4 returns "Unnamed Non-Game Object". Slots 1, 2 and
// 5 are unnamed. Slot 5's default registers a script method "RetDebugString" (0x8276F340).
#ifndef FUN_RUNTIME_SAFEDELETABLE_H
#define FUN_RUNTIME_SAFEDELETABLE_H

#include "cd2/layout.h"
#include "fun_runtime/vec3.h"

namespace Fun_Runtime
{
    class cSafeDeletable;
    class cSafeDeletablePointerBase
    {
    public:
        cSafeDeletablePointerBase();
        virtual ~cSafeDeletablePointerBase();
        // CD2 0x8264B328 initializes the payload before linking this sentinel.
        cSafeDeletablePointerBase *m_pNext;
        cSafeDeletablePointerBase *m_pPrev;
        cSafeDeletable *m_pPtr;

        CD2_LAYOUT_CHECKS(cSafeDeletablePointerBase,
            CD2_SIZE(cSafeDeletablePointerBase, 0x10)
            CD2_OFFSET(cSafeDeletablePointerBase, m_pNext, 0x4)
            CD2_OFFSET(cSafeDeletablePointerBase, m_pPrev, 0x8)
            CD2_OFFSET(cSafeDeletablePointerBase, m_pPtr, 0xC))
    };

    class cSafeDeletable
    {
    public:
        Fun_Runtime::cSafeDeletablePointerBase m_SafeDeletablePointerListHead;

        cSafeDeletable();
        virtual ~cSafeDeletable();

        void NullifySafeDeletablePointers();

        CD2_LAYOUT_CHECKS(cSafeDeletable,
            CD2_SIZE(cSafeDeletable, 0x14)
            CD2_OFFSET(cSafeDeletable, m_SafeDeletablePointerListHead, 0x4))
    };
}

#endif // FUN_RUNTIME_SAFEDELETABLE_H
