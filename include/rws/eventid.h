// RWS::CEventId: reference-header names and layout, confirmed by cAIAnimEventProfile's
// member at 0x44 and its 0x4C allocation. Construction/destruction remain out of line in CD2.
#ifndef RWS_EVENTID_H
#define RWS_EVENTID_H

#include "cd2/layout.h"

namespace RWS
{
    class CRegisteredMsgs;

    class CEventId
    {
    public:
        CEventId();
        ~CEventId();

    private:
        CRegisteredMsgs *pEventId;
        short m_linked_count;
        short m_registered_count;

        CD2_LAYOUT_CHECKS(CEventId,
            CD2_SIZE(CEventId, 8)
            CD2_OFFSET(CEventId, pEventId, 0)
            CD2_OFFSET(CEventId, m_linked_count, 4)
            CD2_OFFSET(CEventId, m_registered_count, 6))
    };
}

#endif
