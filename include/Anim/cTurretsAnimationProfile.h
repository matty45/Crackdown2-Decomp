#ifndef Anim_cTurretsAnimationProfile_H
#define Anim_cTurretsAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataTurrets.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cTurretsAnimationProfile : public cSpecificAnimationProfile, public cProfileDataTurrets
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x8250EEA8) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cTurretsAnimationProfile() : cProfileDataTurrets(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cTurretsAnimationProfile, CD2_SIZE(cTurretsAnimationProfile, 0x48))
    };
}

#endif
