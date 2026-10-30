#include "Anim/cSwimLaunchAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cSwimLaunchAnimationProfile::RetClassName() const
    {
        return "cSwimLaunchAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cSwimLaunchAnimationProfileRegistrar(
        "cSwimLaunchAnimationProfile", cSwimLaunchAnimationProfile::MakeNew, 0x40, false);
}
