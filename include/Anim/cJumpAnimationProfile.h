#ifndef Anim_cJumpAnimationProfile_H
#define Anim_cJumpAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataJump.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cJumpAnimationProfile : public cSpecificAnimationProfile, public cProfileDataJump
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cJumpAnimationProfile, CD2_SIZE(cJumpAnimationProfile, 0x40))
    };
}

#endif
