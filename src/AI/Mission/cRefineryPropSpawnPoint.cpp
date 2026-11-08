// AI/Mission/cRefineryPropSpawnPoint.cpp: RuffKing's Libraries/Shared/AI/Mission/cRefineryPropSpawnPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "AI/cRefineryPropSpawnPoint.h"
#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cRefineryPropSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cRefineryPropSpawnPointClass = new Fun_Runtime::cClass(0x405, "cRefineryPropSpawnPoint", 0x2E0);
        return *cRefineryPropSpawnPointClass;
    }

    const Fun_Runtime::cClass *cRefineryPropSpawnPoint::ms_pcRefineryPropSpawnPointClass = &cRefineryPropSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cRefineryPropSpawnPointcMissionCriticalPropSpawnPointInheritRegistrar(
        cRefineryPropSpawnPoint::StaticCreateClass(), cMissionCriticalPropSpawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cRefineryPropSpawnPointRegistrar(
        "cRefineryPropSpawnPoint", cRefineryPropSpawnPoint::MakeNew, 0x2E0, false);
}
