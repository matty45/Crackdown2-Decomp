#ifndef Anim_cCrouchAnimationProfile_H
#define Anim_cCrouchAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataCrouch.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cCrouchAnimationProfile : public cSpecificAnimationProfile, public cProfileDataCrouch
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cCrouchAnimationProfile, CD2_SIZE(cCrouchAnimationProfile, 0x5C))
    };
}

#endif
