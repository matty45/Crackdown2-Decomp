#ifndef Anim_cJumpLaunchAnimationProfile_H
#define Anim_cJumpLaunchAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataJumpLaunch.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cJumpLaunchAnimationProfile : public cSpecificAnimationProfile, public cProfileDataJumpLaunch
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824F3840) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cJumpLaunchAnimationProfile() : cProfileDataJumpLaunch(*this) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cJumpLaunchAnimationProfile, CD2_SIZE(cJumpLaunchAnimationProfile, 0x40))
    };
}

#endif
