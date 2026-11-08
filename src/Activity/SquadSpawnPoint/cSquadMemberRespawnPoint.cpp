// Activity/SquadSpawnPoint/cSquadMemberRespawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SquadSpawnPoint/cSquadMemberRespawnPoint.cpp.
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
#include "Activity/cSquadMemberRespawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cSquadMemberRespawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSquadMemberRespawnPointClass = new Fun_Runtime::cClass(0x5D21D, "cSquadMemberRespawnPoint", 0x90);
        return *cSquadMemberRespawnPointClass;
    }

    const Fun_Runtime::cClass *cSquadMemberRespawnPoint::ms_pcSquadMemberRespawnPointClass = &cSquadMemberRespawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cSquadMemberRespawnPointcSquadMemberSpawnPointBaseInheritRegistrar(
        cSquadMemberRespawnPoint::StaticCreateClass(), cSquadMemberSpawnPointBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cSquadMemberRespawnPointRegistrar(
        "cSquadMemberRespawnPoint", cSquadMemberRespawnPoint::MakeNew, 0x90, false);
}
