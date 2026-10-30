#include "Anim/cBasePoseAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cBasePoseAnimationProfile::RetClassName() const
    {
        return "cBasePoseAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cBasePoseAnimationProfileRegistrar(
        "cBasePoseAnimationProfile", cBasePoseAnimationProfile::MakeNew, 0x40, false);
}
