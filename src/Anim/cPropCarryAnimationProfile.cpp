#include "Anim/cPropCarryAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cPropCarryAnimationProfile::RetClassName() const
    {
        return "cPropCarryAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cPropCarryAnimationProfileRegistrar(
        "cPropCarryAnimationProfile", cPropCarryAnimationProfile::MakeNew, 0x44, false);
}
