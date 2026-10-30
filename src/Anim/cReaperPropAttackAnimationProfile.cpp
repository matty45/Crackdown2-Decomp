#include "Anim/cReaperPropAttackAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cReaperPropAttackAnimationProfile::RetClassName() const
    {
        return "cReaperPropAttackAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cReaperPropAttackAnimationProfileRegistrar(
        "cReaperPropAttackAnimationProfile", cReaperPropAttackAnimationProfile::MakeNew, 0x44, false);
}
