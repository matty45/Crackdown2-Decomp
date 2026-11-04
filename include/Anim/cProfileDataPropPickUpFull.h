// STAND-IN: cProfileDataPropPickUpFull is named by cAnimHandlerPropPickUpFull.h.
// CD2 0x8250CFB8 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAPROPPICKUPFULL_H
#define ANIM_CPROFILEDATAPROPPICKUPFULL_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataPropPickUpFull : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataPropPickUpFull(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataPropPickUpFull,
            CD2_SIZE(cProfileDataPropPickUpFull, 0x4))
    };
}
#endif
