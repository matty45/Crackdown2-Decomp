#include "Anim/cDeathAnimationProfile.h"
#include "rws/classfactory.h"

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
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cDeathAnimationProfileRegistrar(
        "cDeathAnimationProfile", cDeathAnimationProfile::MakeNew, 0x44, false);
}

#include "cd2/memory.h"

// CD2 0x824FD660: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cDeathAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cDeathAnimationProfile;
    }
}
