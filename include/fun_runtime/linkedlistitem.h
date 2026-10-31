// Fun_Runtime::cLinkedListItem: intrusive-list base from the RuffKing PDB (vptr, next, previous; 0xC bytes).
// CD2's inlined safe-pointer construction leaves the links untouched until insertion. Its empty destructor
// supplies the final base-vtable store after the safe pointer has unlinked itself (AIDamageCache, 0x823E77C8).
#ifndef FUN_RUNTIME_LINKEDLISTITEM_H
#define FUN_RUNTIME_LINKEDLISTITEM_H

#include "cd2/layout.h"

namespace Fun_Runtime
{
    class cLinkedListItem
    {
    public:
        cLinkedListItem() {}
        virtual ~cLinkedListItem() {}
        cLinkedListItem *m_pNext;
        cLinkedListItem *m_pPrev;

        CD2_LAYOUT_CHECKS(cLinkedListItem,
            CD2_SIZE(cLinkedListItem, 0xC)
            CD2_OFFSET(cLinkedListItem, m_pNext, 4)
            CD2_OFFSET(cLinkedListItem, m_pPrev, 8))
    };
}

#endif // FUN_RUNTIME_LINKEDLISTITEM_H
