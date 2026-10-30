#include "Anim/cPropDropAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cPropDropAnimationProfile::RetClassName() const
    {
        return "cPropDropAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cPropDropAnimationProfileRegistrar(
        "cPropDropAnimationProfile", cPropDropAnimationProfile::MakeNew, 0x40, false);
}
