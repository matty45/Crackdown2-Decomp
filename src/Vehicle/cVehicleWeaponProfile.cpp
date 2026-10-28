#include "Vehicle/cVehicleWeaponProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cVehicleWeaponProfile::RetClassName() const
    {
        return "cVehicleWeaponProfile";
    }

    RWS::CAttributeHandler *cVehicleWeaponProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cVehicleWeaponProfile *p = new cVehicleWeaponProfile();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cVehicleWeaponProfileRegistrar(
        "cVehicleWeaponProfile", cVehicleWeaponProfile::MakeNew, 0x18, false);
}
