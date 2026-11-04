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
        // __forceinline: CD2 inlines this constructor into MakeNew (0x82524D88) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cCrowdAnimationProfile() : cProfileDataCrowd(*this) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cCrowdAnimationProfile, CD2_SIZE(cCrowdAnimationProfile, 0x40))
    };
}

#endif
