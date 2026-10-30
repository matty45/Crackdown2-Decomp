#include "GangManager/cVehicleDataPrototype.h"
#include "rws/classfactory.h"

namespace GangManager
{
    const char *cVehicleDataPrototype::RetClassName() const
    {
        return "cVehicleDataPrototype";
    }
}

namespace GangManager
{
    static RWS::CClassFactory::CRegistrar cVehicleDataPrototypeRegistrar(
        "cVehicleDataPrototype", cVehicleDataPrototype::MakeNew, 0x58, false);
}
