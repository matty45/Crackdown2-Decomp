#include "Anim/cGenericFullBodyAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cGenericFullBodyAnimationProfile::RetClassName() const
    {
        return "cGenericFullBodyAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cGenericFullBodyAnimationProfileRegistrar(
        "cGenericFullBodyAnimationProfile", cGenericFullBodyAnimationProfile::MakeNew, 0x40, false);
}
