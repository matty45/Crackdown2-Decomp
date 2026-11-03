#include "Anim/cJumpLandFastAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cJumpLandFastAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataJumpLandFast::HandleAttributeData(*this, packet);
    }

    const char *cJumpLandFastAnimationProfile::RetClassName() const
    {
        return "cJumpLandFastAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cJumpLandFastAnimationProfileRegistrar(
        "cJumpLandFastAnimationProfile", cJumpLandFastAnimationProfile::MakeNew, 0x40, false);
}
