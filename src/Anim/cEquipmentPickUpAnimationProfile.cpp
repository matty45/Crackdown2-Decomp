#include "Anim/cEquipmentPickUpAnimationProfile.h"
#include "rws/classfactory.h"

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
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cEquipmentPickUpAnimationProfileRegistrar(
        "cEquipmentPickUpAnimationProfile", cEquipmentPickUpAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x82512DD0: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cEquipmentPickUpAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentPickUpAnimationProfile;
    }
}
