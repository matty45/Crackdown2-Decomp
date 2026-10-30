#include "CHARACTER/cGlobalControlsProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cGlobalControlsProfile::RetClassName() const
    {
        return "cGlobalControlsProfile";
    }
}

namespace CHARACTER
{
    static RWS::CClassFactory::CRegistrar cGlobalControlsProfileRegistrar(
        "cGlobalControlsProfile", cGlobalControlsProfile::MakeNew, 0x18C, false);
}
