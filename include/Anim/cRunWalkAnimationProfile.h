#ifndef Anim_cRunWalkAnimationProfile_H
#define Anim_cRunWalkAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataRunWalk.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cRunWalkAnimationProfile : public cSpecificAnimationProfile, public cProfileDataRunWalk
    {
    public:
        // CD2 0x824F7850: the allocation factory calls this constructor out of line.
        cRunWalkAnimationProfile();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cRunWalkAnimationProfile, CD2_SIZE(cRunWalkAnimationProfile, 0x1B0))
    };
}

#endif
