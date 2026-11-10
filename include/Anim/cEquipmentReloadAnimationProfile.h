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
        // CD2: cEquipmentReloadAnimationProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributeData(Anim::cSpecificAnimationProfile &,RWS::CAttributePacket const &); // 0: 0x82513518
    public:
        CD2_LAYOUT_CHECKS(cEquipmentReloadAnimationProfile, CD2_SIZE(cEquipmentReloadAnimationProfile, 0x40))
    };
}

#endif
