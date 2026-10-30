#include "Anim/cGoliathAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cGoliathAnimationProfile::RetClassName() const
    {
        return "cGoliathAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cGoliathAnimationProfileRegistrar(
        "cGoliathAnimationProfile", cGoliathAnimationProfile::MakeNew, 0x4C, false);
}
