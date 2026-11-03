#include "Anim/cBeaconPulseHoverAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cBeaconPulseHoverAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataBeaconPulseHover::HandleAttributeData(*this, packet);
    }

    const char *cBeaconPulseHoverAnimationProfile::RetClassName() const
    {
        return "cBeaconPulseHoverAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cBeaconPulseHoverAnimationProfileRegistrar(
        "cBeaconPulseHoverAnimationProfile", cBeaconPulseHoverAnimationProfile::MakeNew, 0x40, false);
}
