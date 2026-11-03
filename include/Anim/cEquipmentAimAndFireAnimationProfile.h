#ifndef Anim_cEquipmentAimAndFireAnimationProfile_H
#define Anim_cEquipmentAimAndFireAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataEquipmentAimAndFire.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cEquipmentAimAndFireAnimationProfile : public cSpecificAnimationProfile, public cProfileDataEquipmentAimAndFire
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentAimAndFireAnimationProfile, CD2_SIZE(cEquipmentAimAndFireAnimationProfile, 0x40))
    };
}

#endif
