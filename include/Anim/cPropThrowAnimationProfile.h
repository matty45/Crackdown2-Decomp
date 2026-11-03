#ifndef Anim_cPropThrowAnimationProfile_H
#define Anim_cPropThrowAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataPropThrow.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cPropThrowAnimationProfile : public cSpecificAnimationProfile, public cProfileDataPropThrow
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cPropThrowAnimationProfile, CD2_SIZE(cPropThrowAnimationProfile, 0x40))
    };
}

#endif
