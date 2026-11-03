#include "Anim/cPropPickUpFullAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cPropPickUpFullAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropPickUpFull::HandleAttributeData(*this, packet);
    }

    const char *cPropPickUpFullAnimationProfile::RetClassName() const
    {
        return "cPropPickUpFullAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cPropPickUpFullAnimationProfileRegistrar(
        "cPropPickUpFullAnimationProfile", cPropPickUpFullAnimationProfile::MakeNew, 0x40, false);
}
