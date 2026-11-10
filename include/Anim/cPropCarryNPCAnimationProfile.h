#ifndef Anim_cPropCarryNPCAnimationProfile_H
#define Anim_cPropCarryNPCAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataPropCarryNPC.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cPropCarryNPCAnimationProfile : public cSpecificAnimationProfile, public cProfileDataPropCarryNPC
    {
    public:
        // CD2 0x824EB840 inlines the derived constructor after the shared profile constructor.
        __forceinline cPropCarryNPCAnimationProfile()
            : cProfileDataPropCarryNPC(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2: cPropCarryNPCAnimationProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributeData(Anim::cSpecificAnimationProfile &,RWS::CAttributePacket const &); // 0: 0x824EBB48
    public:
        CD2_LAYOUT_CHECKS(cPropCarryNPCAnimationProfile, CD2_SIZE(cPropCarryNPCAnimationProfile, 0x4C))
    };
}

#endif
