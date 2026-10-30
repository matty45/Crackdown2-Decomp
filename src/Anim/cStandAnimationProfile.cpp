#include "Anim/cStandAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cStandAnimationProfile::RetClassName() const
    {
        return "cStandAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cStandAnimationProfileRegistrar(
        "cStandAnimationProfile", cStandAnimationProfile::MakeNew, 0x60, false);
}
