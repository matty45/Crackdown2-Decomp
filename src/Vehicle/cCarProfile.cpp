#include "Vehicle/cCarProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cCarProfile::RetClassName() const
    {
        return "cCarProfile";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cCarProfileRegistrar(
        "cCarProfile", cCarProfile::MakeNew, 0x8F0, false);
}
