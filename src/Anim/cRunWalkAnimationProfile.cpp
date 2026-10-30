#include "Anim/cRunWalkAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cRunWalkAnimationProfile::RetClassName() const
    {
        return "cRunWalkAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cRunWalkAnimationProfileRegistrar(
        "cRunWalkAnimationProfile", cRunWalkAnimationProfile::MakeNew, 0x1B0, false);
}
