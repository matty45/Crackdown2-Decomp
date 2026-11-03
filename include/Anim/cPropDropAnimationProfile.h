#ifndef Anim_cPropDropAnimationProfile_H
#define Anim_cPropDropAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataPropDrop.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cPropDropAnimationProfile : public cSpecificAnimationProfile, public cProfileDataPropDrop
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cPropDropAnimationProfile, CD2_SIZE(cPropDropAnimationProfile, 0x40))
    };
}

#endif
