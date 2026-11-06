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
