#include "rws/classfactory.h"
#include "GameManagement/cCheckpointArena.h"

namespace GameManagement
{
    const char *cCheckpointArena::RetClassName() const
    {
        return "cCheckpointArena";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCheckpointArenaRegistrar(
        "cCheckpointArena", cCheckpointArena::MakeNew, 0x120, false);
}
