#include "Anim/cLedgeAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cLedgeAnimationProfile::RetClassName() const
    {
        return "cLedgeAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cLedgeAnimationProfileRegistrar(
        "cLedgeAnimationProfile", cLedgeAnimationProfile::MakeNew, 0x40, false);
}
