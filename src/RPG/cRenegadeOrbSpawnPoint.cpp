// RPG/cRenegadeOrbSpawnPoint.cpp: RuffKing's Libraries/Shared/RPG/cRenegadeOrbSpawnPoint.cpp.
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
#include "RPG/cRenegadeOrbSpawnPoint.h"
#include "cd2/memory.h"

namespace RPG
{
    Fun_Runtime::cClass &cRenegadeOrbSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cRenegadeOrbSpawnPointClass = new Fun_Runtime::cClass(0x67C, "cRenegadeOrbSpawnPoint", 0x90);
        return *cRenegadeOrbSpawnPointClass;
    }

    const Fun_Runtime::cClass *cRenegadeOrbSpawnPoint::ms_pcRenegadeOrbSpawnPointClass = &cRenegadeOrbSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cRenegadeOrbSpawnPointcSpawnPointBaseInheritRegistrar(
        cRenegadeOrbSpawnPoint::StaticCreateClass(), Activity::cSpawnPointBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cRenegadeOrbSpawnPointRegistrar(
        "cRenegadeOrbSpawnPoint", cRenegadeOrbSpawnPoint::MakeNew, 0x90, false);
}
