#include "Vehicle/cSixWheelerProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cSixWheelerProfile::RetClassName() const
    {
        return "cSixWheelerProfile";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cSixWheelerProfileRegistrar(
        "cSixWheelerProfile", cSixWheelerProfile::MakeNew, 0x900, false);
}
