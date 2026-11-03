#include "Anim/cTurretsAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cTurretsAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataTurrets::HandleAttributeData(*this, packet);
    }

    const char *cTurretsAnimationProfile::RetClassName() const
    {
        return "cTurretsAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cTurretsAnimationProfileRegistrar(
        "cTurretsAnimationProfile", cTurretsAnimationProfile::MakeNew, 0x48, false);
}
