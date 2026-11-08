// AI/Mission/cMissionCriticalPropSpawnPoint.cpp: RuffKing's Libraries/Shared/AI/Mission/cMissionCriticalPropSpawnPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "AI/cMissionCriticalPropSpawnPoint.h"
#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cMissionCriticalPropSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMissionCriticalPropSpawnPointClass = new Fun_Runtime::cClass(0x40A, "cMissionCriticalPropSpawnPoint", 0x2D0);
        return *cMissionCriticalPropSpawnPointClass;
    }

    const Fun_Runtime::cClass *cMissionCriticalPropSpawnPoint::ms_pcMissionCriticalPropSpawnPointClass = &cMissionCriticalPropSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cMissionCriticalPropSpawnPointcSpawnPointInheritRegistrar(
        cMissionCriticalPropSpawnPoint::StaticCreateClass(), Activity::cSpawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cMissionCriticalPropSpawnPointRegistrar(
        "cMissionCriticalPropSpawnPoint", cMissionCriticalPropSpawnPoint::MakeNew, 0x2D0, false);
}
