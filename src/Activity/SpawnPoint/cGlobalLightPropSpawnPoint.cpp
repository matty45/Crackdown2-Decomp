// Activity/SpawnPoint/cGlobalLightPropSpawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SpawnPoint/cGlobalLightPropSpawnPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "Activity/cGlobalLightPropSpawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cGlobalLightPropSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cGlobalLightPropSpawnPointClass = new Fun_Runtime::cClass(0x5D1F5, "cGlobalLightPropSpawnPoint", 0x80);
        return *cGlobalLightPropSpawnPointClass;
    }

    const Fun_Runtime::cClass *cGlobalLightPropSpawnPoint::ms_pcGlobalLightPropSpawnPointClass = &cGlobalLightPropSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cGlobalLightPropSpawnPointcSpawnPointInheritRegistrar(
        cGlobalLightPropSpawnPoint::StaticCreateClass(), cSpawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cGlobalLightPropSpawnPointRegistrar(
        "cGlobalLightPropSpawnPoint", cGlobalLightPropSpawnPoint::MakeNew, 0x80, false);
}
