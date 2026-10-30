#include "Anim/cPropThrowAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cPropThrowAnimationProfile::RetClassName() const
    {
        return "cPropThrowAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cPropThrowAnimationProfileRegistrar(
        "cPropThrowAnimationProfile", cPropThrowAnimationProfile::MakeNew, 0x40, false);
}
