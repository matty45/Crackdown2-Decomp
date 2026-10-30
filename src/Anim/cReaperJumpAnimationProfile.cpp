#include "Anim/cReaperJumpAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cReaperJumpAnimationProfile::RetClassName() const
    {
        return "cReaperJumpAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cReaperJumpAnimationProfileRegistrar(
        "cReaperJumpAnimationProfile", cReaperJumpAnimationProfile::MakeNew, 0x40, false);
}
