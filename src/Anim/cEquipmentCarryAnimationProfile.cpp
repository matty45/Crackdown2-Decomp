#include "Anim/cEquipmentCarryAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cEquipmentCarryAnimationProfile::RetClassName() const
    {
        return "cEquipmentCarryAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cEquipmentCarryAnimationProfileRegistrar(
        "cEquipmentCarryAnimationProfile", cEquipmentCarryAnimationProfile::MakeNew, 0x40, false);
}
