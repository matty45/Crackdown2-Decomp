#include "fun_runtime/retval.h"
#include "Vehicle/cLandVehicleProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cLandVehicleProfile::RetClassName() const
    {
        return "cLandVehicleProfile";
    }

    cLandVehicleProfile::~cLandVehicleProfile()
    {
    }

    static RWS::CClassFactory::CRegistrar cLandVehicleProfileRegistrar(
        "cLandVehicleProfile", cLandVehicleProfile::MakeNew, 0x8E0, false);

    Fun_Runtime::RetVal cLandVehicleProfile::Term()
    {
        return Ret_OK;
    }
}
