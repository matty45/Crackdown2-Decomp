// AI/Mission/cMissionPropSpawnPoint.cpp: RuffKing's Libraries/Shared/AI/Mission/cMissionPropSpawnPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "AI/cMissionPropSpawnPoint.h"
#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cMissionPropSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMissionPropSpawnPointClass = new Fun_Runtime::cClass(0x9D808, "cMissionPropSpawnPoint", 0x90);
        return *cMissionPropSpawnPointClass;
    }

    const Fun_Runtime::cClass *cMissionPropSpawnPoint::ms_pcMissionPropSpawnPointClass = &cMissionPropSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cMissionPropSpawnPointcSpawnPointInheritRegistrar(
        cMissionPropSpawnPoint::StaticCreateClass(), Activity::cSpawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cMissionPropSpawnPointRegistrar(
        "cMissionPropSpawnPoint", cMissionPropSpawnPoint::MakeNew, 0x90, false);
}
