#include "Anim/cDeathAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cDeathAnimationProfile::RetClassName() const
    {
        return "cDeathAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cDeathAnimationProfileRegistrar(
        "cDeathAnimationProfile", cDeathAnimationProfile::MakeNew, 0x44, false);
}
