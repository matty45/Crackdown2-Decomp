#ifndef Anim_cReaperJumpAnimationProfile_H
#define Anim_cReaperJumpAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataReaperJump.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cReaperJumpAnimationProfile : public cSpecificAnimationProfile, public cProfileDataReaperJump
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cReaperJumpAnimationProfile, CD2_SIZE(cReaperJumpAnimationProfile, 0x40))
    };
}

#endif
