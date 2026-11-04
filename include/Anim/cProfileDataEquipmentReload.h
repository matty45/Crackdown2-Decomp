// STAND-IN: cProfileDataEquipmentReload is named by cAnimHandlerEquipmentReload.h.
// CD2 0x825132E0 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAEQUIPMENTRELOAD_H
#define ANIM_CPROFILEDATAEQUIPMENTRELOAD_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataEquipmentReload : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataEquipmentReload(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataEquipmentReload,
            CD2_SIZE(cProfileDataEquipmentReload, 0x4))
    };
}
#endif
