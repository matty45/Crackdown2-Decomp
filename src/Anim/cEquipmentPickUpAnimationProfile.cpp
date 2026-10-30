#include "Anim/cEquipmentPickUpAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
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
