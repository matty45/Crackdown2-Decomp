#include "Anim/cWingSuitAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cWingSuitAnimationProfile::RetClassName() const
    {
        return "cWingSuitAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cWingSuitAnimationProfileRegistrar(
        "cWingSuitAnimationProfile", cWingSuitAnimationProfile::MakeNew, 0xDC, false);
}
