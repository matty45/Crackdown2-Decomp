#include "Anim/cPropThrowNPCAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cPropThrowNPCAnimationProfile::RetClassName() const
    {
        return "cPropThrowNPCAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cPropThrowNPCAnimationProfileRegistrar(
        "cPropThrowNPCAnimationProfile", cPropThrowNPCAnimationProfile::MakeNew, 0x40, false);
}
