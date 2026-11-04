#ifndef Anim_cLedgeLaunchAnimationProfile_H
#define Anim_cLedgeLaunchAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataLedgeLaunch.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cLedgeLaunchAnimationProfile : public cSpecificAnimationProfile, public cProfileDataLedgeLaunch
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x82501308) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cLedgeLaunchAnimationProfile() : cProfileDataLedgeLaunch(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cLedgeLaunchAnimationProfile, CD2_SIZE(cLedgeLaunchAnimationProfile, 0x40))
    };
}

#endif
