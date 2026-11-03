#ifndef Anim_cEquipmentThrowAnimationProfile_H
#define Anim_cEquipmentThrowAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataEquipmentThrow.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cEquipmentThrowAnimationProfile : public cSpecificAnimationProfile, public cProfileDataEquipmentThrow
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentThrowAnimationProfile, CD2_SIZE(cEquipmentThrowAnimationProfile, 0x40))
    };
}

#endif
