#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cReaperJumpAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cReaperJumpAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataReaperJump::HandleAttributeData(*this, packet);
    }

    const char *cReaperJumpAnimationProfile::RetClassName() const
    {
        return "cReaperJumpAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cReaperJumpAnimationProfileRegistrar(
        "cReaperJumpAnimationProfile", cReaperJumpAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824F66A0: the class factory.
    RWS::CAttributeHandler *cReaperJumpAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cReaperJumpAnimationProfile;
    }
}
