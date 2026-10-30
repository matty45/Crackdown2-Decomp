#include "Anim/cBeaconPulseHoverAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cBeaconPulseHoverAnimationProfile::RetClassName() const
    {
        return "cBeaconPulseHoverAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cBeaconPulseHoverAnimationProfileRegistrar(
        "cBeaconPulseHoverAnimationProfile", cBeaconPulseHoverAnimationProfile::MakeNew, 0x40, false);
}
