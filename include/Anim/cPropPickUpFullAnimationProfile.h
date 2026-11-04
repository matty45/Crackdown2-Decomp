#ifndef Anim_cPropPickUpFullAnimationProfile_H
#define Anim_cPropPickUpFullAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataPropPickUpFull.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cPropPickUpFullAnimationProfile : public cSpecificAnimationProfile, public cProfileDataPropPickUpFull
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x8250CF18) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cPropPickUpFullAnimationProfile() : cProfileDataPropPickUpFull(*this) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cPropPickUpFullAnimationProfile, CD2_SIZE(cPropPickUpFullAnimationProfile, 0x40))
    };
}

#endif
