#ifndef Anim_cEquipmentSwapAnimationProfile_H
#define Anim_cEquipmentSwapAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataEquipmentSwap.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cEquipmentSwapAnimationProfile : public cSpecificAnimationProfile, public cProfileDataEquipmentSwap
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentSwapAnimationProfile, CD2_SIZE(cEquipmentSwapAnimationProfile, 0x40))
    };
}

#endif
