#include "rws/classfactory.h"
#include "GameManagement/cNetGameSpawnPoint.h"

namespace GameManagement
{
    const char *cNetGameSpawnPoint::RetClassName() const
    {
        return "cNetGameSpawnPoint";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cNetGameSpawnPointRegistrar(
        "cNetGameSpawnPoint", cNetGameSpawnPoint::MakeNew, 0x80, false);
}
