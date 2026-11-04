// STAND-IN: cProfileDataReaperJump is named by cAnimHandlerReaperJump.h.
// CD2 0x824F6740 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAREAPERJUMP_H
#define ANIM_CPROFILEDATAREAPERJUMP_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataReaperJump : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataReaperJump(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataReaperJump,
            CD2_SIZE(cProfileDataReaperJump, 0x4))
    };
}
#endif
