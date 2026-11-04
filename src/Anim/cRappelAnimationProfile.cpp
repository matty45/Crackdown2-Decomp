#include "Anim/cRappelAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cRappelAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataRappel::HandleAttributeData(*this, packet);
    }

    const char *cRappelAnimationProfile::RetClassName() const
    {
        return "cRappelAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cRappelAnimationProfileRegistrar(
        "cRappelAnimationProfile", cRappelAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x824EF200: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cRappelAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRappelAnimationProfile;
    }
}
