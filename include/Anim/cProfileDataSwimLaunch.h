// STAND-IN: cProfileDataSwimLaunch is named by cAnimHandlerSwimLaunch.h.
// CD2 0x82524410 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATASWIMLAUNCH_H
#define ANIM_CPROFILEDATASWIMLAUNCH_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataSwimLaunch : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataSwimLaunch,
            CD2_SIZE(cProfileDataSwimLaunch, 0x4))
    };
}
#endif
