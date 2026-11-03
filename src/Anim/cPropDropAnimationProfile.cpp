#include "Anim/cPropDropAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cPropDropAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropDrop::HandleAttributeData(*this, packet);
    }

    const char *cPropDropAnimationProfile::RetClassName() const
    {
        return "cPropDropAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cPropDropAnimationProfileRegistrar(
        "cPropDropAnimationProfile", cPropDropAnimationProfile::MakeNew, 0x40, false);
}
