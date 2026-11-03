#include "Anim/cPropThrowNPCAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cPropThrowNPCAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropThrowNPC::HandleAttributeData(*this, packet);
    }

    const char *cPropThrowNPCAnimationProfile::RetClassName() const
    {
        return "cPropThrowNPCAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cPropThrowNPCAnimationProfileRegistrar(
        "cPropThrowNPCAnimationProfile", cPropThrowNPCAnimationProfile::MakeNew, 0x40, false);
}
