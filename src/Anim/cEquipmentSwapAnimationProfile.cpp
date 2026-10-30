#include "Anim/cEquipmentSwapAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cEquipmentSwapAnimationProfile::RetClassName() const
    {
        return "cEquipmentSwapAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cEquipmentSwapAnimationProfileRegistrar(
        "cEquipmentSwapAnimationProfile", cEquipmentSwapAnimationProfile::MakeNew, 0x40, false);
}
