#include "Anim/cPropThrowAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cPropThrowAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropThrow::HandleAttributeData(*this, packet);
    }

    const char *cPropThrowAnimationProfile::RetClassName() const
    {
        return "cPropThrowAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cPropThrowAnimationProfileRegistrar(
        "cPropThrowAnimationProfile", cPropThrowAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x8250D9A0: the class factory.
    RWS::CAttributeHandler *cPropThrowAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPropThrowAnimationProfile;
    }
}
