// Script registrar source ownership: CD2 initializer 0x83000A00 names cScriptHost,
// and cleanup 0x83041F30 destroys the same descriptor. Shared interface names are ours.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/scripthost.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/memory.h"

namespace Fun_Runtime
{
    static Fun_Runtime::cScriptTypeRegistrar<cScriptHost> cScriptHostScriptRegistrar(
        "cScriptHost", "Host");

    Fun_Runtime::cClass &cScriptHost::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x3F1, "cScriptHost", 0x1C);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cScriptHost::ms_pcScriptHostClass = &cScriptHost::StaticCreateClass();
}
