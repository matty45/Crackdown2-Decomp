// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cEquipmentCarryAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cEquipmentCarryAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataEquipmentCarry::HandleAttributeData(*this, packet);
    }

    const char *cEquipmentCarryAnimationProfile::RetClassName() const
    {
        return "cEquipmentCarryAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cEquipmentCarryAnimationProfileRegistrar(
        "cEquipmentCarryAnimationProfile", cEquipmentCarryAnimationProfile::MakeNew, 0x40, false);
}
