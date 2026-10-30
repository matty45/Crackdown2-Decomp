#include "Anim/cCrowdAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cCrowdAnimationProfile::RetClassName() const
    {
        return "cCrowdAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cCrowdAnimationProfileRegistrar(
        "cCrowdAnimationProfile", cCrowdAnimationProfile::MakeNew, 0x40, false);
}
