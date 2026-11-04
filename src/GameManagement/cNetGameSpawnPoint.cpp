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

#include "cd2/memory.h"

// CD2 0x8284D8B0: the class-factory constructor; the constructor stays out of line.
namespace GameManagement
{
    RWS::CAttributeHandler *cNetGameSpawnPoint::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cNetGameSpawnPoint;
    }
}
