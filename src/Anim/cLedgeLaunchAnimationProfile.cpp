#include "Anim/cLedgeLaunchAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cLedgeLaunchAnimationProfile::RetClassName() const
    {
        return "cLedgeLaunchAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cLedgeLaunchAnimationProfileRegistrar(
        "cLedgeLaunchAnimationProfile", cLedgeLaunchAnimationProfile::MakeNew, 0x40, false);
}
