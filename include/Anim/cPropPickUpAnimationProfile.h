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
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cPropPickUpAnimationProfile, CD2_SIZE(cPropPickUpAnimationProfile, 0x40))
    };
}

#endif
