// AI::tAITargetData: the four scores of an AI targeting profile. Layout from the RuffKing PDB (16 bytes); in CD2
// cAITargetingProfile::HandleAttributes (0x82451E18) stores the four floats at 0x18..0x24 of the profile, in the
// order of RuffKing's members and command IDs.
#ifndef AI_TAITARGETDATA_H
#define AI_TAITARGETDATA_H

namespace AI
{
    struct tAITargetData
    {
        float m_fDistancePoints;    // 0x0
        float m_fDamagePoints;      // 0x4
        float m_fVisiblePoints;     // 0x8
        float m_fBasePoints;        // 0xC
    };
}

#endif // AI_TAITARGETDATA_H
