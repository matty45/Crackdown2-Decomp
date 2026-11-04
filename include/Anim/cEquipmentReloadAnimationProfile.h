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
        // __forceinline: CD2 inlines this constructor into MakeNew (0x82513240) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cEquipmentReloadAnimationProfile() : cProfileDataEquipmentReload(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentReloadAnimationProfile, CD2_SIZE(cEquipmentReloadAnimationProfile, 0x40))
    };
}

#endif
