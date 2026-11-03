#include "Anim/cReaperJumpAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cReaperJumpAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataReaperJump::HandleAttributeData(*this, packet);
    }

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
