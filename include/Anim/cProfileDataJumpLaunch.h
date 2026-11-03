// STAND-IN: cProfileDataJumpLaunch is named by cAnimHandlerJumpLaunch.h.
// CD2 0x824F38E0 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAJUMPLAUNCH_H
#define ANIM_CPROFILEDATAJUMPLAUNCH_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataJumpLaunch : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataJumpLaunch,
            CD2_SIZE(cProfileDataJumpLaunch, 0x4))
    };
}
#endif
