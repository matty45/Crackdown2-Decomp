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
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824EAF90) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cNPCBargeAnimationProfile() : cProfileDataNPCBarge(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2: cNPCBargeAnimationProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributeData(Anim::cSpecificAnimationProfile &,RWS::CAttributePacket const &); // 0: 0x824EB258
    public:
        CD2_LAYOUT_CHECKS(cNPCBargeAnimationProfile, CD2_SIZE(cNPCBargeAnimationProfile, 0x50))
    };
}

#endif
