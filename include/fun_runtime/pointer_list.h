// STAND-IN: typed adapter for the shared 12-byte pointer-list ABI.
// Descriptive name is ours. Reference cList derives std::list; its allocator
// allocation and destruction remain external here. The constructor at
// 0x82772828 and insertion at 0x827FAF00 establish these members and operations.
#ifndef FUN_RUNTIME_POINTER_LIST_H
#define FUN_RUNTIME_POINTER_LIST_H
#include "cd2/layout.h"
namespace Fun_Runtime
{
    // std::list<T*> with out-of-line push_back and destructor (CD2 0x827FAF00 / 0x82470DA8); constructor inline.
    struct cListNode
    {
        cListNode *m_pNext;
        cListNode *m_pPrev;
        void *m_pValue;
    };
    cListNode *AllocListNode();
    inline cListNode **NextPtr(cListNode *p) { return &p->m_pNext; }
    inline cListNode **PrevPtr(cListNode *p) { return &p->m_pPrev; }

    template <class T>
    class cPointerList
    {
    public:
        cPointerList() { cListNode *n = AllocListNode(); if (n) n->m_pNext = n; cListNode **pp = PrevPtr(n); if (pp) *pp = n; m_pHead = n; m_nSize = 0; }
        ~cPointerList();
        void push_back(const T &);
    private:
        int m_nAlloc;
        cListNode *m_pHead;
        int m_nSize;
        CD2_LAYOUT_CHECKS(cPointerList,
            CD2_SIZE(cPointerList, 0xC)
            CD2_OFFSET(cPointerList, m_pHead, 4)
            CD2_OFFSET(cPointerList, m_nSize, 8))
    };


}
#endif
