#ifndef Anim_cStandTurnAnimationProfile_H
#define Anim_cStandTurnAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataStandTurn.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cStandTurnAnimationProfile : public cSpecificAnimationProfile, public cProfileDataStandTurn
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cStandTurnAnimationProfile, CD2_SIZE(cStandTurnAnimationProfile, 0x40))
    };
}

#endif
