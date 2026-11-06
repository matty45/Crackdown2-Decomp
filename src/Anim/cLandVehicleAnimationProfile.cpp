#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cLandVehicleAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cLandVehicleAnimationProfile::RetClassName() const
    {
        return "cLandVehicleAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cLandVehicleAnimationProfileRegistrar(
        "cLandVehicleAnimationProfile", cLandVehicleAnimationProfile::MakeNew, 0x40, false);
}
