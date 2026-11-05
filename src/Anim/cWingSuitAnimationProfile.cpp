#include "Anim/cWingSuitAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cWingSuitAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataWingSuit::HandleAttributeData(*this, packet);
    }

    const char *cWingSuitAnimationProfile::RetClassName() const
    {
        return "cWingSuitAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cWingSuitAnimationProfileRegistrar(
        "cWingSuitAnimationProfile", cWingSuitAnimationProfile::MakeNew, 0xDC, false);

    // CD2 0x824F3DB0: the class factory.
    RWS::CAttributeHandler *cWingSuitAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cWingSuitAnimationProfile;
    }
}
