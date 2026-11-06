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
