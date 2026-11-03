// RuffKing/Burn's field-less profile-data base; CD2's vtable at 0x8210FCC8
// dispatches HandleAttributeData to 0x824E8590.
#ifndef ANIM_CPROFILEDATACOVER_H
#define ANIM_CPROFILEDATACOVER_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataCover : public cAnimProfileData
    {
    public:
        cProfileDataCover(cSpecificAnimationProfile &);
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataCover, CD2_SIZE(cProfileDataCover, 4))
    };
}
#endif
