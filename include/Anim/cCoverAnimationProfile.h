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
        __forceinline cCoverAnimationProfile() : cProfileDataCover(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2: cCoverAnimationProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributeData(Anim::cSpecificAnimationProfile &,RWS::CAttributePacket const &); // 0: 0x824E8590
    public:
        CD2_LAYOUT_CHECKS(cCoverAnimationProfile, CD2_SIZE(cCoverAnimationProfile, 0x40))
    };
}

#endif
