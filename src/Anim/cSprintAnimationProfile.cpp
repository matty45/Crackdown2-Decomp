#include "Anim/cSprintAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cSprintAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataSprint::HandleAttributeData(*this, packet);
    }

    const char *cSprintAnimationProfile::RetClassName() const
    {
        return "cSprintAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cSprintAnimationProfileRegistrar(
        "cSprintAnimationProfile", cSprintAnimationProfile::MakeNew, 0x6C, false);
}
