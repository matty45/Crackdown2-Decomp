#include "Anim/cEquipmentAimAndFireAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

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

    static RWS::CClassFactory::CRegistrar cEquipmentAimAndFireAnimationProfileRegistrar(
        "cEquipmentAimAndFireAnimationProfile", cEquipmentAimAndFireAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x82510510: the class factory.
    RWS::CAttributeHandler *cEquipmentAimAndFireAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentAimAndFireAnimationProfile;
    }
}
