#include "rws/classfactory.h"
#include "unknown/cNetGameDroppedPickupGroupSpawnPoint.h"

namespace unknown
{
    const char *cNetGameDroppedPickupGroupSpawnPoint::RetClassName() const
    {
        return "cNetGameDroppedPickupGroupSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cNetGameDroppedPickupGroupSpawnPointRegistrar(
        "cNetGameDroppedPickupGroupSpawnPoint", cNetGameDroppedPickupGroupSpawnPoint::MakeNew, 0x3d0, false);
}
