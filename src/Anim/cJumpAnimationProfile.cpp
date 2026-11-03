#include "Anim/cJumpAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cJumpAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataJump::HandleAttributeData(*this, packet);
    }

    const char *cJumpAnimationProfile::RetClassName() const
    {
        return "cJumpAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cJumpAnimationProfileRegistrar(
        "cJumpAnimationProfile", cJumpAnimationProfile::MakeNew, 0x40, false);
}
