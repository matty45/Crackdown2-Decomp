// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cPropCarryAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cPropCarryAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropCarry::HandleAttributeData(*this, packet);
    }

    const char *cPropCarryAnimationProfile::RetClassName() const
    {
        return "cPropCarryAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cPropCarryAnimationProfileRegistrar(
        "cPropCarryAnimationProfile", cPropCarryAnimationProfile::MakeNew, 0x44, false);
}
