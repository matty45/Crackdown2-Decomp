#include "Anim/cReactionAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cReactionAnimationProfile::RetClassName() const
    {
        return "cReactionAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cReactionAnimationProfileRegistrar(
        "cReactionAnimationProfile", cReactionAnimationProfile::MakeNew, 0x40, false);
}
