#include "rws/classfactory.h"
#include "GameManagement/cNetGamePickupSpawnPoint.h"

namespace GameManagement
{
    const char *cNetGamePickupSpawnPoint::RetClassName() const
    {
        return "cNetGamePickupSpawnPoint";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cNetGamePickupSpawnPointRegistrar(
        "cNetGamePickupSpawnPoint", cNetGamePickupSpawnPoint::MakeNew, 0xa0, false);
}
