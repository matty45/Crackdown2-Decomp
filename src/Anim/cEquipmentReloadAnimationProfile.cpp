// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cEquipmentReloadAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cEquipmentReloadAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataEquipmentReload::HandleAttributeData(*this, packet);
    }

    const char *cEquipmentReloadAnimationProfile::RetClassName() const
    {
        return "cEquipmentReloadAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cEquipmentReloadAnimationProfileRegistrar(
        "cEquipmentReloadAnimationProfile", cEquipmentReloadAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82513240: the class factory.
    RWS::CAttributeHandler *cEquipmentReloadAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentReloadAnimationProfile;
    }
}
