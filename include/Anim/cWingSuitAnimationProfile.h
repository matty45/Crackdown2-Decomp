#ifndef Anim_cWingSuitAnimationProfile_H
#define Anim_cWingSuitAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataWingSuit.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cWingSuitAnimationProfile : public cSpecificAnimationProfile, public cProfileDataWingSuit
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cWingSuitAnimationProfile, CD2_SIZE(cWingSuitAnimationProfile, 0xDC))
    };
}

#endif
