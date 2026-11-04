#include "Anim/cJumpLaunchAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cJumpLaunchAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataJumpLaunch::HandleAttributeData(*this, packet);
    }

    const char *cJumpLaunchAnimationProfile::RetClassName() const
    {
        return "cJumpLaunchAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cJumpLaunchAnimationProfileRegistrar(
        "cJumpLaunchAnimationProfile", cJumpLaunchAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x824F3840: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cJumpLaunchAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cJumpLaunchAnimationProfile;
    }
}
