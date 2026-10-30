#include "Anim/cJumpAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cJumpAnimationProfile::RetClassName() const
    {
        return "cJumpAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cJumpAnimationProfileRegistrar(
        "cJumpAnimationProfile", cJumpAnimationProfile::MakeNew, 0x40, false);
}
