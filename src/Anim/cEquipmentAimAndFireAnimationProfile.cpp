#include "Anim/cEquipmentAimAndFireAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cEquipmentAimAndFireAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataEquipmentAimAndFire::HandleAttributeData(*this, packet);
    }

    const char *cEquipmentAimAndFireAnimationProfile::RetClassName() const
    {
        return "cEquipmentAimAndFireAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cEquipmentAimAndFireAnimationProfileRegistrar(
        "cEquipmentAimAndFireAnimationProfile", cEquipmentAimAndFireAnimationProfile::MakeNew, 0x40, false);
}
