#ifndef Anim_cEquipmentAimAndFireAnimationProfile_H
#define Anim_cEquipmentAimAndFireAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataEquipmentAimAndFire.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cEquipmentAimAndFireAnimationProfile : public cSpecificAnimationProfile, public cProfileDataEquipmentAimAndFire
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x82510510) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cEquipmentAimAndFireAnimationProfile() : cProfileDataEquipmentAimAndFire(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2: cEquipmentAimAndFireAnimationProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributeData(Anim::cSpecificAnimationProfile &,RWS::CAttributePacket const &); // 0: 0x82510820
    public:
        CD2_LAYOUT_CHECKS(cEquipmentAimAndFireAnimationProfile, CD2_SIZE(cEquipmentAimAndFireAnimationProfile, 0x40))
    };
}

#endif
