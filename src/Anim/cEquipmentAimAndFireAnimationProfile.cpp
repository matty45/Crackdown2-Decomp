#include "Anim/cEquipmentAimAndFireAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
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
