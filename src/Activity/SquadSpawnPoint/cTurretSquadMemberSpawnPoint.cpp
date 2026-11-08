// Activity/SquadSpawnPoint/cTurretSquadMemberSpawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SquadSpawnPoint/cTurretSquadMemberSpawnPoint.cpp.
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
#include "Activity/cTurretSquadMemberSpawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cTurretSquadMemberSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTurretSquadMemberSpawnPointClass = new Fun_Runtime::cClass(0x5D21F, "cTurretSquadMemberSpawnPoint", 0xC0);
        return *cTurretSquadMemberSpawnPointClass;
    }

    const Fun_Runtime::cClass *cTurretSquadMemberSpawnPoint::ms_pcTurretSquadMemberSpawnPointClass = &cTurretSquadMemberSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cTurretSquadMemberSpawnPointcSquadMemberSpawnPointInheritRegistrar(
        cTurretSquadMemberSpawnPoint::StaticCreateClass(), cSquadMemberSpawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cTurretSquadMemberSpawnPointRegistrar(
        "cTurretSquadMemberSpawnPoint", cTurretSquadMemberSpawnPoint::MakeNew, 0xC0, false);
}
