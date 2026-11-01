#include "rws/classfactory.h"
#include "GameManagement/cGameModeSpawnPoint.h"

namespace GameManagement
{
    const char *cGameModeSpawnPoint::RetClassName() const
    {
        return "cGameModeSpawnPoint";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cGameModeSpawnPointRegistrar(
        "cGameModeSpawnPoint", cGameModeSpawnPoint::MakeNew, 0x60, false);
}
