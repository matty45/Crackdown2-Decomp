// STAND-IN: reference names/base order. CD2 MakeNew 0x824DFFE0 allocates 0x108,
// constructs two maps at 0x24, then clears fifty profile pointers at 0x3C and
// its parent at 0x104. Retail has no reference-build profile-name strings.
#ifndef ANIM_CANIMATIONPROFILE_H
#define ANIM_CANIMATIONPROFILE_H
#include "Anim/cSpecificAnimationProfile.h"
#include "Anim/cAnimData.h"
#include "Anim/etAnimHandlers.h"
#include "rws/systemcommands.h"
namespace Anim
{
    class cAnimationProfile : public RWS::CAttributeHandler, public RWS::CEventHandler,
                              public RWS::CSystemCommands
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 expands construction into MakeNew; ordinary inline leaves a constructor call under /Ob1.
        __forceinline cAnimationProfile() : m_pParent(0)
        {
            for (unsigned int i = 0; i != eNumHandlers; ++i)
                m_pSpecificProfiles[i] = 0;
        }
        virtual ~cAnimationProfile();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void HandleEvents(RWS::CMsg &);
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual bool HandleDataInNewDesignBuild(); // Reference override; CD2 primary slot 9 is the true-return stub.
        static const Fun_Runtime::cClass *ms_pcAnimationProfileClass; // CD2 0x8382130C, RetClass at 0x824DFF70.
        const cSpecificAnimationProfile *RetSpecificAnimationProfile(etAnimHandlers) const;
        cSpecificAnimationProfile *RetSpecificAnimationProfile(etAnimHandlers);
        typedef Fun_Runtime::cMap<int, cAnimData> HAnimDataList;
    protected:
        RWS::CEventId m_Msg_Return_Self;
        HAnimDataList m_AnimDataList[eAT_Num];
        cSpecificAnimationProfile *m_pSpecificProfiles[eNumHandlers];
        cAnimationProfile *m_pParent;
        CD2_LAYOUT_CHECKS(cAnimationProfile,
            CD2_SIZE(cAnimationProfile, 0x108)
            CD2_OFFSET(cAnimationProfile, m_Msg_Return_Self, 0x1C)
            CD2_OFFSET(cAnimationProfile, m_AnimDataList, 0x24)
            CD2_OFFSET(cAnimationProfile, m_pSpecificProfiles, 0x3C)
            CD2_OFFSET(cAnimationProfile, m_pParent, 0x104))
    };
}
#endif
