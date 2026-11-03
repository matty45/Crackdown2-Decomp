#ifndef Anim_cDamageAnimationProfile_H
#define Anim_cDamageAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cDamageProfileData.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cDamageAnimationProfile : public cSpecificAnimationProfile, public cDamageProfileData
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cDamageAnimationProfile, CD2_SIZE(cDamageAnimationProfile, 0x8C))
    };
}

#endif
