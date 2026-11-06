// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
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
