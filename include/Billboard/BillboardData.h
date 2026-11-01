#ifndef Billboard_BillboardData_H
#define Billboard_BillboardData_H

#include "rws/attributes.h"
#include "editor/guid_event_handler.h"
#include "fun_runtime/stringc.h"

namespace RWS { class CResource; }

namespace Billboard
{
    class BillboardData : public RWS::CAttributeHandler
    {
    protected:
        // RuffKing names/layout; CD2's factory 0x82911410 initializes the same offsets.
        Editor::cGUIDEventHandler<BillboardData> m_EventHandler;
        RWS::CResource *m_pVideoResource;
        Fun_Runtime::cStringc m_strPlayEventName;
        Fun_Runtime::cStringc m_strStopEventName;
    public:
        // CD2 inlines the GUID handler and two strings into MakeNew.
        __forceinline BillboardData() : m_pVideoResource(0) {}
        virtual ~BillboardData(); // CD2 out-of-line body at 0x829114F8
        // Factory 0x82911410 and size 0x68 are registered at 0x8302BBC0.
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(BillboardData,
            CD2_SIZE(BillboardData, 0x68)
            CD2_OFFSET(BillboardData, m_EventHandler, 0x18)
            CD2_OFFSET(BillboardData, m_pVideoResource, 0x2C)
            CD2_OFFSET(BillboardData, m_strPlayEventName, 0x30)
            CD2_OFFSET(BillboardData, m_strStopEventName, 0x4C))
    };
}

#endif
