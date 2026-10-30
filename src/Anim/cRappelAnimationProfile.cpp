#include "Anim/cRappelAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cRappelAnimationProfile::RetClassName() const
    {
        return "cRappelAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cRappelAnimationProfileRegistrar(
        "cRappelAnimationProfile", cRappelAnimationProfile::MakeNew, 0x40, false);
}
