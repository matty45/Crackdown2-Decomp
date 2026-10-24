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
    class cSafeDeletablePointerBase
    {
    public:
        virtual ~cSafeDeletablePointerBase();
    private:
        unsigned char m_pad[0xC];
    };

    class cSafeDeletable
    {
    public:
        Fun_Runtime::cSafeDeletablePointerBase m_SafeDeletablePointerListHead;

        cSafeDeletable();
        virtual ~cSafeDeletable();
        virtual void Slot1();
        virtual void Slot2();
        virtual Fun_Runtime::Vec3 RetPosition() const;
        virtual const char *RetName() const;
        virtual void Slot5();
        void NullifySafeDeletablePointers();

        CD2_LAYOUT_CHECKS(cSafeDeletable,
            CD2_SIZE(cSafeDeletable, 0x14)
            CD2_OFFSET(cSafeDeletable, m_SafeDeletablePointerListHead, 0x4))
    };
}

#endif // FUN_RUNTIME_SAFEDELETABLE_H
