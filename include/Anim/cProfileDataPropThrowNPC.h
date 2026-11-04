// STAND-IN: cProfileDataPropThrowNPC is named by cAnimHandlerNPCPropThrowFull.h.
// CD2 0x824EBF38 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAPROPTHROWNPC_H
#define ANIM_CPROFILEDATAPROPTHROWNPC_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataPropThrowNPC : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataPropThrowNPC(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataPropThrowNPC,
            CD2_SIZE(cProfileDataPropThrowNPC, 0x4))
    };
}
#endif
