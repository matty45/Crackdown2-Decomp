// STAND-IN: cProfileDataEquipmentAimAndFire is named by cAnimHandlerEquipmentAimAndFire.h.
// CD2 0x825105B0 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAEQUIPMENTAIMANDFIRE_H
#define ANIM_CPROFILEDATAEQUIPMENTAIMANDFIRE_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataEquipmentAimAndFire : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataEquipmentAimAndFire(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataEquipmentAimAndFire,
            CD2_SIZE(cProfileDataEquipmentAimAndFire, 0x4))
    };
}
#endif
