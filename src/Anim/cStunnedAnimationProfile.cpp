#include "Anim/cStunnedAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cStunnedAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cStunnedProfileData::HandleAttributeData(*this, packet);
    }

    const char *cStunnedAnimationProfile::RetClassName() const
    {
        return "cStunnedAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cStunnedAnimationProfileRegistrar(
        "cStunnedAnimationProfile", cStunnedAnimationProfile::MakeNew, 0x44, false);
}
