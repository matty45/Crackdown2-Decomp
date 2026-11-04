// STAND-IN: cProfileDataJumpLandFast is named by cAnimHandlerJumpLandFast.h.
// CD2 0x824F3380 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAJUMPLANDFAST_H
#define ANIM_CPROFILEDATAJUMPLANDFAST_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataJumpLandFast : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataJumpLandFast(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataJumpLandFast,
            CD2_SIZE(cProfileDataJumpLandFast, 0x4))
    };
}
#endif
