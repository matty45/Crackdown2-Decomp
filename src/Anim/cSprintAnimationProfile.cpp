#include "Anim/cSprintAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cSprintAnimationProfile::RetClassName() const
    {
        return "cSprintAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cSprintAnimationProfileRegistrar(
        "cSprintAnimationProfile", cSprintAnimationProfile::MakeNew, 0x6C, false);
}
