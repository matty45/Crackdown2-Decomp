// Activity/SquadSpawnPoint/cSquadMemberSpawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SquadSpawnPoint/cSquadMemberSpawnPoint.cpp.
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
#include "Activity/cSquadMemberSpawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cSquadMemberSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSquadMemberSpawnPointClass = new Fun_Runtime::cClass(0x5D21C, "cSquadMemberSpawnPoint", 0xA0);
        return *cSquadMemberSpawnPointClass;
    }

    const Fun_Runtime::cClass *cSquadMemberSpawnPoint::ms_pcSquadMemberSpawnPointClass = &cSquadMemberSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cSquadMemberSpawnPointcSquadMemberSpawnPointBaseInheritRegistrar(
        cSquadMemberSpawnPoint::StaticCreateClass(), cSquadMemberSpawnPointBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cSquadMemberSpawnPointRegistrar(
        "cSquadMemberSpawnPoint", cSquadMemberSpawnPoint::MakeNew, 0xA0, false);
}
