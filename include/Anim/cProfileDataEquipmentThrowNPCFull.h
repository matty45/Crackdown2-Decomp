// STAND-IN: cProfileDataEquipmentThrowNPCFull is named by cAnimHandlerNPCEquipmentThrowFull.h.
// CD2 0x824EB598 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAEQUIPMENTTHROWNPCFULL_H
#define ANIM_CPROFILEDATAEQUIPMENTTHROWNPCFULL_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataEquipmentThrowNPCFull : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataEquipmentThrowNPCFull,
            CD2_SIZE(cProfileDataEquipmentThrowNPCFull, 0x4))
    };
}
#endif
