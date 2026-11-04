#ifndef Anim_cReaperPropAttackAnimationProfile_H
#define Anim_cReaperPropAttackAnimationProfile_H

#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cProfileDataReaperPropAttack.h"

namespace Anim
{
    // STAND-IN: reference base order; CD2 HandleAttributes forwards to its data base at 0x3C.
    class cReaperPropAttackAnimationProfile : public cSpecificAnimationProfile, public cProfileDataReaperPropAttack
    {
    public:
        // __forceinline: CD2 inlines this constructor into MakeNew (0x824EC6E0) over cSpecificAnimationProfile's
        // out-of-line constructor (0x824E00A8).
        __forceinline cReaperPropAttackAnimationProfile() : cProfileDataReaperPropAttack(static_cast<cSpecificAnimationProfile &>(*this)) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cReaperPropAttackAnimationProfile, CD2_SIZE(cReaperPropAttackAnimationProfile, 0x44))
    };
}

#endif
