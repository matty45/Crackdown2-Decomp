// Fun_Runtime::cSafeDeletablePointer<T>: STAND-IN for the typed safe pointer in the reference PDBs.
// RuffKing's cSafeDeletablePointer<CHARACTER::cCharacter> derives from cSafeDeletablePointerBase without
// additional storage (0x10 bytes). CD2's cCharacterInterface constructor stores its null payload at +0xC
// before installing the typed pointer's vtable. The converting constructor and copy assignment follow the
// reference declarations; assigning a raw pointer uses an implicit temporary, not a raw-pointer assignment overload.
#ifndef FUN_RUNTIME_SAFEDELETABLEPOINTER_H
#define FUN_RUNTIME_SAFEDELETABLEPOINTER_H

#include "fun_runtime/safedeletable.h"

namespace Fun_Runtime
{
    template <class T> class cSafeDeletablePointer : public cSafeDeletablePointerBase
    {
    public:
        cSafeDeletablePointer() {}
        cSafeDeletablePointer(T *pointer) : cSafeDeletablePointerBase(pointer) {}
        cSafeDeletablePointer(const cSafeDeletablePointer &other) : cSafeDeletablePointerBase(other.m_pPtr) {}

        virtual ~cSafeDeletablePointer()
        {
            if (m_pPtr)
            {
                m_pPrev->m_pNext = m_pNext;
                m_pNext->m_pPrev = m_pPrev;
            }
        }

        cSafeDeletablePointer &operator=(const cSafeDeletablePointer &other)
        {
            if (m_pPtr)
            {
                m_pPrev->m_pNext = m_pNext;
                m_pNext->m_pPrev = m_pPrev;
            }
            m_pPtr = other.m_pPtr;
            if (m_pPtr)
            {
                cSafeDeletablePointerBase *head = &m_pPtr->m_SafeDeletablePointerListHead;
                m_pPrev = head;
                m_pNext = head->m_pNext;
                head->m_pNext = this;
                m_pNext->m_pPrev = this;
            }
            return *this;
        }

        CD2_LAYOUT_CHECKS(cSafeDeletablePointer,
            CD2_SIZE(cSafeDeletablePointer, 0x10))
    };
}

#endif // FUN_RUNTIME_SAFEDELETABLEPOINTER_H
