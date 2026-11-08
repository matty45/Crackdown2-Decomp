// Activity/SquadSpawnPoint/cSquadSpawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SquadSpawnPoint/cSquadSpawnPoint.cpp.
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
#include "rws/classfactory.h"
#include "Activity/cSquadSpawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cSquadSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSquadSpawnPointClass = new Fun_Runtime::cClass(0x5D21B, "cSquadSpawnPoint", 0x1D0);
        return *cSquadSpawnPointClass;
    }

    const Fun_Runtime::cClass *cSquadSpawnPoint::ms_pcSquadSpawnPointClass = &cSquadSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cSquadSpawnPointcSpawnPointBaseInheritRegistrar(
        cSquadSpawnPoint::StaticCreateClass(), cSpawnPointBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cSquadSpawnPointRegistrar(
        "cSquadSpawnPoint", cSquadSpawnPoint::MakeNew, 0x1D0, false);
}
