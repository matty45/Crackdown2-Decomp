// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cNPCBargeAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cNPCBargeAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataNPCBarge::HandleAttributeData(*this, packet);
    }

    const char *cNPCBargeAnimationProfile::RetClassName() const
    {
        return "cNPCBargeAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cNPCBargeAnimationProfileRegistrar(
        "cNPCBargeAnimationProfile", cNPCBargeAnimationProfile::MakeNew, 0x50, false);

    // CD2 0x824EAF90: the class factory.
    RWS::CAttributeHandler *cNPCBargeAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cNPCBargeAnimationProfile;
    }
}
