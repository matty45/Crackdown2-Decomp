#include "LaunchPad/cLaunchPadTargetLocation.h"
#include "rws/classfactory.h"

namespace LaunchPad
{
    const char *cLaunchPadTargetLocation::RetClassName() const
    {
        return "cLaunchPadTargetLocation";
    }
}

namespace LaunchPad
{
    static RWS::CClassFactory::CRegistrar cLaunchPadTargetLocationRegistrar(
        "cLaunchPadTargetLocation", cLaunchPadTargetLocation::MakeNew, 0x40, false);
}
