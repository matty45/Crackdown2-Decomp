// STAND-IN: cProfileDataHand2HandUpper is named by cAnimHandlerHand2HandUpper.h.
// CD2 0x8251FEB8 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x70. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAHAND2HANDUPPER_H
#define ANIM_CPROFILEDATAHAND2HANDUPPER_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataHand2HandUpper : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x30];
        CD2_LAYOUT_CHECKS(cProfileDataHand2HandUpper,
            CD2_SIZE(cProfileDataHand2HandUpper, 0x34)
            CD2_OFFSET(cProfileDataHand2HandUpper, m_unmodelledData4, 4))
    };
}
#endif
