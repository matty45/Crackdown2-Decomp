// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cJumpLandFastAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cJumpLandFastAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataJumpLandFast::HandleAttributeData(*this, packet);
    }

    const char *cJumpLandFastAnimationProfile::RetClassName() const
    {
        return "cJumpLandFastAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cJumpLandFastAnimationProfileRegistrar(
        "cJumpLandFastAnimationProfile", cJumpLandFastAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824F32E0: the class factory.
    RWS::CAttributeHandler *cJumpLandFastAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cJumpLandFastAnimationProfile;
    }
}
