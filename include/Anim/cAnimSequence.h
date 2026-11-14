// STAND-IN: RuffKing names this compact animation description. CD2's map access
// at 0x824E1318 constructs its eight bytes; setters confirm ID at 0 and end mode at 7.
#ifndef ANIM_CANIMSEQUENCE_H
#define ANIM_CANIMSEQUENCE_H
#include "Anim/animationtypes.h"
#include "cd2/layout.h"
namespace Anim
{
    class cAnimSequence
    {
    public:
        cAnimSequence();
        void SetAnimID(int animID) { m_AnimID = animID; }
        void SetRateMultiplier(float rate) { m_nRateMultiplier = static_cast<unsigned short>(rate * 100.0f); }
        void SetBlendToTime(float blendTime) { m_nBlendToTime = static_cast<unsigned char>(blendTime * 100.0f); }
        void SetEndBehaviour(eEndBehavior behavior) { m_nEndBehaviour = behavior; }
    private:
        int m_AnimID;
        unsigned short m_nRateMultiplier;
        unsigned char m_nBlendToTime;
        unsigned char m_nEndBehaviour;
        CD2_LAYOUT_CHECKS(cAnimSequence,
            CD2_SIZE(cAnimSequence, 8)
            CD2_OFFSET(cAnimSequence, m_AnimID, 0)
            CD2_OFFSET(cAnimSequence, m_nRateMultiplier, 4)
            CD2_OFFSET(cAnimSequence, m_nBlendToTime, 6)
            CD2_OFFSET(cAnimSequence, m_nEndBehaviour, 7))
    };
}
#endif
