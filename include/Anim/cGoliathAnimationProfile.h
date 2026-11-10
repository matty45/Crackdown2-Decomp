#ifndef Anim_cGoliathAnimationProfile_H
#define Anim_cGoliathAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataGoliath.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cGoliathAnimationProfile : public cSpecificAnimationProfile, public cProfileDataGoliath
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824ECF80) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cGoliathAnimationProfile() : cProfileDataGoliath(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2: cGoliathAnimationProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributeData(Anim::cSpecificAnimationProfile &,RWS::CAttributePacket const &); // 0: 0x824ED258
    public:
        CD2_LAYOUT_CHECKS(cGoliathAnimationProfile, CD2_SIZE(cGoliathAnimationProfile, 0x4C))
    };
}

#endif
