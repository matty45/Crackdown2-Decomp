#include "Anim/cEquipmentThrowNPCFullAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cEquipmentThrowNPCFullAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataEquipmentThrowNPCFull::HandleAttributeData(*this, packet);
    }

    const char *cEquipmentThrowNPCFullAnimationProfile::RetClassName() const
    {
        return "cEquipmentThrowNPCFullAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cEquipmentThrowNPCFullAnimationProfileRegistrar(
        "cEquipmentThrowNPCFullAnimationProfile", cEquipmentThrowNPCFullAnimationProfile::MakeNew, 0x40, false);
}
