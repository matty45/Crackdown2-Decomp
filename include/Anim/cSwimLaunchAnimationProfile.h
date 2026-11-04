#ifndef Anim_cSwimLaunchAnimationProfile_H
#define Anim_cSwimLaunchAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataSwimLaunch.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cSwimLaunchAnimationProfile : public cSpecificAnimationProfile, public cProfileDataSwimLaunch
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x82524370) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cSwimLaunchAnimationProfile() : cProfileDataSwimLaunch(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cSwimLaunchAnimationProfile, CD2_SIZE(cSwimLaunchAnimationProfile, 0x40))
    };
}

#endif
