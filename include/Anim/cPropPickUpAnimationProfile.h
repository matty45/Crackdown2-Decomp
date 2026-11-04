#ifndef Anim_cPropPickUpAnimationProfile_H
#define Anim_cPropPickUpAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataPropPickUp.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cPropPickUpAnimationProfile : public cSpecificAnimationProfile, public cProfileDataPropPickUp
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x8250CA40) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cPropPickUpAnimationProfile() : cProfileDataPropPickUp(*this) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cPropPickUpAnimationProfile, CD2_SIZE(cPropPickUpAnimationProfile, 0x40))
    };
}

#endif
