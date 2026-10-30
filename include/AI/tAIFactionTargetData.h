// AI::tAIFactionTargetData: a faction's targeting data. Layout from the RuffKing PDB (36 bytes), confirmed in CD2:
// cFactionTargetingProfile's constructor (0x82452008) zeroes 9 words at 0x18, and HandleAttributes (0x82452160)
// stores the switch threshold at +0x18 and the two reciprocal limits at +0x1C and +0x20.
#ifndef AI_TAIFACTIONTARGETDATA_H
#define AI_TAIFACTIONTARGETDATA_H

#include "AI/tAITargetData.h"

namespace AI
{
    struct tAIFactionTargetData
    {
        const tAITargetData *m_apTargetData[6]; // 0x0: one per GangManager::eFactions
        float m_fSwitchThreshold;               // 0x18
        float m_fDistanceLimitRecip;            // 0x1C
        float m_fDamageLimitRecip;              // 0x20
    };
}

#endif // AI_TAIFACTIONTARGETDATA_H
