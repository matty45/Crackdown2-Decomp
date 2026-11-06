// Script registrar source ownership: CD2 initializer 0x82FD68E8 names cGameBase,
// and cleanup 0x8303FD60 destroys the same descriptor. Shared interface names are ours.

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/game_base.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/memory.h"

    static Fun_Runtime::cScriptTypeRegistrar<cGameBase> cGameBaseScriptRegistrar(
        "cGameBase", "cNonGameBase");

    Fun_Runtime::cClass &cGameBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x3EF, "cGameBase", 0x120);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cGameBase::ms_pcGameBaseClass = &cGameBase::StaticCreateClass();
