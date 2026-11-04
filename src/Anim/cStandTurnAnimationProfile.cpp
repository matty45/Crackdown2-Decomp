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

#include "cd2/memory.h"

// CD2 0x82515798: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cStandTurnAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cStandTurnAnimationProfile;
    }
}
