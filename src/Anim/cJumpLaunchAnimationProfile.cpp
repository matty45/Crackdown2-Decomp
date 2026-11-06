#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cJumpLaunchAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

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

    static RWS::CClassFactory::CRegistrar cJumpLaunchAnimationProfileRegistrar(
        "cJumpLaunchAnimationProfile", cJumpLaunchAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824F3840: the class factory.
    RWS::CAttributeHandler *cJumpLaunchAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cJumpLaunchAnimationProfile;
    }
}
