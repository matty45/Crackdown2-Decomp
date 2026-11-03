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
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cEquipmentCarryAnimationProfileRegistrar(
        "cEquipmentCarryAnimationProfile", cEquipmentCarryAnimationProfile::MakeNew, 0x40, false);
}
