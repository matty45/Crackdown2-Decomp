#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cEquipmentThrowAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cEquipmentThrowAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataEquipmentThrow::HandleAttributeData(*this, packet);
    }

    const char *cEquipmentThrowAnimationProfile::RetClassName() const
    {
        return "cEquipmentThrowAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cEquipmentThrowAnimationProfileRegistrar(
        "cEquipmentThrowAnimationProfile", cEquipmentThrowAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82514738: the class factory.
    RWS::CAttributeHandler *cEquipmentThrowAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentThrowAnimationProfile;
    }
}
