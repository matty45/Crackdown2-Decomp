// STAND-IN: cProfileDataReaction is named by cAnimHandlerReaction.h.
// CD2 0x824EDA00 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAREACTION_H
#define ANIM_CPROFILEDATAREACTION_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataReaction : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataReaction(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataReaction,
            CD2_SIZE(cProfileDataReaction, 0x4))
    };
}
#endif
