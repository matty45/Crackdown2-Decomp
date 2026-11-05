#include "rws/classfactory.h"
#include "GameManagement/cGameModeStartZone.h"
#include "cd2/memory.h"

namespace GameManagement
{
    const char *cGameModeStartZone::RetClassName() const
    {
        return "cGameModeStartZone";
    }

    static RWS::CClassFactory::CRegistrar cGameModeStartZoneRegistrar(
        "cGameModeStartZone", cGameModeStartZone::MakeNew, 0x3d0, false);

    // CD2 0x828821E0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cGameModeStartZone::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGameModeStartZone;
    }
}
