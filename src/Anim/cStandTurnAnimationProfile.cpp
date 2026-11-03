#include "Anim/cStandTurnAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cStandTurnAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataStandTurn::HandleAttributeData(*this, packet);
    }

    const char *cStandTurnAnimationProfile::RetClassName() const
    {
        return "cStandTurnAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cStandTurnAnimationProfileRegistrar(
        "cStandTurnAnimationProfile", cStandTurnAnimationProfile::MakeNew, 0x40, false);
}
