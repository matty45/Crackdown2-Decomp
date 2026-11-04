#ifndef Anim_cLedgeAnimationProfile_H
#define Anim_cLedgeAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cLedgeProfileData.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cLedgeAnimationProfile : public cSpecificAnimationProfile, public cLedgeProfileData
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x825019E8) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cLedgeAnimationProfile() : cLedgeProfileData(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cLedgeAnimationProfile, CD2_SIZE(cLedgeAnimationProfile, 0x40))
    };
}

#endif
