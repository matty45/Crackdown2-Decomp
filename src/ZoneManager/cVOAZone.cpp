#include "rws/classfactory.h"
#include "ZoneManager/cVOAZone.h"

namespace ZoneManager
{
    const char *cVOAZone::RetClassName() const
    {
        return "cVOAZone";
    }
}

namespace ZoneManager
{
    static RWS::CClassFactory::CRegistrar cVOAZoneRegistrar(
        "cVOAZone", cVOAZone::MakeNew, 0x100, false);
}
