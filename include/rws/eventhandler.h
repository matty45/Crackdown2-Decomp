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
    class CEventId;

    class CEventHandler
    {
    private:
        CEventHandler(const CEventHandler &);

    public:
        // CD2 0x824BFA80 inlines this field-less base construction (vptr store only).
        CEventHandler() {}
        virtual ~CEventHandler();
        virtual int RetUniqueID();
        virtual bool IsMaster();
        virtual unsigned int RetMasterNetCommID();
        virtual void SendEventToNetComm(CMsg &);
        virtual void HandleEvents(CMsg &) = 0;
        // RuffKing signature; CD2 0x82F021B8 (cLongDistancePropManager's factory passes 0 and 0x8000).
        void LinkMsg(CEventId &, const char *p_formatstring, unsigned short priority);
        void UnLinkMsg(CEventId &);
        static void RegisterMsg(CEventId &, const char *msgName, const char *formatString);
        static void UnRegisterMsg(CEventId &);
        void ReplaceLinkedMsg(CEventId &, const char *name, const char *format);

        CD2_LAYOUT_CHECKS(CEventHandler,
            CD2_SIZE(CEventHandler, 0x4))
    };
}

#endif // RWS_EVENTHANDLER_H
