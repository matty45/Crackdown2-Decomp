#include "unknown/cDefenderActivationZone.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cDefenderActivationZone::RetClassName() const
    {
        return "cDefenderActivationZone";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cDefenderActivationZoneRegistrar(
        "cDefenderActivationZone", cDefenderActivationZone::MakeNew, 0x100, false);
}
