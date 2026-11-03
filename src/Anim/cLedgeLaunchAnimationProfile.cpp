#include "Anim/cLedgeLaunchAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cLedgeLaunchAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataLedgeLaunch::HandleAttributeData(*this, packet);
    }

    const char *cLedgeLaunchAnimationProfile::RetClassName() const
    {
        return "cLedgeLaunchAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cLedgeLaunchAnimationProfileRegistrar(
        "cLedgeLaunchAnimationProfile", cLedgeLaunchAnimationProfile::MakeNew, 0x40, false);
}
