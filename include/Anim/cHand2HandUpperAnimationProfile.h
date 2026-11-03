#ifndef Anim_cHand2HandUpperAnimationProfile_H
#define Anim_cHand2HandUpperAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataHand2HandUpper.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cHand2HandUpperAnimationProfile : public cSpecificAnimationProfile, public cProfileDataHand2HandUpper
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cHand2HandUpperAnimationProfile, CD2_SIZE(cHand2HandUpperAnimationProfile, 0x70))
    };
}

#endif
