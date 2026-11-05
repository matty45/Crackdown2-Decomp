#include "rws/classfactory.h"
#include "GameManagement/cNetGamePickupSpawnPoint.h"
#include "cd2/memory.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cNetGamePickupSpawnPoint::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cNetGamePickupSpawnPoint;
    }
}

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
