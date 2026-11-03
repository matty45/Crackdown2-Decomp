#ifndef Anim_cPropThrowNPCAnimationProfile_H
#define Anim_cPropThrowNPCAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataPropThrowNPC.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cPropThrowNPCAnimationProfile : public cSpecificAnimationProfile, public cProfileDataPropThrowNPC
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cPropThrowNPCAnimationProfile, CD2_SIZE(cPropThrowNPCAnimationProfile, 0x40))
    };
}

#endif
