// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cEquipmentAimAndFireAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cEquipmentAimAndFireAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataEquipmentAimAndFire::HandleAttributeData(*this, packet);
    }

    const char *cEquipmentAimAndFireAnimationProfile::RetClassName() const
    {
        return "cEquipmentAimAndFireAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cEquipmentAimAndFireAnimationProfileRegistrar(
        "cEquipmentAimAndFireAnimationProfile", cEquipmentAimAndFireAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82510510: the class factory.
    RWS::CAttributeHandler *cEquipmentAimAndFireAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentAimAndFireAnimationProfile;
    }
}
