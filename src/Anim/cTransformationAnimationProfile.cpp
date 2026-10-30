#include "Anim/cTransformationAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cTransformationAnimationProfile::RetClassName() const
    {
        return "cTransformationAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cTransformationAnimationProfileRegistrar(
        "cTransformationAnimationProfile", cTransformationAnimationProfile::MakeNew, 0x40, false);
}
