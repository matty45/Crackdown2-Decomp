#include "Anim/cJumpLandAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cJumpLandAnimationProfile::RetClassName() const
    {
        return "cJumpLandAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cJumpLandAnimationProfileRegistrar(
        "cJumpLandAnimationProfile", cJumpLandAnimationProfile::MakeNew, 0x4C, false);
}
