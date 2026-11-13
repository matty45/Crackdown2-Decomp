// Reconstructed insertion for typed script-method lists. Allocation remains
// external; the exception path and links follow CD2 0x827FAF00. This body is
// still unmatched. Legacy list users retain their external implementation.
#ifndef FUN_RUNTIME_POINTER_LIST_IMPL_H
#define FUN_RUNTIME_POINTER_LIST_IMPL_H
#define _SECURE_SCL 0
#include "fun_runtime/pointer_list.h"
#include <new>
#include <stdexcept>
namespace Fun_Runtime
{
    template <class T>
    void cPointerList<T>::push_back(const T &value)
    {
        cListNode *head = m_pHead;
        cListNode *previous = head->m_pPrev;
        cListNode *node = AllocListNode();
        // CD2 constructs the three node subobjects through placement new;
        // its null guards are the compiler's placement-construction guards.
        new (&node->m_pNext) cListNode *(head);
        new (&node->m_pPrev) cListNode *(previous);
        new (&node->m_pValue) void *(value);
        if (0x3FFFFFFFu - m_nSize < 1)
            _THROW(std::length_error, "list<T> too long");
        ++m_nSize;
        head->m_pPrev = node;
        node->m_pPrev->m_pNext = node;
    }

}
#endif
