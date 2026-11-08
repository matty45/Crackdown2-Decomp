// gom/cLimboListManager.cpp: RuffKing's Libraries/Shared/GameObjectManager/cLimboListManager.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/cLimboListManager.h"
#include "cd2/memory.h"

namespace GOM
{
    Fun_Runtime::cClass &cLimboListManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cLimboListManagerClass = new Fun_Runtime::cClass(0x7432AE5F, "cLimboListManager", 0x64);
        return *cLimboListManagerClass;
    }

    const Fun_Runtime::cClass *cLimboListManager::ms_pcLimboListManagerClass = &cLimboListManager::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cLimboListManagercManagerBaseInheritRegistrar(
        cLimboListManager::StaticCreateClass(), cManagerBase::StaticCreateClass());
}
