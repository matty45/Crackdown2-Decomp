// STAND-IN: cProfileDataPropThrow is named by cAnimHandlerPropThrow.h.
// CD2 0x8250DA40 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAPROPTHROW_H
#define ANIM_CPROFILEDATAPROPTHROW_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataPropThrow : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataPropThrow,
            CD2_SIZE(cProfileDataPropThrow, 0x4))
    };
}
#endif
