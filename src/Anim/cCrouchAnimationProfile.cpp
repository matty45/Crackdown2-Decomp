#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cCrouchAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cCrouchAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataCrouch::HandleAttributeData(*this, packet);
    }

    const char *cCrouchAnimationProfile::RetClassName() const
    {
        return "cCrouchAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cCrouchAnimationProfileRegistrar(
        "cCrouchAnimationProfile", cCrouchAnimationProfile::MakeNew, 0x5C, false);
}
