#include "Anim/cCrowdAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cCrowdAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataCrowd::HandleAttributeData(*this, packet);
    }

    const char *cCrowdAnimationProfile::RetClassName() const
    {
        return "cCrowdAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cCrowdAnimationProfileRegistrar(
        "cCrowdAnimationProfile", cCrowdAnimationProfile::MakeNew, 0x40, false);
}
