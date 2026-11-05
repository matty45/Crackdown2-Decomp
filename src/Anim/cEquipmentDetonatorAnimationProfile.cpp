#include "Anim/cEquipmentDetonatorAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cEquipmentDetonatorAnimationProfile::RetClassName() const
    {
        return "cEquipmentDetonatorAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cEquipmentDetonatorAnimationProfileRegistrar(
        "cEquipmentDetonatorAnimationProfile", cEquipmentDetonatorAnimationProfile::MakeNew, 0x40, false);
}
