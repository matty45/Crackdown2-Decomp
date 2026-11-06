// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cStandTurnAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cStandTurnAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataStandTurn::HandleAttributeData(*this, packet);
    }

    const char *cStandTurnAnimationProfile::RetClassName() const
    {
        return "cStandTurnAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cStandTurnAnimationProfileRegistrar(
        "cStandTurnAnimationProfile", cStandTurnAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82515798: the class factory.
    RWS::CAttributeHandler *cStandTurnAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cStandTurnAnimationProfile;
    }
}
