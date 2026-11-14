// Anim/cAnimationProfile.cpp: RuffKing's Libraries/Shared/Animation/cAnimationProfile.cpp.
// Animation-profile factories, runtime type queries and compact sequence setters.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cAnimationProfile.h"

extern template Anim::cAnimSequence &std::map<int, Anim::cAnimSequence, std::less<int>,
    Fun_Runtime::cAllocator<std::pair<int, Anim::cAnimSequence> > >::operator[](const int &);

namespace Anim
{
    RWS::CAttributeHandler *cSpecificAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSpecificAnimationProfile;
    }

    const char *cSpecificAnimationProfile::RetClassName() const
    {
        return "cSpecificAnimationProfile";
    }

    const Fun_Runtime::cClass &cAnimationProfile::RetClass() const
    {
        return *ms_pcAnimationProfileClass;
    }

    bool cAnimationProfile::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcAnimationProfileClass->IsA(testClass);
    }

    RWS::CAttributeHandler *cAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cAnimationProfile;
    }

    const char *cAnimationProfile::RetClassName() const
    {
        return "cAnimationProfile";
    }

    cSpecificAnimationProfile::cSpecificAnimationProfile()
    {
    }

    void cSpecificAnimationProfile::HandleAttributes(const RWS::CAttributePacket &attr)
    {
        RWS::CAttributeCommandIterator it(attr, "cSpecificAnimationProfile");
        while (!it.IsFinished())
        {
            if (it->GetCommandId() == 0)
                ReplaceLinkedMsg(m_Msg_Return_Self, it->GetAs_char_ptr(), "return cSpecificAnimationProfile*");
            ++it;
        }
    }

    void cSpecificAnimationProfile::SetRawAnimation(eActionType eType, unsigned int animIndex, int animID)
    {
        m_AnimSequenceList[eType][animIndex].SetAnimID(animID);
    }

    void cSpecificAnimationProfile::SetRateMultiplier(eActionType eType, unsigned int animIndex, float rate)
    {
        m_AnimSequenceList[eType][animIndex].SetRateMultiplier(rate);
    }

    void cSpecificAnimationProfile::SetBlendTime(eActionType eType, unsigned int animIndex, float blendTime)
    {
        m_AnimSequenceList[eType][animIndex].SetBlendToTime(blendTime);
    }

    void cSpecificAnimationProfile::SetEndBehavior(eActionType eType, unsigned int animIndex, eEndBehavior behavior)
    {
        m_AnimSequenceList[eType][animIndex].SetEndBehaviour(behavior);
    }

    const cSpecificAnimationProfile *cAnimationProfile::RetSpecificAnimationProfile(etAnimHandlers handler) const
    {
        if (m_pSpecificProfiles[handler])
            return m_pSpecificProfiles[handler];
        if (m_pParent)
            return static_cast<const cAnimationProfile *>(m_pParent)->RetSpecificAnimationProfile(handler);
        return 0;
    }

}
