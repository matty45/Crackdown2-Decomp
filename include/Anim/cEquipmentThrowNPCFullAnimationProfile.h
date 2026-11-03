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
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cEquipmentThrowNPCFullAnimationProfile, CD2_SIZE(cEquipmentThrowNPCFullAnimationProfile, 0x40))
    };
}

#endif
