// AI/Behaviour/NPC/Vehicle/AgressiveResponseBaseBehaviour.cpp: RuffKing's Libraries/Shared/AI/Behaviour/NPC/Vehicle/AgressiveResponseBaseBehaviour.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cAgressiveResponseBase.h"
#include "cd2/memory.h"

namespace AI
{
    const char *cAgressiveResponseBase::RetClassName() const
    {
        return "cAgressiveResponseBase";
    }

    const Fun_Runtime::cClass &cAgressiveResponseBase::RetClass() const
    {
        return *ms_pcAgressiveResponseBaseClass;
    }

    Fun_Runtime::cClass &cAgressiveResponseBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgressiveResponseBaseClass =
            new Fun_Runtime::cClass(g_nBehaviourClassID++, "cAgressiveResponseBase", 0x100);
        return *cAgressiveResponseBaseClass;
    }

    cAgressiveResponseBase::cAgressiveResponseBase()
    {
    }

    void cAgressiveResponseBase::vf119()
    {
        m_bClearTargetOnDeath = true;
        ChangeState(eState_Chasing);
    }
}
