#ifndef Anim_cEquipmentCarryAnimationProfile_H
#define Anim_cEquipmentCarryAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataEquipmentCarry.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cEquipmentCarryAnimationProfile : public cSpecificAnimationProfile, public cProfileDataEquipmentCarry
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentCarryAnimationProfile, CD2_SIZE(cEquipmentCarryAnimationProfile, 0x40))
    };
}

#endif
