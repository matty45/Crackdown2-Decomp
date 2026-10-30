#include "Anim/cNPCBargeAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cNPCBargeAnimationProfile::RetClassName() const
    {
        return "cNPCBargeAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cNPCBargeAnimationProfileRegistrar(
        "cNPCBargeAnimationProfile", cNPCBargeAnimationProfile::MakeNew, 0x50, false);
}
