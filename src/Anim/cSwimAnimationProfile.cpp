#include "Anim/cSwimAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cSwimAnimationProfile::RetClassName() const
    {
        return "cSwimAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cSwimAnimationProfileRegistrar(
        "cSwimAnimationProfile", cSwimAnimationProfile::MakeNew, 0x4C, false);
}
