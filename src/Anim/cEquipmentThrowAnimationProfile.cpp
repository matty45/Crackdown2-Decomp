#include "Anim/cEquipmentThrowAnimationProfile.h"
#include "rws/classfactory.h"

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
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cEquipmentThrowAnimationProfileRegistrar(
        "cEquipmentThrowAnimationProfile", cEquipmentThrowAnimationProfile::MakeNew, 0x40, false);
}
