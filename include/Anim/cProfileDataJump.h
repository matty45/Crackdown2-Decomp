// STAND-IN: cProfileDataJump is named by cAnimHandlerJump.h.
// CD2 0x824EF7C8 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAJUMP_H
#define ANIM_CPROFILEDATAJUMP_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataJump : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataJump(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataJump,
            CD2_SIZE(cProfileDataJump, 0x4))
    };
}
#endif
