#ifndef Anim_cSwimAnimationProfile_H
#define Anim_cSwimAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataSwim.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cSwimAnimationProfile : public cSpecificAnimationProfile, public cProfileDataSwim
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cSwimAnimationProfile, CD2_SIZE(cSwimAnimationProfile, 0x4C))
    };
}

#endif
