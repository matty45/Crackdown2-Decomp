#ifndef Anim_cHand2HandFullAnimationProfile_H
#define Anim_cHand2HandFullAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataHand2HandFull.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its aligned data base at 0x40.
    class cHand2HandFullAnimationProfile : public cSpecificAnimationProfile, public cProfileDataHand2HandFull
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cHand2HandFullAnimationProfile, CD2_SIZE(cHand2HandFullAnimationProfile, 0x3EE0))
    };
}

#endif
