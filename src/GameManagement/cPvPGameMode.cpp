// GameManagement::cPvPGameModePrototype: reference names from RuffKing's cPvPGameMode.cpp.
// CD2 constructor 0x8283E2F8 installs table 0x8215B308; its getters confirm the arrays and timeout.
// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "GameManagement/cPvPGameModePrototype.h"
#include <xtl.h>
namespace GameManagement
{
    unsigned int cPvPGameModePrototype::RetDefaultTimeLimit()
    {
        return m_aDefaultTimeLimit;
    }

    unsigned int cPvPGameModePrototype::RetEndLimit(unsigned int index) const
    {
        return m_aEndLimits[index];
    }

    unsigned int cPvPGameModePrototype::RetTimeLimit(unsigned int index) const
    {
        return m_aTimeLimits[index];
    }

    float cPvPGameModePrototype::RetSpawnPointTimeOut() const
    {
        return m_fSpawnPointTimeOut;
    }

    cPvPGameModePrototype::cPvPGameModePrototype()
        : m_pGameDamageProfile(0), m_nNumOrbsForKill(0),
          m_fKillSkillPointsModifier(0.0f), m_fDeathSkillPointsModifier(0.0f),
          m_fSpawnPointTimeOut(0.0f)
    {
        // CD2 clears each limits array with a separate XMemSet call.
        XMemSet(m_aEndLimits, 0, sizeof(m_aEndLimits));
        XMemSet(m_aTimeLimits, 0, sizeof(m_aTimeLimits));
    }
}
