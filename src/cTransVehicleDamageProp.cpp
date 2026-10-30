#include "unknown/cTransVehicleDamageProp.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cTransVehicleDamageProp::RetClassName() const
    {
        return "cTransVehicleDamageProp";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cTransVehicleDamagePropRegistrar(
        "cTransVehicleDamageProp", cTransVehicleDamageProp::MakeNew, 0xEE0, false);
}
