// Activity/SquadSpawnPoint/cWeaponVehicleSpawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SquadSpawnPoint/cWeaponVehicleSpawnPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "Activity/cWeaponVehicleSpawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cWeaponVehicleSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cWeaponVehicleSpawnPointClass = new Fun_Runtime::cClass(0x5D228, "cWeaponVehicleSpawnPoint", 0xB0);
        return *cWeaponVehicleSpawnPointClass;
    }

    const Fun_Runtime::cClass *cWeaponVehicleSpawnPoint::ms_pcWeaponVehicleSpawnPointClass = &cWeaponVehicleSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cWeaponVehicleSpawnPointcSquadMemberSpawnPointInheritRegistrar(
        cWeaponVehicleSpawnPoint::StaticCreateClass(), cSquadMemberSpawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cWeaponVehicleSpawnPointRegistrar(
        "cWeaponVehicleSpawnPoint", cWeaponVehicleSpawnPoint::MakeNew, 0xB0, false);
}
