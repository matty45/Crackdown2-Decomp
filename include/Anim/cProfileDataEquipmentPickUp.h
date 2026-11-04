// STAND-IN: cProfileDataEquipmentPickUp is named by cAnimHandlerEquipmentPickUp.h.
// CD2 0x82512E70 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAEQUIPMENTPICKUP_H
#define ANIM_CPROFILEDATAEQUIPMENTPICKUP_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataEquipmentPickUp : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataEquipmentPickUp(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataEquipmentPickUp,
            CD2_SIZE(cProfileDataEquipmentPickUp, 0x4))
    };
}
#endif
