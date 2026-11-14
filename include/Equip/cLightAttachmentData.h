#ifndef Equip_cLightAttachmentData_H
#define Equip_cLightAttachmentData_H

#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "rws/eventid.h"

namespace Equip
{
    // STAND-IN: reference base order/names, CD2 factories 0x826159C0/0x826162B0 confirm all offsets below.
    class cLightAttachmentData : public RWS::CAttributeHandler, public RWS::CEventHandler
    {
    public:
        // The UV factory uses this default constructor and leaves the light settings uninitialized.
        cLightAttachmentData() {}
        virtual ~cLightAttachmentData();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void HandleEvents(RWS::CMsg &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    private:
        float m_fConeAngle;
        float m_fConeLength;
        float m_fPowerTime;
        float m_fRechargeTime;
        char m_nLightID;
        bool m_bInfinitePower;
        RWS::CEventId m_RetrieveLightData;

        CD2_LAYOUT_CHECKS(cLightAttachmentData,
            CD2_SIZE(cLightAttachmentData, 0x38)
            CD2_OFFSET(cLightAttachmentData, m_fConeAngle, 0x1C)
            CD2_OFFSET(cLightAttachmentData, m_fConeLength, 0x20)
            CD2_OFFSET(cLightAttachmentData, m_fPowerTime, 0x24)
            CD2_OFFSET(cLightAttachmentData, m_fRechargeTime, 0x28)
            CD2_OFFSET(cLightAttachmentData, m_nLightID, 0x2C)
            CD2_OFFSET(cLightAttachmentData, m_bInfinitePower, 0x2D)
            CD2_OFFSET(cLightAttachmentData, m_RetrieveLightData, 0x30))
    };
}

#endif
