// Fun_Runtime::cSafeDeletablePointer<T>: STAND-IN for the typed safe pointer in the reference PDBs.
// RuffKing's cSafeDeletablePointer<CHARACTER::cCharacter> derives from cSafeDeletablePointerBase without
// additional storage (0x10 bytes). CD2's cCharacterInterface constructor stores its null payload at +0xC
// before installing the typed pointer's vtable. The converting constructor and copy assignment follow the
// reference declarations; assigning a raw pointer uses an implicit temporary, not a raw-pointer assignment overload.
// operator T *() is Burn's (inline, const); it converts the stored cSafeDeletable * down to T, so a null pointer stays
// null (CD2's event getters such as AI::cDamageTakenEvent::RetInstigator).
#ifndef FUN_RUNTIME_SAFEDELETABLEPOINTER_H
#define FUN_RUNTIME_SAFEDELETABLEPOINTER_H

#include "fun_runtime/safedeletable.h"

namespace Fun_Runtime
{
    template <class T> class cSafeDeletablePointer : public cSafeDeletablePointerBase
    {
    public:
        cSafeDeletablePointer() {}
        // CD2 initializes the payload before the typed vptr, then inserts the fully typed node into the list.
        // Linking in the base constructor leaves redundant base/derived vptr stores when the pointer escapes.
        cSafeDeletablePointer(T *pointer) : cSafeDeletablePointerBase(pointer)
        {
            Link();
        }
        cSafeDeletablePointer(const cSafeDeletablePointer &other) : cSafeDeletablePointerBase(other.m_pPtr) { Link(); }

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

        operator T *() const
        {
            return static_cast<T *>(m_pPtr);
        }

        // Pointer comparisons are declared in Burn's cSafeDeletablePointer specializations.
        // Comparing in the stored base type also lets a null test avoid a derived-pointer adjustment.
        bool operator==(T *pointer) { return m_pPtr == pointer; }
        bool operator!=(T *pointer) { return m_pPtr != pointer; }

    private:
        void Link()
        {
            if (m_pPtr)
            {
                cSafeDeletablePointerBase *head = &m_pPtr->m_SafeDeletablePointerListHead;
                m_pPrev = head;
                m_pNext = head->m_pNext;
                head->m_pNext = this;
                m_pNext->m_pPrev = this;
            }
        }

    public:
        CD2_LAYOUT_CHECKS(cSafeDeletablePointer,
            CD2_SIZE(cSafeDeletablePointer, 0x10))
    };
}

#endif // FUN_RUNTIME_SAFEDELETABLEPOINTER_H
