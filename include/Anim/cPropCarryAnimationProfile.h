#ifndef Anim_cPropCarryAnimationProfile_H
#define Anim_cPropCarryAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataPropCarry.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cPropCarryAnimationProfile : public cSpecificAnimationProfile, public cProfileDataPropCarry
    {
    public:
        // CD2 inlines the derived construction into MakeNew, after the shared profile constructor.
        __forceinline cPropCarryAnimationProfile()
            : cProfileDataPropCarry(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cPropCarryAnimationProfile, CD2_SIZE(cPropCarryAnimationProfile, 0x44))
    };
}

#endif
