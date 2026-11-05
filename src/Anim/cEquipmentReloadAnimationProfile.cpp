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
