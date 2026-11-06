// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cCrowdAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cCrowdAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataCrowd::HandleAttributeData(*this, packet);
    }

    const char *cCrowdAnimationProfile::RetClassName() const
    {
        return "cCrowdAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cCrowdAnimationProfileRegistrar(
        "cCrowdAnimationProfile", cCrowdAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82524D88: the class factory.
    RWS::CAttributeHandler *cCrowdAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCrowdAnimationProfile;
    }
}
