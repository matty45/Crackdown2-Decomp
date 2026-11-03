// STAND-IN: cProfileDataPropPickUp is named by cAnimHandlerPropPickUp.h.
// CD2 0x8250CAE0 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAPROPPICKUP_H
#define ANIM_CPROFILEDATAPROPPICKUP_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataPropPickUp : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataPropPickUp,
            CD2_SIZE(cProfileDataPropPickUp, 0x4))
    };
}
#endif
