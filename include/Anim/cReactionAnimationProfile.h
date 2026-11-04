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
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824ED960) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cReactionAnimationProfile() : cProfileDataReaction(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cReactionAnimationProfile, CD2_SIZE(cReactionAnimationProfile, 0x40))
    };
}

#endif
