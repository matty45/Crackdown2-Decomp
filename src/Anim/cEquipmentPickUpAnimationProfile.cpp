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
