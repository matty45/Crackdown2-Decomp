#include "Anim/cEquipmentReloadAnimationProfile.h"
#include "rws/classfactory.h"

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
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cEquipmentReloadAnimationProfileRegistrar(
        "cEquipmentReloadAnimationProfile", cEquipmentReloadAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x82513240: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cEquipmentReloadAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentReloadAnimationProfile;
    }
}
