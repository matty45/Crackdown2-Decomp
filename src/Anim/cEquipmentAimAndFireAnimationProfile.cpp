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

#include "cd2/memory.h"

// CD2 0x82510510: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cEquipmentAimAndFireAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentAimAndFireAnimationProfile;
    }
}
