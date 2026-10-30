#include "Vehicle/cLandVehicleProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cLandVehicleProfile::RetClassName() const
    {
        return "cLandVehicleProfile";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cLandVehicleProfileRegistrar(
        "cLandVehicleProfile", cLandVehicleProfile::MakeNew, 0x8E0, false);
}
