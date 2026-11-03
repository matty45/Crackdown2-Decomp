// STAND-IN: cProfileDataPropDrop is named by cAnimHandlerPropDrop.h.
// CD2 0x8250C310 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAPROPDROP_H
#define ANIM_CPROFILEDATAPROPDROP_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataPropDrop : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataPropDrop,
            CD2_SIZE(cProfileDataPropDrop, 0x4))
    };
}
#endif
