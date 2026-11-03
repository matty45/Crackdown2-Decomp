// STAND-IN: cProfileDataTransformation is named by cAnimHandlerTransformation.h.
// CD2 0x82524888 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATATRANSFORMATION_H
#define ANIM_CPROFILEDATATRANSFORMATION_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataTransformation : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataTransformation,
            CD2_SIZE(cProfileDataTransformation, 0x4))
    };
}
#endif
