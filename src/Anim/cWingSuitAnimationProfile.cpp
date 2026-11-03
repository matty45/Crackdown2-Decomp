#include "Anim/cWingSuitAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cWingSuitAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataWingSuit::HandleAttributeData(*this, packet);
    }

    const char *cWingSuitAnimationProfile::RetClassName() const
    {
        return "cWingSuitAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cWingSuitAnimationProfileRegistrar(
        "cWingSuitAnimationProfile", cWingSuitAnimationProfile::MakeNew, 0xDC, false);
}
