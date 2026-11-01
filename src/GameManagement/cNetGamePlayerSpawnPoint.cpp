#include "rws/classfactory.h"
#include "GameManagement/cNetGamePlayerSpawnPoint.h"

namespace GameManagement
{
    const char *cNetGamePlayerSpawnPoint::RetClassName() const
    {
        return "cNetGamePlayerSpawnPoint";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cNetGamePlayerSpawnPointRegistrar(
        "cNetGamePlayerSpawnPoint", cNetGamePlayerSpawnPoint::MakeNew, 0x90, false);
}
