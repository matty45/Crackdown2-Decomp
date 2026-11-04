// STAND-IN: cProfileDataEquipmentThrow is named by cAnimHandlerEquipmentThrow.h.
// CD2 0x825147D8 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAEQUIPMENTTHROW_H
#define ANIM_CPROFILEDATAEQUIPMENTTHROW_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataEquipmentThrow : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataEquipmentThrow(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataEquipmentThrow,
            CD2_SIZE(cProfileDataEquipmentThrow, 0x4))
    };
}
#endif
