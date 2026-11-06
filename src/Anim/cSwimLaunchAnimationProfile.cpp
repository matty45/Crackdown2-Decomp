// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
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
