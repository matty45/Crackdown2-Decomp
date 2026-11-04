#ifndef Anim_cCoverAnimationProfile_H
#define Anim_cCoverAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataCover.h"

namespace Anim
{
    class cCoverAnimationProfile : public cSpecificAnimationProfile, public cProfileDataCover
    {
    public:
        cCoverAnimationProfile(const RWS::CAttributePacket &);
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824E7A30) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cCoverAnimationProfile() : cProfileDataCover(*this) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cCoverAnimationProfile, CD2_SIZE(cCoverAnimationProfile, 0x40))
    };
}

#endif
