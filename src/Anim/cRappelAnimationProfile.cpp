#include "Anim/cRappelAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

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

    static RWS::CClassFactory::CRegistrar cRappelAnimationProfileRegistrar(
        "cRappelAnimationProfile", cRappelAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824EF200: the class factory.
    RWS::CAttributeHandler *cRappelAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRappelAnimationProfile;
    }
}
