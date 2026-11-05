#include "Anim/cSwimLaunchAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cSwimLaunchAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataSwimLaunch::HandleAttributeData(*this, packet);
    }

    const char *cSwimLaunchAnimationProfile::RetClassName() const
    {
        return "cSwimLaunchAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cSwimLaunchAnimationProfileRegistrar(
        "cSwimLaunchAnimationProfile", cSwimLaunchAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82524370: the class factory.
    RWS::CAttributeHandler *cSwimLaunchAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSwimLaunchAnimationProfile;
    }
}
