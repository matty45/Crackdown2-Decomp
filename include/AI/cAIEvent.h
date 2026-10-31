// AI::cAIEvent (Crackdown 2): STAND-IN for the event source and the size only. Evidence:
//   - CD2's registration function 0x8243D6B0 registers the script methods "RetType" and then "RetSource" (0x823E7A80,
//     which returns the word at 0x38): RuffKing's cAIEvent has exactly RetType and RetSource as accessors.
//   - RuffKing's m_pSource is a safe pointer; CD2's RetSource returns the word at 0x38 without the downcast a safe
//     pointer would need, so the field is a plain pointer here.
//   - The copy at 0x823E7A80 lies in cAiPlayer.cpp's range: the linker folded identical getters (a class in cPlayer.cpp
//     has one in its vtable 0x8213D374) and kept the copy from cAiPlayer's object, so src/AI/cAiPlayer.cpp defines it.
//   - Size 0x44: in both reference builds cDiedEvent's and cDamageTakenEvent's first field is a safe pointer right after
//     cAIEvent, and CD2's "RetKiller" (registered at 0x824418A4) and cDamageTakenEvent's "RetInstigator" (0x824416A4)
//     read that safe pointer's object pointer at 0x50, so the safe pointer is at 0x44 (AI/cDamageTakenEvent.h).
#ifndef AI_CAIEVENT_H
#define AI_CAIEVENT_H

#include "cd2/layout.h"

class cNonGameBase;

namespace AI
{
    class cAIEvent
    {
    private:
        unsigned char m_pad0[0x38];
    protected:
        cNonGameBase *m_pSource;                // 0x38
    private:
        unsigned char m_pad3C[0x44 - 0x3C];

    public:
        cNonGameBase *RetSource() const;

        CD2_LAYOUT_CHECKS(cAIEvent,
            CD2_SIZE(cAIEvent, 0x44)
            CD2_OFFSET(cAIEvent, m_pSource, 0x38))
    };
}

#endif // AI_CAIEVENT_H
