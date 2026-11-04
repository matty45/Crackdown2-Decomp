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

#include "cd2/memory.h"

// CD2 0x82514738: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cEquipmentThrowAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentThrowAnimationProfile;
    }
}
