#include "rws/classfactory.h"
#include "unknown/cVehicleTagGameModePrototype.h"

namespace unknown
{
    const char *cVehicleTagGameModePrototype::RetClassName() const
    {
        return "cVehicleTagGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cVehicleTagGameModePrototypeRegistrar(
        "cVehicleTagGameModePrototype", cVehicleTagGameModePrototype::MakeNew, 0x238, false);
}
