#include "Anim/cCrouchAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cCrouchAnimationProfile::RetClassName() const
    {
        return "cCrouchAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cCrouchAnimationProfileRegistrar(
        "cCrouchAnimationProfile", cCrouchAnimationProfile::MakeNew, 0x5C, false);
}
