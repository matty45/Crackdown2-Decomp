// AI::CellMinigunPrototype (Crackdown 2): STAND-IN. RuffKing's class (CellMinigunPrototype.h): NPCBehaviourPrototype
// (0x90 bytes in CD2 too) and its floats from 0x90. CD2's CellMinigun::OnAttacking (0x824C3BB8) and OnInvestigating
// (0x824C3AB0) pass the float at prototype +0x9C to the target info's CanPrimaryFire, as RuffKing's pass
// m_fSuppressDuration. The complete size (RuffKing 0xB0) is not established in CD2.
#ifndef AI_CELLMINIGUNPROTOTYPE_H
#define AI_CELLMINIGUNPROTOTYPE_H

#include "AI/NPCBehaviourPrototype.h"

namespace AI
{
    class CellMinigunPrototype : public NPCBehaviourPrototype
    {
    public:
        float m_fViewRange;                     // 0x90
        float m_fMoveToDist;                    // 0x94
        float m_fMaxRange;                      // 0x98
        float m_fSuppressDuration;              // 0x9C

        CD2_LAYOUT_CHECKS(CellMinigunPrototype,
            CD2_OFFSET(CellMinigunPrototype, m_fSuppressDuration, 0x9C))
    };
}

#endif // AI_CELLMINIGUNPROTOTYPE_H
