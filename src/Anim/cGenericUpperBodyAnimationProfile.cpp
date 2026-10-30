#include "Anim/cGenericUpperBodyAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cGenericUpperBodyAnimationProfile::RetClassName() const
    {
        return "cGenericUpperBodyAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cGenericUpperBodyAnimationProfileRegistrar(
        "cGenericUpperBodyAnimationProfile", cGenericUpperBodyAnimationProfile::MakeNew, 0x40, false);
}
