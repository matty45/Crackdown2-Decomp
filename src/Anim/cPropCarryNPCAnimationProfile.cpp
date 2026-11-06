// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cPropCarryNPCAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cPropCarryNPCAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropCarryNPC::HandleAttributeData(*this, packet);
    }

    const char *cPropCarryNPCAnimationProfile::RetClassName() const
    {
        return "cPropCarryNPCAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cPropCarryNPCAnimationProfileRegistrar(
        "cPropCarryNPCAnimationProfile", cPropCarryNPCAnimationProfile::MakeNew, 0x4C, false);
}
