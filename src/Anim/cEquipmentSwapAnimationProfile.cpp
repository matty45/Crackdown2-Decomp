#include "Anim/cEquipmentSwapAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

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

    static RWS::CClassFactory::CRegistrar cEquipmentSwapAnimationProfileRegistrar(
        "cEquipmentSwapAnimationProfile", cEquipmentSwapAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82513C48: the class factory.
    RWS::CAttributeHandler *cEquipmentSwapAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentSwapAnimationProfile;
    }
}
