// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cLedgeLaunchAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cLedgeLaunchAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataLedgeLaunch::HandleAttributeData(*this, packet);
    }

    const char *cLedgeLaunchAnimationProfile::RetClassName() const
    {
        return "cLedgeLaunchAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cLedgeLaunchAnimationProfileRegistrar(
        "cLedgeLaunchAnimationProfile", cLedgeLaunchAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82501308: the class factory.
    RWS::CAttributeHandler *cLedgeLaunchAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cLedgeLaunchAnimationProfile;
    }
}
