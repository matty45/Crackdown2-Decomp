#include "rws/classfactory.h"
#include "unknown/cNetGamePickupGroupMemberSpawnPoint.h"

namespace unknown
{
    const char *cNetGamePickupGroupMemberSpawnPoint::RetClassName() const
    {
        return "cNetGamePickupGroupMemberSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cNetGamePickupGroupMemberSpawnPointRegistrar(
        "cNetGamePickupGroupMemberSpawnPoint", cNetGamePickupGroupMemberSpawnPoint::MakeNew, 0xa0, false);
}
