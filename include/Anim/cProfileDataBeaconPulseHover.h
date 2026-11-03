// STAND-IN: cProfileDataBeaconPulseHover is named by cAnimHandlerBeaconPulseHover.h.
// CD2 0x824EC240 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATABEACONPULSEHOVER_H
#define ANIM_CPROFILEDATABEACONPULSEHOVER_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataBeaconPulseHover : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataBeaconPulseHover,
            CD2_SIZE(cProfileDataBeaconPulseHover, 0x4))
    };
}
#endif
