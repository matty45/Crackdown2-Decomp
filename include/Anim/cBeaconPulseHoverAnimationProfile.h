#ifndef Anim_cBeaconPulseHoverAnimationProfile_H
#define Anim_cBeaconPulseHoverAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataBeaconPulseHover.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cBeaconPulseHoverAnimationProfile : public cSpecificAnimationProfile, public cProfileDataBeaconPulseHover
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824EC1A0) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cBeaconPulseHoverAnimationProfile() : cProfileDataBeaconPulseHover(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2: cBeaconPulseHoverAnimationProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributeData(Anim::cSpecificAnimationProfile &,RWS::CAttributePacket const &); // 0: 0x824EC288
    public:
        CD2_LAYOUT_CHECKS(cBeaconPulseHoverAnimationProfile, CD2_SIZE(cBeaconPulseHoverAnimationProfile, 0x40))
    };
}

#endif
