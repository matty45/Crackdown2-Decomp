// STAND-IN: cProfileDataPropCarry is named by cAnimHandlerPropCarry.h.
// CD2 0x82507FC8 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x44. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAPROPCARRY_H
#define ANIM_CPROFILEDATAPROPCARRY_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataPropCarry : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x4];
        CD2_LAYOUT_CHECKS(cProfileDataPropCarry,
            CD2_SIZE(cProfileDataPropCarry, 0x8)
            CD2_OFFSET(cProfileDataPropCarry, m_unmodelledData4, 4))
    };
}
#endif
