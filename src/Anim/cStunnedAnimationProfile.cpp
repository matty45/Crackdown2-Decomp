#include "Anim/cStunnedAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

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

    static RWS::CClassFactory::CRegistrar cStunnedAnimationProfileRegistrar(
        "cStunnedAnimationProfile", cStunnedAnimationProfile::MakeNew, 0x44, false);

    // CD2 0x82500428: the class factory.
    RWS::CAttributeHandler *cStunnedAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cStunnedAnimationProfile;
    }
}
