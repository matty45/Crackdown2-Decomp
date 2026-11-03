#ifndef Anim_cBasePoseAnimationProfile_H
#define Anim_cBasePoseAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataBasePose.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cBasePoseAnimationProfile : public cSpecificAnimationProfile, public cProfileDataBasePose
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cBasePoseAnimationProfile, CD2_SIZE(cBasePoseAnimationProfile, 0x40))
    };
}

#endif
