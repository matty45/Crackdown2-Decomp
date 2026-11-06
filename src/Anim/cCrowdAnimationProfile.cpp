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
