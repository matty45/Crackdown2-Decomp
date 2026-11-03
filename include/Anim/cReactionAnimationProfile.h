#ifndef Anim_cReactionAnimationProfile_H
#define Anim_cReactionAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataReaction.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cReactionAnimationProfile : public cSpecificAnimationProfile, public cProfileDataReaction
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cReactionAnimationProfile, CD2_SIZE(cReactionAnimationProfile, 0x40))
    };
}

#endif
