#include "Anim/cGoliathAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cGoliathAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataGoliath::HandleAttributeData(*this, packet);
    }

    const char *cGoliathAnimationProfile::RetClassName() const
    {
        return "cGoliathAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cGoliathAnimationProfileRegistrar(
        "cGoliathAnimationProfile", cGoliathAnimationProfile::MakeNew, 0x4C, false);
}
