#include "Vehicle/cGenericCarDamageProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cGenericCarDamageProfile::RetClassName() const
    {
        return "cGenericCarDamageProfile";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cGenericCarDamageProfileRegistrar(
        "cGenericCarDamageProfile", cGenericCarDamageProfile::MakeNew, 0x5C, false);
}
