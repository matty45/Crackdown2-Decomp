#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "fun_runtime/retval.h"
#include "Vehicle/cLandVehicleProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    RWS::CAttributeHandler *cLandVehicleProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cLandVehicleProfile;
    }

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
