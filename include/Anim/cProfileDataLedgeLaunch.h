// STAND-IN: cProfileDataLedgeLaunch is named by cAnimHandlerLedgeLaunch.h.
// CD2 0x825013A8 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATALEDGELAUNCH_H
#define ANIM_CPROFILEDATALEDGELAUNCH_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataLedgeLaunch : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataLedgeLaunch,
            CD2_SIZE(cProfileDataLedgeLaunch, 0x4))
    };
}
#endif
