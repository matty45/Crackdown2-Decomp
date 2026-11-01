#include "rws/classfactory.h"
#include "ZoneManager/cAmbienceZone.h"

namespace ZoneManager
{
    const char *cAmbienceZone::RetClassName() const
    {
        return "cAmbienceZone";
    }
}

namespace ZoneManager
{
    static RWS::CClassFactory::CRegistrar cAmbienceZoneRegistrar(
        "cAmbienceZone", cAmbienceZone::MakeNew, 0x100, false);
}
