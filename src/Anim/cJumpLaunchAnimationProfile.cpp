#include "Anim/cJumpLaunchAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cJumpLaunchAnimationProfile::RetClassName() const
    {
        return "cJumpLaunchAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cJumpLaunchAnimationProfileRegistrar(
        "cJumpLaunchAnimationProfile", cJumpLaunchAnimationProfile::MakeNew, 0x40, false);
}
