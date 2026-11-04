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
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824F32E0) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cJumpLandFastAnimationProfile() : cProfileDataJumpLandFast(*this) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cJumpLandFastAnimationProfile, CD2_SIZE(cJumpLandFastAnimationProfile, 0x40))
    };
}

#endif
