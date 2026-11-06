// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cEquipmentPickUpAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cEquipmentPickUpAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataEquipmentPickUp::HandleAttributeData(*this, packet);
    }

    const char *cEquipmentPickUpAnimationProfile::RetClassName() const
    {
        return "cEquipmentPickUpAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cEquipmentPickUpAnimationProfileRegistrar(
        "cEquipmentPickUpAnimationProfile", cEquipmentPickUpAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82512DD0: the class factory.
    RWS::CAttributeHandler *cEquipmentPickUpAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentPickUpAnimationProfile;
    }
}
