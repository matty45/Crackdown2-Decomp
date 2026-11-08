// AI/Mission/Training/cTrainingDoorSpawnPoint.cpp: RuffKing's Libraries/Shared/AI/Mission/Training/cTrainingDoorSpawnPoint.cpp.
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
#include "AI/cTrainingDoorSpawnPoint.h"
#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cTrainingDoorSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTrainingDoorSpawnPointClass = new Fun_Runtime::cClass(0x5D31B, "cTrainingDoorSpawnPoint", 0x90);
        return *cTrainingDoorSpawnPointClass;
    }

    const Fun_Runtime::cClass *cTrainingDoorSpawnPoint::ms_pcTrainingDoorSpawnPointClass = &cTrainingDoorSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cTrainingDoorSpawnPointcSpawnPointInheritRegistrar(
        cTrainingDoorSpawnPoint::StaticCreateClass(), Activity::cSpawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cTrainingDoorSpawnPointRegistrar(
        "cTrainingDoorSpawnPoint", cTrainingDoorSpawnPoint::MakeNew, 0x90, false);
}
