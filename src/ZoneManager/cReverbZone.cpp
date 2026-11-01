#include "rws/classfactory.h"
#include "ZoneManager/cReverbZone.h"

namespace ZoneManager
{
    const char *cReverbZone::RetClassName() const
    {
        return "cReverbZone";
    }
}

namespace ZoneManager
{
    static RWS::CClassFactory::CRegistrar cReverbZoneRegistrar(
        "cReverbZone", cReverbZone::MakeNew, 0x150, false);
}
