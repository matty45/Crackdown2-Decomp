#include "rws/classfactory.h"
#include "GameManagement/cGameModeSpawnPoint.h"
#include "cd2/memory.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cGameModeSpawnPoint::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGameModeSpawnPoint;
    }

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
