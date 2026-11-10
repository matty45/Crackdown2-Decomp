#ifndef Anim_cSwimLaunchAnimationProfile_H
#define Anim_cSwimLaunchAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataSwimLaunch.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cSwimLaunchAnimationProfile : public cSpecificAnimationProfile, public cProfileDataSwimLaunch
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x82524370) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cSwimLaunchAnimationProfile() : cProfileDataSwimLaunch(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2: cSwimLaunchAnimationProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributeData(Anim::cSpecificAnimationProfile &,RWS::CAttributePacket const &); // 0: 0x82524508
    public:
        CD2_LAYOUT_CHECKS(cSwimLaunchAnimationProfile, CD2_SIZE(cSwimLaunchAnimationProfile, 0x40))
    };
}

#endif
