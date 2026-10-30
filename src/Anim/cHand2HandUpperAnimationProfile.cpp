#include "Anim/cHand2HandUpperAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cHand2HandUpperAnimationProfile::RetClassName() const
    {
        return "cHand2HandUpperAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cHand2HandUpperAnimationProfileRegistrar(
        "cHand2HandUpperAnimationProfile", cHand2HandUpperAnimationProfile::MakeNew, 0x70, false);
}
