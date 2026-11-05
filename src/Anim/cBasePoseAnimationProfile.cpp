#include "Anim/cBasePoseAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cBasePoseAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataBasePose::HandleAttributeData(*this, packet);
    }

    const char *cBasePoseAnimationProfile::RetClassName() const
    {
        return "cBasePoseAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cBasePoseAnimationProfileRegistrar(
        "cBasePoseAnimationProfile", cBasePoseAnimationProfile::MakeNew, 0x40, false);
}
