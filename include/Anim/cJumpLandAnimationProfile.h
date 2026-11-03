#ifndef Anim_cJumpLandAnimationProfile_H
#define Anim_cJumpLandAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataJumpLand.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cJumpLandAnimationProfile : public cSpecificAnimationProfile, public cProfileDataJumpLand
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cJumpLandAnimationProfile, CD2_SIZE(cJumpLandAnimationProfile, 0x4C))
    };
}

#endif
