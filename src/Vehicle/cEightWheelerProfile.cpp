#include "Vehicle/cEightWheelerProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cEightWheelerProfile::RetClassName() const
    {
        return "cEightWheelerProfile";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cEightWheelerProfileRegistrar(
        "cEightWheelerProfile", cEightWheelerProfile::MakeNew, 0x8F0, false);
}
