#ifndef Anim_cJumpLandFastAnimationProfile_H
#define Anim_cJumpLandFastAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataJumpLandFast.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cJumpLandFastAnimationProfile : public cSpecificAnimationProfile, public cProfileDataJumpLandFast
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cJumpLandFastAnimationProfile, CD2_SIZE(cJumpLandFastAnimationProfile, 0x40))
    };
}

#endif
