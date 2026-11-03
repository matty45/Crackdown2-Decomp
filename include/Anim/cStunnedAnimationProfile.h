#ifndef Anim_cStunnedAnimationProfile_H
#define Anim_cStunnedAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cStunnedProfileData.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cStunnedAnimationProfile : public cSpecificAnimationProfile, public cStunnedProfileData
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cStunnedAnimationProfile, CD2_SIZE(cStunnedAnimationProfile, 0x44))
    };
}

#endif
