// AI::cAiTargetInfo (Crackdown 2): STAND-IN for two flags only. RuffKing names. Evidence:
//   - The script methods "IsPrimaryFireBlocked" and "IsTargetVisible" (registered by 0x822572C8, next to the
//     "eTargetEventFlags" enum) are 0x823E7C30 (returns the byte at 0x20) and 0x823E7C38 (the byte at 0x2E). RuffKing's
//     cAiTargetInfo has m_bPrimaryFireBlocked at 0x8 and m_bVisible at 0x16: 0xE apart, as here.
//   - Both copies lie in cAiPlayer.cpp's range: the linker folded identical getters and kept the copies from
//     cAiPlayer's object, so src/AI/cAiPlayer.cpp defines them.
#ifndef AI_CAITARGETINFO_H
#define AI_CAITARGETINFO_H

#include "cd2/layout.h"

namespace AI
{
    class cAiTargetInfo
    {
    private:
        unsigned char m_pad0[0x20];
    protected:
        bool m_bPrimaryFireBlocked;             // 0x20
    private:
        unsigned char m_pad21[0x2E - 0x21];
    protected:
        bool m_bVisible;                        // 0x2E

    public:
        bool IsPrimaryFireBlocked() const;
        bool IsTargetVisible() const;

        CD2_LAYOUT_CHECKS(cAiTargetInfo,
            CD2_OFFSET(cAiTargetInfo, m_bPrimaryFireBlocked, 0x20)
            CD2_OFFSET(cAiTargetInfo, m_bVisible, 0x2E))
    };
}

#endif // AI_CAITARGETINFO_H
