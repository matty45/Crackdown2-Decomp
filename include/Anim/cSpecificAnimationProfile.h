// STAND-IN: RuffKing/Burn base order. CD2 constructor 0x824E00A8 initializes
// CAttributeHandler at 0, CEventHandler at 0x18, the event ID at 0x1C and two
// 12-byte sequence maps at 0x24. The constructor takes no packet in CD2.
#ifndef ANIM_CSPECIFICANIMATIONPROFILE_H
#define ANIM_CSPECIFICANIMATIONPROFILE_H

#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "rws/eventid.h"
#include "fun_runtime/class.h"
#include "Anim/cAnimSequence.h"
#include "fun_runtime/map.h"

namespace Anim
{
    class cSpecificAnimationProfile : public RWS::CAttributeHandler, public RWS::CEventHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        cSpecificAnimationProfile();
        virtual ~cSpecificAnimationProfile();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void HandleEvents(RWS::CMsg &);
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        void SetRawAnimation(eActionType, unsigned int animIndex, int animID);
        void SetRateMultiplier(eActionType, unsigned int animIndex, float rate);
        void SetBlendTime(eActionType, unsigned int animIndex, float blendTime);
        void SetEndBehavior(eActionType, unsigned int animIndex, eEndBehavior);
        typedef Fun_Runtime::cMap<int, cAnimSequence> HAnimSequenceList;
    protected:
        RWS::CEventId m_Msg_Return_Self;
        HAnimSequenceList m_AnimSequenceList[eAT_Num];
        CD2_LAYOUT_CHECKS(cSpecificAnimationProfile,
            CD2_SIZE(cSpecificAnimationProfile, 0x3C)
            CD2_OFFSET(cSpecificAnimationProfile, m_Msg_Return_Self, 0x1C)
            CD2_OFFSET(cSpecificAnimationProfile, m_AnimSequenceList, 0x24))
    };
}
#endif
