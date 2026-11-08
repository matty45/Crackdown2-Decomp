// RPG/cPlayerStatManager.cpp: RuffKing's Libraries/Shared/Rpg/cPlayerStatManager.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cRagdollProfile.h"
#include "CHARACTER/cCharacterController.h"
#include "AI/aiconstants.h"
#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "RPG/cPlayerStatManager.h"
#include "cd2/memory.h"

namespace RPG
{
    Fun_Runtime::cClass &cPlayerStatManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPlayerStatManagerClass = new Fun_Runtime::cClass(0x516, "cPlayerStatManager", 0x15F0);
        return *cPlayerStatManagerClass;
    }

    const Fun_Runtime::cClass *cPlayerStatManager::ms_pcPlayerStatManagerClass = &cPlayerStatManager::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cPlayerStatManagercDebugPageHandlerInheritRegistrar(
        cPlayerStatManager::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());
}
