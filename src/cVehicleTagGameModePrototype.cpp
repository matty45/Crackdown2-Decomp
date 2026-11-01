#include "rws/classfactory.h"
#include "unknown/cVehicleTagGameModePrototype.h"

namespace unknown
{
    const char *cVehicleTagGameModePrototype::RetClassName() const
    {
        return "cVehicleTagGameModePrototype";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cVehicleTagGameModePrototypeRegistrar(
        "cVehicleTagGameModePrototype", cVehicleTagGameModePrototype::MakeNew, 0x238, false);
}
