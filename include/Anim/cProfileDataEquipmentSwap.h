// STAND-IN: cProfileDataEquipmentSwap is named by cAnimHandlerEquipmentSwap.h.
// CD2 0x82513CE8 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAEQUIPMENTSWAP_H
#define ANIM_CPROFILEDATAEQUIPMENTSWAP_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataEquipmentSwap : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataEquipmentSwap(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataEquipmentSwap,
            CD2_SIZE(cProfileDataEquipmentSwap, 0x4))
    };
}
#endif
