// RWS::CMsg: an event message delivered to CEventHandler::HandleEvents. Names and order from the RuffKing PDB
// (ceventhandler.h). CD2's HandleEvents overrides read Id at 0 and write pData at 4; the later fields are RuffKing's
// and are not confirmed by CD2 code yet.
#ifndef RWS_MSG_H
#define RWS_MSG_H

#include "cd2/layout.h"

namespace RWS
{
    class CRegisteredMsgs;

    class CMsg
    {
    public:
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
}

#endif // RWS_MSG_H
