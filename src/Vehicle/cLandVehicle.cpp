#include "Vehicle/cLandVehicle.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cLandVehicle::RetClassName() const
    {
        return "cLandVehicle";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cLandVehicleRegistrar(
        "cLandVehicle", cLandVehicle::MakeNew, 0x28C0, false);
}
