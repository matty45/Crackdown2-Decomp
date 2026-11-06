// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cRunWalkAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cRunWalkAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataRunWalk::HandleAttributeData(*this, packet);
    }

    const char *cRunWalkAnimationProfile::RetClassName() const
    {
        return "cRunWalkAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cRunWalkAnimationProfileRegistrar(
        "cRunWalkAnimationProfile", cRunWalkAnimationProfile::MakeNew, 0x1B0, false);

    RWS::CAttributeHandler *cRunWalkAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRunWalkAnimationProfile;
    }
}
