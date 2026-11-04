#ifndef Anim_cSprintAnimationProfile_H
#define Anim_cSprintAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataSprint.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cSprintAnimationProfile : public cSpecificAnimationProfile, public cProfileDataSprint
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x825218B8) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cSprintAnimationProfile() : cProfileDataSprint(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cSprintAnimationProfile, CD2_SIZE(cSprintAnimationProfile, 0x6C))
    };
}

#endif
