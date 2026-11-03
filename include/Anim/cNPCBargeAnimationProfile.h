#ifndef Anim_cNPCBargeAnimationProfile_H
#define Anim_cNPCBargeAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataNPCBarge.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cNPCBargeAnimationProfile : public cSpecificAnimationProfile, public cProfileDataNPCBarge
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cNPCBargeAnimationProfile, CD2_SIZE(cNPCBargeAnimationProfile, 0x50))
    };
}

#endif
