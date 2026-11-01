#include "rws/classfactory.h"
#include "GameManagement/cWeaponPickupSpawnPoint.h"

namespace GameManagement
{
    const char *cWeaponPickupSpawnPoint::RetClassName() const
    {
        return "cWeaponPickupSpawnPoint";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cWeaponPickupSpawnPointRegistrar(
        "cWeaponPickupSpawnPoint", cWeaponPickupSpawnPoint::MakeNew, 0xd0, false);
}
