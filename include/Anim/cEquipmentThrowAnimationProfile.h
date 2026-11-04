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
        // __forceinline: CD2 inlines this constructor into MakeNew (0x82514738) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cEquipmentThrowAnimationProfile() : cProfileDataEquipmentThrow(*this) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentThrowAnimationProfile, CD2_SIZE(cEquipmentThrowAnimationProfile, 0x40))
    };
}

#endif
