// AI::cAiTargetInfo (Crackdown 2): STAND-IN for two flags only. RuffKing names. Evidence:
//   - The script methods "IsPrimaryFireBlocked" and "IsTargetVisible" (registered by 0x822572C8, next to the
//     "eTargetEventFlags" enum) are 0x823E7C30 (returns the byte at 0x20) and 0x823E7C38 (the byte at 0x2E). RuffKing's
//     cAiTargetInfo has m_bPrimaryFireBlocked at 0x8 and m_bVisible at 0x16: 0xE apart, as here.
//   - Both copies lie in cAiPlayer.cpp's range: the linker folded identical getters and kept the copies from
//     cAiPlayer's object, so src/AI/cAiPlayer.cpp defines them.
#ifndef AI_CAITARGETINFO_H
#define AI_CAITARGETINFO_H

#include "cd2/layout.h"
#include "fun_runtime/class.h"

namespace AI
{
    class cAiTargetInfo
    {
    private:
        unsigned char m_pad0[0x1C];
        // RuffKing field name; CD2 registers the getter at 0x8244D9A0 under this name.
        bool m_bPrimaryFireInRange;
        unsigned char m_pad1D[0x20 - 0x1D];
    protected:
        bool m_bPrimaryFireBlocked;             // 0x20
    private:
        unsigned char m_pad21[0x2E - 0x21];
    protected:
        bool m_bVisible;                        // 0x2E
    private:
        unsigned char m_pad2F[0x37 - 0x2F];
    protected:
        // RuffKing's names and order (its +0x1E/+0x1F). CellMinigun::OnAttacking (0x824C3BB8) tests 0x38 before 0x37,
        // as RuffKing's tests m_bIsDeleted before m_bIsAlive.
        bool m_bIsAlive;                        // 0x37
        bool m_bIsDeleted;                      // 0x38

    public:
        // CD2 0x8244DCD8 builds the cClass "cAiTargetInfo"; cAiTargetPositionInfo's inheritance registrar
        // (0x82F82898) calls it for the parent.
        static Fun_Runtime::cClass &StaticCreateClass();
        bool IsPrimaryFireInRange() const;
        bool IsPrimaryFireBlocked() const;
        bool IsTargetVisible() const;
        // RuffKing's; CD2 0x82450418 (CellMinigun's OnAttacking/OnInvestigating pass the suppress duration).
        bool CanPrimaryFire(float fSuppressingFireTime) const;
        // RuffKing's accessors; CD2's behaviours read the bytes in place.
        bool IsTargetAlive() const { return m_bIsAlive; }
        bool IsTargetDeleted() const { return m_bIsDeleted; }

        CD2_LAYOUT_CHECKS(cAiTargetInfo,
            CD2_OFFSET(cAiTargetInfo, m_bPrimaryFireInRange, 0x1C)
            CD2_OFFSET(cAiTargetInfo, m_bPrimaryFireBlocked, 0x20)
            CD2_OFFSET(cAiTargetInfo, m_bVisible, 0x2E)
            CD2_OFFSET(cAiTargetInfo, m_bIsAlive, 0x37)
            CD2_OFFSET(cAiTargetInfo, m_bIsDeleted, 0x38))
    };
}

#endif // AI_CAITARGETINFO_H
