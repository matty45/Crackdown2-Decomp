// STAND-IN: cProfileDataEquipmentCarry is named by cAnimHandlerEquipmentCarry.h.
// CD2 0x82512BC0 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAEQUIPMENTCARRY_H
#define ANIM_CPROFILEDATAEQUIPMENTCARRY_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataEquipmentCarry : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataEquipmentCarry,
            CD2_SIZE(cProfileDataEquipmentCarry, 0x4))
    };
}
#endif
