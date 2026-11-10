#ifndef Anim_cJumpLandAnimationProfile_H
#define Anim_cJumpLandAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataJumpLand.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cJumpLandAnimationProfile : public cSpecificAnimationProfile, public cProfileDataJumpLand
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824F1688) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cJumpLandAnimationProfile() : cProfileDataJumpLand(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2: cJumpLandAnimationProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributeData(Anim::cSpecificAnimationProfile &,RWS::CAttributePacket const &); // 0: 0x824F20E0
    public:
        CD2_LAYOUT_CHECKS(cJumpLandAnimationProfile, CD2_SIZE(cJumpLandAnimationProfile, 0x4C))
    };
}

#endif
