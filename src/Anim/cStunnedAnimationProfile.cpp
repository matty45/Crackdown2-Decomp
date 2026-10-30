#include "Anim/cStunnedAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cStunnedAnimationProfile::RetClassName() const
    {
        return "cStunnedAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cStunnedAnimationProfileRegistrar(
        "cStunnedAnimationProfile", cStunnedAnimationProfile::MakeNew, 0x44, false);
}
