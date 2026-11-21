// STAND-IN: RWS::CRegisteredMsgs is named by the reference CMsg/CEventId types.
// Only its linked-message head is recovered: CD2's inline SendMsg tests +0
// before calling _SendMsg (0x82F01D90). The member name is descriptive and ours;
// the remaining record layout and complete size are not recovered.
#ifndef RWS_CREGISTEREDMSGS_H
#define RWS_CREGISTEREDMSGS_H
#include "cd2/layout.h"
namespace RWS
{
    class CLinkedMsg;
    class CRegisteredMsgs
    {
    public:
        CLinkedMsg *m_pLinkedMessages;
        CD2_LAYOUT_CHECKS(CRegisteredMsgs,
            CD2_OFFSET(CRegisteredMsgs, m_pLinkedMessages, 0))
    };
}
#endif
