#include "Vehicle/cCarDamageProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cCarDamageProfile::RetClassName() const
    {
        return "cCarDamageProfile";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cCarDamageProfileRegistrar(
        "cCarDamageProfile", cCarDamageProfile::MakeNew, 0x230, false);
}
