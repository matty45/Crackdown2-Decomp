#include "Anim/cEquipmentSwapAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cEquipmentSwapAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataEquipmentSwap::HandleAttributeData(*this, packet);
    }

    const char *cEquipmentSwapAnimationProfile::RetClassName() const
    {
        return "cEquipmentSwapAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cEquipmentSwapAnimationProfileRegistrar(
        "cEquipmentSwapAnimationProfile", cEquipmentSwapAnimationProfile::MakeNew, 0x40, false);
}
