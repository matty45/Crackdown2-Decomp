#ifndef Anim_cCrowdAnimationProfile_H
#define Anim_cCrowdAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataCrowd.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cCrowdAnimationProfile : public cSpecificAnimationProfile, public cProfileDataCrowd
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cCrowdAnimationProfile, CD2_SIZE(cCrowdAnimationProfile, 0x40))
    };
}

#endif
