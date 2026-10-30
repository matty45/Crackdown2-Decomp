#include "Anim/cEquipmentThrowNPCFullAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cEquipmentThrowNPCFullAnimationProfile::RetClassName() const
    {
        return "cEquipmentThrowNPCFullAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cEquipmentThrowNPCFullAnimationProfileRegistrar(
        "cEquipmentThrowNPCFullAnimationProfile", cEquipmentThrowNPCFullAnimationProfile::MakeNew, 0x40, false);
}
