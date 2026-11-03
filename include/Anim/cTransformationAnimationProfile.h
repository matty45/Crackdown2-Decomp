#ifndef Anim_cTransformationAnimationProfile_H
#define Anim_cTransformationAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataTransformation.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cTransformationAnimationProfile : public cSpecificAnimationProfile, public cProfileDataTransformation
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cTransformationAnimationProfile, CD2_SIZE(cTransformationAnimationProfile, 0x40))
    };
}

#endif
