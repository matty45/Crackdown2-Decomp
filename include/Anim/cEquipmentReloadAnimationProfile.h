#ifndef Anim_cEquipmentReloadAnimationProfile_H
#define Anim_cEquipmentReloadAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataEquipmentReload.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cEquipmentReloadAnimationProfile : public cSpecificAnimationProfile, public cProfileDataEquipmentReload
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentReloadAnimationProfile, CD2_SIZE(cEquipmentReloadAnimationProfile, 0x40))
    };
}

#endif
