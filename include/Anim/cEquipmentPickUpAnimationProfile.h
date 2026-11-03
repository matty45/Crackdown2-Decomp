#ifndef Anim_cEquipmentPickUpAnimationProfile_H
#define Anim_cEquipmentPickUpAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataEquipmentPickUp.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cEquipmentPickUpAnimationProfile : public cSpecificAnimationProfile, public cProfileDataEquipmentPickUp
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentPickUpAnimationProfile, CD2_SIZE(cEquipmentPickUpAnimationProfile, 0x40))
    };
}

#endif
