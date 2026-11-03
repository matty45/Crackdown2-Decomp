// STAND-IN: cProfileDataJumpLand is named by cAnimHandlerJumpLand.h.
// CD2 0x824F1728 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x4C. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAJUMPLAND_H
#define ANIM_CPROFILEDATAJUMPLAND_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataJumpLand : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0xC];
        CD2_LAYOUT_CHECKS(cProfileDataJumpLand,
            CD2_SIZE(cProfileDataJumpLand, 0x10)
            CD2_OFFSET(cProfileDataJumpLand, m_unmodelledData4, 4))
    };
}
#endif
