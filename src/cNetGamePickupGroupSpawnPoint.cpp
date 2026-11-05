#include "rws/classfactory.h"
#include "unknown/cNetGamePickupGroupSpawnPoint.h"

namespace unknown
{
    const char *cNetGamePickupGroupSpawnPoint::RetClassName() const
    {
        return "cNetGamePickupGroupSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cNetGamePickupGroupSpawnPointRegistrar(
        "cNetGamePickupGroupSpawnPoint", cNetGamePickupGroupSpawnPoint::MakeNew, 0x120, false);
}
