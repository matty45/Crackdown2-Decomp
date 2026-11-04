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
        // __forceinline: CD2 inlines this constructor into MakeNew (0x82513C48) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cEquipmentSwapAnimationProfile() : cProfileDataEquipmentSwap(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentSwapAnimationProfile, CD2_SIZE(cEquipmentSwapAnimationProfile, 0x40))
    };
}

#endif
