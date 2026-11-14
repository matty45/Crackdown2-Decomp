#ifndef Equip_cUVLightAttachmentData_H
#define Equip_cUVLightAttachmentData_H

#include "Equip/cLightAttachmentData.h"

namespace Equip
{
    // STAND-IN: reference hierarchy/name; CD2 factory 0x826162B0 initializes the UV damage at +0x38.
    class cUVLightAttachmentData : public cLightAttachmentData
    {
    public:
        cUVLightAttachmentData() : m_fUVDamage(0.0f) {}
        virtual ~cUVLightAttachmentData() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    private:
        float m_fUVDamage;
        CD2_LAYOUT_CHECKS(cUVLightAttachmentData,
            CD2_SIZE(cUVLightAttachmentData, 0x3C)
            CD2_OFFSET(cUVLightAttachmentData, m_fUVDamage, 0x38))
    };
}

#endif
