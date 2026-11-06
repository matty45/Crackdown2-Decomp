// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cReactionAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cReactionAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataReaction::HandleAttributeData(*this, packet);
    }

    const char *cReactionAnimationProfile::RetClassName() const
    {
        return "cReactionAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cReactionAnimationProfileRegistrar(
        "cReactionAnimationProfile", cReactionAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824ED960: the class factory.
    RWS::CAttributeHandler *cReactionAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cReactionAnimationProfile;
    }
}
