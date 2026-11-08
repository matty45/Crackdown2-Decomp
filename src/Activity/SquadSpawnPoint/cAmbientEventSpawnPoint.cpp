// Activity/SquadSpawnPoint/cAmbientEventSpawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SquadSpawnPoint/cAmbientEventSpawnPoint.cpp.
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
#include "Activity/cAmbientEventSpawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cAmbientEventSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAmbientEventSpawnPointClass = new Fun_Runtime::cClass(0x74EE7, "cAmbientEventSpawnPoint", 0x100);
        return *cAmbientEventSpawnPointClass;
    }

    const Fun_Runtime::cClass *cAmbientEventSpawnPoint::ms_pcAmbientEventSpawnPointClass = &cAmbientEventSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cAmbientEventSpawnPointcSquadMemberSpawnPointInheritRegistrar(
        cAmbientEventSpawnPoint::StaticCreateClass(), cSquadMemberSpawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cAmbientEventSpawnPointRegistrar(
        "cAmbientEventSpawnPoint", cAmbientEventSpawnPoint::MakeNew, 0x100, false);
}
