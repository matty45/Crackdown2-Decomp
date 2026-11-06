// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cJumpLandAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cJumpLandAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataJumpLand::HandleAttributeData(*this, packet);
    }

    const char *cJumpLandAnimationProfile::RetClassName() const
    {
        return "cJumpLandAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cJumpLandAnimationProfileRegistrar(
        "cJumpLandAnimationProfile", cJumpLandAnimationProfile::MakeNew, 0x4C, false);

    // CD2 0x824F1688: the class factory.
    RWS::CAttributeHandler *cJumpLandAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cJumpLandAnimationProfile;
    }
}
