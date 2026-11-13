// Script registrar source ownership: CD2 initializer 0x82F82080 names cAiTargetInfo,
// and cleanup 0x8303AB88 destroys the same descriptor. Shared interface names are ours.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cAiTargetInfo.h"
#include "AI/cTargetInfoFlagsScriptRegistration.h"
#include "AI/cTargetEventFlagsScriptRegistration.h"
#include "fun_runtime/script_type_registrar.h"

namespace AI
{
    const char *cTargetInfoFlagsScriptRegistration::RetName() const
    {
        return "eTargetInfoFlags";
    }

    const char *cTargetEventFlagsScriptRegistration::RetName() const
    {
        return "eTargetEventFlags";
    }

    bool cAiTargetInfo::IsPrimaryFireInRange() const
    {
        return m_bPrimaryFireInRange;
    }

    static Fun_Runtime::cScriptTypeRegistrar<cAiTargetInfo> cAiTargetInfoScriptRegistrar(
        "cAiTargetInfo", "cScriptHost");
    // CD2 0x82F820D8: enum object 0x8381B240, table 0x82000B28.
    static cTargetInfoFlagsScriptRegistration g_cTargetInfoFlagsScriptRegistration;

    // CD2 0x82F82120: enum object 0x8381B244, table 0x8210173C.
    static cTargetEventFlagsScriptRegistration g_cTargetEventFlagsScriptRegistration;

}
