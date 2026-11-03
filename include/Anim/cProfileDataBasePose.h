// STAND-IN: cProfileDataBasePose is named by cAnimHandlerBasePose.h.
// CD2 0x82524B88 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATABASEPOSE_H
#define ANIM_CPROFILEDATABASEPOSE_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataBasePose : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataBasePose,
            CD2_SIZE(cProfileDataBasePose, 0x4))
    };
}
#endif
