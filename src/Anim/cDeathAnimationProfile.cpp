#include "Anim/cDeathAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cDeathAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cDeathProfileData::HandleAttributeData(*this, packet);
    }

    const char *cDeathAnimationProfile::RetClassName() const
    {
        return "cDeathAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cDeathAnimationProfileRegistrar(
        "cDeathAnimationProfile", cDeathAnimationProfile::MakeNew, 0x44, false);

    // CD2 0x824FD660: the class factory.
    RWS::CAttributeHandler *cDeathAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cDeathAnimationProfile;
    }
}
