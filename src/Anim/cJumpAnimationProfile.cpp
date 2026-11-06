// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cJumpAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cJumpAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataJump::HandleAttributeData(*this, packet);
    }

    const char *cJumpAnimationProfile::RetClassName() const
    {
        return "cJumpAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cJumpAnimationProfileRegistrar(
        "cJumpAnimationProfile", cJumpAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824EF728: the class factory.
    RWS::CAttributeHandler *cJumpAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cJumpAnimationProfile;
    }
}
