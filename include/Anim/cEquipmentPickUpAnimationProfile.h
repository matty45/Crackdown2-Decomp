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
        // __forceinline: CD2 inlines this constructor into MakeNew (0x82512DD0) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cEquipmentPickUpAnimationProfile() : cProfileDataEquipmentPickUp(*this) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentPickUpAnimationProfile, CD2_SIZE(cEquipmentPickUpAnimationProfile, 0x40))
    };
}

#endif
