// CHARACTER::cCwTransCharacterWrapper: the player's character class in Crackdown 2 (CD2 only; Burn renamed it
// cPlayerCharacterWrapper: Burn's CHARACTER::EmitTransCharacterClassSizeBreakDown, in cPlayerCharacterWrapper.cpp,
// prints the "Trans Character" sizes). STAND-IN, sized to CD2; only what matched code needs so far. Evidence (CD2):
//   - StaticCreateClass 0x8253EE20 builds cClass(0x672, "cCwTransCharacterWrapper", 0x5B40); the initializer 0x82FAC110
//     stores its result in the class pointer 0x83823D4C, which RetClass (0x8253ECF8) and IsA (0x8253ED08) read.
//   - Base: its constructor 0x82267148 (SpawnFromPrototype 0x8253EDE8 tail-calls it) first calls cCwTransCharacter's
//     constructor 0x82231358 (CHARACTER/cCwTransCharacter.h).
//   - m_Targeting (0x2E00): a TGT::cPlayerTargeting, built by 0x827790F0(member, this) and stored in m_pTargeting by
//     the constructor; RuffKing's cFrontEndAgent and Burn's cPlayerCharacterWrapper have TGT::cPlayerTargeting
//     m_Targeting.
//   - m_AiTargeting (0x35C0; the name is ours): a TGT::cAiTargeting (vptr 0x82147B98, owner at +4).
//   - SetAITargeting is ours: PLAYER::cPlayer::SetAITargeting (0x82724998) writes m_pTargeting directly, which the
//     original could only do through an inline accessor (m_pTargeting is protected in RuffKing).
#ifndef CHARACTER_CCWTRANSCHARACTERWRAPPER_H
#define CHARACTER_CCWTRANSCHARACTERWRAPPER_H

#include "fun_runtime/class.h"
#include "CHARACTER/cCwTransCharacter.h"
#include "TGT/cPlayerTargeting.h"
#include "TGT/cAiTargeting.h"

namespace CHARACTER
{
    class cCwTransCharacterWrapper : public cCwTransCharacter
    {
    private:
        TGT::cPlayerTargeting m_Targeting;      // 0x2E00
        TGT::cAiTargeting m_AiTargeting;        // 0x35C0
        unsigned char m_pad3620[0x5B40 - 0x3620];

    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcCwTransCharacterWrapperClass;     // 0x83823D4C

        void SetAITargeting(bool bAITargeting)
        {
            if (bAITargeting)
                m_pTargeting = &m_AiTargeting;
            else
                m_pTargeting = &m_Targeting;
        }

        CD2_LAYOUT_CHECKS(cCwTransCharacterWrapper,
            CD2_SIZE(cCwTransCharacterWrapper, 0x5B40)
            CD2_OFFSET(cCwTransCharacterWrapper, m_Targeting, 0x2E00)
            CD2_OFFSET(cCwTransCharacterWrapper, m_AiTargeting, 0x35C0))
    };
}

#endif // CHARACTER_CCWTRANSCHARACTERWRAPPER_H
