// gom/cTargetDebugManager.cpp: RuffKing's Libraries/Shared/Targeting/cTargetDebugManager.cpp.
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
#include "gom/cTargetingDebugPage.h"
#include "gom/cTargetDebugPage.h"
#include "cd2/memory.h"

namespace GOM
{
    Fun_Runtime::cClass &cTargetingDebugPage::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTargetingDebugPageClass = new Fun_Runtime::cClass(0x517, "cTargetingDebugPage", 0x4);
        return *cTargetingDebugPageClass;
    }

    const Fun_Runtime::cClass *cTargetingDebugPage::ms_pcTargetingDebugPageClass = &cTargetingDebugPage::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cTargetingDebugPagecDebugPageHandlerInheritRegistrar(
        cTargetingDebugPage::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());

    Fun_Runtime::cClass &cTargetDebugPage::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTargetDebugPageClass = new Fun_Runtime::cClass(0x515, "cTargetDebugPage", 0x4);
        return *cTargetDebugPageClass;
    }

    const Fun_Runtime::cClass *cTargetDebugPage::ms_pcTargetDebugPageClass = &cTargetDebugPage::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cTargetDebugPagecDebugPageHandlerInheritRegistrar(
        cTargetDebugPage::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());
}
