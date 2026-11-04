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
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824F1688) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cJumpLandAnimationProfile() : cProfileDataJumpLand(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cJumpLandAnimationProfile, CD2_SIZE(cJumpLandAnimationProfile, 0x4C))
    };
}

#endif
