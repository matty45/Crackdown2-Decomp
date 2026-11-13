// Core/cScheduler.cpp: RuffKing's Libraries/Shared/Core/cScheduler.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Core/cScheduler.h"
#include "cd2/memory.h"

namespace Core
{
    Fun_Runtime::cClass &cScheduler::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSchedulerClass = new Fun_Runtime::cClass(0x522, "cScheduler", 0x44);
        return *cSchedulerClass;
    }

    const Fun_Runtime::cClass *cScheduler::ms_pcSchedulerClass = &cScheduler::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cSchedulercDebugPageHandlerInheritRegistrar(
        cScheduler::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());
}
