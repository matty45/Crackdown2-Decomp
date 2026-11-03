// STAND-IN: cProfileDataPropCarryNPC is named by cAnimHandlerNPCPropCarryFull.h.
// CD2 0x824EB900 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x4C. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAPROPCARRYNPC_H
#define ANIM_CPROFILEDATAPROPCARRYNPC_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataPropCarryNPC : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0xC];
        CD2_LAYOUT_CHECKS(cProfileDataPropCarryNPC,
            CD2_SIZE(cProfileDataPropCarryNPC, 0x10)
            CD2_OFFSET(cProfileDataPropCarryNPC, m_unmodelledData4, 4))
    };
}
#endif
