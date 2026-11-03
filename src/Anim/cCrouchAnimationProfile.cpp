#include "Anim/cCrouchAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cCrouchAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataCrouch::HandleAttributeData(*this, packet);
    }

    const char *cCrouchAnimationProfile::RetClassName() const
    {
        return "cCrouchAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cCrouchAnimationProfileRegistrar(
        "cCrouchAnimationProfile", cCrouchAnimationProfile::MakeNew, 0x5C, false);
}
