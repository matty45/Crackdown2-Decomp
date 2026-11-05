#include "Anim/cStandTurnAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

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

    static RWS::CClassFactory::CRegistrar cStandTurnAnimationProfileRegistrar(
        "cStandTurnAnimationProfile", cStandTurnAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82515798: the class factory.
    RWS::CAttributeHandler *cStandTurnAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cStandTurnAnimationProfile;
    }
}
