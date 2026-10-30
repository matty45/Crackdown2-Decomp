#include "Anim/cEquipmentThrowAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
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
