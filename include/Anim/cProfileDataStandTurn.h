// STAND-IN: cProfileDataStandTurn is named by cAnimHandlerStandTurn.h.
// CD2 0x82515838 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATASTANDTURN_H
#define ANIM_CPROFILEDATASTANDTURN_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataStandTurn : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataStandTurn(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataStandTurn,
            CD2_SIZE(cProfileDataStandTurn, 0x4))
    };
}
#endif
