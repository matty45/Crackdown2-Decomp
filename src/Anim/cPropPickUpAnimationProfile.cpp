#include "Anim/cPropPickUpAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cPropPickUpAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropPickUp::HandleAttributeData(*this, packet);
    }

    const char *cPropPickUpAnimationProfile::RetClassName() const
    {
        return "cPropPickUpAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cPropPickUpAnimationProfileRegistrar(
        "cPropPickUpAnimationProfile", cPropPickUpAnimationProfile::MakeNew, 0x40, false);
}
