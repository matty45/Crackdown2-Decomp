#ifndef Anim_cGoliathAnimationProfile_H
#define Anim_cGoliathAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataGoliath.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cGoliathAnimationProfile : public cSpecificAnimationProfile, public cProfileDataGoliath
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cGoliathAnimationProfile, CD2_SIZE(cGoliathAnimationProfile, 0x4C))
    };
}

#endif
