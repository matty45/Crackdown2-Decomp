#include "Anim/cHand2HandFullAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cHand2HandFullAnimationProfile::RetClassName() const
    {
        return "cHand2HandFullAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cHand2HandFullAnimationProfileRegistrar(
        "cHand2HandFullAnimationProfile", cHand2HandFullAnimationProfile::MakeNew, 0x3EE0, false);
}
