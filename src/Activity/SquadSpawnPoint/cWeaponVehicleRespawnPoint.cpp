// Activity/SquadSpawnPoint/cWeaponVehicleRespawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SquadSpawnPoint/cWeaponVehicleRespawnPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "Activity/cWeaponVehicleRespawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cWeaponVehicleRespawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cWeaponVehicleRespawnPointClass = new Fun_Runtime::cClass(0x5D219, "cWeaponVehicleRespawnPoint", 0x90);
        return *cWeaponVehicleRespawnPointClass;
    }

    const Fun_Runtime::cClass *cWeaponVehicleRespawnPoint::ms_pcWeaponVehicleRespawnPointClass = &cWeaponVehicleRespawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cWeaponVehicleRespawnPointcSquadMemberRespawnPointInheritRegistrar(
        cWeaponVehicleRespawnPoint::StaticCreateClass(), cSquadMemberRespawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cWeaponVehicleRespawnPointRegistrar(
        "cWeaponVehicleRespawnPoint", cWeaponVehicleRespawnPoint::MakeNew, 0x90, false);
}
