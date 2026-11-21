// RWS::CMsg: an event message delivered to CEventHandler::HandleEvents. Names and order from the RuffKing PDB
// (ceventhandler.h). CD2's HandleEvents overrides read Id at 0 and write pData at 4; the later fields are RuffKing's
// and are not confirmed by CD2 code yet.
#ifndef RWS_MSG_H
#define RWS_MSG_H

#include "cd2/layout.h"
#include "rws/CRegisteredMsgs.h"

namespace RWS
{
    class CRegisteredMsgs;
    class CEventId;

    class CMsg
    {
    public:
        CMsg(const CEventId &tId, int toID); // Reference signature; CD2 0x82F01460.
        CRegisteredMsgs *Id;
        void *pData;
        int nDataSize;
        unsigned int nToId;
        bool bSendNetworked;
        unsigned int nNetCommID;

        CD2_LAYOUT_CHECKS(CMsg,
            CD2_OFFSET(CMsg, Id, 0)
            CD2_OFFSET(CMsg, pData, 4))
    };

    // Descriptive global name is ours: CD2 compares message IDs with the
    // sentinel pointer at 0x83821310 before checking their linked-message head.
    extern CRegisteredMsgs *g_pNullMessage;
    bool _SendMsg(CMsg &message); // Reference name; CD2 0x82F01D90.
    inline bool SendMsg(CMsg &message)
    {
        if (message.Id != g_pNullMessage && message.Id->m_pLinkedMessages != 0)
            return _SendMsg(message);
        return false;
    }
}

#endif // RWS_MSG_H
