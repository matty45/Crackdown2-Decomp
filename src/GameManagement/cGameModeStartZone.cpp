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
