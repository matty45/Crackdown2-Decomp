// STAND-IN: reference base order, confirmed by CD2 constructor 0x828498C0.
// CD2 adds the DLC flag at 0x40, event ID at 0x44 and GUID handler at 0x4C; size 0x60.
#ifndef GAMEMANAGEMENT_CGMMRESOURCE_H
#define GAMEMANAGEMENT_CGMMRESOURCE_H
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "rws/eventid.h"
#include "fun_runtime/string.h"
#include "editor/guid_event_handler.h"
namespace GameManagement
{
    class cGMMResource : public RWS::CAttributeHandler, public RWS::CEventHandler
    {
    public:
        cGMMResource();
        virtual ~cGMMResource();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void HandleEvents(RWS::CMsg &);
    protected:
        short m_nResourceID;
        Fun_Runtime::cString m_sResourceName;
        // CD2 leaves this word uninitialized; its meaning is not recovered.
        unsigned char m_unmodelled3C[4];
        bool m_bDLCResource;
        RWS::CEventId m_GMMResourceEventID;
        Editor::cGUIDEventHandler<cGMMResource> m_EventHandler;
        CD2_LAYOUT_CHECKS(cGMMResource,
            CD2_SIZE(cGMMResource, 0x60)
            CD2_OFFSET(cGMMResource, m_nResourceID, 0x1C)
            CD2_OFFSET(cGMMResource, m_sResourceName, 0x20)
            CD2_OFFSET(cGMMResource, m_bDLCResource, 0x40)
            CD2_OFFSET(cGMMResource, m_GMMResourceEventID, 0x44)
            CD2_OFFSET(cGMMResource, m_EventHandler, 0x4C))
    };
}
#endif
