#include "Anim/cEquipmentReloadAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
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
