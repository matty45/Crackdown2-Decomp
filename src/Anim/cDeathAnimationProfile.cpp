// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cDeathAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cDeathAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cDeathProfileData::HandleAttributeData(*this, packet);
    }

    const char *cDeathAnimationProfile::RetClassName() const
    {
        return "cDeathAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cDeathAnimationProfileRegistrar(
        "cDeathAnimationProfile", cDeathAnimationProfile::MakeNew, 0x44, false);

    // CD2 0x824FD660: the class factory.
    RWS::CAttributeHandler *cDeathAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cDeathAnimationProfile;
    }
}
