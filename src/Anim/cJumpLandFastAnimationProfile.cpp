#include "Anim/cJumpLandFastAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cJumpLandFastAnimationProfile::RetClassName() const
    {
        return "cJumpLandFastAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cJumpLandFastAnimationProfileRegistrar(
        "cJumpLandFastAnimationProfile", cJumpLandFastAnimationProfile::MakeNew, 0x40, false);
}
