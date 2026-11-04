// STAND-IN: cProfileDataCrowd is named by cAnimHandlerCrowd.h.
// CD2 0x82524E28 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATACROWD_H
#define ANIM_CPROFILEDATACROWD_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataCrowd : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataCrowd(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataCrowd,
            CD2_SIZE(cProfileDataCrowd, 0x4))
    };
}
#endif
