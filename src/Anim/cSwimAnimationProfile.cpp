// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cSwimAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cSwimAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataSwim::HandleAttributeData(*this, packet);
    }

    const char *cSwimAnimationProfile::RetClassName() const
    {
        return "cSwimAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cSwimAnimationProfileRegistrar(
        "cSwimAnimationProfile", cSwimAnimationProfile::MakeNew, 0x4C, false);
}
