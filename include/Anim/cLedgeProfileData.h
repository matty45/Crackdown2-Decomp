// STAND-IN: cLedgeProfileData is named by cLedgeHandler.h.
// CD2 0x82501A88 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CLEDGEPROFILEDATA_H
#define ANIM_CLEDGEPROFILEDATA_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cLedgeProfileData : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cLedgeProfileData(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cLedgeProfileData,
            CD2_SIZE(cLedgeProfileData, 0x4))
    };
}
#endif
