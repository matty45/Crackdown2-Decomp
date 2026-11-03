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
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cLedgeLaunchAnimationProfile, CD2_SIZE(cLedgeLaunchAnimationProfile, 0x40))
    };
}

#endif
