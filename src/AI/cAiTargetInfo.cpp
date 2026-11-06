// Script registrar source ownership: CD2 initializer 0x82F82080 names cAiTargetInfo,
// and cleanup 0x8303AB88 destroys the same descriptor. Shared interface names are ours.

#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cAiTargetInfo.h"
#include "fun_runtime/script_type_registrar.h"

namespace AI
{
    bool cAiTargetInfo::IsPrimaryFireInRange() const
    {
        return m_bPrimaryFireInRange;
    }

    static Fun_Runtime::cScriptTypeRegistrar<cAiTargetInfo> cAiTargetInfoScriptRegistrar(
        "cAiTargetInfo", "cScriptHost");
}
