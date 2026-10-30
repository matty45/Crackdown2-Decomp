#include "unknown/cLaunchPadLocation.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cLaunchPadLocation::RetClassName() const
    {
        return "cLaunchPadLocation";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cLaunchPadLocationRegistrar(
        "cLaunchPadLocation", cLaunchPadLocation::MakeNew, 0xA0, false);
}
