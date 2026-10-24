// RWS::CEventHandler: receives RenderWare Studio event messages. Polymorphic base of every game object (cNonGameBase,
// at 0x18). Virtual order from the RuffKing PDB (Burn's has only the destructor and HandleEvents). CD2 has the same
// six: its own vtable (0x820FAD9C) is [destructor, return 0, return 1, return 0, empty, _purecall], i.e. RetUniqueID,
// IsMaster, RetMasterNetCommID, an empty SendEventToNetComm and a pure HandleEvents.
#ifndef RWS_EVENTHANDLER_H
#define RWS_EVENTHANDLER_H

#include "cd2/layout.h"

namespace RWS
{
    class CMsg;

    class CEventHandler
    {
    private:
        CEventHandler(const CEventHandler &);

    public:
        CEventHandler();
        virtual ~CEventHandler();
        virtual int RetUniqueID();
        virtual bool IsMaster();
        virtual unsigned int RetMasterNetCommID();
        virtual void SendEventToNetComm(CMsg &);
        virtual void HandleEvents(CMsg &) = 0;

        CD2_LAYOUT_CHECKS(CEventHandler,
            CD2_SIZE(CEventHandler, 0x4))
    };
}

#endif // RWS_EVENTHANDLER_H
