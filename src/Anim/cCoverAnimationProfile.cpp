#include "Anim/cCoverAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cCoverAnimationProfile::RetClassName() const
    {
        return "cCoverAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cCoverAnimationProfileRegistrar(
        "cCoverAnimationProfile", cCoverAnimationProfile::MakeNew, 0x40, false);
}
