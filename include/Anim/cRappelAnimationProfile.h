#ifndef Anim_cRappelAnimationProfile_H
#define Anim_cRappelAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataRappel.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cRappelAnimationProfile : public cSpecificAnimationProfile, public cProfileDataRappel
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824EF200) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cRappelAnimationProfile() : cProfileDataRappel(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cRappelAnimationProfile, CD2_SIZE(cRappelAnimationProfile, 0x40))
    };
}

#endif
