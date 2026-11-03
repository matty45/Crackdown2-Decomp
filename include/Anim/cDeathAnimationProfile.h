#ifndef Anim_cDeathAnimationProfile_H
#define Anim_cDeathAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cDeathProfileData.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cDeathAnimationProfile : public cSpecificAnimationProfile, public cDeathProfileData
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cDeathAnimationProfile, CD2_SIZE(cDeathAnimationProfile, 0x44))
    };
}

#endif
