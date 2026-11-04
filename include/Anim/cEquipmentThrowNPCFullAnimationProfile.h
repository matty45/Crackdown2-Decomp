#ifndef Anim_cEquipmentThrowNPCFullAnimationProfile_H
#define Anim_cEquipmentThrowNPCFullAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataEquipmentThrowNPCFull.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cEquipmentThrowNPCFullAnimationProfile : public cSpecificAnimationProfile, public cProfileDataEquipmentThrowNPCFull
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824EB4F8) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cEquipmentThrowNPCFullAnimationProfile() : cProfileDataEquipmentThrowNPCFull(*this) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentThrowNPCFullAnimationProfile, CD2_SIZE(cEquipmentThrowNPCFullAnimationProfile, 0x40))
    };
}

#endif
