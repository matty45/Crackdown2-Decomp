#include "rws/classfactory.h"
#include "GameManagement/cGameModeStartZone.h"

namespace GameManagement
{
    const char *cGameModeStartZone::RetClassName() const
    {
        return "cGameModeStartZone";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cGameModeStartZoneRegistrar(
        "cGameModeStartZone", cGameModeStartZone::MakeNew, 0x3d0, false);
}

#include "cd2/memory.h"

// CD2 0x828821E0: the class-factory constructor; the constructor stays out of line.
namespace GameManagement
{
    RWS::CAttributeHandler *cGameModeStartZone::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGameModeStartZone;
    }
}
