#include "Anim/cSwimAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cSwimAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataSwim::HandleAttributeData(*this, packet);
    }

    const char *cSwimAnimationProfile::RetClassName() const
    {
        return "cSwimAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cSwimAnimationProfileRegistrar(
        "cSwimAnimationProfile", cSwimAnimationProfile::MakeNew, 0x4C, false);
}
