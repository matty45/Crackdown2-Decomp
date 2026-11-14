// RPG/cSkillPickupManager.cpp: RuffKing's Libraries/Shared/Rpg/cSkillPickupManager.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "RPG/skill_pickup_debug.h"
#include "ORB/cSkillPickupManager.h"
#include "ORB/cSkillPickupProfile.h"
#include <string.h>

namespace RPG
{
    bool g_bTestSkillPickup = true;

    void ToggleSkillPickupTest(void *, wchar_t *)
    {
        g_bTestSkillPickup = !g_bTestSkillPickup;
    }
}

namespace ORB
{
    cSkillPickupManager::cSkillPickupManager() : m_pPlayer(0)
    {
        tSkillPickupPool *pools = m_aSkillPickupPool;
        memset(pools, 0, sizeof(m_aSkillPickupPool));
        cSkillPickupProfile *profile = cSkillPickupProfile::RetSingleton();
        SetMaxPickups(eSP_Agility, profile->m_aSkillPickupData[eSP_Agility].nMaxPickups);
        SetMaxPickups(eSP_Driving, profile->m_aSkillPickupData[eSP_Driving].nMaxPickups);
        SetMaxPickups(eSP_Explosives, profile->m_aSkillPickupData[eSP_Explosives].nMaxPickups);
        SetMaxPickups(eSP_Strength, profile->m_aSkillPickupData[eSP_Strength].nMaxPickups);
        SetMaxPickups(eSP_FireArms, profile->m_aSkillPickupData[eSP_FireArms].nMaxPickups);
        tSkillPickupData *data = cSkillPickupProfile::RetSingleton()->m_aSkillPickupData;
        for (tSkillPickupPool *pool = pools, *end = pools + eSP_Num; pool != end; ++pool)
        {
            pool->pData = data++;
            pool->aDropping = pool->aSkillPickup;
            pool->aCollecting = pool->aSkillPickup;
        }
    }
}
