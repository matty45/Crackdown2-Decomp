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

#include "cd2/memory.h"

// CD2 0x824EC1A0: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cBeaconPulseHoverAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cBeaconPulseHoverAnimationProfile;
    }
}
