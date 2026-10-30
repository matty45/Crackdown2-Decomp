#include "Anim/cLandVehicleAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cLandVehicleAnimationProfile::RetClassName() const
    {
        return "cLandVehicleAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cLandVehicleAnimationProfileRegistrar(
        "cLandVehicleAnimationProfile", cLandVehicleAnimationProfile::MakeNew, 0x40, false);
}
