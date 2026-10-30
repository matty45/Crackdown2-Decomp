#include "Anim/cTurretsAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cTurretsAnimationProfile::RetClassName() const
    {
        return "cTurretsAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cTurretsAnimationProfileRegistrar(
        "cTurretsAnimationProfile", cTurretsAnimationProfile::MakeNew, 0x48, false);
}
